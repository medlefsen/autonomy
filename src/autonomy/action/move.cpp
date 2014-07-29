#include <autonomy/action/move.hpp>

BOOST_CLASS_EXPORT(autonomy::action::move_direction);
BOOST_CLASS_EXPORT(autonomy::action::move_direction_response);

namespace autonomy
{
    namespace action
    {

        action_handler_generic * move_direction::default_handler()
        {
            return new action_handler::move_direction_default;
        }

        action_handler_generic * move_direction_response::default_handler()
        {
            return new action_handler::move_direction_response_default;
        }
    }
}
