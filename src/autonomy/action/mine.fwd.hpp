#ifndef AUTONOMY_ACTION_MINE_FWD_HPP
#define AUTONOMY_ACTION_MINE_FWD_HPP

#include <autonomy/action_handler.hpp>
#include <autonomy/entity/asteroid.fwd.hpp>
#include <autonomy/entity/universe.fwd.hpp>
#include <autonomy/entity/scripted_drone.fwd.hpp>

namespace autonomy
{
    namespace action
    {
        class mine;
        class mine_location;
        class mine_response;
    }

    typedef action_handler_base<action::mine,entity::asteroid>
        mine_handler_base_t;
    typedef action_handler_base<action::mine_location,entity::universe>
        mine_location_handler_base_t;
    typedef action_handler_base<action::mine_response,entity::scripted_drone>
        mine_response_handler_base_t;
}
#endif
