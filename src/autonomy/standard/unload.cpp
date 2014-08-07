#include <autonomy/standard/unload.hpp>

BOOST_CLASS_EXPORT(autonomy::standard::unload_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::standard::unload_fuel_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::standard::unload_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::standard::unload);
BOOST_CLASS_EXPORT(autonomy::standard::unload_fuel);
BOOST_CLASS_EXPORT(autonomy::standard::unload_response);

namespace autonomy { namespace standard
{
  action_handler_generic * unload::default_handler() const
  {
    return new unload_default;
  }

  action_handler_generic * unload_fuel::default_handler() const
  {
    return new unload_fuel_default;
  }

  action_handler_generic * unload_response::default_handler() const
  {
    return new unload_response_default;
  }
}}
