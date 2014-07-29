#include <autonomy/action/unload.hpp>

BOOST_CLASS_EXPORT(autonomy::unload_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::unload_fuel_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::unload_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::action::unload);
BOOST_CLASS_EXPORT(autonomy::action::unload_fuel);
BOOST_CLASS_EXPORT(autonomy::action::unload_response);

namespace autonomy
{

    namespace action
    {

        action_handler_generic * unload::default_handler()
        {
            return new action_handler::unload_default;
        }

        action_handler_generic * unload_fuel::default_handler()
        {
            return new action_handler::unload_fuel_default;
        }

        action_handler_generic * unload_response::default_handler()
        {
            return new action_handler::unload_response_default;
        }
    }
}
