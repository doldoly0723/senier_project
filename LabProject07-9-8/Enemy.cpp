//-----------------------------------------------------------------------------
// File: CEnemy.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Enemy.h"
#include "Shader.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CEnemy

CEnemy::CEnemy()
{
	m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);

	m_xmf3Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_xmf3Gravity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_fMaxVelocityXZ = 0.0f;
	m_fMaxVelocityY = 0.0f;
	m_fFriction = 0.0f;

	m_fPitch = 0.0f;
	m_fRoll = 0.0f;
	m_fYaw = 0.0f;

	m_pEnemyUpdatedContext = NULL;

	// state 수정 필요
	m_pStateMachine = new StateMachine<CEnemy>(this);
}

CEnemy::~CEnemy()
{
	// ??
	//ReleaseShaderVariables();
}

void CEnemy::Move(DWORD dwDirection, float fDistance, bool bUpdateVelocity)
{
	if (dwDirection)
	{
		XMFLOAT3 xmf3Shift = XMFLOAT3(0, 0, 0);
		if (dwDirection & DIR_FORWARD) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Look, fDistance);
		if (dwDirection & DIR_BACKWARD) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Look, -fDistance);
		if (dwDirection & DIR_RIGHT) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Right, fDistance);
		if (dwDirection & DIR_LEFT) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Right, -fDistance);
		if (dwDirection & DIR_UP) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Up, fDistance);
		if (dwDirection & DIR_DOWN) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Up, -fDistance);

		Move(xmf3Shift, bUpdateVelocity);
	}
}

void CEnemy::Move(const XMFLOAT3& xmf3Shift, bool bUpdateVelocity)
{

	if (bUpdateVelocity)
	{
		m_xmf3Velocity = Vector3::Add(m_xmf3Velocity, xmf3Shift);
	}
	else
	{
		m_xmf3Position = Vector3::Add(m_xmf3Position, xmf3Shift);
	}
}

void CEnemy::Rotate(float x, float y, float z)
{


	if (x != 0.0f)
	{
		m_fPitch += x;
		if (m_fPitch > +89.0f) { x -= (m_fPitch - 89.0f); m_fPitch = +89.0f; }
		if (m_fPitch < -89.0f) { x -= (m_fPitch + 89.0f); m_fPitch = -89.0f; }
	}
	if (y != 0.0f)
	{
		m_fYaw += y;
		if (m_fYaw > 360.0f) m_fYaw -= 360.0f;
		if (m_fYaw < 0.0f) m_fYaw += 360.0f;
	}
	if (z != 0.0f)
	{
		m_fRoll += z;
		if (m_fRoll > +20.0f) { z -= (m_fRoll - 20.0f); m_fRoll = +20.0f; }
		if (m_fRoll < -20.0f) { z -= (m_fRoll + 20.0f); m_fRoll = -20.0f; }
	}
	if (y != 0.0f)
	{
		XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Up), XMConvertToRadians(y));
		m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, xmmtxRotate);
		m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, xmmtxRotate);
	}


	m_xmf3Look = Vector3::Normalize(m_xmf3Look);
	m_xmf3Right = Vector3::CrossProduct(m_xmf3Up, m_xmf3Look, true);
	m_xmf3Up = Vector3::CrossProduct(m_xmf3Look, m_xmf3Right, true);
}

void CEnemy::Update(float fTimeElapsed)
{
	m_xmf3Velocity = Vector3::Add(m_xmf3Velocity, m_xmf3Gravity);
	float fLength = sqrtf(m_xmf3Velocity.x * m_xmf3Velocity.x + m_xmf3Velocity.z * m_xmf3Velocity.z);
	float fMaxVelocityXZ = m_fMaxVelocityXZ;
	if (fLength > m_fMaxVelocityXZ)
	{
		m_xmf3Velocity.x *= (fMaxVelocityXZ / fLength);
		m_xmf3Velocity.z *= (fMaxVelocityXZ / fLength);
	}
	float fMaxVelocityY = m_fMaxVelocityY;
	fLength = sqrtf(m_xmf3Velocity.y * m_xmf3Velocity.y);
	if (fLength > m_fMaxVelocityY) m_xmf3Velocity.y *= (fMaxVelocityY / fLength);

	XMFLOAT3 xmf3Velocity = Vector3::ScalarProduct(m_xmf3Velocity, fTimeElapsed, false);
	Move(xmf3Velocity, false);

	if (m_pEnemyUpdatedContext) OnEnemyUpdateCallback(fTimeElapsed);

	fLength = Vector3::Length(m_xmf3Velocity);
	float fDeceleration = (m_fFriction * fTimeElapsed);
	if (fDeceleration > fLength) fDeceleration = fLength;
	m_xmf3Velocity = Vector3::Add(m_xmf3Velocity, Vector3::ScalarProduct(m_xmf3Velocity, -fDeceleration, true));
}

CTerrainEnemy::CTerrainEnemy(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, void* pContext)
{
	CLoadedModelInfo* pAngrybotModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/Player.bin", NULL);
	SetChild(pAngrybotModel->m_pModelRootObject, true);
	int standAnimationTrack = 11;
	m_pSkinnedAnimationController = new CAnimationController(pd3dDevice, pd3dCommandList, standAnimationTrack, pAngrybotModel);

	for (int i = 0; i < standAnimationTrack; i++)
	{
		m_pSkinnedAnimationController->SetTrackAnimationSet(i, i);
		m_pSkinnedAnimationController->SetTrackEnable(i, false);
	}
	m_pSkinnedAnimationController->SetTrackEnable(0, true);


	//m_pSkinnedAnimationController->SetTrackAnimationSet(0, 0);
	//m_pSkinnedAnimationController->SetTrackAnimationSet(1, 1);
	//m_pSkinnedAnimationController->SetTrackAnimationSet(2, 2);
	//m_pSkinnedAnimationController->SetTrackEnable(1, false);
	//m_pSkinnedAnimationController->SetTrackEnable(2, false);

	m_pSkinnedAnimationController->SetCallbackKeys(1, 2);				// 1번 애니메이션 소리를 위한 설정
#ifdef _WITH_SOUND_RESOURCE
	m_pSkinnedAnimationController->SetCallbackKey(0, 0.1f, _T("Footstep01"));
	m_pSkinnedAnimationController->SetCallbackKey(1, 0.5f, _T("Footstep02"));
	m_pSkinnedAnimationController->SetCallbackKey(2, 0.9f, _T("Footstep03"));
#else
	//m_pSkinnedAnimationController->SetCallbackKey(1, 0, 0.2f, _T("Sound/Footstep01.wav"));
	//m_pSkinnedAnimationController->SetCallbackKey(1, 1, 0.5f, _T("Sound/Footstep02.wav"));
//	m_pSkinnedAnimationController->SetCallbackKey(1, 2, 0.39f, _T("Sound/Footstep03.wav"));
#endif
	//CAnimationCallbackHandler* pAnimationCallbackHandler = new CSoundCallbackHandler();
	//m_pSkinnedAnimationController->SetAnimationCallbackHandler(1, pAnimationCallbackHandler);

	CGameObject::SetBoundingBox(pAngrybotModel->m_pModelRootObject->m_xmOOBB, pAngrybotModel->m_pModelRootObject);

	for (int i = 0; i < ENEMY_MAX_BULLETS; i++)
	{
		CLoadedModelInfo* pBulletMesh = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/Bullet.bin", NULL);

		m_ppBullets[i] = new CBulletObject(m_fBulletEffectiveRange);
		m_ppBullets[i]->SetScale(10.0f, 10.0f, 10.5f);
		m_ppBullets[i]->SetChild(pBulletMesh->m_pModelRootObject, true);
		m_ppBullets[i]->SetMovingSpeed(100.0f);
		m_ppBullets[i]->SetActive(false);

		// 흠..
		m_ppBullets[i]->m_pSkinnedAnimationController = new CAnimationController(pd3dDevice, pd3dCommandList, 1, pBulletMesh);
		m_ppBullets[i]->m_pSkinnedAnimationController->SetTrackAnimationSet(0, 0);
		m_ppBullets[i]->m_pSkinnedAnimationController->SetCallbackKeys(0, 1);

	}

	std::cout << "총알 생성 완료" << std::endl;

	CreateShaderVariables(pd3dDevice, pd3dCommandList);

	SetEnemyUpdatedContext(pContext);

	CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)pContext;
	SetPosition(XMFLOAT3(310.0f, pTerrain->GetHeight(310.0f, 590.0f), 590.0f));
	SetScale(XMFLOAT3(10.0f, 10.0f, 10.0f));

	if (pAngrybotModel) delete pAngrybotModel;
}

CTerrainEnemy::~CTerrainEnemy()
{
}

void CTerrainEnemy::OnPlayerUpdateCallback(float fTimeElapsed)
{
	CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)m_pEnemyUpdatedContext;
	XMFLOAT3 xmf3Scale = pTerrain->GetScale();
	XMFLOAT3 xmf3EnemyPosition = GetPosition();
	int z = (int)(xmf3EnemyPosition.z / xmf3Scale.z);
	bool bReverseQuad = ((z % 2) != 0);
	float fHeight = pTerrain->GetHeight(xmf3EnemyPosition.x, xmf3EnemyPosition.z, bReverseQuad) + 0.0f;
	if (xmf3EnemyPosition.y < fHeight)
	{
		XMFLOAT3 xmf3PlayerVelocity = GetVelocity();
		xmf3PlayerVelocity.y = 0.0f;
		SetVelocity(xmf3PlayerVelocity);
		xmf3EnemyPosition.y = fHeight;
		SetPosition(xmf3EnemyPosition);
	}
}

void CTerrainEnemy::Move(DWORD dwDirection, float fDistance, bool bUpdateVelocity)
{
	if (dwDirection && !bZoom)			// 기본 이동
	{
		m_pSkinnedAnimationController->SetTrackEnable(8, false);
		m_pSkinnedAnimationController->SetTrackEnable(5, false);
		m_pSkinnedAnimationController->SetTrackEnable(0, false);

		m_pSkinnedAnimationController->SetTrackEnable(1, true);
	}

	else if (dwDirection && bZoom)		// 조준 이동
	{
		if (!bFire)
		{
			// 이동하면서 조준하는 애니메이션
			m_pSkinnedAnimationController->SetTrackEnable(1, false);
			m_pSkinnedAnimationController->SetTrackEnable(5, false);
			m_pSkinnedAnimationController->SetTrackEnable(0, false);

			m_pSkinnedAnimationController->SetTrackEnable(10, false);

			m_pSkinnedAnimationController->SetTrackEnable(8, true);
		}
		else
		{
			m_pSkinnedAnimationController->SetTrackEnable(1, false);
			m_pSkinnedAnimationController->SetTrackEnable(5, false);
			m_pSkinnedAnimationController->SetTrackEnable(0, false);

			m_pSkinnedAnimationController->SetTrackEnable(8, false);

			m_pSkinnedAnimationController->SetTrackEnable(10, true);


		}

	}

	CEnemy::Move(dwDirection, fDistance, bUpdateVelocity);
}

void CTerrainEnemy::Update(float fTimeElapsed)			// 기본 일어서 있는 상태를 여기서 처리해도 될듯?
{
	CEnemy::Update(fTimeElapsed);

	if (m_pSkinnedAnimationController)
	{
		//stand
		float fLength = sqrtf(m_xmf3Velocity.x * m_xmf3Velocity.x + m_xmf3Velocity.z * m_xmf3Velocity.z);
		if (::IsZero(fLength))
		{
			m_pSkinnedAnimationController->SetTrackEnable(0, true);
			m_pSkinnedAnimationController->SetTrackEnable(1, false);
			m_pSkinnedAnimationController->SetTrackEnable(2, false);
			m_pSkinnedAnimationController->SetTrackEnable(3, false);
			m_pSkinnedAnimationController->SetTrackEnable(4, false);

			m_pSkinnedAnimationController->SetTrackEnable(8, false);

			m_pSkinnedAnimationController->SetTrackEnable(10, false);

			m_pSkinnedAnimationController->SetTrackPosition(1, 0.0f);
		}

		//Aiming
		if (bZoom && !bMove)
		{
			if (!bFire)
			{
				//cout << "ZOOM ON" << endl;
				m_pSkinnedAnimationController->SetTrackEnable(0, false);
				m_pSkinnedAnimationController->SetTrackEnable(1, false);
				m_pSkinnedAnimationController->SetTrackEnable(2, false);
				m_pSkinnedAnimationController->SetTrackEnable(3, false);
				m_pSkinnedAnimationController->SetTrackEnable(4, false);

				m_pSkinnedAnimationController->SetTrackEnable(8, false);

				m_pSkinnedAnimationController->SetTrackEnable(10, false);

				m_pSkinnedAnimationController->SetTrackEnable(5, true);
			}
			else
			{
				m_pSkinnedAnimationController->SetTrackEnable(0, false);
				m_pSkinnedAnimationController->SetTrackEnable(1, false);
				m_pSkinnedAnimationController->SetTrackEnable(2, false);
				m_pSkinnedAnimationController->SetTrackEnable(3, false);
				m_pSkinnedAnimationController->SetTrackEnable(4, false);

				m_pSkinnedAnimationController->SetTrackEnable(5, false);
				m_pSkinnedAnimationController->SetTrackEnable(8, false);



				m_pSkinnedAnimationController->SetTrackEnable(10, true);
			}

		}
		else if (!bZoom && !bMove)
		{
			//m_pSkinnedAnimationController->SetTrackEnable(0, true);
			m_pSkinnedAnimationController->SetTrackEnable(5, false);
		}
	}
}


void CTerrainEnemy::Animate(float fTimeElapsed)
{
	if (m_pSkinnedAnimationController) m_pSkinnedAnimationController->AdvanceTime(fTimeElapsed, this);

	if (m_pSibling) m_pSibling->Animate(fTimeElapsed);
	if (m_pChild) m_pChild->Animate(fTimeElapsed);

	for (int i = 0; i < ENEMY_MAX_BULLETS; i++)
	{
		if (m_ppBullets[i]->m_bActive) {
			m_ppBullets[i]->Animate(fTimeElapsed);
		};
	}
}

void CTerrainEnemy::FireBullet()
{
	// std::cout << "발사 됨" << std::endl;
	if (m_fFireWaitingTime > 0.0f)
	{
		m_fFireWaitingTime -= 0.1f;
		return;
	}

	std::cout << m_fFireWaitingTime << std::endl;

	CBulletObject* pBulletObject = NULL;
	for (int i = 0; i < ENEMY_MAX_BULLETS; i++)
	{
		if (!m_ppBullets[i]->m_bActive)
		{
			pBulletObject = m_ppBullets[i];
			break;
		}
	}

	if (pBulletObject)
	{
		XMFLOAT3 xmf3Position = GetPosition();
		XMFLOAT3 xmf3Direction = GetLook();
		XMFLOAT3 xmf3Right = GetRight();
		XMFLOAT3 xmf3Up = GetUp();
		XMFLOAT3 xmf3FirePosition = m_xmf3Look;

		XMFLOAT3 m_xmf3Look = GetLookVector();

		pBulletObject->m_xmf3Look = m_xmf3Look;

		pBulletObject->m_xmf4x4ToParent = m_xmf4x4ToParent;
		// 발사 위치
		xmf3FirePosition.x = xmf3Position.x + 2;
		xmf3FirePosition.y = xmf3Position.y + 12.2;
		// xmf3FirePosition.y = xmf3Position.y;
		xmf3FirePosition.z = xmf3Position.z + 2.3;
		//
		pBulletObject->SetPosition(xmf3FirePosition);
		pBulletObject->SetMovingDirection(xmf3Direction);
		pBulletObject->SetActive(true);
		pBulletObject->SetScale(0.1f, 0.1f, 0.05f);

		m_fFireWaitingTime = m_fFireDelayTime * 1.0f;
	}
}
void CTerrainEnemy::Aiming(bool bEnable)
{
	//여기서 충돌 발생
	if (bEnable)
	{
		m_pSkinnedAnimationController->SetTrackEnable(0, false);
		m_pSkinnedAnimationController->SetTrackEnable(5, true);
	}
	else if (!bEnable)
	{
		//m_pSkinnedAnimationController->SetTrackEnable(0, true);
		m_pSkinnedAnimationController->SetTrackEnable(5, false);
	}
}


