#ifndef AUTONOMY_ACTION_WHERE_FWD_HPP
#define AUTONOMY_ACTION_WHERE_FWD_HPP

#include <autonomy/action_handler.hpp>
#include <autonomy/universe.fwd.hpp>
#include <autonomy/standard/scripted_drone.fwd.hpp>

namespace autonomy { namespace standard
{
  class where;
  class where_response;

  typedef action_handler_base<where, universe>
    where_handler_base_t;
  typedef action_handler_base<where_response, scripted_drone>
    where_response_handler_base_t;
}}
#endif
