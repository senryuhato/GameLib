#include "../Classes/SystemServiceLocator.h"

// �N���X�O���Œ�`
std::unordered_map<std::type_index, std::shared_ptr<void>> SystemServiceLocator::services;