#ifndef AUTONOMY_ACTION_CREATE_DRONE_FWD_HPP
#define AUTONOMY_ACTION_CREATE_DRONE_FWD_HPP

#include <autonomy/action_handler.hpp>
#include <autonomy/universe.fwd.hpp>
#include <autonomy/standard/drone.fwd.hpp>

namespace autonomy { namespace standard
{
  class create_drone;
  class create_drone_response;

  typedef action_handler_base<create_drone,universe>
    create_drone_handler_base_t;

  typedef action_handler_base<create_drone_response,drone>
    create_drone_response_handler_base_t;
}}
#endif
