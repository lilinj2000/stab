// Copyright (c) 2010
// All rights reserved.

#ifndef STAB_SERVER_HH
#define STAB_SERVER_HH

#include <map>
#include "sea/TraderService.hh"
#include "Config.hh"
#include "air/TimeStampDataFile.hh"

namespace stab {

typedef std::map<int, air::TimeStampData*> TimeStampRecords;

typedef std::map<int, int> TokenRecords;

class Server : public sea::TraderServiceCallback {
 public:
  Server(Options* stab_options, soil::Options* trader_options);

  virtual ~Server();

  virtual void onOrderAccept(int client_order_token, int market_order_token);

  virtual void onOrderMarketAccept(int market_order_token);

  virtual void onOrderReject(int client_order_token);

  virtual void onOrderMarketReject(int market_order_token);

  virtual void onOrderExecution(int client_order_token,
                                int market_order_token,
                                unsigned int quntity,
                                double price);

  virtual void onOrderCxled(int client_order_token,
                            int market_order_token,
                            unsigned int quntity);

  virtual void onCxlOrderReject(int market_order_token);

  void run();

 protected:
  void updateT1(int client_order_token, int market_order_token);

  void updateT2(int market_order_token);

 private:
  Options* stab_options_;

  std::unique_ptr<sea::TraderService> trader_service_;

  TimeStampRecords records_;

  std::unique_ptr<air::TimeStampDataFile> timestamp_file_;

  TokenRecords tokens_;
};

}  // namespace stab
#endif
