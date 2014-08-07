#include <autonomy/standard/create_asteroid.hpp>

BOOST_CLASS_EXPORT(autonomy::standard::create_asteroid_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::standard::create_asteroid_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::standard::create_asteroid);
BOOST_CLASS_EXPORT(autonomy::standard::create_asteroid_response);

namespace autonomy { namespace standard
{
  action_handler_generic * create_asteroid::default_handler() const
  {
    return new create_asteroid_default;
  }

  action_handler_generic * create_asteroid_response::default_handler() const
  {
    return new create_asteroid_response_default;
  }
}}
