#ifndef STAB_TRADER_SERVER_HH
#define STAB_TRADER_SERVER_HH

#include "sea/TraderService.hh"
#include "StabConfig.hh"
#include "air/TimeStampDataFile.hh"

namespace stab
{

typedef std::map<int, air::TimeStampData*> TimeStampRecords;

typedef std::map<int, int> TokenRecords;

class TraderServer : public sea::TraderServiceCallback
{
 public:
  TraderServer(StabOptions* stab_options, soil::Options* trader_options);
               
  virtual ~TraderServer();

  virtual void onOrderAccept(int client_order_token, int market_order_token) ;
  
  virtual void onOrderMarketAccept(int market_order_token) ;

  virtual void onOrderReject(int client_order_token) ;

  virtual void onOrderMarketReject(int market_order_token) ;

  virtual void onOrderExecution(int client_order_token,
                                int market_order_token,
                                unsigned int quntity,
                                double price) ;

  virtual void onOrderCxled(int client_order_token,
                            int market_order_token,
                            unsigned int quntity) ;

  virtual void onCxlOrderReject(int market_order_token) ;

  void run();

 protected:

  void updateT1(int client_order_token, int market_order_token);

  void updateT2(int market_order_token);
  
 private:

  StabOptions* stab_options_;
  
  std::unique_ptr<sea::TraderService> trader_service_;

  TimeStampRecords records_;

  std::unique_ptr<air::TimeStampDataFile> timestamp_file_;

  TokenRecords tokens_;
};

};

#endif
