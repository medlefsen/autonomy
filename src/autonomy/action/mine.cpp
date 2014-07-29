#include <autonomy/action/mine.hpp>

BOOST_CLASS_EXPORT(autonomy::mine_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::mine_location_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::mine_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::action::mine);
BOOST_CLASS_EXPORT(autonomy::action::mine_location);
BOOST_CLASS_EXPORT(autonomy::action::mine_response);

namespace autonomy
{

    namespace action
    {

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
