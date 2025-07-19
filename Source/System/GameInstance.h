#pragma once

class GameInstance
{
public:
	// インスタンス取得
	static GameInstance& GetInstance()
	{
		return *instance;
	}

private:
	static GameInstance* instance;
};