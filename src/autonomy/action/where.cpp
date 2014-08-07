#include <autonomy/action/where.hpp>

BOOST_CLASS_EXPORT(autonomy::where_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::where_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::actor::where);
BOOST_CLASS_EXPORT(autonomy::actor::where_response);

namespace autonomy
{

    namespace actor
    {
        action_handler_generic * where::default_handler() const
        {
            return new action_handler::where_default;
        }

        action_handler_generic * where_response::default_handler() const
        {
            return new action_handler::where_response_default;
        }
    }
}
