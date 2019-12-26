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

std::string PathManager::getPicturePath(const std::string &pictureTitle) const {
    boost::filesystem::path resultPath(_pathToCommonPictures);

    resultPath /= pictureTitle;
    resultPath += ".png";

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

std::string PathManager::getStaticModelPath(const std::string &modelName) const {
    boost::filesystem::path resultPath(_pathToAllModels);
    resultPath /= "Static";

    resultPath /= modelName;
    // в данный момент у нас нет единства в плане формата моделей (присутствуют .dae, .obj, .mtl и другие),
    // переводить все модели в единый 3D формат сейчас затруднительно и времязатратно, поэтому остановимся на
    // костыле с перебором формата до нахождения существующего файла

    if (boost::filesystem::exists(resultPath.string() + ".dae")) {
        resultPath += ".dae";
    } else if (boost::filesystem::exists(resultPath.string() + ".obj")) {
        resultPath += ".obj";
    } else if (boost::filesystem::exists(resultPath.string() + ".mtl")) {
        resultPath += ".mtl";
    }


    return resultPath.string();
}




