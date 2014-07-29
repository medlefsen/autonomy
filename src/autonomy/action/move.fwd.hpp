#ifndef AUTONOMY_ACTION_MOVE_FWD_HPP
#define AUTONOMY_ACTION_MOVE_FWD_HPP
#include <autonomy/action_handler.hpp>
#include <autonomy/entity/universe.fwd.hpp>
#include <autonomy/entity/drone.fwd.hpp>
#include <autonomy/entity/scripted_drone.fwd.hpp>
namespace autonomy
{
    namespace action
    {
        class move_direction;
        class move_direction_response;
    }

    typedef action_handler_base<action::move_direction, entity::universe>
        move_direction_handler_base_t;
    typedef action_handler_base<action::move_direction_response, entity::scripted_drone>
        move_direction_response_handler_base_t;
}
#endif
