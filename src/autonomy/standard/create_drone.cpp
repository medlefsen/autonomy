#include <autonomy/standard/create_drone.hpp>

BOOST_CLASS_EXPORT(autonomy::standard::create_drone_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::standard::create_drone_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::standard::create_drone);
BOOST_CLASS_EXPORT(autonomy::standard::create_drone_response);

namespace autonomy { namespace standard
{
  action_handler_generic * create_drone::default_handler() const
  {
    return new create_drone_default;
  }

  action_handler_generic * create_drone_response::default_handler() const
  {
    return new create_drone_response_default;
  }
}}
