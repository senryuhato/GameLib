//#pragma once
//#include "../../Library/Cereal/Cereal.h"
//#include <d3d11.h>
//#include <string>
//
//class SkinnedMesh
//{
//public:
//	//���_�f�[�^
//	struct  Vertex
//	{
//		DirectX::XMFLOAT3 position; // ���W
//		DirectX::XMFLOAT3 normal; // �@��
//		DirectX::XMFLOAT2 texcoord; // UV
//
//		template<class T>
//		void serialize(T& archive)
//		{
//			archive(
//				CEREAL_NVP(position),
//				CEREAL_NVP(normal),
//				CEREAL_NVP(texcoord));
//		}
//	};
//
//	// �}�e���A���ɑ΂��Ē��_�̋敪
//	struct Subset
//	{
//
//	};
//	
//public:
//	// �t�@�C���ǂݍ���
//	SkinnedMesh(ID3D11Device* device, const std::string& file_name);
//	// FBX�t�@�C���ǂݍ���
//	void FbxFileLoad(const std::string& filename);
//};
//
//#pragma region MyRegion
//
//// StaticMeshRenderData
////pragma once
////#include "../../Library/Cereal/Cereal.h"
////#include <DirectXMath.h>
////#include <vector>
////#include <memory>
////
//////// ���_�V�F�[�_�[�Ŏg�p
//////D3D11_INPUT_ELEMENT_DESC input_element_desc[]
//////{
//////	 { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//////	 { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//////	 { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//////};
////
//////���_�f�[�^
////struct  StaticMeshVertexData
////{
////	DirectX::XMFLOAT3 position; // ���W
////	DirectX::XMFLOAT3 normal; // �@��
////	DirectX::XMFLOAT2 texcoord; // UV
////
////	// std::vector<std::string> Semantics{ "POSITION", "NORMAL", "TEXCOORD" };
////
////	template<class T>
////	void serialize(T& archive)
////	{
////		archive(
////			CEREAL_NVP(position),
////			CEREAL_NVP(normal),
////			CEREAL_NVP(texcoord));
////	}
////};
////
////// ���_�f�[�^���܂ރo�b�t�@
////struct  StaticMeshVertexBuffer
////{
////	std::vector<StaticMeshVertexData> vertices; // ���_�f�[�^
////	std::vector<uint32_t> indices; // �C���f�b�N�X�f�[�^
////
////	template<class T>
////	void serialize(T& archive)
////	{
////		archive(
////			CEREAL_NVP(vertices),
////			CEREAL_NVP(indices));
////	}
////
////	// �f�[�^�T�C�Y
////	const uint32_t vertex_stride = sizeof(StaticMeshVertexData);
////};
////
////// �}�e���A���ɑ΂��Ē��_�̋敪
////struct  StaticMeshRenderSection
////{
////	uint32_t start_index_location{ 0 }; // �C���f�b�N�X�J�n�ԍ�
////	uint32_t index_count{ 0 }; // ���_��(�C���f�b�N�X)
////	uint32_t material_index = 0; // �}�e���A���̃C���f�b�N�X
////
////	template<class T>
////	void serialize(T& archive)
////	{
////		archive(
////			CEREAL_NVP(start_index_location),
////			CEREAL_NVP(index_count),
////			CEREAL_NVP(material_index));
////	}
////};
////
////// �`��p�f�[�^
////struct StaticMeshRenderData
////{
////	// �}�e���A���ɑ΂��Ē��_�̋敪
////	std::vector<StaticMeshRenderSection> render_sections; // render_section�̑傫�����}�e���A���̐�
////
////	// ���_�f�[�^���܂ރo�b�t�@
////	StaticMeshVertexBuffer vertex_buffers;
////
////	template<class T>
////	void serialize(T& archive)
////	{
////		archive(
////			CEREAL_NVP(render_sections),
////			CEREAL_NVP(vertex_buffers));
////	}
////};
//
////// ���_�f�[�^�ƃC���f�b�N�X�̎��o��
////void FetchStaticMeshVerticesAndIndices(FbxMesh* fbx_mesh, std::vector<FbxSurfaceMaterial*> fbx_materials, std::vector<StaticMeshVertexData>& vertices, std::vector<uint32_t>& indices, std::vector<StaticMeshRenderSection>& render_section);
//
////// ���_�f�[�^�ƃC���f�b�N�X�̎��o��
////void FetchStaticMeshVerticesAndIndices(FbxMesh* fbx_mesh, std::vector<FbxSurfaceMaterial*> fbx_materials, std::vector<StaticMeshVertexData>& vertices, std::vector<uint32_t>& indices, std::vector<StaticMeshRenderSection>& render_section)
////{
////	const int polygon_count{ fbx_mesh->GetPolygonCount() }; // ���b�V���̃|���S����
////	// �e�N�X�`�����
////	FbxStringList uv_names;
////	fbx_mesh->GetUVSetNames(uv_names);
////
////	// ���_�f�[�^�̎��o��
////	for (int polygon_index = 0; polygon_index < polygon_count; ++polygon_index)
////	{
////		for (int edge_index = 0; edge_index < 3; edge_index++)
////		{
////			StaticMeshVertexData fetched_vertex;
////			bool has_normal = fbx_mesh->GetElementNormalCount() > 0;
////			bool has_uv = fbx_mesh->GetElementUVCount() > 0;
////
////			const FbxVector4* control_points{ fbx_mesh->GetControlPoints() }; // ���_�z��
////			const int polygon_vertex{ fbx_mesh->GetPolygonVertex(polygon_index, edge_index) }; // ���_�ԍ�
////
////			// �ʒu���
////			fetched_vertex.position.x = static_cast<float>(control_points[polygon_vertex][0]);
////			fetched_vertex.position.y = static_cast<float>(control_points[polygon_vertex][1]);
////			fetched_vertex.position.z = static_cast<float>(control_points[polygon_vertex][2]);
////
////			if (has_normal)
////			{
////				FbxVector4 normal;
////				fbx_mesh->GetPolygonVertexNormal(polygon_index, edge_index, normal);
////				fetched_vertex.normal.x = static_cast<float>(normal[0]);
////				fetched_vertex.normal.y = static_cast<float>(normal[1]);
////				fetched_vertex.normal.z = static_cast<float>(normal[2]);
////			}
////
////			if (has_uv)
////			{
////				FbxVector2 uv;
////				bool unmapped_uv;
////				fbx_mesh->GetPolygonVertexUV(polygon_index, edge_index, uv_names[0], uv, unmapped_uv);
////				fetched_vertex.texcoord.x = static_cast<float>(uv[0]);
////				fetched_vertex.texcoord.y = static_cast<float>(uv[1]);
////				fetched_vertex.texcoord.y = 1 - fetched_vertex.texcoord.y;
////
////				vertices.push_back(std::move(fetched_vertex));
////			}
////		}
////	}
////
////	// �}�e���A�����̎��o��
////	const int material_count{ static_cast<int>(fbx_materials.size()) };
////	// �}�e���A�����Ȃ���Έ�p�ӂ���
////	render_section.resize(material_count > 0 ? material_count : 1);
////
////	for (int material_index = 0; material_index < material_count; material_index++)
////	{
////		StaticMeshRenderSection& subset = render_section.at(material_index);
////		subset.material_index = material_index;
////	}
////
////	if (material_count > 0)
////	{
////		// �e�}�e���A���̖ʂ��J�E���g����B
////		const int polygon_count{ fbx_mesh->GetPolygonCount() };
////		for (int polygon_index = 0; polygon_index < polygon_count; ++polygon_index)
////		{
////			const int material_index{ fbx_mesh->GetElementMaterial()->GetIndexArray().GetAt(polygon_index) };
////			render_section.at(material_index).index_count += 3;
////		}
////
////		// �I�t�Z�b�g�̋L�^(���_�̐�)
////		uint32_t offset{ 0 };
////		for (StaticMeshRenderSection& subset : render_section)
////		{
////			subset.start_index_location = offset;
////			offset += subset.index_count;
////			// ���̎菇�ŃJ�E���^�Ƃ��Ďg�p����邽�߁A�[���Ƀ��Z�b�g���܂��B
////			subset.index_count = 0;
////		}
////	}
////	else
////	{
////		// �Ȃ��ꍇ�O�Ԃ��g�p����
////		render_section.at(0).start_index_location = 0;
////		render_section.at(0).material_index = 0;
////	}
////
////	// �C���f�b�N�X�z��̗��Ē���
////	std::int32_t vertex_count = 0;
////	indices.resize(polygon_count * 3LL);
////	for (int polygon_index = 0; polygon_index < polygon_count; polygon_index++)
////	{
////		// ���݂̃}�e���A���̖�
////		int material_index = 0;
////		if (material_count > 0)
////		{
////			material_index = fbx_mesh->GetElementMaterial()->GetIndexArray().GetAt(polygon_index);
////		}
////		else // fbx_mesh�Ƀ}�e���A�����Ȃ��ꍇ�_�~�[������B
////		{
////			material_index = 0;
////		}
////		// �}�e���A���ɉ����ăC���f�b�N�X��ۑ�����
////		StaticMeshRenderSection& subset = render_section.at(material_index);
////		const std::int32_t index_offset = subset.start_index_location + subset.index_count;
////
////		for (int edge_index = 0; edge_index < 3; ++edge_index)
////		{
////			indices.at(index_offset + static_cast<uint32_t>(edge_index)) = vertex_count;
////
////			vertex_count += 1;
////		}
////		subset.index_count += 3;
////	}
////}
//
//#pragma endregion
//
