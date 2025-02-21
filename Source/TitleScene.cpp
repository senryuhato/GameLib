#include <windows.h>
#include "TitleScene.h"

#pragma region 更新処理
/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update()
{
	if (GetAsyncKeyState('1') & 1)
	{
		int a = 0;
		a++;
	}
}
#pragma endregion
