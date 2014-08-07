#ifndef AUTONOMY_ACTION_SCAN_FWD_HPP
#define AUTONOMY_ACTION_SCAN_FWD_HPP

#include <autonomy/action_handler.hpp>
#include <autonomy/entity/universe.fwd.hpp>
#include <autonomy/entity/scripted_drone.fwd.hpp>

namespace autonomy
{
    namespace actor
    {
        class scan;
        class scan_response;
    }

    typedef action_handler_base<actor::scan, entity::universe>
        scan_handler_base_t;
    typedef action_handler_base<actor::scan_response, entity::scripted_drone>
        scan_response_handler_base_t;
}
#endif
