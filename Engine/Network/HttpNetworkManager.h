#ifndef NETWORK_HTTP_MANAGER_H_
#define NETWORK_HTTP_MANAGER_H_

#include <NetworkManager.h>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http/status.hpp>

using namespace boost::beast;
using boost::asio::ip::tcp;

class HttpNetworkManager : public NetworkManager {
 public:
    HttpNetworkManager(const std::string &addr, const std::string &port);
    ~HttpNetworkManager() = default;

    std::pair<http::status, std::string> get(const std::string &target, const std::string &queryString = ""); // return body of response
    std::pair<http::status, std::string> post(const std::string &target, std::map<std::string, std::string> &infoForSend); // return body of response

    std::map<std::string, std::string> jsonToMap(std::string &jsonBody);
    void mapToJson(std::map<std::string, std::string> &info, std::ostream &output, bool pretty);

 private:
    boost::asio::io_context _ioContext;
    tcp::resolver _resolver;
    boost::beast::tcp_stream _stream;

    // oriented to fixed server
    std::string _addr;
    std::string _port;
};

#endif  // NETWORK_HTTP_MANAGER_H_