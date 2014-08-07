#include <autonomy/standard/mine.hpp>

BOOST_CLASS_EXPORT(autonomy::standard::mine_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::standard::mine_location_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::standard::mine_response_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::standard::mine);
BOOST_CLASS_EXPORT(autonomy::standard::mine_location);
BOOST_CLASS_EXPORT(autonomy::standard::mine_response);

namespace autonomy { namespace standard
{
  action_handler_generic * mine::default_handler() const
  {
    return new mine_default;
  }

  action_handler_generic * mine_location::default_handler() const
  {
    return new mine_location_default;
  }

  action_handler_generic * mine_response::default_handler() const
  {
    return new mine_response_default;
  }
}}
