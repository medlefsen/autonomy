#include <autonomy/action/where.hpp>

namespace autonomy
{
    BOOST_CLASS_EXPORT(where_handler_base_t);
    BOOST_CLASS_EXPORT(where_response_handler_base_t);

    namespace action
    {
        BOOST_CLASS_EXPORT(where);
        BOOST_CLASS_EXPORT(where_response);

        action_handler_generic * where::default_handler()
        {
            return new action_handler::where_default;
        }

        action_handler_generic * where_response::default_handler()
        {
            return new action_handler::where_response_default;
        }
    }
}
