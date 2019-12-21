#include "ModelSwitcher.h"
#include "PathManager.h"

template <class ModelType>
ModelSwitcher<ModelType>::ModelSwitcher(GameState &state,
                             std::vector<std::string> &modelNames,
                             Camera *camera,
                             glm::vec3 translate,
                             float scale,
                             glm::vec3 angles,
                             int width,
                             int height,
                             std::string type,
                             std::string animationName) : _state(state), _modelNames(modelNames),
                                           _camera(camera), _translate(translate),
                                           _scale(scale), _angles(angles),
                                           _width(width), _height(height),
                                           _id(0), _type(type), _animationName(animationName) {

    std::string initModelPath = {};
    if (_type == "pokemon") {
        initModelPath = _pathManager.getPokemonPath(_modelNames[_id], _animationName);
    } else if (_type == "trainer") {
        initModelPath = _pathManager.getTrainerPath(_modelNames[_id], _animationName);
    }


    auto model = std::make_shared<ModelType>(initModelPath,
                        camera,
                        _translate,
                        _scale,
                        _angles,
                        _width,
                        _height,
                        modelNames[_id]);

    model->addMeta("modelToDelete", "true");
    state.addElement(std::move(model));

}

template <class ModelType>
void ModelSwitcher<ModelType>::switchToRight() {
    _id = (_id - 1);

    if (_id < 0) {
        _id = _id + _modelNames.size();
    }

    _state.deleteElement([](GameElement *el) {
        return el->getMeta("modelToDelete") == "true";
    });


    std::string initModelPath = {};
    if (_type == "pokemon") {
        initModelPath = _pathManager.getPokemonPath(_modelNames[_id], _animationName);
    } else if (_type == "trainer") {
        initModelPath = _pathManager.getTrainerPath(_modelNames[_id], _animationName);
    }

    auto newModel = std::make_shared<ModelType>(initModelPath,
                                                _camera,
                                                _translate,
                                                _scale,
                                                _angles,
                                                _width,
                                                _height,
                                                _modelNames[_id]);

    newModel->addMeta("modelToDelete", "true");
    _state.addElement(std::move(newModel));

}

template <class ModelType>
void ModelSwitcher<ModelType>::switchToLeft() {
    _id = (_id + 1) % _modelNames.size();

    _state.deleteElement([](GameElement *el) {
        return el->getMeta("modelToDelete") == "true";
    });

    std::string initModelPath = {};
    if (_type == "pokemon") {
        initModelPath = _pathManager.getPokemonPath(_modelNames[_id], _animationName);
    } else if (_type == "trainer") {
        initModelPath = _pathManager.getTrainerPath(_modelNames[_id], _animationName);
    }

    auto newModel = std::make_shared<ModelType>(initModelPath,
                                                _camera,
                                                _translate,
                                                _scale,
                                                _angles,
                                                _width,
                                                _height,
                                                _modelNames[_id]);

    newModel->addMeta("modelToDelete", "true");
    _state.addElement(std::move(newModel));
}

template <class ModelType>
std::string ModelSwitcher<ModelType>::returnCurrentModelName() {
    return _modelNames[_id];
}