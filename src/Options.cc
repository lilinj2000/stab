// Copyright (c) 2010
// All rights reserved.

#include "Options.hh"

namespace stab {

using soil::json::get_item_value;

Options::Options(
    const rapidjson::Document& doc) {
  get_item_value(&instru, doc, "/stab/instru");
  get_item_value(&price, doc, "/stab/price");
  get_item_value(&volume, doc, "/stab/volume");
  get_item_value(&order_counter, doc, "/stab/order_counter");
  get_item_value(&order_interval, doc, "/stab/order_interval");
  get_item_value(&timestamp_file, doc, "/stab/timestamp_file");

  return;
}

}  // namespace stab
