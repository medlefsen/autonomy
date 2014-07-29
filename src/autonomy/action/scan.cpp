#include <autonomy/action/scan.hpp>
namespace autonomy
{
    BOOST_CLASS_EXPORT(scan_handler_base_t);
    BOOST_CLASS_EXPORT(scan_response_handler_base_t);

    namespace action
    {
        BOOST_CLASS_EXPORT(scan);
        BOOST_CLASS_EXPORT(scan_response);

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
