//#include "FbxFileImporter.h"
//#include "../Misc.h"
//#include <filesystem>
//#include <functional>
//
//// �R���X�g���N�^
//FbxFileImporter::FbxFileImporter()
//{
//	// FBX SDK �}�l�[�W���[�̐���
//	fbx_manager = FbxManager::Create();
//	// FBX�ɑ΂�����o�͂��`����B IOSROOT ���f�t�H���g
//	fbx_manager->SetIOSettings(FbxIOSettings::Create(fbx_manager, IOSROOT));
//
//	// �ǂݍ��ݏ��
//	current_phase = IMPORTPHASE::NOTSTARTED;
//}
//
//// �f�X�g���N�^
//FbxFileImporter::~FbxFileImporter()
//{
//	ReleaseScene(); // �V�[���̉��
//	fbx_manager->Destroy(); // �}�l�[�W���[�̉��
//}
//
//// �ǂݍ��݂̊J��
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
//// �t�@�C���̊J��
//bool FbxFileImporter::OpenFile(std::string filename)
//{
//	if (current_phase != IMPORTPHASE::NOTSTARTED) return false;
//
//	// �t�@�C�������邩
//	std::filesystem::path file_name(filename);
//	file_name.replace_extension(".fbx"); // �g���q��ύX
//	if (!std::filesystem::exists(file_name)) return false;
//
//	// �C���|�[�^�[�̐���
//	fbx_importer = FbxImporter::Create(fbx_manager, "");
//	// Importer�̏�����
//	bool import_status = fbx_importer->Initialize(filename.c_str());
//	_ASSERT_EXPR_A(import_status, fbx_importer->GetStatus().GetErrorString());
//
//	current_phase = IMPORTPHASE::FILEOPENED;
//	return true;
//}
//
//// �t�@�C���̓ǂݍ���
//bool FbxFileImporter::ImportFile()
//{
//	if (current_phase != IMPORTPHASE::FILEOPENED) return false;
//
//	// �ǂݍ��܂ꂽ�t�@�C���ɂ���ĐV�����V�[����ݒ肷��B
//	fbx_scene = FbxScene::Create(fbx_manager, "");
//	// Scene�I�u�W�F�N�g��FBX�t�@�C�����̏��𗬂�����
//	bool import_status = fbx_importer->Import(fbx_scene);
//	_ASSERT_EXPR_A(import_status, fbx_importer->GetStatus().GetErrorString());
//
//	current_phase = IMPORTPHASE::IMPORTED;
//	return true;
//}
//
//// Scene�ϊ�
//bool FbxFileImporter::ConvertScene()
//{
//	if (current_phase != IMPORTPHASE::IMPORTED) return false;
//
//	// ���b�V��,NURBS,�p�b�`���O�p�`�ɕϊ�
//	fbxsdk::FbxGeometryConverter geometry_converter(fbx_manager);
//	geometry_converter.Triangulate(fbx_scene, /*replace*/true);
//
//	// ���ϊ�
//	FbxAxisSystem axis_system;
//	axis_system.ConvertScene(fbx_scene);
//	FbxAxisSystem axis_system_reference = fbx_scene->GetGlobalSettings().GetAxisSystem();
//
//	// ���s��
//	FbxAMatrix pMatrix;
//	axis_system_reference.GetMatrix(pMatrix);
//	axis_system_transform = ToXMFloat4x4(pMatrix);
//
//	// CM����M�ւ̕Ԋ�
//	if (fbx_scene->GetGlobalSettings().GetSystemUnit() == FbxSystemUnit::cm)
//	{
//		system_unit_transform._11 = system_unit_transform._22 = system_unit_transform._33 = 0.01f;
//	}
//	current_phase = IMPORTPHASE::FIXEDANDCONVERTED;
//	return true;
//}
//
//#pragma region �T���v��
////// �t�@�C���ǂݍ���
////FbxFileImporter fbxFileImporter;
////
////if (!fbxFileImporter.OpenFile(file_name)) return;
////if (!fbxFileImporter.ImportFile()) return;
////if (!fbxFileImporter.ConvertScene())return;
////
////FbxNode* root_node_to_import = fbxFileImporter.fbx_scene->GetRootNode();
////std::vector<FbxNode*> fetched_meshes;
////
////// FBX�m�[�h���ċA�I�ɒH���ă��b�V���f�[�^���\�z����
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
////	// �ċA�I�Ɏq�m�[�h����������
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