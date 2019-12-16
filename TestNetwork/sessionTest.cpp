#include <iostream>
#include <UserSession.h>

int main() {
    UserSession session;

    bool result = session.logIn("booooooom", "password11", "asdjh@");

    std::cout << (result ? "Success" : "Fail") << std::endl;
}