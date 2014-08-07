#include <autonomy/standard/where.hpp>

BOOST_CLASS_EXPORT(autonomy::standard::where_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::standard::where_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::standard::where);
BOOST_CLASS_EXPORT(autonomy::standard::where_response);

namespace autonomy { namespace standard
{
  action_handler_generic * where::default_handler() const
  {
    return new where_default;
  }

  action_handler_generic * where_response::default_handler() const
  {
    return new where_response_default;
  }
}}
