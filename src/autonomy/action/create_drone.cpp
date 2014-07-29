#include <autonomy/action/create_drone.hpp>

BOOST_CLASS_EXPORT(autonomy::create_drone_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::create_drone_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::action::create_drone);
BOOST_CLASS_EXPORT(autonomy::action::create_drone_response);

namespace autonomy
{

    namespace action
    {

        action_handler_generic * create_drone::default_handler()
        {
            return new action_handler::create_drone_default;
        }

        action_handler_generic * create_drone_response::default_handler()
        {
            return new action_handler::create_drone_response_default;
        }
    }
}
