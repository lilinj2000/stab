// Copyright (c) 2010
// All rights reserved.

#include <memory>
#include "Config.hh"
#include "Server.hh"

int main(int argc, char* argv[]) {
  std::unique_ptr<stab::Config> config;
  config.reset(new stab::Config(argc, argv));

  stab::Options* stab_options = config->stabOptions();

  std::unique_ptr<stab::Server> server;
  server.reset(new stab::Server(stab_options, config->seaTraderOptions()));

  server->run();

  return 0;
}
