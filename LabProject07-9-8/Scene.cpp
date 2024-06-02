//-----------------------------------------------------------------------------
// File: CScene.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Scene.h"

ID3D12DescriptorHeap *CScene::m_pd3dCbvSrvDescriptorHeap = NULL;

D3D12_CPU_DESCRIPTOR_HANDLE	CScene::m_d3dCbvCPUDescriptorStartHandle;
D3D12_GPU_DESCRIPTOR_HANDLE	CScene::m_d3dCbvGPUDescriptorStartHandle;
D3D12_CPU_DESCRIPTOR_HANDLE	CScene::m_d3dSrvCPUDescriptorStartHandle;
D3D12_GPU_DESCRIPTOR_HANDLE	CScene::m_d3dSrvGPUDescriptorStartHandle;

D3D12_CPU_DESCRIPTOR_HANDLE	CScene::m_d3dCbvCPUDescriptorNextHandle;
D3D12_GPU_DESCRIPTOR_HANDLE	CScene::m_d3dCbvGPUDescriptorNextHandle;
D3D12_CPU_DESCRIPTOR_HANDLE	CScene::m_d3dSrvCPUDescriptorNextHandle;
D3D12_GPU_DESCRIPTOR_HANDLE	CScene::m_d3dSrvGPUDescriptorNextHandle;

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::BuildDefaultLightsAndMaterials()
{
	m_nLights = 5;
	m_pLights = new LIGHT[m_nLights];
	::ZeroMemory(m_pLights, sizeof(LIGHT) * m_nLights);

	m_xmf4GlobalAmbient = XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f);

	m_pLights[0].m_bEnable = true;
	m_pLights[0].m_nType = POINT_LIGHT;
	m_pLights[0].m_fRange = 300.0f;
	m_pLights[0].m_xmf4Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_pLights[0].m_xmf4Diffuse = XMFLOAT4(0.4f, 0.3f, 0.8f, 1.0f);
	m_pLights[0].m_xmf4Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 0.0f);
	m_pLights[0].m_xmf3Position = XMFLOAT3(230.0f, 330.0f, 480.0f);
	m_pLights[0].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);
	m_pLights[1].m_bEnable = true;
	m_pLights[1].m_nType = SPOT_LIGHT;
	m_pLights[1].m_fRange = 500.0f;
	m_pLights[1].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights[1].m_xmf4Diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	m_pLights[1].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[1].m_xmf3Position = XMFLOAT3(-50.0f, 20.0f, -5.0f);
	m_pLights[1].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 1.0f);
	m_pLights[1].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights[1].m_fFalloff = 8.0f;
	m_pLights[1].m_fPhi = (float)cos(XMConvertToRadians(40.0f));
	m_pLights[1].m_fTheta = (float)cos(XMConvertToRadians(20.0f));
	m_pLights[2].m_bEnable = true;
	m_pLights[2].m_nType = DIRECTIONAL_LIGHT;
	m_pLights[2].m_xmf4Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[2].m_xmf4Diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	m_pLights[2].m_xmf4Specular = XMFLOAT4(0.4f, 0.4f, 0.4f, 0.0f);
	m_pLights[2].m_xmf3Direction = XMFLOAT3(1.0f, -1.0f, 0.0f);
	m_pLights[3].m_bEnable = true;
	m_pLights[3].m_nType = SPOT_LIGHT;
	m_pLights[3].m_fRange = 600.0f;
	m_pLights[3].m_xmf4Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	m_pLights[3].m_xmf4Diffuse = XMFLOAT4(0.3f, 0.7f, 0.0f, 1.0f);
	m_pLights[3].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[3].m_xmf3Position = XMFLOAT3(550.0f, 330.0f, 530.0f);
	m_pLights[3].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 1.0f);
	m_pLights[3].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights[3].m_fFalloff = 8.0f;
	m_pLights[3].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	m_pLights[3].m_fTheta = (float)cos(XMConvertToRadians(30.0f));
	m_pLights[4].m_bEnable = true;
	m_pLights[4].m_nType = POINT_LIGHT;
	m_pLights[4].m_fRange = 200.0f;
	m_pLights[4].m_xmf4Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	m_pLights[4].m_xmf4Diffuse = XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f);
	m_pLights[4].m_xmf4Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 0.0f);
	m_pLights[4].m_xmf3Position = XMFLOAT3(600.0f, 250.0f, 700.0f);
	m_pLights[4].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);
}

void CScene::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);

	CreateCbvSrvDescriptorHeaps(pd3dDevice, 0, 76 + 30); //SuperCobra(17), Gunship(2), Player:Mi24(1), Angrybot() + ÃÑ¾Ë 30?

	CMaterial::PrepareShaders(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);

	BuildDefaultLightsAndMaterials();

	m_pSkyBox = new CSkyBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);
	m_pUI = new CUI(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);

	XMFLOAT3 xmf3Scale(8.0f, 0.0f, 8.0f);
	//XMFLOAT4 xmf4Color(0.0f, 0.0f, 0.0f, 0.0f);
	XMFLOAT4 xmf4Color = XMFLOAT4(0.7608f, 0.6980f, 0.5020f, 0.0f);
	m_pTerrain = new CHeightMapTerrain(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, _T("Terrain/HeightMap.raw"), 513, 513, xmf3Scale, xmf4Color);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// loadscenefromfile 이 벡터를 리턴하여 벡터 안에는 게임 오브젝트? 로드모델인포       들이 들어가도록

	// CGameObject
	// gameScene가 std::vector<CLoadedModelInfo*> 형태의 게임모델 로드 정보를 리턴
	// 리턴받은 벡터에서 하나씩 꺼내 게임오브젝트에 연결
	// 
	// 
	// 벡터에서 하나씩 꺼내 게임 오브젝트벡터에 연결 
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//m_nHierarchicalGameObjects = 10;
	//m_ppHierarchicalGameObjects = new CGameObject * [m_nHierarchicalGameObjects];


	//CLoadedModelInfo* pEthanModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/NPC.bin", NULL);
	//m_ppHierarchicalGameObjects[0] = new CEnemyNPC(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, pEthanModel, 4);
	//CGameObject* pEthanNPC = new CEnemyNPC(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, pEthanModel, 4);
	//
	///*for (int i = 0; i < 4; i++)
	//{
	//	m_ppHierarchicalGameObjects[0]->m_pSkinnedAnimationController->SetTrackAnimationSet(i, i);
	//	m_ppHierarchicalGameObjects[0]->m_pSkinnedAnimationController->SetTrackEnable(i, false);
	//}
	//m_ppHierarchicalGameObjects[0]->m_pSkinnedAnimationController->SetTrackEnable(0, true);*/
	//
	//m_ppHierarchicalGameObjects[0]->SetPosition(1610.0f, m_pTerrain->GetHeight(430.0f, 700.0f), 1875.0f);
	//m_ppHierarchicalGameObjects[0]->Rotate(0.0f, 225.0f, 0.0f);
	//m_ppHierarchicalGameObjects[0]->SetScale(10.0f, 10.0f, 10.0f);
	//m_ppHierarchicalGameObjects[0]->SetBoundingBox(m_ppHierarchicalGameObjects[0]->m_xmOOBB, m_ppHierarchicalGameObjects[0]);

	//m_ppHierarchicalGameObjects[0]->ScaleBoundingBox(5.0f, 20.0f, 5.0f);
	//m_ppHierarchicalGameObjects[0]->RotateBoundingBox(0.0f, XMConvertToRadians(225.0f), 0.0f);
	//m_ppHierarchicalGameObjects[0]->nonConflicting = true;
	//m_ppHierarchicalGameObjects[0]->isNPC = true;
	//m_pBoundingBox[0] = new CBoundingBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, m_ppHierarchicalGameObjects[0]->m_xmOOBB);

	//// m_lpGameObjects.push_back(m_ppHierarchicalGameObjects[0]);
	//if (pEthanModel) delete pEthanModel;



	CLoadedModelInfo* pboxModel1 = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/box3.bin", NULL);
	CGameObject* pboxObject1 = new CLionObject(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, pboxModel1, 1);
	//m_ppHierarchicalGameObjects[1]->m_pSkinnedAnimationController->SetTrackAnimationSet(0, 1);
	pboxObject1->SetPosition(1230.0f, m_pTerrain->GetHeight(430.0f, 700.0f), 1630.0f);
	pboxObject1->SetScale(50.0f, 30.0f, 50.0f);
	pboxObject1->SetBoundingBox(pboxObject1->m_xmOOBB, pboxObject1);
	pboxObject1->ScaleBoundingBox(10.0f, 10.0f, 10.0f);
	CBoundingBox* pboundingBox = new CBoundingBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, pboxObject1->m_xmOOBB);
	m_vBoundingBox.push_back(pboundingBox);

	//m_pBoundingBox[1] = new CBoundingBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, pboxObject1->m_xmOOBB);
	// m_lpGameObjects.push_back(m_ppHierarchicalGameObjects[1]);
	
	if (pboxModel1) delete pboxModel1;
	//if (pboxObject1) delete pboxObject1;

	m_vGameObjects.push_back(pboxObject1);


	///////////////////////////////////////////////
	// 현재 씬을 로드하면 바운딩 박스가 씬의 중심에만 생성된다
	// 각각의 물체에 따른 바운딩 박스가 생성되지 않음
	std::vector<CLoadedModelInfo*> pScenes = CGameObject::LoadSceneFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/GameScene.bin", NULL);
	for (auto pLoadedModel : pScenes) {
		CGameObject* pObj = new CLionObject(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, pLoadedModel, 1);
		pObj->SetPosition(1330.0f, m_pTerrain->GetHeight(430.0f, 700.0f), 1630.0f);
		pObj->SetScale(50.0f, 30.0f, 50.0f);
		pObj->SetBoundingBox(pObj->m_xmOOBB, pObj);
		pObj->ScaleBoundingBox(10.0f, 10.0f, 10.0f);
		
		CBoundingBox* pbBox = new CBoundingBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, pObj->m_xmOOBB);
		m_vBoundingBox.push_back(pbBox);
		// 여기에서 각 pLoadedModel에 대한 처리를 할 수 있습니다.
		// 예를 들어 모델의 정보를 출력하거나, 초기화 과정을 진행할 수 있습니다.

		// 필요한 경우 각 모델을 게임 환경에 추가하는 로직을 구현합니다.
		// 예: 게임 환경에 모델 추가, 렌더링 준비 등
		m_vGameObjects.push_back(pObj);
	}
	
	//CLoadedModelInfo* pbox = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/box3.bin", NULL);
	//m_ppHierarchicalGameObjects[2] = new CSwatMan(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, pbox, 1);
	////m_ppHierarchicalGameObjects[2]->m_pSkinnedAnimationController->SetTrackAnimationSet(0, 1);

	//m_ppHierarchicalGameObjects[2]->SetPosition(1200.0f, m_pTerrain->GetHeight(430.0f, 700.0f), 1650.0f);
	//m_ppHierarchicalGameObjects[2]->SetScale(50.0f, 30.0f, 50.0f);
	//m_ppHierarchicalGameObjects[2]->SetBoundingBox(m_ppHierarchicalGameObjects[2]->m_xmOOBB, m_ppHierarchicalGameObjects[2]);
	// m_ppHierarchicalGameObjects[2]->ScaleBoundingBox(10.0f, 20.0f, 10.0f);
	//m_pBoundingBox[2] = new CBoundingBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, m_ppHierarchicalGameObjects[2]->m_xmOOBB);
	//// m_lpGameObjects.push_back(m_ppHierarchicalGameObjects[2]);
	//if (pbox) delete pbox;

	////CLoadedModelInfo* pbox1 = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/GameScene.bin", NULL);
	////m_ppHierarchicalGameObjects[3] = new CSwatMan(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, pbox1, 1);
	//////m_ppHierarchicalGameObjects[2]->m_pSkinnedAnimationController->SetTrackAnimationSet(0, 1);
	////m_ppHierarchicalGameObjects[3]->SetPosition(350.0f, m_pTerrain->GetHeight(430.0f, 700.0f), 650.0f);
	////m_ppHierarchicalGameObjects[3]->SetScale(10.0f, 10.0f, 10.0f);
	////m_ppHierarchicalGameObjects[3]->SetBoundingBox(m_ppHierarchicalGameObjects[3]->m_xmOOBB, m_ppHierarchicalGameObjects[3]);
	//////m_ppHierarchicalGameObjects[3]->ScaleBoundingBox(30.0f, 30.0f, 30.0f);
	////m_pBoundingBox[3] = new CBoundingBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, m_ppHierarchicalGameObjects[3]->m_xmOOBB);
	////// m_lpGameObjects.push_back(m_ppHierarchicalGameObjects[2]);
	////if (pbox1) delete pbox1;

	//// 길이가 300 정도 된다
	//CLoadedModelInfo* wall1 = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/Plastered_Wall.bin", NULL);
	//m_ppHierarchicalGameObjects[3] = new CSwatMan(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, wall1, 1);
	////m_ppHierarchicalGameObjects[2]->m_pSkinnedAnimationController->SetTrackAnimationSet(0, 1);
	//m_ppHierarchicalGameObjects[3]->SetPosition(1350.0f, m_pTerrain->GetHeight(430.0f, 700.0f), 1750.0f);
	//m_ppHierarchicalGameObjects[3]->SetScale(10.0f, 10.0f, 10.0f);
	//m_ppHierarchicalGameObjects[3]->SetBoundingBox(m_ppHierarchicalGameObjects[3]->m_xmOOBB, m_ppHierarchicalGameObjects[3]);
	//m_ppHierarchicalGameObjects[3]->ScaleBoundingBox(10.0f, 20.0f, 180.0f);
	//m_pBoundingBox[3] = new CBoundingBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, m_ppHierarchicalGameObjects[3]->m_xmOOBB);
	//// m_lpGameObjects.push_back(m_ppHierarchicalGameObjects[2]);
	//if (wall1) delete wall1;

	//CLoadedModelInfo* wall2 = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/Plastered_Wall.bin", NULL);
	//m_ppHierarchicalGameObjects[4] = new CSwatMan(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, wall2, 1);
	//m_ppHierarchicalGameObjects[4]->SetPosition(1520.0f, m_pTerrain->GetHeight(430.0f, 700.0f), 1920.0f);
	//m_ppHierarchicalGameObjects[4]->Rotate(0.0f, 90.0f, 0.0f);
	//m_ppHierarchicalGameObjects[4]->SetScale(10.0f, 10.0f, 10.0f);
	//m_ppHierarchicalGameObjects[4]->SetBoundingBox(m_ppHierarchicalGameObjects[4]->m_xmOOBB, m_ppHierarchicalGameObjects[4]);
	//m_ppHierarchicalGameObjects[4]->ScaleBoundingBox(180.0f, 20.0f, 10.0f);
	//m_pBoundingBox[4] = new CBoundingBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, m_ppHierarchicalGameObjects[4]->m_xmOOBB);
	//// m_lpGameObjects.push_back(m_ppHierarchicalGameObjects[2]);
	//if (wall2) delete wall2;

	//CLoadedModelInfo* wall3 = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/Plastered_Wall.bin", NULL);
	//m_ppHierarchicalGameObjects[5] = new CSwatMan(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, wall3, 1);
	//m_ppHierarchicalGameObjects[5]->SetPosition(1670.0f, m_pTerrain->GetHeight(430.0f, 700.0f), 1750.0f);
	////m_ppHierarchicalGameObjects[5]->Rotate(0.0f, 90.0f, 0.0f);
	//m_ppHierarchicalGameObjects[5]->SetScale(10.0f, 10.0f, 10.0f);
	//m_ppHierarchicalGameObjects[5]->SetBoundingBox(m_ppHierarchicalGameObjects[5]->m_xmOOBB, m_ppHierarchicalGameObjects[5]);
	//m_ppHierarchicalGameObjects[5]->ScaleBoundingBox(10.0f, 20.0f, 180.0f);
	//m_pBoundingBox[5] = new CBoundingBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, m_ppHierarchicalGameObjects[5]->m_xmOOBB);
	//// m_lpGameObjects.push_back(m_ppHierarchicalGameObjects[2]);
	//if (wall3) delete wall3;


	//CLoadedModelInfo* container1 = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/container.bin", NULL);
	//m_ppHierarchicalGameObjects[6] = new CSwatMan(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, container1, 1);
	//m_ppHierarchicalGameObjects[6]->SetPosition(1450.0f, m_pTerrain->GetHeight(430.0f, 700.0f), 1800.0f);
	//m_ppHierarchicalGameObjects[6]->Rotate(0.0f, 60.0f, 0.0f);
	//m_ppHierarchicalGameObjects[6]->SetScale(10.0f, 10.0f, 10.0f);
	//m_ppHierarchicalGameObjects[6]->SetBoundingBox(m_ppHierarchicalGameObjects[6]->m_xmOOBB, m_ppHierarchicalGameObjects[6]);
	//m_ppHierarchicalGameObjects[6]->ScaleBoundingBox(65.0f, 20.0f, 30.0f);
	//m_ppHierarchicalGameObjects[6]->RotateBoundingBox(0.0f, XMConvertToRadians(60.0f), 0.0f);
	//m_pBoundingBox[6] = new CBoundingBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, m_ppHierarchicalGameObjects[6]->m_xmOOBB);
	//// m_lpGameObjects.push_back(m_ppHierarchicalGameObjects[2]);
	//if (container1) delete container1;

	//CLoadedModelInfo* container2 = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/container.bin", NULL);
	//m_ppHierarchicalGameObjects[7] = new CSwatMan(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, container2, 1);
	//m_ppHierarchicalGameObjects[7]->SetPosition(1600.0f, m_pTerrain->GetHeight(430.0f, 700.0f), 1700.0f);
	////m_ppHierarchicalGameObjects[5]->Rotate(0.0f, 90.0f, 0.0f);
	//m_ppHierarchicalGameObjects[7]->SetScale(10.0f, 10.0f, 10.0f);
	//m_ppHierarchicalGameObjects[7]->SetBoundingBox(m_ppHierarchicalGameObjects[7]->m_xmOOBB, m_ppHierarchicalGameObjects[7]);
	//m_ppHierarchicalGameObjects[7]->ScaleBoundingBox(65.0f, 20.0f, 30.0f);
	//m_pBoundingBox[7] = new CBoundingBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, m_ppHierarchicalGameObjects[7]->m_xmOOBB);
	//// m_lpGameObjects.push_back(m_ppHierarchicalGameObjects[2]);
	//if (container2) delete container2;

	//CLoadedModelInfo* sandbag = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/sandbag2.bin", NULL);
	//m_ppHierarchicalGameObjects[8] = new CSwatMan(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, sandbag, 1);
	//m_ppHierarchicalGameObjects[8]->SetPosition(1620.0f, m_pTerrain->GetHeight(430.0f, 700.0f), 1860.0f);
	//m_ppHierarchicalGameObjects[8]->Rotate(0.0f, 0.0f, 0.0f);
	//m_ppHierarchicalGameObjects[8]->SetScale(10.0f, 10.0f, 10.0f);
	//m_ppHierarchicalGameObjects[8]->SetBoundingBox(m_ppHierarchicalGameObjects[8]->m_xmOOBB, m_ppHierarchicalGameObjects[8]);
	//m_ppHierarchicalGameObjects[8]->ScaleBoundingBox(1.0f, 1.0f, 1.0f);
	//m_pBoundingBox[8] = new CBoundingBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, m_ppHierarchicalGameObjects[8]->m_xmOOBB);
	//// m_lpGameObjects.push_back(m_ppHierarchicalGameObjects[2]);
	//if (sandbag) delete sandbag;

	//CLoadedModelInfo* pNPCModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/NPC.bin", NULL);
	//m_ppHierarchicalGameObjects[9] = new CEnemyNPC(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, pNPCModel, 4);
	//m_ppHierarchicalGameObjects[9]->SetPosition(1380.0f, m_pTerrain->GetHeight(430.0f, 700.0f), 1875.0f);
	//m_ppHierarchicalGameObjects[9]->Rotate(0.0f, 180.0f, 0.0f);
	//m_ppHierarchicalGameObjects[9]->SetScale(10.0f, 10.0f, 10.0f);
	//m_ppHierarchicalGameObjects[9]->SetBoundingBox(m_ppHierarchicalGameObjects[9]->m_xmOOBB, m_ppHierarchicalGameObjects[9]);

	//m_ppHierarchicalGameObjects[9]->ScaleBoundingBox(5.0f, 20.0f, 5.0f);
	//m_ppHierarchicalGameObjects[9]->RotateBoundingBox(0.0f, XMConvertToRadians(225.0f), 0.0f);
	//m_ppHierarchicalGameObjects[9]->nonConflicting = true;
	//m_ppHierarchicalGameObjects[9]->isNPC = true;
	//m_pBoundingBox[9] = new CBoundingBox(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, m_ppHierarchicalGameObjects[9]->m_xmOOBB);

	//// m_lpGameObjects.push_back(m_ppHierarchicalGameObjects[0]);
	//if (pNPCModel) delete pNPCModel;


	//for (int i = 0; i < m_nHierarchicalGameObjects; i++)
	//{
	//	if (m_ppHierarchicalGameObjects[i]) //m_ppHierarchicalGameObjects[i]->SetBoundingBox(m_ppHierarchicalGameObjects[i]->m_xmOOBB, m_ppHierarchicalGameObjects[i]);
	//		m_lpGameObjects.push_back(m_ppHierarchicalGameObjects[i]);		
	//}

	
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();
	if (m_pd3dCbvSrvDescriptorHeap) m_pd3dCbvSrvDescriptorHeap->Release();

	if (m_ppGameObjects)
	{
		for (int i = 0; i < m_nGameObjects; i++) if (m_ppGameObjects[i]) m_ppGameObjects[i]->Release();
		delete[] m_ppGameObjects;
	}

	if (m_ppShaders)
	{
		for (int i = 0; i < m_nShaders; i++)
		{
			m_ppShaders[i]->ReleaseShaderVariables();
			m_ppShaders[i]->ReleaseObjects();
			m_ppShaders[i]->Release();
		}
		delete[] m_ppShaders;
	}

	while (m_vGameObjects.size()) {
		m_vGameObjects.back()->Release();
		m_vGameObjects.pop_back();
	}

	if (m_pTerrain) delete m_pTerrain;
	if (m_pSkyBox) delete m_pSkyBox;

	//// OBB 제거
	//for (int i = 0; i < 4; i++)
	//	delete m_pBoundingBox[i];

	for (auto boungBox : m_vBoundingBox)
		delete boungBox;

	// 여기 고쳐야함

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		// 흠..
		if (m_pPlayer->m_ppBullets[i]->m_bActive) m_pPlayer->m_ppBullets[i]->Release();
			delete m_pPlayer->m_ppBullets[i];
	}

	//if (m_ppHierarchicalGameObjects)
	//{
	//	for (int i = 0; i < m_nHierarchicalGameObjects; i++) if (m_ppHierarchicalGameObjects[i]) m_ppHierarchicalGameObjects[i]->Release();
	//	delete[] m_ppHierarchicalGameObjects;
	//}

	ReleaseShaderVariables();

	if (m_pLights) delete[] m_pLights;
}

ID3D12RootSignature *CScene::CreateGraphicsRootSignature(ID3D12Device *pd3dDevice)
{
	ID3D12RootSignature *pd3dGraphicsRootSignature = NULL;

	D3D12_DESCRIPTOR_RANGE pd3dDescriptorRanges[10];

	pd3dDescriptorRanges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[0].NumDescriptors = 1;
	pd3dDescriptorRanges[0].BaseShaderRegister = 6; //t6: gtxtAlbedoTexture
	pd3dDescriptorRanges[0].RegisterSpace = 0;
	pd3dDescriptorRanges[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[1].NumDescriptors = 1;
	pd3dDescriptorRanges[1].BaseShaderRegister = 7; //t7: gtxtSpecularTexture
	pd3dDescriptorRanges[1].RegisterSpace = 0;
	pd3dDescriptorRanges[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[2].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[2].NumDescriptors = 1;
	pd3dDescriptorRanges[2].BaseShaderRegister = 8; //t8: gtxtNormalTexture
	pd3dDescriptorRanges[2].RegisterSpace = 0;
	pd3dDescriptorRanges[2].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[3].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[3].NumDescriptors = 1;
	pd3dDescriptorRanges[3].BaseShaderRegister = 9; //t9: gtxtMetallicTexture
	pd3dDescriptorRanges[3].RegisterSpace = 0;
	pd3dDescriptorRanges[3].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[4].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[4].NumDescriptors = 1;
	pd3dDescriptorRanges[4].BaseShaderRegister = 10; //t10: gtxtEmissionTexture
	pd3dDescriptorRanges[4].RegisterSpace = 0;
	pd3dDescriptorRanges[4].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[5].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[5].NumDescriptors = 1;
	pd3dDescriptorRanges[5].BaseShaderRegister = 11; //t11: gtxtEmissionTexture
	pd3dDescriptorRanges[5].RegisterSpace = 0;
	pd3dDescriptorRanges[5].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[6].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[6].NumDescriptors = 1;
	pd3dDescriptorRanges[6].BaseShaderRegister = 12; //t12: gtxtEmissionTexture
	pd3dDescriptorRanges[6].RegisterSpace = 0;
	pd3dDescriptorRanges[6].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[7].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[7].NumDescriptors = 1;
	pd3dDescriptorRanges[7].BaseShaderRegister = 13; //t13: gtxtSkyBoxTexture
	pd3dDescriptorRanges[7].RegisterSpace = 0;
	pd3dDescriptorRanges[7].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[8].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[8].NumDescriptors = 1;
	pd3dDescriptorRanges[8].BaseShaderRegister = 1; //t1: gtxtTerrainBaseTexture
	pd3dDescriptorRanges[8].RegisterSpace = 0;
	pd3dDescriptorRanges[8].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[9].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[9].NumDescriptors = 1;
	pd3dDescriptorRanges[9].BaseShaderRegister = 2; //t2: gtxtTerrainDetailTexture
	pd3dDescriptorRanges[9].RegisterSpace = 0;
	pd3dDescriptorRanges[9].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	D3D12_ROOT_PARAMETER pd3dRootParameters[15];

	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[0].Descriptor.ShaderRegister = 1; //Camera
	pd3dRootParameters[0].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 33;
	pd3dRootParameters[1].Constants.ShaderRegister = 2; //GameObject
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[2].Descriptor.ShaderRegister = 4; //Lights
	pd3dRootParameters[2].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[3].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[3].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[0]);
	pd3dRootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[4].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[4].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[1]);
	pd3dRootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[5].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[5].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[5].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[2]);
	pd3dRootParameters[5].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[6].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[6].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[6].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[3]);
	pd3dRootParameters[6].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[7].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[7].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[7].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[4]);
	pd3dRootParameters[7].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[8].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[8].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[8].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[5]);
	pd3dRootParameters[8].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[9].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[9].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[9].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[6]);
	pd3dRootParameters[9].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[10].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[10].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[10].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[7]);
	pd3dRootParameters[10].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[11].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[11].Descriptor.ShaderRegister = 7; //Skinned Bone Offsets
	pd3dRootParameters[11].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[11].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

	pd3dRootParameters[12].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[12].Descriptor.ShaderRegister = 8; //Skinned Bone Transforms
	pd3dRootParameters[12].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[12].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

	pd3dRootParameters[13].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[13].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[13].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[8]);
	pd3dRootParameters[13].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[14].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[14].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[14].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[9]);
	pd3dRootParameters[14].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	D3D12_STATIC_SAMPLER_DESC pd3dSamplerDescs[2];

	pd3dSamplerDescs[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	pd3dSamplerDescs[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pd3dSamplerDescs[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pd3dSamplerDescs[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pd3dSamplerDescs[0].MipLODBias = 0;
	pd3dSamplerDescs[0].MaxAnisotropy = 1;
	pd3dSamplerDescs[0].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	pd3dSamplerDescs[0].MinLOD = 0;
	pd3dSamplerDescs[0].MaxLOD = D3D12_FLOAT32_MAX;
	pd3dSamplerDescs[0].ShaderRegister = 0;
	pd3dSamplerDescs[0].RegisterSpace = 0;
	pd3dSamplerDescs[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dSamplerDescs[1].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	pd3dSamplerDescs[1].AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	pd3dSamplerDescs[1].AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	pd3dSamplerDescs[1].AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	pd3dSamplerDescs[1].MipLODBias = 0;
	pd3dSamplerDescs[1].MaxAnisotropy = 1;
	pd3dSamplerDescs[1].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	pd3dSamplerDescs[1].MinLOD = 0;
	pd3dSamplerDescs[1].MaxLOD = D3D12_FLOAT32_MAX;
	pd3dSamplerDescs[1].ShaderRegister = 1;
	pd3dSamplerDescs[1].RegisterSpace = 0;
	pd3dSamplerDescs[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = _countof(pd3dSamplerDescs);
	d3dRootSignatureDesc.pStaticSamplers = pd3dSamplerDescs;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob *pd3dSignatureBlob = NULL;
	ID3DBlob *pd3dErrorBlob = NULL;
	D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(), pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void **)&pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return(pd3dGraphicsRootSignature);
}

void CScene::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(LIGHTS) + 255) & ~255); //256ÀÇ ¹è¼ö
	m_pd3dcbLights = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbLights->Map(0, NULL, (void **)&m_pcbMappedLights);
}

void CScene::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	::memcpy(m_pcbMappedLights->m_pLights, m_pLights, sizeof(LIGHT) * m_nLights);
	::memcpy(&m_pcbMappedLights->m_xmf4GlobalAmbient, &m_xmf4GlobalAmbient, sizeof(XMFLOAT4));
	::memcpy(&m_pcbMappedLights->m_nLights, &m_nLights, sizeof(int));
}

void CScene::ReleaseShaderVariables()
{
	if (m_pd3dcbLights)
	{
		m_pd3dcbLights->Unmap(0, NULL);
		m_pd3dcbLights->Release();
	}
}

void CScene::ReleaseUploadBuffers()
{
	for (const auto& elm : m_vGameObjects) elm->ReleaseUploadBuffers();

	if (m_pSkyBox) m_pSkyBox->ReleaseUploadBuffers();
	if (m_pTerrain) m_pTerrain->ReleaseUploadBuffers();

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (m_pPlayer->m_ppBullets[i]->m_bActive)
			m_pPlayer->m_ppBullets[i]->ReleaseUploadBuffers();
	}
	

	for (int i = 0; i < m_nShaders; i++) m_ppShaders[i]->ReleaseUploadBuffers();
	for (int i = 0; i < m_nGameObjects; i++) if (m_ppGameObjects[i]) m_ppGameObjects[i]->ReleaseUploadBuffers();
	//for (int i = 0; i < m_nHierarchicalGameObjects; i++) m_ppHierarchicalGameObjects[i]->ReleaseUploadBuffers();
}

void CScene::CreateCbvSrvDescriptorHeaps(ID3D12Device *pd3dDevice, int nConstantBufferViews, int nShaderResourceViews)
{
	D3D12_DESCRIPTOR_HEAP_DESC d3dDescriptorHeapDesc;
	d3dDescriptorHeapDesc.NumDescriptors = nConstantBufferViews + nShaderResourceViews; //CBVs + SRVs 
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	d3dDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	d3dDescriptorHeapDesc.NodeMask = 0;
	pd3dDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, __uuidof(ID3D12DescriptorHeap), (void **)&m_pd3dCbvSrvDescriptorHeap);

	m_d3dCbvCPUDescriptorNextHandle = m_d3dCbvCPUDescriptorStartHandle = m_pd3dCbvSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	m_d3dCbvGPUDescriptorNextHandle = m_d3dCbvGPUDescriptorStartHandle = m_pd3dCbvSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
	m_d3dSrvCPUDescriptorNextHandle.ptr = m_d3dSrvCPUDescriptorStartHandle.ptr = m_d3dCbvCPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nConstantBufferViews);
	m_d3dSrvGPUDescriptorNextHandle.ptr = m_d3dSrvGPUDescriptorStartHandle.ptr = m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nConstantBufferViews);
}

D3D12_GPU_DESCRIPTOR_HANDLE CScene::CreateConstantBufferViews(ID3D12Device *pd3dDevice, int nConstantBufferViews, ID3D12Resource *pd3dConstantBuffers, UINT nStride)
{
	D3D12_GPU_DESCRIPTOR_HANDLE d3dCbvGPUDescriptorHandle = m_d3dCbvGPUDescriptorNextHandle;
	D3D12_GPU_VIRTUAL_ADDRESS d3dGpuVirtualAddress = pd3dConstantBuffers->GetGPUVirtualAddress();
	D3D12_CONSTANT_BUFFER_VIEW_DESC d3dCBVDesc;
	d3dCBVDesc.SizeInBytes = nStride;
	for (int j = 0; j < nConstantBufferViews; j++)
	{
		d3dCBVDesc.BufferLocation = d3dGpuVirtualAddress + (nStride * j);
		m_d3dCbvCPUDescriptorNextHandle.ptr = m_d3dCbvCPUDescriptorNextHandle.ptr + ::gnCbvSrvDescriptorIncrementSize;
		pd3dDevice->CreateConstantBufferView(&d3dCBVDesc, m_d3dCbvCPUDescriptorNextHandle);
		m_d3dCbvGPUDescriptorNextHandle.ptr = m_d3dCbvGPUDescriptorNextHandle.ptr + ::gnCbvSrvDescriptorIncrementSize;
	}
	return(d3dCbvGPUDescriptorHandle);
}

void CScene::CreateShaderResourceViews(ID3D12Device* pd3dDevice, CTexture* pTexture, UINT nDescriptorHeapIndex, UINT nRootParameterStartIndex)
{
	m_d3dSrvCPUDescriptorNextHandle.ptr += (::gnCbvSrvDescriptorIncrementSize * nDescriptorHeapIndex);
	m_d3dSrvGPUDescriptorNextHandle.ptr += (::gnCbvSrvDescriptorIncrementSize * nDescriptorHeapIndex);

	if (pTexture)
	{
		int nTextures = pTexture->GetTextures();
		for (int i = 0; i < nTextures; i++)
		{
			ID3D12Resource* pShaderResource = pTexture->GetResource(i);
			D3D12_SHADER_RESOURCE_VIEW_DESC d3dShaderResourceViewDesc = pTexture->GetShaderResourceViewDesc(i);
			pd3dDevice->CreateShaderResourceView(pShaderResource, &d3dShaderResourceViewDesc, m_d3dSrvCPUDescriptorNextHandle);
			m_d3dSrvCPUDescriptorNextHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;
			pTexture->SetGpuDescriptorHandle(i, m_d3dSrvGPUDescriptorNextHandle);
			m_d3dSrvGPUDescriptorNextHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;
		}
	}
	int nRootParameters = pTexture->GetRootParameters();
	for (int j = 0; j < nRootParameters; j++) pTexture->SetRootParameterIndex(j, nRootParameterStartIndex + j);
}

void CScene::CheckPlayerByObjectCollisions()
{
	for (auto iter = m_vGameObjects.begin(); iter != m_vGameObjects.end(); ++iter)
	{
		CGameObject* Object = *iter;
		//XMFLOAT3 objectCenter = Object->m_xmOOBB.Center;
		//auto t = Object->GetPosition();
		//XMFLOAT3 playerCenter = m_pPlayer->m_xmOOBB.Center;

		//std::cout << "Object위치: " << objectCenter.x << ", " << objectCenter.y << ", " << objectCenter.z << std::endl;
		//std::cout << "Player위치: " << playerCenter.x << ", " << playerCenter.y << ", " << playerCenter.z << std::endl;

		//std::cout << "Object OBB: " << objectCenter.x << ", " << objectCenter.y << ", " << objectCenter.z << std::endl;
		//std::cout << "Object Position: " << t.x << ", " << t.y << ", " << t.z << std::endl;

		if (Object->m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB))
		{
			// 이전 위치로 돌려보내기
			// 충돌하면 어느 방향으로도 안움직이네..
			// 충돌한 객체와 플레이어의 위치를 사용하여 표면 법선 계산
			//XMFLOAT3 xmf3CollisionPoint = m_pPlayer->GetPosition();
			//XMFLOAT3 xmf3ObjectCenter = Object->GetPosition();
			//XMFLOAT3 xmf3SurfaceNormal;

			//// 표면 법선 계산
			//XMStoreFloat3(&xmf3SurfaceNormal, XMVector3Normalize(XMLoadFloat3(&xmf3CollisionPoint) - XMLoadFloat3(&xmf3ObjectCenter)));

			//XMVECTOR incidentDirection = XMLoadFloat3(&m_pPlayer->m_xmf3MovingDirection);
			//XMVECTOR normal = XMLoadFloat3(&xmf3SurfaceNormal);

			//// 반사 벡터 계산
			//XMVECTOR reflectedDirection = XMVector3Reflect(incidentDirection, normal);

			//// 반사 벡터를 플레이어의 방향으로 설정
			//XMStoreFloat3(&m_pPlayer->m_xmf3MovingDirection, reflectedDirection);

			//auto t = m_pPlayer->GetPreviousPosition();
			//m_pPlayer->SetPosition(t);
			//m_pPlayer->Move(m_pPlayer->m_xmf3MovingDirection);

			// 충돌한 물체의 법선 벡터 계산해서 플레이어의 이동 방향 벡터를 반대로 돌리기
			XMFLOAT3 playerPosition = m_pPlayer->GetPosition();
			XMFLOAT3 objectPosition = Object->GetPosition();

			// 충돌 지점에서의 노멀 벡터 계산
			XMFLOAT3 collisionNormal;
			XMStoreFloat3(&collisionNormal, XMVector3Normalize(XMLoadFloat3(&playerPosition) - XMLoadFloat3(&objectPosition)));

			// 충돌 법선의 반대 방향으로 플레이어 이동
			XMFLOAT3 newPosition;
			XMStoreFloat3(&newPosition, XMLoadFloat3(&playerPosition) + XMLoadFloat3(&collisionNormal));

			// 새로운 위치로 플레이어 이동
			m_pPlayer->SetPosition(newPosition);

			//std::cout << "충돌!" << std::endl;
			
		}
	}
}

void CScene::CheckBulletByObjectCollisions()
{
	for (auto iter = m_vGameObjects.begin(); iter != m_vGameObjects.end(); ++iter)
	{
		CGameObject* Object = *iter;

		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (m_pPlayer->m_ppBullets[i]->m_bActive)
				if (m_pPlayer->m_ppBullets[i]->m_xmOOBB.Intersects(Object->m_xmOOBB))
				{
					if (!Object->nonConflicting)
					{
						// std::cout << "충돌!" << std::endl;

					// 충돌한 객체와 총알의 위치를 사용하여 표면 법선 계산
						XMFLOAT3 xmf3CollisionPoint = m_pPlayer->m_ppBullets[i]->GetPosition();
						XMFLOAT3 xmf3ObjectCenter = Object->GetPosition();
						XMFLOAT3 xmf3SurfaceNormal;
						
						// 우선은 y축은 고정으로
						xmf3CollisionPoint.y = xmf3ObjectCenter.y;
						

						XMFLOAT3 corners[8];
						Object->m_xmOOBB.GetCorners(corners);
						 

						// 정면		 4 5 6 7
						// 왼쪽		 0 4 7 3
						// 오른쪽	 5 1 2 6
						// 뒤쪽		 1 2 3 0
						
						// 위쪽		 7 6 2 3
						// 아래쪽	 0 1 5 4


						XMVECTOR xmCorners[8];
						for (int i = 0; i < 8; i++) {
							xmCorners[i] = XMLoadFloat3(&corners[i]);
						}

						XMVECTOR collisionPoint = XMLoadFloat3(&xmf3CollisionPoint);

						std::vector<PlaneData> planeDistances;

						// 면의 거리 계산 및 저장
						auto calculateAndStoreDistance = [&](int a, int b, int c) {
							// 평면의 법선 벡터 계산
							XMVECTOR planeNormal = XMVector3Normalize(XMVector3Cross(XMVectorSubtract(xmCorners[b], xmCorners[a]), XMVectorSubtract(xmCorners[c], xmCorners[a])));
							float planeD = -XMVectorGetX(XMVector3Dot(planeNormal, xmCorners[a]));
							float distance = XMVectorGetX(XMVector3Dot(planeNormal, collisionPoint)) + planeD;
							planeDistances.emplace_back(planeNormal, distance);
							};

						// 각 면에 대해 계산
						calculateAndStoreDistance(4, 5, 6); // Front
						calculateAndStoreDistance(0, 4, 7); // Left
						calculateAndStoreDistance(5, 1, 2); // Right
						calculateAndStoreDistance(1, 2, 3); // Back
						calculateAndStoreDistance(7, 6, 2); // Top
						calculateAndStoreDistance(0, 1, 5); // Bottom

						// 가장 가까운 면 찾기
						float minDistance = FLT_MAX;
						XMVECTOR xmvNearestNormal;
						for (const auto& plane : planeDistances) {
							if (fabs(plane.distance) < minDistance) {
								minDistance = fabs(plane.distance);
								xmvNearestNormal = plane.normal;
							}
						}

						// 가장 가까운 면의 법선 벡터 출력
						XMFLOAT3 xmf3NearestNormalFloat3;
						XMStoreFloat3(&xmf3NearestNormalFloat3, xmvNearestNormal);

						// 총알을 반사시키는 함수 호출
						//XMFLOAT3 pastDirection = m_pPlayer->m_ppBullets[i]->m_xmf3MovingDirection;
						m_pPlayer->m_ppBullets[i]->ReflectBullet(xmf3NearestNormalFloat3);
						//XMFLOAT3 nowDirection =  m_pPlayer->m_ppBullets[i]->m_xmf3MovingDirection;		
						// 총알이 도탄되는 방향으로 과거와 현재의 방향을 비교하여회전시켜라

						//m_pPlayer->m_ppBullets[i]->RotateBulletTowards(pastDirection, nowDirection);
					}
					else
					{
						if (Object->isNPC)
						{
							Object->isheat = true;
							cout << "NPC 맞음" << endl;
							Object->m_pSkinnedAnimationController->SetTrackType(2, ANIMATION_TYPE_ONCE);
							Object->m_pSkinnedAnimationController->SetTrackEnable(0, false);
							Object->m_pSkinnedAnimationController->SetTrackEnable(1, false);
							Object->m_pSkinnedAnimationController->SetTrackEnable(2, true);
							Object->m_pSkinnedAnimationController->SetTrackEnable(3, false);
							
						}
					}
					

				}
		}
	}
}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		break;
	default:
		break;
	}
	return(false);
}

bool CScene::ProcessInput(UCHAR *pKeysBuffer)
{
	return(false);
}

void CScene::AnimateObjects(float fTimeElapsed)
{
	m_fElapsedTime = fTimeElapsed;

	CheckPlayerByObjectCollisions();
	//CheckBulletByObjectCollisions();

	for (int i = 0; i < m_nGameObjects; i++) if (m_ppGameObjects[i]) m_ppGameObjects[i]->Animate(fTimeElapsed);
	for (int i = 0; i < m_nShaders; i++) if (m_ppShaders[i]) m_ppShaders[i]->AnimateObjects(fTimeElapsed);

	if (m_pLights)
	{
		m_pLights[1].m_xmf3Position = m_pPlayer->GetPosition();
		m_pLights[1].m_xmf3Direction = m_pPlayer->GetLookVector();
	}

	CheckPlayerByObjectCollisions();
	CheckBulletByObjectCollisions();

	
	//m_ppHierarchicalGameObjects[0]->MoveToTarget(m_pPlayer->GetPosition(), 0.5f);

	//for (int i = 0; i < m_nHierarchicalGameObjects; i++)
	//{
	//	if (m_ppHierarchicalGameObjects[i]->isNPC)
	//	{
	//		if (!m_ppHierarchicalGameObjects[i]->isheat)
	//		{
	//			if (m_ppHierarchicalGameObjects[i]->findPlayer(m_pPlayer->GetPosition()))
	//			{
	//				m_ppHierarchicalGameObjects[i]->m_pSkinnedAnimationController->SetTrackEnable(0, false);
	//				m_ppHierarchicalGameObjects[i]->m_pSkinnedAnimationController->SetTrackEnable(1, true);
	//			}
	//			else
	//			{
	//				m_ppHierarchicalGameObjects[i]->m_pSkinnedAnimationController->SetTrackEnable(0, true);
	//				m_ppHierarchicalGameObjects[i]->m_pSkinnedAnimationController->SetTrackEnable(1, false);
	//			}
	//		}
	//		else
	//		{
	//			//m_ppHierarchicalGameObjects[0]->m_pSkinnedAnimationController->SetTrackPosition(2, 3.0f);
	//		}
	//	}
	//}

	for (auto iter = m_vGameObjects.begin(); iter != m_vGameObjects.end(); ++iter)
	{
		CGameObject* obj = *iter;
		if (obj->isNPC)
		{
			if (!obj->isheat)
			{
				if (obj->findPlayer(m_pPlayer->GetPosition()))
				{
					obj->m_pSkinnedAnimationController->SetTrackEnable(0, false);
					obj->m_pSkinnedAnimationController->SetTrackEnable(1, true);
				}
				else
				{
					obj->m_pSkinnedAnimationController->SetTrackEnable(0, true);
					obj->m_pSkinnedAnimationController->SetTrackEnable(1, false);
				}
			}
			else
			{
				//m_ppHierarchicalGameObjects[0]->m_pSkinnedAnimationController->SetTrackPosition(2, 3.0f);
			}
		}
	}

}

void CScene::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	if (m_pd3dGraphicsRootSignature) pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);
	if (m_pd3dCbvSrvDescriptorHeap) pd3dCommandList->SetDescriptorHeaps(1, &m_pd3dCbvSrvDescriptorHeap);

	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pCamera->UpdateShaderVariables(pd3dCommandList);

	UpdateShaderVariables(pd3dCommandList);

	D3D12_GPU_VIRTUAL_ADDRESS d3dcbLightsGpuVirtualAddress = m_pd3dcbLights->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(2, d3dcbLightsGpuVirtualAddress); //Lights
	
	if (m_pSkyBox) m_pSkyBox->Render(pd3dCommandList, pCamera);
	if (m_pTerrain) m_pTerrain->Render(pd3dCommandList, pCamera);
	
	/*XMFLOAT2 xmpos = { 10, 10 };
	m_pTextureToViewportShader->Render(pd3dCommandList, pCamera, 100.0f,xmpos) ;*/

	// 총알 렌더링
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (m_pPlayer->m_ppBullets[i]->m_bActive)
		{
			m_pPlayer->m_ppBullets[i]->Render(pd3dCommandList, pCamera);
		}
	}

	

	for (int i = 0; i < m_nGameObjects; i++) if (m_ppGameObjects[i]) m_ppGameObjects[i]->Render(pd3dCommandList, pCamera);
	for (int i = 0; i < m_nShaders; i++) if (m_ppShaders[i]) m_ppShaders[i]->Render(pd3dCommandList, pCamera);

	//for (int i = 0; i < m_nHierarchicalGameObjects; i++)
	//{
	//	if (m_ppHierarchicalGameObjects[i])
	//	{
	//		m_ppHierarchicalGameObjects[i]->Animate(m_fElapsedTime);
	//		if (!m_ppHierarchicalGameObjects[i]->m_pSkinnedAnimationController) m_ppHierarchicalGameObjects[i]->UpdateTransform(NULL);
	//		m_ppHierarchicalGameObjects[i]->Render(pd3dCommandList, pCamera);
	//	}
	//}

	for (auto iter = m_vGameObjects.begin(); iter != m_vGameObjects.end(); ++iter) 
	{
		CGameObject* obj = *iter;
		obj->Animate(m_fElapsedTime);
		if (!obj->m_pSkinnedAnimationController) obj->UpdateTransform(NULL);
		obj->Render(pd3dCommandList, pCamera);
	}


	for (const auto& elm : m_vGameObjects) {
		elm->UpdateTransform(NULL);
		elm->Render(pd3dCommandList, pCamera);
	}
	// OOBB 렌더링
	if (m_pPlayer->DrawBoundingBox)
	{
		/*for (int i = 0; i < 10; i++)
		{
			m_pBoundingBox[i]->Render(pd3dCommandList, pCamera);
		}*/

		for (auto boundingBox : m_vBoundingBox)
			boundingBox->Render(pd3dCommandList, pCamera);
	}


	if(m_pUI)
		m_pUI->Render(pd3dCommandList, pCamera);
}

