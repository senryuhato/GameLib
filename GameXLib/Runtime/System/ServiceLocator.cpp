#include "ServiceLocator.h"

// �N���X�O���Œ�`
std::unordered_map<std::string, std::shared_ptr<void>> ServiceLocator::services;