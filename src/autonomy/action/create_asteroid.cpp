#include <autonomy/action/create_asteroid.hpp>
namespace autonomy
{
    BOOST_CLASS_EXPORT(create_asteroid_handler_base_t);
    BOOST_CLASS_EXPORT(create_asteroid_response_handler_base_t);

    namespace action
    {
        BOOST_CLASS_EXPORT(create_asteroid);
        BOOST_CLASS_EXPORT(create_asteroid_response);

        action_handler_generic * create_asteroid::default_handler()
        {
            return new action_handler::create_asteroid_default;
        }

        action_handler_generic * create_asteroid_response::default_handler()
        {
            return new action_handler::create_asteroid_response_default;
        }
    }
}
