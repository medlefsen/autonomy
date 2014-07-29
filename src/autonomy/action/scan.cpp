#include <autonomy/action/scan.hpp>

BOOST_CLASS_EXPORT(autonomy::scan_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::scan_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::action::scan);
BOOST_CLASS_EXPORT(autonomy::action::scan_response);

namespace autonomy
{

    namespace action
    {
        action_handler_generic * scan::default_handler()
        {
            return new action_handler::scan_default;
        }

        action_handler_generic * scan_response::default_handler()
        {
            return new action_handler::scan_response_default;
        }
    }
}
