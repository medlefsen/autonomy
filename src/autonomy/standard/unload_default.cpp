#include <autonomy/standard/unload_default.hpp>

#include <algorithm>

BOOST_CLASS_EXPORT(autonomy::standard::unload_default);
BOOST_CLASS_EXPORT(autonomy::standard::unload_fuel_default);
BOOST_CLASS_EXPORT(autonomy::standard::unload_response_default);

namespace autonomy { namespace standard
{
  void unload_default::execute( base_station & entity )
  {
    for(auto& unload_act : _action_group)
    {
      int fuel_unloaded = std::max(0, std::min(unload_act->fuel(), entity.get_fuel()));
      (unload_act->subject())->send_action<unload_response>(fuel_unloaded);
      entity.add_fuel(fuel_unloaded);
    }
  }

  void unload_fuel_default::execute( universe & entity )
  {
    location_module & loc(entity.location_module());

    for(auto& unload_loc : _action_group)
    {
      entity_id_t object(loc.query(unload_loc->location()));

      // XXX:  do we want to continue using typeid, or should we switch
      // to the "custom" util::id?
      if (object != entity_id_t() 
          && typeid(*object) == typeid(base_station) )
      {
        object->send_action<unload>(unload_loc->fuel(), unload_loc->subject());
      }
      else
      {
        unload_loc->subject()->send_action<unload_response>(0);
      }
    }

  }

  void unload_response_default::execute( scripted_drone & entity )
  {
    for(auto& ur : _action_group)
    {
      entity.push_stack(ur->fuel());
      entity.drain_fuel(ur->fuel());
    }
  }
}}
