#include <autonomy/action/unload.hpp>

namespace autonomy
{
    BOOST_CLASS_EXPORT(unload_handler_base_t);
    BOOST_CLASS_EXPORT(unload_fuel_handler_base_t);
    BOOST_CLASS_EXPORT(unload_response_handler_base_t);

    namespace action
    {
        BOOST_CLASS_EXPORT(unload);
        BOOST_CLASS_EXPORT(unload_fuel);
        BOOST_CLASS_EXPORT(unload_response);

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
