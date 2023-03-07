#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "../libs/httplib.h"
#include "domain.h"

int main() {
    {
        using namespace httplib;

        //httplib::Client cli("http://cpp-httplib-server.yhirose.repl.co");
        httplib::Client cli("https://cpp-httplib-server.yhirose.repl.co");

        auto res = cli.Get("/hi");
        std::cout << res->status << std::endl;
    }

    QueryBuilder builder{};
    try {
        std::cout << builder.getRawData() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}