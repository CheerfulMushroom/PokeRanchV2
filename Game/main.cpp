#include "BaseClasses/include/Engine.h"
#include "States/include/AuthState.h"

int main() {
    auto state = std::make_unique<AuthState>();
    auto engine = Engine(std::move(state));
    engine.start();
}