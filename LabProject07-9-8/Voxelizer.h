//#pragma once
//#include <cmath>
//
//#include "Mesh.h"
//#include "Object.h"
//#include "Shader.h"
//#include "ComputeBuffer.h"
//
//class Voxelizer {
//private:
//    // 정적 복셀 버퍼, 연기 복셀 버퍼, 연기 핑 복셀 버퍼, args 버퍼
//    ComputeBuffer m_staticVoxelsBuffer, m_smokeVoxelsBuffer, m_smokePingVoxelsBuffer, m_argsBuffer;
//
//    // 복셀화 컴퓨트 셰이더
//    ComputeShader m_voxelizeCompute;
//
//    // 디버그 복셀 머티리얼
//    CMaterial m_debugVoxelMaterial;
//
//    // 디버그 바운딩 박스
//    BoundingBox m_debugBounds;
//
//    // 복셀 해상도
//    int m_voxelsX, m_voxelsY, m_voxelsZ, m_totalVoxels;
//
//    // 반경
//    float m_radius;
//
//    // 연막 시작점
//    XMFLOAT3 m_smokeOrigin;
//
//public:
//    // 복셀화 영역의 크기
//    XMFLOAT3 boundsExtent = XMFLOAT3(3, 3, 3);
//
//    // 복셀 하나의 크기
//    float voxelSize = 0.25f;
//
//    // 복셀화 대상 오브젝트
//    CGameObject objectsToVoxelize = NULL;
//
//    // 교차점 바이어스
//    [Range(0.0f, 2.0f)]
//    float intersectionBias = 1.0f;
//
//    // 디버그용 메쉬
//    CMesh debugMesh;
//
//    // 정적 복셀 디버그 여부
//    bool debugStaticVoxels = false;
//
//    // 연기 복셀 디버그 여부
//    bool debugSmokeVoxels = false;
//
//    // 엣지 복셀 디버그 여부
//    bool debugEdgeVoxels = false;
//
//    // 가장 큰 반경
//    XMFLOAT3 maxRadius = XMFLOAT3(1, 1, 1);
//
//    // 연기 확산 속도
//    [Range(0.01f, 5.0f)]
//    float growthSpeed = 1.0f;
//
//    // 최대 확산 범위
//    [Range(0, 128)]
//    int maxFillSteps = 16;
//
//    // 채우기 반복 여부
//    bool iterateFill = false;
//
//    // 상수 채우기 여부
//    bool constantFill = false;
//
//    // 연기 복셀 버퍼 반환 함수
//    ComputeBuffer GetSmokeVoxelBuffer();
//
//    // 복셀 해상도 반환 함수
//    XMFLOAT3 GetVoxelResolution();
//
//    // 복셀화 영역 반환 함수
//    XMFLOAT3 GetBoundsExtent();
//
//    // 복셀 크기 반환 함수
//    float GetVoxelSize();
//
//    // 연기 원점 반환 함수
//    XMFLOAT3 GetSmokeOrigin();
//
//    // 연기 반경 반환 함수
//    XMFLOAT3 GetSmokeRadius();
//
//    // easing(???) 반환 함수
//    float GetEasing();
//
//    // 연기 보이게 설정
//    void OnEnable();
//
//    // Easing 함수
//    float Easing(float x);
//
//    // 업데이트 함수
//    void Update();
//
//    // 연기 안보이게 설정
//    void OnDisable();
//
//    // 디버그용 바운딩 박스 그리기
//    void OnDrawGizmos();
//};