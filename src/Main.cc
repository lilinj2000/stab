#include <memory>
#include "StabConfig.hh"
#include "TraderServer.hh"

int main(int argc, char* argv[])
{

  std::unique_ptr<stab::StabConfig> config;
  config.reset(new stab::StabConfig(argc, argv));

  stab::StabOptions* stab_options = config->stabOptions();

  std::unique_ptr<stab::TraderServer> server;
  server.reset(new stab::TraderServer(stab_options, config->seaTraderOptions()));

  server->run();
  
  return 0;
}
