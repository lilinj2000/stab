// Copyright (c) 2010
// All rights reserved.

#include "Server.hh"
#include "soil/Log.hh"
#include "soil/STimer.hh"

namespace stab {

Server::Server(
    const rapidjson::Document& doc) {
  SOIL_FUNC_TRACE;

  options_.reset(new Options(doc));

  trader_service_.reset(
      sea::TraderService::create(doc, this));

  if (!options_->timestamp_file.empty()) {
    timestamp_file_.reset(
        new air::TimeStampDataFile(options_->timestamp_file));
  }
}

Server::~Server() {
  SOIL_FUNC_TRACE;
}

void Server::onOrderAccept(
    const std::string& theAccept) {
  SOIL_FUNC_TRACE;

  // STAB_INFO <<"client_order_token: " <<client_order_token
  //            <<"market_order_token: " <<market_order_token;

  // updateT1(client_order_token, market_order_token);
}

void Server::onOrderMarketAccept(
    const std::string& theAccept) {
  SOIL_FUNC_TRACE;

  // STAB_INFO <<"market_order_token: " <<market_order_token;

  // updateT2(market_order_token);
}

void Server::onOrderReject(
    const std::string& theReject) {
  SOIL_FUNC_TRACE;

  rapidjson::Document doc;
  if (doc.Parse(theReject).HasParseError()) {
    throw std::runtime_error(
        soil::json::get_parse_error(doc, theReject));
  }

  int clientOrderToken = -1;
  soil::json::get_item_value(
      &clientOrderToken,
      doc,
      "/EES_OrderRejectField/m_ClientOrderToken");

  updateT1(clientOrderToken);
}

void Server::onOrderMarketReject(
    const std::string& theReject) {
  SOIL_FUNC_TRACE;

  // STAB_INFO <<"market_order_token: " <<market_order_token;

  // updateT2(market_order_token);
}

void Server::run() {
  SOIL_FUNC_TRACE;

  int counter = 0;

  std::unique_ptr<soil::STimer> cond;
  cond.reset(soil::STimer::create());

  do {
    int clientOrderToken = -1;

    clientOrderToken = trader_service_->openBuyOrderFOK(
        options_->instru,
        options_->price,
        options_->volume);

    std::shared_ptr<air::TimeStampData>
        ts(new air::TimeStampData(clientOrderToken));
    records_[clientOrderToken] = ts;

    ++counter;

    if (options_->order_counter > 0
        && counter >= options_->order_counter)
      break;

    cond->wait(options_->order_interval);
  }while(true);

  cond->wait(1000);
}

void Server::updateT1(
    int client_order_token,
    int market_order_token) {
  SOIL_FUNC_TRACE;

  auto it = records_.find(client_order_token);

  if (it != records_.end()) {
    it->second->updateT1();
    timestamp_file_->putData(it->second);

    records_.erase(it);
  }

  // tokens_[market_order_token] = client_order_token;
}

void Server::updateT2(int market_order_token) {
  SOIL_FUNC_TRACE;

  auto it_token = tokens_.find(market_order_token);

  int client_order_token = -1;

  if (it_token != tokens_.end()) {
    client_order_token = it_token->second;

    tokens_.erase(it_token);
  } else {
    throw std::runtime_error("unexpected onOrderMarketAccept.");
  }

  auto it = records_.find(client_order_token);

  if (it != records_.end()) {
    it->second->updateT2();
    // timestamp_file_->putData(it->second);

    records_.erase(it);
  }
}

}  // namespace stab
