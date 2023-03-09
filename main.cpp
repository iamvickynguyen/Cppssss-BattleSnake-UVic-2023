// HTTP credits: http://lcs.ios.ac.cn/~maxt/SPelton/reports/report-9aa0d3.html
// JSON credits: https://github.com/nlohmann/json
#include "./http_stuff.h"
#include "./json.hpp"
#include "./move.hpp"
#include <iostream>
using namespace std;
using namespace nlohmann;

void add_cors_headers(httplib::Response &res) {
  res.set_header("Allow", "GET, POST");
  res.set_header("Access-Control-Allow-Origin", "*");
  res.set_header("Access-Control-Allow-Methods", "GET, POST");
  res.set_header("Access-Control-ALlow-Headers", "Content-Type");
}

int main(void) {
  httplib::Server svr;
  svr.Options(".*", [](const auto &, auto &res) {
    res.set_content("ok", "text/plain");

    add_cors_headers(res);
  });
  svr.Get("/", [](const auto &, auto &res) {
    string head = "default";  // TODO: Change head
    string tail = "default";  // TODO: Change tail
    string author = "";       // TODO: Change your battlesnake username
    string color = "#888888"; // TODO: Change a hex color
    res.set_content("{\"apiversion\":\"1\", \"head\":\"" + head +
                        "\", \"tail\":\"" + tail + "\", \"color\":\"" + color +
                        "\", " + "\"author\":\"" + author + "\"}",
                    "application/json");

    add_cors_headers(res);
  });
  svr.Post("/end", [](const auto &, auto &res) {
    res.set_content("ok", "text/plain");

    add_cors_headers(res);
  });
  svr.Post("/start", [](const auto &, auto &res) {
    res.set_content("ok", "text/plain");

    add_cors_headers(res);
  });
  svr.Post("/move", [](auto &req, auto &res) {
    const json data = json::parse(req.body);
    cout << data;
    cout << "\n\n";
    // You can get the "you" property like this:
    // data["you"];
    // Almost alike python dictionary parsing, but with a semicolon at the end
    // of each line. You might need to make some structs to store some data in a
    // variable Example: you_struct you = data["you"];
    string moves[4] = {"up", "down", "left", "right"};
    // int index = rand() % 4;

    int index = cppssss::move(data);

    res.set_content("{\"move\": \"" + moves[index] + "\"}", "text/plain");

    add_cors_headers(res);
  });
  svr.listen("0.0.0.0", 8080);
  cout << "Server started";
}
