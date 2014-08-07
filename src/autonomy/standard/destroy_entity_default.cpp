#include <autonomy/standard/destroy_entity_default.hpp>

BOOST_CLASS_EXPORT(autonomy::standard::hide_entity_default);
BOOST_CLASS_EXPORT(autonomy::standard::destroy_entity_default);

namespace autonomy { namespace standard
{
  void hide_entity_default::execute( universe & entity )
  {
    location_module & loc (entity.location_module());
    for(auto& he : _action_group)
    {
      loc.remove(he->entity());
    }
  }

  void destroy_entity_default::execute( universe & entity )
  {
    for(auto& de : _action_group)
    {
      entity.remove(de->entity());
    }
  }
}}
