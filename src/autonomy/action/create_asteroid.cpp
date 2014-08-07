#include <autonomy/action/create_asteroid.hpp>

BOOST_CLASS_EXPORT(autonomy::create_asteroid_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::create_asteroid_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::actor::create_asteroid);
BOOST_CLASS_EXPORT(autonomy::actor::create_asteroid_response);

namespace autonomy
{

    namespace actor
    {

        action_handler_generic * create_asteroid::default_handler() const
        {
            return new action_handler::create_asteroid_default;
        }

        action_handler_generic * create_asteroid_response::default_handler() const
        {
            return new action_handler::create_asteroid_response_default;
        }
    }
}
