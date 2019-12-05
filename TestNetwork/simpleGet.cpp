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

    infoForOutput.insert(std::make_pair("monkey", "6"));
    infoForOutput.insert(std::make_pair("zebra", "5"));
    infoForOutput.insert(std::make_pair("dog", "3"));
    infoForOutput.insert(std::make_pair("cat", "3"));
    infoForOutput.insert(std::make_pair("frog", "4"));

    netManager.mapToJson(infoForOutput, std::cout, true);

    HttpNetworkManager netPostManager("postman-echo.com", "80");
    netPostManager.post("/post", infoForOutput);

    return 0;
}