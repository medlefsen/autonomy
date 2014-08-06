//! \file
//! \brief
//!
//! Contributing Author:  Aaron Weeden

#include <autonomy/action_handler/create_drone_default.hpp>

BOOST_CLASS_EXPORT(autonomy::action_handler::create_drone_default);
BOOST_CLASS_EXPORT(autonomy::action_handler::create_drone_response_default);

namespace autonomy
{
    namespace action_handler
    {

        void create_drone_default::execute( entity::universe & entity )
        {
            location_module & loc (entity.location_module());

            BOOST_FOREACH(action::create_drone * cd, _action_group)
            {
               entity_id_t      me(entity);
               util::coord_pair drone_loc(cd->location());
               entity_id_t      new_drone(static_cast<entity_generic*>
                                   (new entity::scripted_drone(me, cd->script(), cd->fuel())));
               action_generic*  cdr;

               if (loc.move(new_drone, drone_loc))
               {
                    cdr = static_cast<action_generic*>(new action::create_drone_response(true));
                    entity.add(new_drone);
               }
               else
               {
                    cdr = static_cast<action_generic*>(new action::create_drone_response(false));
              	    std::cerr << "Warning!  Drone lost (created on top of other entity)" << std::endl;
	       }
               (cd->subject())->send_action(cdr);
            }
        }

        void create_drone_response_default::execute( entity::drone & entity )
        {}
    }
}
