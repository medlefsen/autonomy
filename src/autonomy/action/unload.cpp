#include <autonomy/action/unload.hpp>

BOOST_CLASS_EXPORT(autonomy::unload_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::unload_fuel_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::unload_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::actor::unload);
BOOST_CLASS_EXPORT(autonomy::actor::unload_fuel);
BOOST_CLASS_EXPORT(autonomy::actor::unload_response);

namespace autonomy
{

    namespace actor
    {

        action_handler_generic * unload::default_handler() const
        {
            return new action_handler::unload_default;
        }

        action_handler_generic * unload_fuel::default_handler() const
        {
            return new action_handler::unload_fuel_default;
        }

        action_handler_generic * unload_response::default_handler() const
        {
            return new action_handler::unload_response_default;
        }
    }
}
