#include "Engine.h"
#include "HomeState.h"

int main() {
    auto state = std::make_unique<HomeState>();
    auto engine = Engine(std::move(state));
    engine.start();
}