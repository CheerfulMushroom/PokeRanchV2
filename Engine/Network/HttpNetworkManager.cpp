#include <HttpNetworkManager.h>
#include <boost/beast/version.hpp>
#include <boost/beast/http.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

HttpNetworkManager::HttpNetworkManager(const std::string &addr, const std::string &port) :
    _resolver(_ioContext),
    _stream(_ioContext),
    _addr(addr),
    _port(port) {
}

//HttpNetworkManager::~HttpNetworkManager() {}

std::pair<http::status, std::string> HttpNetworkManager::get(const std::string &target, const std::string &queryString) {
    // Open socket
    tcp::resolver::results_type endpoints = _resolver.resolve(_addr, _port);
    _stream.connect(endpoints);

    std::string targetWithQuery = target;

    // отсюда тестим
    if (!queryString.empty()) {
        targetWithQuery += '?';
        targetWithQuery += queryString;
    }

    http::request<http::string_body> request(http::verb::get, targetWithQuery, 11);
    request.set(http::field::host, _addr);
    request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    http::write(_stream, request);

    boost::beast::flat_buffer buffer;
    http::response<http::string_body> response;

    http::read(_stream, buffer, response);

    // Close socket
    boost::beast::error_code errorCode;
    _stream.socket().shutdown(tcp::socket::shutdown_both, errorCode);

    return std::make_pair(response.result(), response.body());
}

std::pair<http::status, std::string> HttpNetworkManager::post(const std::string &target, std::map<std::string, std::string> &infoForSend) {
    // Open socket
    tcp::resolver::results_type endpoints = _resolver.resolve(_addr, _port);
    _stream.connect(endpoints);

    http::request<http::string_body> request(http::verb::post, target, 11);
    request.set(http::field::host, _addr);
    request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    std::stringstream jsonStream;
    mapToJson(infoForSend, jsonStream, false);

    request.set(http::field::content_type, "text/plain");
    request.set(http::field::content_length, jsonStream.str().length());;
    request.body() = jsonStream.str();

    std::cout << request << std::endl;

    http::write(_stream, request);

    boost::beast::flat_buffer buffer;
    http::response<http::string_body> response;

    http::read(_stream, buffer, response);

    // Close socket
    boost::beast::error_code errorCode;
    _stream.socket().shutdown(tcp::socket::shutdown_both, errorCode);

    return std::make_pair(response.result(), response.body());
}

std::map<std::string, std::string> HttpNetworkManager::jsonToMap(std::string &jsonBody) {
    std::stringstream jsonStream(jsonBody);
    std::map<std::string, std::string> encodedInfo;

    boost::property_tree::ptree root;
    boost::property_tree::read_json(jsonStream, root);

    // depend of json document structure
    // now for (key : value), where value is simple var
    for (auto &node : root.get_child("")) {
        encodedInfo.insert(std::make_pair(node.first, node.second.data()));
    }

    return std::move(encodedInfo);
}

void HttpNetworkManager::mapToJson(std::map<std::string, std::string> &info, std::ostream &output, bool pretty) {
    boost::property_tree::ptree root;

    // depend of json document structure
    // now for (key : value), where value is simple var

    for (auto &x : info) {
        root.put(x.first, x.second);
    }

    boost::property_tree::write_json(output, root, pretty);
}


