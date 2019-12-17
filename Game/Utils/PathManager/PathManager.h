#ifndef GAME_PATH_MANAGER_H_
#define GAME_PATH_MANAGER_H_

#include <boost/filesystem.hpp>
#include <string>

class PathManager {
 public:
    PathManager();

    std::string getPokemonPath(const std::string &pokemonName, const std::string &animName);
    std::string getTrainerPath(const std::string &trainerName, const std::string &animName);
    std::string getStaticModelPath(const std::string &modelName);
    std::string getCommonPicturePath(const std::string &pictureName);

    std::tuple<std::string, std::string> getStaticModelShadersSources();
    std::tuple<std::string, std::string> getAnimModelShadersSources();

 private:
    std::string _pathToCommonPictures;
    std::string _pathToAllModels;

};




#endif  // GAME_PATH_MAHAGER_H_