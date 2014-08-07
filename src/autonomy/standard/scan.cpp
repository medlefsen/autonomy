#include <autonomy/standard/scan.hpp>

BOOST_CLASS_EXPORT(autonomy::standard::scan_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::standard::scan_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::standard::scan);
BOOST_CLASS_EXPORT(autonomy::standard::scan_response);

namespace autonomy { namespace standard
{
  action_handler_generic * scan::default_handler() const
  {
    return new scan_default;
  }

  action_handler_generic * scan_response::default_handler() const
  {
    return new scan_response_default;
  }
}}
