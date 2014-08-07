#ifndef AUTONOMY_ACTION_CREATE_ASTEROID_FWD_HPP
#define AUTONOMY_ACTION_CREATE_ASTEROID_FWD_HPP

#include <autonomy/action_handler.hpp>
#include <autonomy/universe.fwd.hpp>
#include <autonomy/standard/drone.fwd.hpp>

namespace autonomy { namespace standard
{
  class create_asteroid;
  class create_asteroid_response;

  typedef action_handler_base<create_asteroid, universe>
    create_asteroid_handler_base_t;

  typedef action_handler_base<create_asteroid_response, drone>
    create_asteroid_response_handler_base_t;
}}
#endif
