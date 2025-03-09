//#include "SkinnedMesh.h"
//#include <filesystem>
//#include <functional>
//#include "..\..\Library\Misc.h"
//#include "..\..\Library\FbxSdk\FbxSdk.h"
//
//// �t�@�C���ǂݍ���
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
//	// �t�@�C���ǂݍ���
//	FbxFileLoad(file_name);
//}
//
//// FBX�t�@�C���ǂݍ���
//void SkinnedMesh::FbxFileLoad(const std::string& filename)
//{
//	// FBX SDK �}�l�[�W���[�̐���
//	FbxManager* fbx_manager = FbxManager::Create();
//	// FBX�ɑ΂�����o�͂��`����B IOSROOT ���f�t�H���g
//	fbx_manager->SetIOSettings(FbxIOSettings::Create(fbx_manager, IOSROOT));
//
//	// �C���|�[�^�[�̐���
//	FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "");
//	// Importer�̏�����
//	bool import_status = fbx_importer->Initialize(filename.c_str());
//	_ASSERT_EXPR_A(import_status, fbx_importer->GetStatus().GetErrorString());
//
//	// �ǂݍ��܂ꂽ�t�@�C���ɂ���ĐV�����V�[����ݒ肷��B
//	FbxScene* fbx_scene = FbxScene::Create(fbx_manager, "");
//	// Scene�I�u�W�F�N�g��FBX�t�@�C�����̏��𗬂�����(���Ԃ�����)
//	import_status = fbx_importer->Import(fbx_scene);
//	_ASSERT_EXPR_A(import_status, fbx_importer->GetStatus().GetErrorString());
//
//	fbx_importer->Destroy();	// �V�[���𗬂����񂾂�Importer�͉������OK
//
//	// ���b�V��,NURBS,�p�b�`���O�p�`�ɕϊ�
//	fbxsdk::FbxGeometryConverter geometry_converter(fbx_manager);
//	geometry_converter.Triangulate(fbx_scene, /*replace*/true);
//
//	// ���f���f�[�^�̓ǂݍ���
//
//
//	/*std::ofstream ofs(cereal_filename.c_str(), std::ios::binary);
//	cereal::BinaryOutputArchive serialization(ofs);
//	serialization(scene_view, meshes, materials, animation_clips);*/
//}