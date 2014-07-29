#include <autonomy/action/move.hpp>
namespace autonomy
{
    namespace action
    {
        BOOST_CLASS_EXPORT(move_direction);
        BOOST_CLASS_EXPORT(move_direction_response);

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
