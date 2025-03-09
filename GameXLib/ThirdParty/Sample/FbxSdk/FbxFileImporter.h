//#pragma once
//#include "FbxSdk.h"
//#include <vector>
//
//// フェーズ
//enum class IMPORTPHASE
//{
//	NONE = -1,
//	NOTSTARTED = 0, // マネージャー生成された
//	FILEOPENED, // インポーター作成された
//	IMPORTED, // シーン作成された
//	FIXEDANDCONVERTED, // 固定及び変換
//};
//
//// マテリアルデータ
//struct ImportedMaterialData
//{
//	// 記入
//	void AddImportedMaterialName(std::string imported_material_name)
//	{
//		if (IsAlreadyImported(imported_material_name)) return;
//		import_material_name.push_back(imported_material_name);
//	}
//	// 存在する
//	bool IsAlreadyImported(std::string imported_material_name)
//	{
//		for (std::string& str : import_material_name)
//		{
//			if (str == imported_material_name) return true;
//		}
//		return false;
//	}
//	// fbxの一部マテリアルは同じ名前なので一意かどうか判断する
//	std::vector<std::string> import_material_name; // マテリアルの名前
//};
//
//class FbxFileImporter
//{
//public:
//	// コンストラクタ
//	FbxFileImporter();
//	// デストラクタ
//	~FbxFileImporter();
//	// 読み込みの開放
//	void ReleaseScene();
//
//	// ファイルの開示
//	bool OpenFile(std::string filename);
//	// ファイルの読み込み
//	bool ImportFile();
//	// Scene変換
//	bool ConvertScene();
//
//public:
//	// 軸変換
//	DirectX::XMFLOAT4X4 axis_system_transform{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
//	// 距離などの基本的な変換
//	DirectX::XMFLOAT4X4 system_unit_transform{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
//
//	ImportedMaterialData import_material_data; // マテリアルデータ
//
//	FbxScene* fbx_scene = nullptr; // Fbx読み込みデータ
//
//private:
//	IMPORTPHASE current_phase = IMPORTPHASE::NONE; // 読み込みの状態を表す
//	FbxManager* fbx_manager = nullptr; // Fbxマネージャー
//	FbxImporter* fbx_importer = nullptr; // Fbxインポーター
//};
//
