#ifndef POKERANCHV2_HOMESTATE_H
#define POKERANCHV2_HOMESTATE_H

#include <memory>
#include "GameState.h"
#include "ServerAPI.h"
#include "Pokemon.h"

class Engine;

class HomeState : public GameState {
public:
    explicit HomeState(Engine *parentEngine);
    void saveProgress(const std::shared_ptr<Pokemon>& pokemon);

private:
    ServerAPI _api;
};

#endif //POKERANCHV2_HOMESTATE_H
