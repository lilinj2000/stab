// Copyright (c) 2010
// All rights reserved.

#ifndef STAB_OPTIONS_HH
#define STAB_OPTIONS_HH

#include <string>
#include "soil/json.hh"

namespace stab {

class Options {
 public:
  Options(
      const rapidjson::Document& doc);

  std::string instru;
  double price;
  int volume;

  int order_counter;
  int order_interval;

  std::string timestamp_file;
};

}  // namespace stab

#endif
