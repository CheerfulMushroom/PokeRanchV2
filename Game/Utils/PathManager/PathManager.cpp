#include "PathManager.h"

PathManager::PathManager() :
        _pathToCommonPictures("Game/Resources/Pictures/"),  // со слэшом или без ?
        _pathToAllModels("Game/Resources/Models/") {}

std::string PathManager::getPokemonPath(const std::string &pokemonName, const std::string &animName) const {
    boost::filesystem::path resultPath(_pathToAllModels);

    resultPath /= "Pokemons";
    resultPath /= pokemonName;
    resultPath /= animName;
    resultPath += ".dae";

    //TODO добавить проверки на сущестование файла и тому подобное

    return resultPath.string();
}

std::string PathManager::getTrainerPath(const std::string &trainerName, const std::string &animName) const {
    boost::filesystem::path resultPath(_pathToAllModels);

    resultPath /= "Trainers";
    resultPath /= trainerName;
    resultPath /= animName;
    resultPath += ".dae";

    // проверки

    return resultPath.string();
}




