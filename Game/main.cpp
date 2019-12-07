#include "Engine.h"
#include "HomeState.h"

int main() {
    auto engine = Engine();
    auto state = std::make_unique<HomeState>(&engine);
    engine.setState(std::move(state));
    engine.start();
}