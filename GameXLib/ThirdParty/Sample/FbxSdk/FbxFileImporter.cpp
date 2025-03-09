//#include "FbxFileImporter.h"
//#include "../Misc.h"
//#include <filesystem>
//#include <functional>
//
//// コンストラクタ
//FbxFileImporter::FbxFileImporter()
//{
//	// FBX SDK マネージャーの生成
//	fbx_manager = FbxManager::Create();
//	// FBXに対する入出力を定義する。 IOSROOT がデフォルト
//	fbx_manager->SetIOSettings(FbxIOSettings::Create(fbx_manager, IOSROOT));
//
//	// 読み込み状態
//	current_phase = IMPORTPHASE::NOTSTARTED;
//}
//
//// デストラクタ
//FbxFileImporter::~FbxFileImporter()
//{
//	ReleaseScene(); // シーンの解放
//	fbx_manager->Destroy(); // マネージャーの解放
//}
//
//// 読み込みの開放
//void FbxFileImporter::ReleaseScene()
//{
//	if (fbx_importer)
//	{
//		fbx_importer->Destroy();
//		fbx_importer = nullptr;
//	}
//
//	if (fbx_scene)
//	{
//		fbx_scene->Destroy();
//		fbx_scene = nullptr;
//	}
//
//	axis_system_transform = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
//	system_unit_transform = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
//
//	import_material_data.import_material_name.clear();
//
//	current_phase = IMPORTPHASE::NOTSTARTED;
//}
//
//// ファイルの開示
//bool FbxFileImporter::OpenFile(std::string filename)
//{
//	if (current_phase != IMPORTPHASE::NOTSTARTED) return false;
//
//	// ファイルがあるか
//	std::filesystem::path file_name(filename);
//	file_name.replace_extension(".fbx"); // 拡張子を変更
//	if (!std::filesystem::exists(file_name)) return false;
//
//	// インポーターの生成
//	fbx_importer = FbxImporter::Create(fbx_manager, "");
//	// Importerの初期化
//	bool import_status = fbx_importer->Initialize(filename.c_str());
//	_ASSERT_EXPR_A(import_status, fbx_importer->GetStatus().GetErrorString());
//
//	current_phase = IMPORTPHASE::FILEOPENED;
//	return true;
//}
//
//// ファイルの読み込み
//bool FbxFileImporter::ImportFile()
//{
//	if (current_phase != IMPORTPHASE::FILEOPENED) return false;
//
//	// 読み込まれたファイルによって新しいシーンを設定する。
//	fbx_scene = FbxScene::Create(fbx_manager, "");
//	// SceneオブジェクトにFBXファイル内の情報を流し込む
//	bool import_status = fbx_importer->Import(fbx_scene);
//	_ASSERT_EXPR_A(import_status, fbx_importer->GetStatus().GetErrorString());
//
//	current_phase = IMPORTPHASE::IMPORTED;
//	return true;
//}
//
//// Scene変換
//bool FbxFileImporter::ConvertScene()
//{
//	if (current_phase != IMPORTPHASE::IMPORTED) return false;
//
//	// メッシュ,NURBS,パッチを三角形に変換
//	fbxsdk::FbxGeometryConverter geometry_converter(fbx_manager);
//	geometry_converter.Triangulate(fbx_scene, /*replace*/true);
//
//	// 軸変換
//	FbxAxisSystem axis_system;
//	axis_system.ConvertScene(fbx_scene);
//	FbxAxisSystem axis_system_reference = fbx_scene->GetGlobalSettings().GetAxisSystem();
//
//	// 軸行列
//	FbxAMatrix pMatrix;
//	axis_system_reference.GetMatrix(pMatrix);
//	axis_system_transform = ToXMFloat4x4(pMatrix);
//
//	// CMからMへの返還
//	if (fbx_scene->GetGlobalSettings().GetSystemUnit() == FbxSystemUnit::cm)
//	{
//		system_unit_transform._11 = system_unit_transform._22 = system_unit_transform._33 = 0.01f;
//	}
//	current_phase = IMPORTPHASE::FIXEDANDCONVERTED;
//	return true;
//}
//
//#pragma region サンプル
////// ファイル読み込み
////FbxFileImporter fbxFileImporter;
////
////if (!fbxFileImporter.OpenFile(file_name)) return;
////if (!fbxFileImporter.ImportFile()) return;
////if (!fbxFileImporter.ConvertScene())return;
////
////FbxNode* root_node_to_import = fbxFileImporter.fbx_scene->GetRootNode();
////std::vector<FbxNode*> fetched_meshes;
////
////// FBXノードを再帰的に辿ってメッシュデータを構築する
////std::function<void(FbxNode*)> traverse = [&](FbxNode* fbx_node)
////{
////	FbxNodeAttribute* fbx_node_attribute = fbx_node->GetNodeAttribute();
////
////	if (fbx_node_attribute)
////	{
////		switch (fbx_node_attribute->GetAttributeType())
////		{
////		case FbxNodeAttribute::eMesh:
////			fetched_meshes.push_back(fbx_node);
////			break;
////		default:
////			break;
////		}
////	}
////
////	// 再帰的に子ノードを処理する
////	for (int index_of_child = 0; index_of_child < fbx_node->GetChildCount(); ++index_of_child)
////	{
////		traverse(fbx_node->GetChild(index_of_child));
////	}
////};
////traverse(root_node_to_import);
////
////for (FbxNode* it : fetched_meshes)
////{
////}
////
////fbxFileImporter.ReleaseScene();
//#pragma endregion