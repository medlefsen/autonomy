#ifndef AUTONOMY_ACTION_UNLOAD_FWD_HPP
#define AUTONOMY_ACTION_UNLOAD_FWD_HPP

#include <autonomy/action_handler.hpp>
#include <autonomy/entity/base_station.fwd.hpp>
#include <autonomy/entity/universe.fwd.hpp>
#include <autonomy/entity/scripted_drone.fwd.hpp>

namespace autonomy
{
    namespace actor
    {
        class unload;
        class unload_fuel;
        class unload_response;
    }

    typedef action_handler_base<actor::unload,entity::base_station>
        unload_handler_base_t;
    typedef action_handler_base<actor::unload_fuel,entity::universe>
        unload_fuel_handler_base_t;
    typedef action_handler_base<actor::unload_response,entity::scripted_drone>
        unload_response_handler_base_t;
}
#endif
