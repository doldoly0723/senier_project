#pragma once
#include "Object.h"
#include "Camera.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CBulletObject : public CGameObject
{
public:
	CBulletObject(float fEffectiveRange);
	CBulletObject(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, CLoadedModelInfo* pModel, int nAnimationTracks);

	virtual ~CBulletObject() {};
public:
	virtual void Animate(float fElapsedTime);
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);


	float						m_fBulletEffectiveRange = 600.0f;
	float						m_fMovingDistance = 0.0f;
	float						m_fRotationAngle = 0.0f;
	XMFLOAT3					m_xmf3FirePosition = XMFLOAT3(0.0f, 0.0f, 1.0f);

	float						m_fElapsedTimeAfterFire = 0.0f;
	float						m_fLockingDelayTime = 0.3f;
	float						m_fLockingTime = 4.0f;
	CGameObject* m_pLockedObject = NULL;

	XMFLOAT4X4						m_xmf4x4Transform;


	XMFLOAT3					m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3					m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);
	XMFLOAT3					m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3					m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);

	bool						is_fire = false;
	bool						is_enemy_fire = false;
	float						m_fRotationSpeed = 0.0f;

	float m_fPitch, m_fYaw, m_fRoll;

	void SetRotationAxis(XMFLOAT3& xmf3RotationAxis) { m_xmf3RotationAxis = Vector3::Normalize(xmf3RotationAxis); }
	void SetRotationSpeed(float fSpeed) { m_fRotationSpeed = fSpeed; }
	void SetMovingSpeed(float fSpeed) { m_fMovingSpeed = fSpeed; }
	void SetMovingDirection(XMFLOAT3& xmf3MovingDirection) { m_xmf3MovingDirection = Vector3::Normalize(xmf3MovingDirection); }
	XMFLOAT3 GetDirection() { return m_xmf3MovingDirection; }

	void SetFirePosition(XMFLOAT3 xmf3FirePosition) {
		m_xmf3FirePosition = xmf3FirePosition; SetPosition(xmf3FirePosition);
		m_xmf4x4ToParent._41 = m_xmf3FirePosition.x;
		m_xmf4x4ToParent._42 = m_xmf3FirePosition.y;
		m_xmf4x4ToParent._43 = m_xmf3FirePosition.z;
	};

	void Move(DWORD dwDirection, float fDistance);
	void Move(const XMFLOAT3& xmf3Shift);
	void Move(XMFLOAT3& vDirection, float fSpeed);
	void Reset();

	void ReflectBullet(const XMFLOAT3& surfaceNormal);

};