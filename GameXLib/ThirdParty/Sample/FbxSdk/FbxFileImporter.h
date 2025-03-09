//#pragma once
//#include "FbxSdk.h"
//#include <vector>
//
//// �t�F�[�Y
//enum class IMPORTPHASE
//{
//	NONE = -1,
//	NOTSTARTED = 0, // �}�l�[�W���[�������ꂽ
//	FILEOPENED, // �C���|�[�^�[�쐬���ꂽ
//	IMPORTED, // �V�[���쐬���ꂽ
//	FIXEDANDCONVERTED, // �Œ�y�ѕϊ�
//};
//
//// �}�e���A���f�[�^
//struct ImportedMaterialData
//{
//	// �L��
//	void AddImportedMaterialName(std::string imported_material_name)
//	{
//		if (IsAlreadyImported(imported_material_name)) return;
//		import_material_name.push_back(imported_material_name);
//	}
//	// ���݂���
//	bool IsAlreadyImported(std::string imported_material_name)
//	{
//		for (std::string& str : import_material_name)
//		{
//			if (str == imported_material_name) return true;
//		}
//		return false;
//	}
//	// fbx�̈ꕔ�}�e���A���͓������O�Ȃ̂ň�ӂ��ǂ������f����
//	std::vector<std::string> import_material_name; // �}�e���A���̖��O
//};
//
//class FbxFileImporter
//{
//public:
//	// �R���X�g���N�^
//	FbxFileImporter();
//	// �f�X�g���N�^
//	~FbxFileImporter();
//	// �ǂݍ��݂̊J��
//	void ReleaseScene();
//
//	// �t�@�C���̊J��
//	bool OpenFile(std::string filename);
//	// �t�@�C���̓ǂݍ���
//	bool ImportFile();
//	// Scene�ϊ�
//	bool ConvertScene();
//
//public:
//	// ���ϊ�
//	DirectX::XMFLOAT4X4 axis_system_transform{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
//	// �����Ȃǂ̊�{�I�ȕϊ�
//	DirectX::XMFLOAT4X4 system_unit_transform{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
//
//	ImportedMaterialData import_material_data; // �}�e���A���f�[�^
//
//	FbxScene* fbx_scene = nullptr; // Fbx�ǂݍ��݃f�[�^
//
//private:
//	IMPORTPHASE current_phase = IMPORTPHASE::NONE; // �ǂݍ��݂̏�Ԃ�\��
//	FbxManager* fbx_manager = nullptr; // Fbx�}�l�[�W���[
//	FbxImporter* fbx_importer = nullptr; // Fbx�C���|�[�^�[
//};
//
