#ifndef AUTONOMY_ACTION_MINE_FWD_HPP
#define AUTONOMY_ACTION_MINE_FWD_HPP

#include <autonomy/action_handler.hpp>
#include <autonomy/standard/asteroid.fwd.hpp>
#include <autonomy/universe.fwd.hpp>
#include <autonomy/standard/scripted_drone.fwd.hpp>

namespace autonomy { namespace standard
{
  class mine;
  class mine_location;
  class mine_response;

  typedef action_handler_base<mine,asteroid>
    mine_handler_base_t;
  typedef action_handler_base<mine_location,universe>
    mine_location_handler_base_t;
  typedef action_handler_base<mine_response,scripted_drone>
    mine_response_handler_base_t;
}}
#endif
