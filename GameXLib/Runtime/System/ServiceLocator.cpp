#include "ServiceLocator.h"

// クラス外部で定義
std::unordered_map<std::string, std::shared_ptr<void>> ServiceLocator::services;