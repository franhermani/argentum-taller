#include "manager.h"

GameManager::GameManager(FileParser& file_parser) : fileParser(file_parser),
params(fileParser.getGameParams()) {}
