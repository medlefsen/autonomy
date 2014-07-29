#include <autonomy/action/create_drone.hpp>
namespace autonomy
{
    BOOST_CLASS_EXPORT(create_drone_handler_base_t);
    BOOST_CLASS_EXPORT(create_drone_response_handler_base_t);

    namespace action
    {
        BOOST_CLASS_EXPORT(create_drone);
        BOOST_CLASS_EXPORT(create_drone_response);

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
