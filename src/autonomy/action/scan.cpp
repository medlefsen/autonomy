#include <autonomy/action/scan.hpp>

BOOST_CLASS_EXPORT(autonomy::scan_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::scan_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::actor::scan);
BOOST_CLASS_EXPORT(autonomy::actor::scan_response);

namespace autonomy
{

    namespace actor
    {
        action_handler_generic * scan::default_handler() const
        {
            return new action_handler::scan_default;
        }

        action_handler_generic * scan_response::default_handler() const
        {
            return new action_handler::scan_response_default;
        }
    }
}
