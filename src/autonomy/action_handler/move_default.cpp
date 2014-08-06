#include <autonomy/action_handler/move_default.hpp>
#include <autonomy/entity/scripted_drone.hpp>

BOOST_CLASS_EXPORT(autonomy::action_handler::move_direction_default);
BOOST_CLASS_EXPORT(autonomy::action_handler::move_direction_response_default);

namespace autonomy
{
    namespace action_handler
    {

        void move_direction_default::execute( entity::universe & entity )
        {
            location_module & loc(entity.location_module());
            BOOST_FOREACH(action::move_direction * md, _action_group)
            {
#ifdef DEBUG
                std::cout << "Universe: Start move action handler.\n";
#endif
                int x((md->horizontal() < 0) 
                        ? -1 : ((md->horizontal() > 0) ? 1 : 0) );
                int y(md->vertical() < 0
                        ? -1 : ((md->vertical() > 0) ? 1 : 0) );

                util::coord_pair
                    new_loc(util::coord_pair(loc.locate(entity_id_t(md->subject())).x() + x, 
                                loc.locate(entity_id_t(md->subject())).y() + y));

                action_generic* mdr;
                // a default constructed entity_id_t means "not found"
                if (loc.query(new_loc) == entity_id_t())
                {
                    loc.move(entity_id_t(md->subject()), new_loc);
                    mdr = static_cast<action_generic*>(new action::move_direction_response(true));
                }
                else
                {
                    mdr = static_cast<action_generic*>(new action::move_direction_response(false));
                }
                (md->subject())->send_action(mdr);
            }
        }

        void move_direction_response_default::execute( entity::scripted_drone & entity )
        {
            BOOST_FOREACH(action::move_direction_response * mdr, _action_group)
            {
                entity.push_stack(mdr->success());
            }
        }

    }
}
