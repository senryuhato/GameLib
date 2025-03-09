//#pragma once
//#include "../../Library/Cereal/Cereal.h"
//#include <d3d11.h>
//#include <string>
//
//class SkinnedMesh
//{
//public:
//	//頂点データ
//	struct  Vertex
//	{
//		DirectX::XMFLOAT3 position; // 座標
//		DirectX::XMFLOAT3 normal; // 法線
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
//	// マテリアルに対して頂点の区分
//	struct Subset
//	{
//
//	};
//	
//public:
//	// ファイル読み込み
//	SkinnedMesh(ID3D11Device* device, const std::string& file_name);
//	// FBXファイル読み込み
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
//////// 頂点シェーダーで使用
//////D3D11_INPUT_ELEMENT_DESC input_element_desc[]
//////{
//////	 { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//////	 { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//////	 { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//////};
////
//////頂点データ
////struct  StaticMeshVertexData
////{
////	DirectX::XMFLOAT3 position; // 座標
////	DirectX::XMFLOAT3 normal; // 法線
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
////// 頂点データを含むバッファ
////struct  StaticMeshVertexBuffer
////{
////	std::vector<StaticMeshVertexData> vertices; // 頂点データ
////	std::vector<uint32_t> indices; // インデックスデータ
////
////	template<class T>
////	void serialize(T& archive)
////	{
////		archive(
////			CEREAL_NVP(vertices),
////			CEREAL_NVP(indices));
////	}
////
////	// データサイズ
////	const uint32_t vertex_stride = sizeof(StaticMeshVertexData);
////};
////
////// マテリアルに対して頂点の区分
////struct  StaticMeshRenderSection
////{
////	uint32_t start_index_location{ 0 }; // インデックス開始番号
////	uint32_t index_count{ 0 }; // 頂点数(インデックス)
////	uint32_t material_index = 0; // マテリアルのインデックス
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
////// 描画用データ
////struct StaticMeshRenderData
////{
////	// マテリアルに対して頂点の区分
////	std::vector<StaticMeshRenderSection> render_sections; // render_sectionの大きさがマテリアルの数
////
////	// 頂点データを含むバッファ
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
////// 頂点データとインデックスの取り出し
////void FetchStaticMeshVerticesAndIndices(FbxMesh* fbx_mesh, std::vector<FbxSurfaceMaterial*> fbx_materials, std::vector<StaticMeshVertexData>& vertices, std::vector<uint32_t>& indices, std::vector<StaticMeshRenderSection>& render_section);
//
////// 頂点データとインデックスの取り出し
////void FetchStaticMeshVerticesAndIndices(FbxMesh* fbx_mesh, std::vector<FbxSurfaceMaterial*> fbx_materials, std::vector<StaticMeshVertexData>& vertices, std::vector<uint32_t>& indices, std::vector<StaticMeshRenderSection>& render_section)
////{
////	const int polygon_count{ fbx_mesh->GetPolygonCount() }; // メッシュのポリゴン数
////	// テクスチャ情報
////	FbxStringList uv_names;
////	fbx_mesh->GetUVSetNames(uv_names);
////
////	// 頂点データの取り出し
////	for (int polygon_index = 0; polygon_index < polygon_count; ++polygon_index)
////	{
////		for (int edge_index = 0; edge_index < 3; edge_index++)
////		{
////			StaticMeshVertexData fetched_vertex;
////			bool has_normal = fbx_mesh->GetElementNormalCount() > 0;
////			bool has_uv = fbx_mesh->GetElementUVCount() > 0;
////
////			const FbxVector4* control_points{ fbx_mesh->GetControlPoints() }; // 頂点配列
////			const int polygon_vertex{ fbx_mesh->GetPolygonVertex(polygon_index, edge_index) }; // 頂点番号
////
////			// 位置情報
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
////	// マテリアル情報の取り出し
////	const int material_count{ static_cast<int>(fbx_materials.size()) };
////	// マテリアルがなければ一つ用意する
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
////		// 各マテリアルの面をカウントする。
////		const int polygon_count{ fbx_mesh->GetPolygonCount() };
////		for (int polygon_index = 0; polygon_index < polygon_count; ++polygon_index)
////		{
////			const int material_index{ fbx_mesh->GetElementMaterial()->GetIndexArray().GetAt(polygon_index) };
////			render_section.at(material_index).index_count += 3;
////		}
////
////		// オフセットの記録(頂点の数)
////		uint32_t offset{ 0 };
////		for (StaticMeshRenderSection& subset : render_section)
////		{
////			subset.start_index_location = offset;
////			offset += subset.index_count;
////			// 次の手順でカウンタとして使用されるため、ゼロにリセットします。
////			subset.index_count = 0;
////		}
////	}
////	else
////	{
////		// ない場合０番を使用する
////		render_section.at(0).start_index_location = 0;
////		render_section.at(0).material_index = 0;
////	}
////
////	// インデックス配列の立て直し
////	std::int32_t vertex_count = 0;
////	indices.resize(polygon_count * 3LL);
////	for (int polygon_index = 0; polygon_index < polygon_count; polygon_index++)
////	{
////		// 現在のマテリアルの面
////		int material_index = 0;
////		if (material_count > 0)
////		{
////			material_index = fbx_mesh->GetElementMaterial()->GetIndexArray().GetAt(polygon_index);
////		}
////		else // fbx_meshにマテリアルがない場合ダミーを一つ作る。
////		{
////			material_index = 0;
////		}
////		// マテリアルに応じてインデックスを保存する
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
