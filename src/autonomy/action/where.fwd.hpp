#ifndef AUTONOMY_ACTION_WHERE_FWD_HPP
#define AUTONOMY_ACTION_WHERE_FWD_HPP

#include <autonomy/action_handler.hpp>
#include <autonomy/entity/universe.fwd.hpp>
#include <autonomy/entity/scripted_drone.fwd.hpp>

namespace autonomy
{
    namespace action
    {
        class where;
        class where_response;
    }

    typedef action_handler_base<action::where, entity::universe>
        where_handler_base_t;
    typedef action_handler_base<action::where_response, entity::scripted_drone>
        where_response_handler_base_t;
}
#endif
