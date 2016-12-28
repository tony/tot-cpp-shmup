/* Copyright 2016 Tony Narlock. All rights reserved. */
#ifndef SRC_STATS_H_
#define SRC_STATS_H_

#include <memory>
#include "ship.h"

class StatService {
 public:
  StatService() {}
  void set_ship_stats(const std::shared_ptr<ShipStats>& ship_stats) {
    ship = ship_stats;
  }
  std::shared_ptr<ShipStats> ship;
};
#endif  // SRC_STATS_H_
