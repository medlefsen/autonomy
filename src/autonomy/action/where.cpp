#include <autonomy/action/where.hpp>

BOOST_CLASS_EXPORT(autonomy::where_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::where_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::action::where);
BOOST_CLASS_EXPORT(autonomy::action::where_response);

namespace autonomy
{

    namespace action
    {
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
