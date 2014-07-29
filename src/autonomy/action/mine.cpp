#include <autonomy/action/mine.hpp>

namespace autonomy
{
    BOOST_CLASS_EXPORT(mine_handler_base_t);
    BOOST_CLASS_EXPORT(mine_location_handler_base_t);
    BOOST_CLASS_EXPORT(mine_response_handler_base_t);

    namespace action
    {
        BOOST_CLASS_EXPORT(mine);
        BOOST_CLASS_EXPORT(mine_location);
        BOOST_CLASS_EXPORT(mine_response);

        action_handler_generic * mine::default_handler()
        {
            return new action_handler::mine_default;
        }

        action_handler_generic * mine_location::default_handler()
        {
            return new action_handler::mine_location_default;
        }

        action_handler_generic * mine_response::default_handler()
        {
            return new action_handler::mine_response_default;
        }
    }
}
