#include "Engine.h"
#include "AuthState.h"
#include "HomeState.h"
#include "SelectionState.h"

int main() {
    auto engine = Engine();
    auto state = std::make_shared<SelectionState>(&engine);
    engine.setState(std::move(state));
    engine.start();
}