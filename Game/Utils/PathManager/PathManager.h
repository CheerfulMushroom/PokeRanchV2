#ifndef GAME_PATH_MANAGER_H_
#define GAME_PATH_MANAGER_H_

#include <boost/filesystem.hpp>
#include <string>

class PathManager {
 public:
    PathManager();

    std::string getPokemonPath(const std::string &pokemonName, const std::string &animName) const;
    std::string getTrainerPath(const std::string &trainerName, const std::string &animName) const;
    std::string getStaticModelPath(const std::string &modelName) const;
    std::string getCommonPicturePath(const std::string &pictureName) const;

    std::tuple<std::string, std::string> getStaticModelShadersSources() const;
    std::tuple<std::string, std::string> getAnimModelShadersSources() const;

 private:
    std::string _pathToCommonPictures;
    std::string _pathToAllModels;

};




#endif  // GAME_PATH_MAHAGER_H_