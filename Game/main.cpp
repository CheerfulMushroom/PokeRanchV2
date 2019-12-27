#include "Engine.h"
#include "AuthState.h"

int main() {
    auto engine = Engine(1366, 768);
    auto state = std::make_shared<AuthState>(&engine);
    engine.setState(std::move(state));
    engine.start();
}