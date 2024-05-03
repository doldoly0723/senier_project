#include "stdafx.h"
#include "Bullet.h"

CBulletObject::CBulletObject(float fEffectiveRange)
{
	m_fBulletEffectiveRange = fEffectiveRange;
}

CBulletObject::CBulletObject(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, CLoadedModelInfo* pModel, int nAnimationTracks)
{
	CLoadedModelInfo* pBulletModel = pModel;
	if (!pBulletModel) pBulletModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/Cube.bin", NULL);

	//if (pBulletModel->m_pModelRootObject->m_ppMaterials[0])
	//{
	//	//pBulletModel->m_pModelRootObject->m_ppMaterials[0]->m_xmf4AlbedoColor = XMFLOAT4(1, 1, 1, 1);
	//	pBulletModel->m_pModelRootObject->m_ppMaterials[0]->m_xmf4EmissiveColor = XMFLOAT4(1, 1, 1, 1);
	//	pBulletModel->m_pModelRootObject->m_ppMaterials[0]->m_xmf4AmbientColor = XMFLOAT4(1, 1, 1, 1);
	//	pBulletModel->m_pModelRootObject->m_ppMaterials[0]->m_xmf4SpecularColor = XMFLOAT4(1, 1, 1, 1);
	//}

	SetChild(pBulletModel->m_pModelRootObject, true);
	m_pSkinnedAnimationController = new CAnimationController(pd3dDevice, pd3dCommandList, nAnimationTracks, pBulletModel);
}

void CBulletObject::Animate(float fElapsedTime)
{
	m_fElapsedTimeAfterFire += fElapsedTime;

	float fDistance = m_fMovingSpeed * fElapsedTime;

	if ((m_fElapsedTimeAfterFire > m_fLockingDelayTime))
	{
		m_xmf3Position.x = m_xmf4x4ToParent._41;
		m_xmf3Position.y = m_xmf4x4ToParent._42;
		m_xmf3Position.z = m_xmf4x4ToParent._43;

	}
	m_xmf3Position.x = m_xmf4x4ToParent._41;
	m_xmf3Position.y = m_xmf4x4ToParent._42;
	m_xmf3Position.z = m_xmf4x4ToParent._43;

	m_fMovingDistance += fDistance;
	//std::cout << "fElapsedTime : " << fElapsedTime << std::endl;
	//std::cout << "fDistance : " << fDistance << " m_fMovingDistance : " << m_fMovingDistance << std::endl;

	// 여기서 무조건 전진하고 있음
	// Move(DIR_FORWARD, fDistance);
	Move(m_xmf3MovingDirection, fDistance);

	//cout << "Ani X : " << GetPosition().x << '\t';
	//cout << "Ani Y : " << GetPosition().y << '\t';
	//cout << "Ani Z : " << GetPosition().z << endl;

	CGameObject::Animate(fElapsedTime);

	if ((m_fMovingDistance > m_fBulletEffectiveRange) || (m_fElapsedTimeAfterFire > m_fLockingTime)) Reset();
}

void CBulletObject::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	//if (m_pMesh)
//{
//	// 총알 객체의 월드 행렬 업데이트
//	UpdateShaderVariable(pd3dCommandList, &m_xmf4x4World);

//	// 총알 객체의 머티리얼 렌더링
//	if (m_nMaterials > 0)
//	{
//		for (int i = 0; i < m_nMaterials; i++)
//		{
//			if (m_ppMaterials[i])
//			{
//				if (m_ppMaterials[i]->m_pShader) m_ppMaterials[i]->m_pShader->Render(pd3dCommandList, pCamera);
//				m_ppMaterials[i]->UpdateShaderVariable(pd3dCommandList);
//			}

//			m_pMesh->Render(pd3dCommandList, i);
//		}
//	}
//}

//// 형제 객체와 자식 객체의 렌더링 호출
//if (m_pSibling) m_pSibling->Render(pd3dCommandList, pCamera);
//if (m_pChild) m_pChild->Render(pd3dCommandList, pCamera);
	CGameObject::Render(pd3dCommandList, pCamera);
}

void CBulletObject::Move(DWORD dwDirection, float fDistance)
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

		Move(xmf3Shift);
	}
}

void CBulletObject::Move(XMFLOAT3& vDirection, float fSpeed)
{
	SetPosition(m_xmf4x4World._41 + vDirection.x * fSpeed, m_xmf4x4World._42 + vDirection.y * fSpeed, m_xmf4x4World._43 + vDirection.z * fSpeed);
}

void CBulletObject::Move(const XMFLOAT3& xmf3Shift)
{
	m_xmf3Position = Vector3::Add(m_xmf3Position, xmf3Shift);
	SetPosition(m_xmf3Position);
}

void CBulletObject::Reset()
{
	Rotate(-m_fPitch, -m_fYaw, -m_fRoll);
	m_fPitch = 0; m_fYaw = 0; m_fRoll = 0;
	m_pLockedObject = NULL;
	m_fElapsedTimeAfterFire = 0;
	m_fMovingDistance = 0;
	m_fRotationAngle = 0.0f;

	m_bActive = false;
}

void CBulletObject::ReflectBullet(const XMFLOAT3& surfaceNormal)
{
	// surfaceNormal은 충돌한 객체의 표면 법선입니다.

	// 총알의 방향을 반사시킵니다.
	// 방향 벡터를 surfaceNormal에 대한 반사로 갱신합니다.
	XMVECTOR incidentDirection = XMLoadFloat3(&m_xmf3MovingDirection);
	XMVECTOR normal = XMLoadFloat3(&surfaceNormal);

	// 반사 벡터 계산
	XMVECTOR reflectedDirection = XMVector3Reflect(incidentDirection, normal);

	// Rotate(10.0f, 10.0f, 0.0f);
	// 반사 벡터를 총알의 방향으로 설정
	XMStoreFloat3(&m_xmf3MovingDirection, reflectedDirection);
}
