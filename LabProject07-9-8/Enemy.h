#pragma once

#include "Object.h"
#include "Bullet.h"
#include "StateMachine.h"

#define ENEMY_MAX_BULLETS 10

class CEnemy : public CGameObject
{
protected:
	XMFLOAT3					m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3					m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3					m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMFLOAT3					m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);

	XMFLOAT3					m_xmf3Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	float           			m_fPitch = 0.0f;
	float           			m_fYaw = 0.0f;
	float           			m_fRoll = 0.0f;

	XMFLOAT3					m_xmf3Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3     				m_xmf3Gravity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	float           			m_fMaxVelocityXZ = 0.0f;
	float           			m_fMaxVelocityY = 0.0f;
	float           			m_fFriction = 0.0f;

	LPVOID						m_pEnemyUpdatedContext = NULL;

	// fire
	float						m_fFireDelayTime = 0.5f;
	float						m_fFireWaitingTime;

	bool						bZoom = FALSE;
	bool						bMove = FALSE;
	bool						bFire = FALSE;

	// state
	BoundingSphere				m_detectSphere;

	StateMachine<CEnemy>*		m_pStateMachine;

	bool						m_IsFindPlayer = false;

public:
	CEnemy();
	virtual ~CEnemy();

	XMFLOAT3 GetPosition() { return(m_xmf3Position); }
	XMFLOAT3 GetLookVector() { return(m_xmf3Look); }
	XMFLOAT3 GetUpVector() { return(m_xmf3Up); }
	XMFLOAT3 GetRightVector() { return(m_xmf3Right); }

	void SetFriction(float fFriction) { m_fFriction = fFriction; }
	void SetGravity(const XMFLOAT3& xmf3Gravity) { m_xmf3Gravity = xmf3Gravity; }
	void SetMaxVelocityXZ(float fMaxVelocity) { m_fMaxVelocityXZ = fMaxVelocity; }
	void SetMaxVelocityY(float fMaxVelocity) { m_fMaxVelocityY = fMaxVelocity; }
	void SetVelocity(const XMFLOAT3& xmf3Velocity) { m_xmf3Velocity = xmf3Velocity; }
	void SetPosition(const XMFLOAT3& xmf3Position) { Move(XMFLOAT3(xmf3Position.x - m_xmf3Position.x, xmf3Position.y - m_xmf3Position.y, xmf3Position.z - m_xmf3Position.z), false); }

	void SetScale(XMFLOAT3& xmf3Scale) { m_xmf3Scale = xmf3Scale; }

	const XMFLOAT3& GetVelocity() const { return(m_xmf3Velocity); }
	float GetYaw() const { return(m_fYaw); }
	float GetPitch() const { return(m_fPitch); }
	float GetRoll() const { return(m_fRoll); }

	virtual void Move(ULONG nDirection, float fDistance, bool bVelocity = false);
	void Move(const XMFLOAT3& xmf3Shift, bool bVelocity = false);
	void Move(float fxOffset = 0.0f, float fyOffset = 0.0f, float fzOffset = 0.0f);
	void Rotate(float x, float y, float z);

	virtual void Update(float fTimeElapsed);

	virtual void OnEnemyUpdateCallback(float fTimeElapsed) { }
	void SetEnemyUpdatedContext(LPVOID pContext) { m_pEnemyUpdatedContext = pContext; }


	//
	CGameObject** m_BulletObjects = NULL;
	CBulletObject* m_ppBullets[ENEMY_MAX_BULLETS];

	void SetMovingDirection(XMFLOAT3& xmf3MovingDirection) { m_xmf3MovingDirection = Vector3::Normalize(xmf3MovingDirection); }
	// 연속적인 총알 발사를 위해 추가
	bool bLeftMouseButtonDown = false;

	void SetZoom(bool bEnable) { bZoom = bEnable; }
	void SetMove(bool bEnable) { bMove = bEnable; }
	void SetFire(bool bEnable) { bFire = bEnable; }

	virtual void Aiming(bool bEnable) {}
};

class CTerrainEnemy : public CEnemy
{
public:
	CTerrainEnemy(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, void* pContext = NULL);
	virtual ~CTerrainEnemy();

public:
	virtual void OnPlayerUpdateCallback(float fTimeElapsed);

	virtual void Move(ULONG nDirection, float fDistance, bool bVelocity = false);

	virtual void Update(float fTimeElapsed);


	// 
	// void UpdateTransform(XMFLOAT4X4* pxmf4x4Parent = NULL);
	void Animate(float fTimeElapsed);
	// void ReleaseUploadBuffers();


	void FireBullet();
	float						m_fBulletEffectiveRange = 300.0f;

	virtual void Aiming(bool bzoom);


};