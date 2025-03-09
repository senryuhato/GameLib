//#pragma once
//#define USE_IMGUI
//#include <fbxsdk.h>
//#include <DirectXMath.h>
//
//// AttributeType
////enum EType
////{
////	eUnknown,
////	eNull,
////	eMarker,
////	eSkeleton,
////	eMesh,
////	eNurbs,
////	ePatch,
////	eCamera,
////	eCameraStereo,
////	eCameraSwitcher,
////	eLight,
////	eOpticalReference,
////	eOpticalMarker,
////	eNurbsCurve,
////	eTrimNurbsSurface,
////	eBoundary,
////	eNurbsSurface,
////	eShape,
////	eLODGroup,
////	eSubDiv,
////	eCachedEffect,
////	eLine
////};
//
////************************************************
//
//// Fbx->XMFloat•ÏŠ·
//inline DirectX::XMFLOAT4X4 ToXMFloat4x4(const FbxAMatrix& fbxamatrix)
//{
//	DirectX::XMFLOAT4X4 xmfloat4x4;
//	for (int row = 0; row < 4; row++)
//	{
//		for (int column = 0; column < 4; column++)
//		{
//			xmfloat4x4.m[row][column] = static_cast<float>(fbxamatrix[row][column]);
//		}
//	}
//	return xmfloat4x4;
//}
//
//// Fbx->XMFloat•ÏŠ·
//inline DirectX::XMFLOAT3 ToXMFloat3(const FbxDouble3& fbxdouble3)
//{
//	DirectX::XMFLOAT3 xmfloat3;
//	xmfloat3.x = static_cast<float>(fbxdouble3[0]);
//	xmfloat3.y = static_cast<float>(fbxdouble3[1]);
//	xmfloat3.z = static_cast<float>(fbxdouble3[2]);
//	return xmfloat3;
//}
//
//// Fbx->XMFloat•ÏŠ·
//inline DirectX::XMFLOAT4 ToXMFloat4(const FbxDouble4& fbxdouble4)
//{
//	DirectX::XMFLOAT4 xmfloat4;
//	xmfloat4.x = static_cast<float>(fbxdouble4[0]);
//	xmfloat4.y = static_cast<float>(fbxdouble4[1]);
//	xmfloat4.z = static_cast<float>(fbxdouble4[2]);
//	xmfloat4.w = static_cast<float>(fbxdouble4[3]);
//	return xmfloat4;
//}