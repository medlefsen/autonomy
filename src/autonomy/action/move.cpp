#include <autonomy/action/move.hpp>

BOOST_CLASS_EXPORT(autonomy::actor::move_direction);
BOOST_CLASS_EXPORT(autonomy::actor::move_direction_response);

namespace autonomy
{
    namespace actor
    {

        action_handler_generic * move_direction::default_handler() const
        {
            return new action_handler::move_direction_default;
        }

        action_handler_generic * move_direction_response::default_handler() const
        {
            return new action_handler::move_direction_response_default;
        }
    }
}
