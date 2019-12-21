#include "Engine.h"
#include "AuthState.h"

int main() {
    auto engine = Engine();
    auto state = std::make_shared<AuthState>(&engine);
    engine.setState(std::move(state));
    engine.start();
}