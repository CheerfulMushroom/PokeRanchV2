#include <iostream>
#include <UserSession.h>
#include <PathManager.h>

int main() {
    UserSession session;
    PathManager pathManager;
    
    bool result = session.auth("booooooom", "password11");

    std::cout << session.getPokemonName() << '\n';
    std::cout << session.getTrainerName() << '\n';

    std::string pathToPoke = pathManager.getPokemonPath("Pikachu", "stay");

    std::cout << (result ? "Success" : "Fail") << std::endl;
}