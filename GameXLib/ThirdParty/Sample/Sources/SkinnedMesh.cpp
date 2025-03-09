//#include "SkinnedMesh.h"
//#include <filesystem>
//#include <functional>
//#include "..\..\Library\Misc.h"
//#include "..\..\Library\FbxSdk\FbxSdk.h"
//
//// ファイル読み込み
//SkinnedMesh::SkinnedMesh(ID3D11Device* device, const std::string& file_name)
//{
//	/*std::filesystem::path cereal_filename(fbx_filename);
//	cereal_filename.replace_extension("cereal");
//	if (std::filesystem::exists(cereal_filename.c_str()) && load_cereal)
//	{
//		std::ifstream ifs(cereal_filename.c_str(), std::ios::binary);
//		cereal::BinaryInputArchive deserialization(ifs);
//		deserialization(scene_view, meshes, materials, animation_clips);
//	}*/
//
//	// ファイル読み込み
//	FbxFileLoad(file_name);
//}
//
//// FBXファイル読み込み
//void SkinnedMesh::FbxFileLoad(const std::string& filename)
//{
//	// FBX SDK マネージャーの生成
//	FbxManager* fbx_manager = FbxManager::Create();
//	// FBXに対する入出力を定義する。 IOSROOT がデフォルト
//	fbx_manager->SetIOSettings(FbxIOSettings::Create(fbx_manager, IOSROOT));
//
//	// インポーターの生成
//	FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "");
//	// Importerの初期化
//	bool import_status = fbx_importer->Initialize(filename.c_str());
//	_ASSERT_EXPR_A(import_status, fbx_importer->GetStatus().GetErrorString());
//
//	// 読み込まれたファイルによって新しいシーンを設定する。
//	FbxScene* fbx_scene = FbxScene::Create(fbx_manager, "");
//	// SceneオブジェクトにFBXファイル内の情報を流し込む(時間かかる)
//	import_status = fbx_importer->Import(fbx_scene);
//	_ASSERT_EXPR_A(import_status, fbx_importer->GetStatus().GetErrorString());
//
//	fbx_importer->Destroy();	// シーンを流し込んだらImporterは解放してOK
//
//	// メッシュ,NURBS,パッチを三角形に変換
//	fbxsdk::FbxGeometryConverter geometry_converter(fbx_manager);
//	geometry_converter.Triangulate(fbx_scene, /*replace*/true);
//
//	// モデルデータの読み込み
//
//
//	/*std::ofstream ofs(cereal_filename.c_str(), std::ios::binary);
//	cereal::BinaryOutputArchive serialization(ofs);
//	serialization(scene_view, meshes, materials, animation_clips);*/
//}