#include "Engine.h"
#include "AuthState.h"
<<<<<<< HEAD
#include "HomeState.h"
=======
>>>>>>> 995b53d2eb7d35290f9e8d15619421eed58bcd92
#include "SelectionState.h"

int main() {
    auto engine = Engine();
    auto state = std::make_shared<AuthState>(&engine);
    engine.setState(std::move(state));
    engine.start();
}