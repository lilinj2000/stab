#ifndef STAB_CONFIG_HH
#define STAB_CONFIG_HH

#include <string>
#include <memory>
#include "soil/Config.hh"

namespace stab
{

namespace po = boost::program_options;

class StabOptions : public soil::Options
{
 public:

  StabOptions();
  
  virtual ~StabOptions();

  virtual po::options_description* configOptions();

  std::string instrument_id;
  double price;
  int volume;
  bool is_buy;

  int order_counter;
  int order_interval;

  std::string log_cfg;

  std::string timestamp_file;

 private:
  boost::program_options::options_description config_options_;
};

class StabConfig
{
 public:
  
  StabConfig(int argc=0, char* argv[]=NULL);
  ~StabConfig();

  StabOptions* stabOptions()
  {
    return stab_options_.get();
  }

  soil::Options* seaTraderOptions()
  {
    return sea_trader_options_.get();
  }

 private:
  std::unique_ptr<StabOptions> stab_options_;
  
  std::unique_ptr<soil::Options> sea_trader_options_;

};

}  


#endif 
