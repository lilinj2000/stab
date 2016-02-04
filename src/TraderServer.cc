#include "TraderServer.hh"
#include "StabLog.hh"

#include "soil/STimer.hh"

namespace stab
{

TraderServer::TraderServer(StabOptions* stab_options, soil::Options* trader_options):
    stab_options_(stab_options)
{
  STAB_TRACE <<"TraderServer::TraderServer()";

  trader_service_.reset( sea::TraderService::createService(trader_options, this) );

  if( !stab_options->timestamp_file.empty() )
    timestamp_file_.reset( new air::TimeStampDataFile(stab_options->timestamp_file) );

}

TraderServer::~TraderServer()
{
  STAB_TRACE <<"TraderServer::~TraderServer()";
}

void TraderServer::onOrderAccept(int client_order_token, int market_order_token)
{
  STAB_TRACE <<"TraderServer::onOrderAccept()";

  STAB_INFO <<"client_order_token: " <<client_order_token
             <<"market_order_token: " <<market_order_token;

  updateT1( client_order_token, market_order_token );
  
  
}
  
void TraderServer::onOrderMarketAccept(int market_order_token)
{
  STAB_TRACE <<"TraderServer::onOrderMarketAccept()";

  STAB_INFO <<"market_order_token: " <<market_order_token;

  updateT2( market_order_token );

}


void TraderServer::onOrderReject(int client_order_token)
{
  STAB_TRACE <<"TraderServer::onOrderReject()";

  STAB_INFO <<"client_order_token: " <<client_order_token;
}

void TraderServer::onOrderMarketReject(int market_order_token)
{
  STAB_TRACE <<"TraderServer::onOrderMarketReject()";

  STAB_INFO <<"market_order_token: " <<market_order_token;

  updateT2( market_order_token );
}

void TraderServer::onOrderExecution(int client_order_token,
                              int market_order_token,
                              unsigned int quntity,
                              double price)
{
  STAB_TRACE <<"TraderServer::onOrderExecution()";

  STAB_INFO <<"client_order_token: " <<client_order_token
            <<" market_order_token: " <<market_order_token
            <<" quntity: " <<quntity
            <<" price: " <<price;
}

void TraderServer::onOrderCxled(int client_order_token,
                          int market_order_token,
                          unsigned int quntity)
{
  STAB_TRACE <<"TraderServer::onOrderCxled()";

  STAB_INFO <<"client_order_token: " <<client_order_token
            <<" market_order_token: " <<market_order_token
            <<" quntity: " <<quntity;
}

void TraderServer::onCxlOrderReject(int market_order_token)
{
  STAB_TRACE <<"TraderServer::onCxlOrderReject()";

  STAB_INFO <<"market_order_token: " <<market_order_token;
}

void TraderServer::run()
{
  STAB_TRACE <<"TraderServer::run()";

  int counter = 0;

  std::unique_ptr<soil::STimer> cond;
  cond.reset( soil::STimer::create() );

  do
  {
    int order_ref = -1;

    if( stab_options_->is_buy )
    {
      order_ref = trader_service_->orderOpenBuyFOK(
          stab_options_->instrument_id,
          stab_options_->price,
          stab_options_->volume);

      
    }
    else
    {
      order_ref = trader_service_->orderOpenSellFOK(
          stab_options_->instrument_id,
          stab_options_->price,
          stab_options_->volume);
    }

    records_[order_ref] = new air::TimeStampData(order_ref);
    
    ++counter;

    if( stab_options_->order_counter>0 && counter>=stab_options_->order_counter )
      break;
      
    cond->wait(stab_options_->order_interval);
      
  }while(true);

  cond->wait(1000);
}

void TraderServer::updateT1(int client_order_token, int market_order_token)
{
  STAB_TRACE <<"TraderServer::updateT1()";

  auto it = records_.find(client_order_token);

  if( it!=records_.end() )
    it->second->updateT1();

  tokens_[market_order_token] = client_order_token;
}

void TraderServer::updateT2(int market_order_token)
{
  STAB_TRACE <<"TraderServer::updateT2()";

  auto it_token = tokens_.find(market_order_token);

  int client_order_token = -1;
  
  if( it_token!=tokens_.end() )
  {
    client_order_token = it_token->second;

    tokens_.erase( it_token );
  }
  else
  {
    throw std::runtime_error("unexpected onOrderMarketAccept.");
  }
  
  auto it = records_.find(client_order_token);

  if( it!=records_.end() )
  {
    it->second->updateT2();
    timestamp_file_->putData( it->second );

    records_.erase( it );
  }

}

};
