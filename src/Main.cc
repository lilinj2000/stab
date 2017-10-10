// Copyright (c) 2010
// All rights reserved.

#include <memory>
#include "Server.hh"
#include "soil/Log.hh"

int main(int argc, char* argv[]) {
  std::string config_file = "stab.json";
  rapidjson::Document doc;
  soil::json::load_from_file(&doc, config_file);
  soil::log::init(doc);

  try {
    std::unique_ptr<stab::Server> server;
    server.reset(new stab::Server(doc));

    server->run();
  } catch (std::exception& e) {
    SOIL_ERROR("Error: {}", e.what());
  }

  return 0;
}
