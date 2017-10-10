// Copyright (c) 2010
// All rights reserved.

#ifndef STAB_SERVER_HH
#define STAB_SERVER_HH

#include <map>
#include <string>
#include "sea/TraderService.hh"
#include "Options.hh"
#include "air/TimeStampDataFile.hh"
#include "soil/json.hh"

namespace stab {

typedef std::map<int,
                 std::shared_ptr<air::TimeStampData> > TimeStampRecords;

typedef std::map<int, int> TokenRecords;

class Server :
      public sea::TraderCallback {
 public:
  explicit Server(
      const rapidjson::Document& doc);

  virtual ~Server();

  virtual void onOrderAccept(
      const std::string& theAccept);

  virtual void onOrderMarketAccept(
      const std::string& theAccept);

  virtual void onOrderReject(
      const std::string& theReject);

  virtual void onOrderMarketReject(
      const std::string& theReject);

  void run();

 protected:
  void updateT1(
      int client_order_token,
      int market_order_token = -1);

  void updateT2(int market_order_token);

 private:
  std::unique_ptr<Options> options_;

  std::unique_ptr<sea::TraderService> trader_service_;

  TimeStampRecords records_;

  std::unique_ptr<air::TimeStampDataFile> timestamp_file_;

  TokenRecords tokens_;
};

}  // namespace stab
#endif
