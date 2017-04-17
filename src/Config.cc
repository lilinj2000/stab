// Copyright (c) 2010
// All rights reserved.

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

#include "Config.hh"
#include "Log.hh"
#include "sea/TraderService.hh"

namespace stab {

Options::Options():
    config_options_("StabConfigOptions") {
  namespace po = boost::program_options;

  config_options_.add_options()
      ("stab.instrument_id", po::value<std::string>(&instrument_id),
       "instrument id")
      ("stab.price", po::value<double>(&price),
       "price")
      ("stab.volume", po::value<int>(&volume),
       "volume")
      ("stab.is_buy", po::value<bool>(&is_buy),
       "is buy")
      ("stab.order_counter", po::value<int>(&order_counter),
       "order counter")
      ("stab.order_interval", po::value<int>(&order_interval),
       "order interval")
      ("stab.log_cfg", po::value<std::string>(&log_cfg),
       "log config file")
      ("stab.timestamp_file", po::value<std::string>(&timestamp_file),
       "timestamp file");
  return;
}

Options::~Options() {
}

po::options_description* Options::configOptions() {
  return &config_options_;
}

Config::Config(int argc, char* argv[]) {
  stab_options_.reset(new Options());
  sea_trader_options_.reset(sea::TraderService::createOptions());

  std::unique_ptr<soil::Config> config(soil::Config::create());
  config->registerOptions(stab_options_.get());
  config->registerOptions(sea_trader_options_.get());

  config->configFile() = "stab.cfg";
  config->loadConfig(argc, argv);

  // init the log
  STAB_LOG_INIT(stab_options_->log_cfg);

  return;
}

Config::~Config() {
}

}  // namespace stab
