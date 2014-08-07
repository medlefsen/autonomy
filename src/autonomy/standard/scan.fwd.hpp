#ifndef AUTONOMY_ACTION_SCAN_FWD_HPP
#define AUTONOMY_ACTION_SCAN_FWD_HPP

#include <autonomy/action_handler.hpp>
#include <autonomy/universe.fwd.hpp>
#include <autonomy/standard/scripted_drone.fwd.hpp>

namespace autonomy { namespace standard
{
  class scan;
  class scan_response;

  typedef action_handler_base<scan, universe>
    scan_handler_base_t;
  typedef action_handler_base<scan_response, scripted_drone>
    scan_response_handler_base_t;
}}
#endif
