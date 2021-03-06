//! \file
//! \brief
//!
//! Contributing Author:  Aaron Weeden

#include <autonomy/action_handler/create_asteroid_default.hpp>

BOOST_CLASS_EXPORT(autonomy::action_handler::create_asteroid_default);
BOOST_CLASS_EXPORT(autonomy::action_handler::create_asteroid_response_default);

namespace autonomy
{
    namespace action_handler
    {

        void create_asteroid_default::execute( entity::universe & entity, 
                                               size_t which_queue )
        {
            location_module<game> & loc  (entity.location_module());
            processor             & proc (entity.processor());

            BOOST_FOREACH(action::create_asteroid * ca, _action_group)
            {
               entity_id_t      me(entity);
               util::coord_pair asteroid_loc(ca->location());
               entity_id_t      new_asteroid(static_cast<entity_generic*>
                                   (new entity::asteroid(me, ca->fuel())));
               action_generic*  car;

               if (loc.move(new_asteroid, asteroid_loc))
               {
                    car = static_cast<action_generic*>(new action::create_asteroid_response(true));
                    proc.add(new_asteroid);
               }
               else
               {
                    car = static_cast<action_generic*>(new action::create_asteroid_response(false));
		    std::cerr << "Warning!  Asteroid lost (created on top of other entity)" << std::endl;
	       }
               (ca->subject())->send_action(which_queue, car);
            }
        }

        void create_asteroid_response_default::execute( entity::drone & entity, 
                                                        size_t which_queue )
        {}
    }
}
