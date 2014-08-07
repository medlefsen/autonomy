#ifndef AUTONOMY_ACTION_CREATE_STATION_FWD_HPP
#define AUTONOMY_ACTION_CREATE_STATION_FWD_HPP

#include <autonomy/action_handler.hpp>
#include <autonomy/entity/universe.fwd.hpp>

namespace autonomy
{
    namespace actor
    {
        class create_station;
    }

    typedef action_handler_base<actor::create_station,entity::universe>
        create_station_handler_base_t;
}
#endif
