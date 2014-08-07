#include <autonomy/standard/mine_default.hpp>

#include <algorithm>

BOOST_CLASS_EXPORT(autonomy::standard::mine_default);
BOOST_CLASS_EXPORT(autonomy::standard::mine_location_default);
BOOST_CLASS_EXPORT(autonomy::standard::mine_response_default);

namespace autonomy { namespace standard
{
  void mine_default::execute( asteroid & entity )
  {
    for(auto& mine_act : _action_group)
    {
      int fuel_obtained = std::max(0, std::min(mine_act->fuel(), entity.get_fuel()));
      (mine_act->subject())->send_action<mine_response>(fuel_obtained);
      entity.drain_fuel(fuel_obtained);
    }
  }

  void mine_location_default::execute( universe & entity )
  {
    location_module & loc(entity.location_module());

    for(auto& mine_loc : _action_group)
    {
      entity_id_t object(loc.query(mine_loc->location()));

      // XXX:  do we want to continue using typeid, or should we switch
      // to the "custom" util::id?
      if (object != entity_id_t() 
          && typeid(*object) == typeid(asteroid) )
      {
        object->send_action<mine>(mine_loc->fuel(), mine_loc->subject());
      }
      else
      {
        mine_loc->subject()->send_action<mine_response>(0);
      }
    }

  }

  void mine_response_default::execute( scripted_drone & entity )
  {
    for(auto& mr : _action_group)
    {
      entity.push_stack(mr->fuel());
      entity.add_fuel(mr->fuel());
    }
  }
}}