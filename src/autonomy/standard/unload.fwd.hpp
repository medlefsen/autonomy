#ifndef AUTONOMY_ACTION_UNLOAD_FWD_HPP
#define AUTONOMY_ACTION_UNLOAD_FWD_HPP

#include <autonomy/action_handler.hpp>
#include <autonomy/standard/base_station.fwd.hpp>
#include <autonomy/universe.fwd.hpp>
#include <autonomy/standard/scripted_drone.fwd.hpp>

namespace autonomy { namespace standard
{
  class unload;
  class unload_fuel;
  class unload_response;

  typedef action_handler_base<unload,base_station>
    unload_handler_base_t;
  typedef action_handler_base<unload_fuel,universe>
    unload_fuel_handler_base_t;
  typedef action_handler_base<unload_response,scripted_drone>
    unload_response_handler_base_t;
}}
#endif
