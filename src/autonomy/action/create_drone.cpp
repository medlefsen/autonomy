#include <autonomy/action/create_drone.hpp>

BOOST_CLASS_EXPORT(autonomy::create_drone_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::create_drone_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::actor::create_drone);
BOOST_CLASS_EXPORT(autonomy::actor::create_drone_response);

namespace autonomy
{

    namespace actor
    {

        action_handler_generic * create_drone::default_handler() const
        {
            return new action_handler::create_drone_default;
        }

        action_handler_generic * create_drone_response::default_handler() const
        {
            return new action_handler::create_drone_response_default;
        }
    }
}
