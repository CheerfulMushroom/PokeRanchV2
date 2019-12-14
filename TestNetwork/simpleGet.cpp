#include <iostream>
#include <HttpNetworkManager.h>

int main() {
    HttpNetworkManager netManager("jsonplaceholder.typicode.com", "80");

    std::string jsonBody = netManager.get("/todos/1");
    std::map<std::string, std::string> info = netManager.jsonToMap(jsonBody);

    for (auto &x : info) {
        std::cout << std::get<0>(x) << ' ' << std::get<1>(x) << '\n';
    }

    std::map<std::string, std::string> infoForOutput;

    std::cout << '\n';

    infoForOutput.insert(std::make_pair("login", "booooooom"));
    infoForOutput.insert(std::make_pair("password", "password11"));
    infoForOutput.insert(std::make_pair("mail", "asdjh@"));

    netManager.mapToJson(infoForOutput, std::cout, true);

    HttpNetworkManager netPostManager("0.0.0.0", "8888");
    netPostManager.post("/auth", infoForOutput);

    return 0;
}