//#include "stdafx.h"
//#include "Voxelizer.h"
//
//// 연기 복셀 버퍼 반환 함수
//ComputeBuffer Voxelizer::GetSmokeVoxelBuffer()
//{
//    return m_smokeVoxelsBuffer;
//}
//
//// 복셀 해상도 반환 함수
//XMFLOAT3 Voxelizer::GetVoxelResolution()
//{
//    return XMFLOAT3(m_voxelsX, m_voxelsY, m_voxelsZ);
//}
//
//// 복셀화 영역 반환 함수
//XMFLOAT3 Voxelizer::GetBoundsExtent()
//{
//    return boundsExtent;
//}
//
//// 복셀 크기 반환 함수
//float Voxelizer::GetVoxelSize()
//{
//    return voxelSize;
//}
//
//// 연기 원점 반환 함수
//XMFLOAT3 Voxelizer::GetSmokeOrigin()
//{
//    return m_smokeOrigin;
//}
//
//// 연기 반경 반환 함수
//XMFLOAT3 Voxelizer::GetSmokeRadius()
//{
//    return Vector3::Lerp(Vector3::ZeroFloat(), maxRadius, Easing(m_radius));
//}
//
//// easing 반환 함수
//float Voxelizer::GetEasing()
//{
//    return Easing(m_radius);
//}
//
//void Voxelizer::OnEnable()
//{
//    // 초기화 및 설정
//    CMaterial debugMaterial();
//
//    m_radius = 0.0f;
//    m_debugVoxelMaterial = CMaterial::SetShader("Hidden/VisualizeVoxels");
//    m_voxelizeCompute = (ComputeShader)Resources.Load("Voxelize");
//
//    XMFLOAT3 boundsSize = Vector3::ScalarProduct(boundsExtent, 2, false);
//    m_debugBounds = BoundingBox(XMFLOAT3(0, boundsExtent.y, 0), boundsSize);
//
//    m_voxelsX = CeilToInt(boundsSize.x / voxelSize);
//    m_voxelsY = CeilToInt(boundsSize.y / voxelSize);
//    m_voxelsZ = CeilToInt(boundsSize.z / voxelSize);
//    m_totalVoxels = m_voxelsX * m_voxelsY * m_voxelsZ;
//
//    m_staticVoxelsBuffer = ComputeBuffer(m_totalVoxels, 4);
//
//    // 정적 복셀 버퍼 초기화
//    m_voxelizeCompute.SetBuffer(0, "_Voxels", m_staticVoxelsBuffer);
//    m_voxelizeCompute.Dispatch(0, CeilToInt(m_totalVoxels / 128.0f), 1, 1);
//
//    // 화면의 복셀화 사전 계산
//    ComputeBuffer verticesBuffer, trianglesBuffer;
//    foreach(Transform child in objectsToVoxelize.GetComponentsInChildren<Transform>()) {
//        MeshFilter meshFilter = child.gameObject.GetComponent<MeshFilter>();
//
//        if (!meshFilter) continue;
//        CMesh sharedMesh = meshFilter.sharedMesh;
//
//        verticesBuffer = ComputeBuffer(sharedMesh.vertexCount, 3 * sizeof(float));
//        verticesBuffer.SetData(sharedMesh.vertices);
//        trianglesBuffer = ComputeBuffer(sharedMesh.triangles.Length, sizeof(int));
//        trianglesBuffer.SetData(sharedMesh.triangles);
//
//        m_voxelizeCompute.SetBuffer(1, "_StaticVoxels", m_staticVoxelsBuffer);
//        m_voxelizeCompute.SetBuffer(1, "_MeshVertices", verticesBuffer);
//        m_voxelizeCompute.SetBuffer(1, "_MeshTriangleIndices", trianglesBuffer);
//        m_voxelizeCompute.SetVector("_VoxelResolution", new Vector3(m_voxelsX, m_voxelsY, m_voxelsZ));
//        m_voxelizeCompute.SetVector("_BoundsExtent", boundsExtent);
//        m_voxelizeCompute.SetMatrix("_MeshLocalToWorld", child.localToWorldMatrix);
//        m_voxelizeCompute.SetInt("_VoxelCount", m_totalVoxels);
//        m_voxelizeCompute.SetInt("_TriangleCount", sharedMesh.triangles.Length);
//        m_voxelizeCompute.SetFloat("_VoxelSize", voxelSize);
//        m_voxelizeCompute.SetFloat("_IntersectionBias", intersectionBias);
//
//        m_voxelizeCompute.Dispatch(1, CeilToInt(m_totalVoxels / 128.0f), 1, 1);
//
//        verticesBuffer.Release();
//        trianglesBuffer.Release();
//    }
//
//    // 연기 복셀 버퍼 초기화
//    m_smokeVoxelsBuffer = ComputeBuffer(m_totalVoxels, sizeof(int));
//    m_smokePingVoxelsBuffer = ComputeBuffer(m_totalVoxels, sizeof(int));
//
//    // 버퍼 초기화
//    m_voxelizeCompute.SetBuffer(0, "_Voxels", m_smokeVoxelsBuffer);
//    m_voxelizeCompute.Dispatch(0, CeilToInt(m_totalVoxels / 128.0f), 1, 1);
//    m_voxelizeCompute.SetBuffer(0, "_Voxels", m_smokePingVoxelsBuffer);
//    m_voxelizeCompute.Dispatch(0, CeilToInt(m_totalVoxels / 128.0f), 1, 1);
//
//    m_voxelizeCompute.SetBuffer(2, "_SmokeVoxels", m_smokeVoxelsBuffer);
//
//    m_voxelizeCompute.SetBuffer(3, "_StaticVoxels", m_staticVoxelsBuffer);
//    m_voxelizeCompute.SetBuffer(3, "_SmokeVoxels", m_smokeVoxelsBuffer);
//    m_voxelizeCompute.SetBuffer(3, "_PingVoxels", m_smokePingVoxelsBuffer);
//
//    m_voxelizeCompute.SetBuffer(4, "_Voxels", m_smokeVoxelsBuffer);
//    m_voxelizeCompute.SetBuffer(4, "_PingVoxels", m_smokePingVoxelsBuffer);
//    m_voxelizeCompute.SetBuffer(4, "_StaticVoxels", m_staticVoxelsBuffer);
//
//    // 디버그 메시 인스턴스화
//    m_argsBuffer = ComputeBuffer(1, 5 * sizeof(uint), ComputeBufferType.IndirectArguments);
//    uint[] args = uint[5]{ 0, 0, 0, 0, 0 };
//    args[0] = (uint)debugMesh.GetIndexCount(0);
//    args[1] = (uint)m_totalVoxels;
//    args[2] = (uint)debugMesh.GetIndexStart(0);
//    args[3] = (uint)debugMesh.GetBaseVertex(0);
//    m_argsBuffer.SetData(args);
//}
//
//float Voxelizer::Easing(float x)
//{
//    return 1 - (1 - x) * (1 - x);
//}
//
//void Voxelizer::Update()
//{
//    // 최대 범위 단계 설정
//    m_voxelizeCompute.SetInt("_MaxFillSteps", maxFillSteps);
//
//    // 마우스 입력에 따른 연막 원점 설정
//    if (Input.GetMouseButtonDown(0)) {
//        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
//        RaycastHit hit;
//        if (Physics.Raycast(ray, out hit, 50)) {
//            m_smokeOrigin = hit.point;
//            m_voxelizeCompute.SetVector("_SmokeOrigin", m_smokeOrigin);
//
//            m_radius = 0;
//            m_voxelizeCompute.SetBuffer(0, "_Voxels", m_smokeVoxelsBuffer);
//            m_voxelizeCompute.Dispatch(0, CeilToInt(m_totalVoxels / 128.0f), 1, 1);
//
//            m_voxelizeCompute.Dispatch(2, 1, 1, 1);
//        }
//    }
//
//    // 연막 채우기
//    if (iterateFill || constantFill) {
//        m_voxelizeCompute.SetVector("_Radius", Vector3.Lerp(Vector3.zero, maxRadius, Easing(m_radius)));
//
//        m_voxelizeCompute.Dispatch(3, CeilToInt(m_totalVoxels / 128.0f), 1, 1);
//        m_voxelizeCompute.Dispatch(4, CeilToInt(m_totalVoxels / 128.0f), 1, 1);
//
//        iterateFill = false;
//        if (m_radius < 1)
//            m_radius += growthSpeed * Time.deltaTime;
//    }
//
//    // 디버그 복셀 렌더링
//    if (debugStaticVoxels || debugSmokeVoxels || debugEdgeVoxels) {
//        m_debugVoxelMaterial.SetBuffer("_StaticVoxels", m_staticVoxelsBuffer);
//        m_debugVoxelMaterial.SetBuffer("_SmokeVoxels", m_smokeVoxelsBuffer);
//        m_debugVoxelMaterial.SetVector("_VoxelResolution", new Vector3(m_voxelsX, m_voxelsY, m_voxelsZ));
//        m_debugVoxelMaterial.SetVector("_BoundsExtent", boundsExtent);
//        m_debugVoxelMaterial.SetFloat("_VoxelSize", voxelSize);
//        m_debugVoxelMaterial.SetInt("_MaxFillSteps", maxFillSteps);
//        m_debugVoxelMaterial.SetInt("_DebugSmokeVoxels", debugSmokeVoxels ? 1 : 0);
//        m_debugVoxelMaterial.SetInt("_DebugStaticVoxels", debugStaticVoxels ? 1 : 0);
//
//        Graphics.DrawMeshInstancedIndirect(debugMesh, 0, m_debugVoxelMaterial, m_debugBounds, m_argsBuffer);
//    }
//}
//
//void Voxelizer::OnDisable()
//{
//    m_staticVoxelsBuffer.Release();
//    m_smokeVoxelsBuffer.Release();
//    m_smokePingVoxelsBuffer.Release();
//    m_argsBuffer.Release();
//}
//
//void Voxelizer::OnDrawGizmos()
//{
//    Gizmos.color = Color.red;
//    Gizmos.DrawWireCube(m_debugBounds.center, m_debugBounds.extents * 2);
//}