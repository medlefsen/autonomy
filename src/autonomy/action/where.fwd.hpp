#ifndef AUTONOMY_ACTION_WHERE_FWD_HPP
#define AUTONOMY_ACTION_WHERE_FWD_HPP

#include <autonomy/action_handler.hpp>
#include <autonomy/entity/universe.fwd.hpp>
#include <autonomy/entity/scripted_drone.fwd.hpp>

namespace autonomy
{
    namespace actor
    {
        class where;
        class where_response;
    }

    typedef action_handler_base<actor::where, entity::universe>
        where_handler_base_t;
    typedef action_handler_base<actor::where_response, entity::scripted_drone>
        where_response_handler_base_t;
}
#endif
