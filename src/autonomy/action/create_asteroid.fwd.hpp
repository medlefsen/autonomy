#ifndef AUTONOMY_ACTION_CREATE_ASTEROID_FWD_HPP
#define AUTONOMY_ACTION_CREATE_ASTEROID_FWD_HPP

#include <autonomy/action_handler.hpp>
#include <autonomy/entity/universe.fwd.hpp>
#include <autonomy/entity/drone.fwd.hpp>

namespace autonomy
{
    namespace action
    {
        class create_asteroid;
        class create_asteroid_response;
    }

    typedef action_handler_base<action::create_asteroid, entity::universe>
        create_asteroid_handler_base_t;

    typedef action_handler_base<action::create_asteroid_response, entity::drone>
        create_asteroid_response_handler_base_t;
}
#endif
