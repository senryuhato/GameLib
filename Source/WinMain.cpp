#include "..\GameXLib\System\Classes\GameXLib.h"
#include "../GameXLib/System/Classes/ServiceLocator.h"
#include "../Source/GameFramework.h"

#pragma region C++/CLI Windows アプリケーションのエントリポイント
/// <summary>
/// C++/CLI での Windows アプリケーションのエントリポイント。
/// </summary>
/// <param name="hInstance">現在のインスタンスハンドル</param>
/// <param name="hPrevInstance">以前のインスタンスハンドル（常に NULL）</param>
/// <param name="lpCmdLine">コマンドライン引数</param>
/// <param name="nShowCmd">ウィンドウの表示状態</param>
/// <returns>プログラムの終了コード（通常は 0）</returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	GameXLib& gameXLib = GameXLib::GetInstance();
	// ゲームフレームワークの登録
	std::shared_ptr<GameFramework> framework = std::make_shared<GameFramework>();
	ServiceLocator::RegisterService<Framework>(framework);

	if (!gameXLib.Initialize(hInstance, nShowCmd, 1280, 720, L"ゲームプロジェクト"))
	{
		return -1;
	}
	gameXLib.Run();
	gameXLib.Uninitialize(hInstance);
	// 正常終了
	return 0;
}
#pragma endregion
