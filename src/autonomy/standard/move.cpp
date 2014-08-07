#include <autonomy/standard/move.hpp>

BOOST_CLASS_EXPORT(autonomy::standard::move_direction);
BOOST_CLASS_EXPORT(autonomy::standard::move_direction_response);

namespace autonomy { namespace standard
{
  action_handler_generic * move_direction::default_handler() const
  {
    return new move_direction_default;
  }

  action_handler_generic * move_direction_response::default_handler() const
  {
    return new move_direction_response_default;
  }
}}
