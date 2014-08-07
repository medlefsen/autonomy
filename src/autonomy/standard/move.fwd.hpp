#ifndef AUTONOMY_ACTION_MOVE_FWD_HPP
#define AUTONOMY_ACTION_MOVE_FWD_HPP
#include <autonomy/action_handler.hpp>
#include <autonomy/universe.fwd.hpp>
#include <autonomy/standard/drone.fwd.hpp>
#include <autonomy/standard/scripted_drone.fwd.hpp>
namespace autonomy { namespace standard
{
  class move_direction;
  class move_direction_response;

  typedef action_handler_base<move_direction, universe>
    move_direction_handler_base_t;
  typedef action_handler_base<move_direction_response, scripted_drone>
    move_direction_response_handler_base_t;
}}
#endif
