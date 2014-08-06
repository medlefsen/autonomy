#include <autonomy/action_handler/unload_default.hpp>

#include <algorithm>

BOOST_CLASS_EXPORT(autonomy::action_handler::unload_default);
BOOST_CLASS_EXPORT(autonomy::action_handler::unload_fuel_default);
BOOST_CLASS_EXPORT(autonomy::action_handler::unload_response_default);

namespace autonomy
{
    namespace action_handler
    {

        void unload_default::execute( entity::base_station & entity )
        {
            BOOST_FOREACH(action::unload *  unload_act, _action_group)
            {
                int fuel_unloaded = std::max(0, std::min(unload_act->fuel(), entity.get_fuel()));
                (unload_act->subject())->send_action(new action::unload_response(fuel_unloaded));
                entity.add_fuel(fuel_unloaded);
            }
        }

        void unload_fuel_default::execute( entity::universe & entity )
        {
            location_module & loc(entity.location_module());

            BOOST_FOREACH(action::unload_fuel * unload_loc, _action_group)
            {
                entity_id_t object(loc.query(unload_loc->location()));
                
                // XXX:  do we want to continue using typeid, or should we switch
                // to the "custom" util::id?
                if (object != entity_id_t() 
                        && typeid(*object) == typeid(entity::base_station) )
                {
                    object->send_action(static_cast<action_generic*>(
                                new action::unload(unload_loc->fuel(),
                                                 unload_loc->subject())));
                }
                else
                {
                    unload_loc->subject()->send_action(static_cast<action_generic*>(
                                new action::unload_response(0)));
                }
            }

        }

        void unload_response_default::execute( entity::scripted_drone & entity )
        {
            BOOST_FOREACH(action::unload_response * ur, _action_group)
            {
                entity.push_stack(ur->fuel());
                entity.drain_fuel(ur->fuel());
            }
        }
    }
}
