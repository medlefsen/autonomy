#include <autonomy/standard/destroy_entity.hpp>

BOOST_CLASS_EXPORT(autonomy::standard::hide_entity_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::standard::destroy_entity_handler_base_t);

BOOST_CLASS_EXPORT(autonomy::standard::hide_entity);
BOOST_CLASS_EXPORT(autonomy::standard::destroy_entity);

namespace autonomy { namespace standard
{
  action_handler_generic * hide_entity::default_handler() const
  {
    return new hide_entity_default;
  }

  action_handler_generic * destroy_entity::default_handler() const
  {
    return new destroy_entity_default;
  }
}}
