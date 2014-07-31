#include <autonomy/action_handler/scan_default.hpp>

BOOST_CLASS_EXPORT(autonomy::action_handler::scan_default);
BOOST_CLASS_EXPORT(autonomy::action_handler::scan_response_default);

namespace autonomy
{
    namespace action_handler
    {

        void scan_default::execute( entity::universe & entity, 
                                    size_t which_queue )
        {
            location_module & loc(entity.location_module());
            BOOST_FOREACH(action::scan * s, _action_group)
            {
#ifdef DEBUG
                std::cout << "Universe: Start scan action handler.\n";
#endif
                action::scan_response* 
                    sr(new action::scan_response(loc.query(s->location())));

                (s->subject())->send_action(which_queue, sr);
            }
        }

        void scan_response_default::execute( entity::scripted_drone & entity, 
                                             size_t which_queue )
        {
            BOOST_FOREACH(action::scan_response * sr, _action_group)
            {
                if ( entity_id_t(sr->entity()) == entity_id_t() )
                {
                    entity.push_stack(static_cast<int>(entity::scripted_drone::EMPTY));
                }
                else if ( typeid(*(sr->entity())) == typeid(entity::scripted_drone) )
                {
                    entity.push_stack(static_cast<int>(entity::scripted_drone::DRONE));
                }
                else if ( typeid(*(sr->entity())) == typeid(entity::base_station) )
                {
                    entity.push_stack(static_cast<int>(entity::scripted_drone::BASE));
                }
                else if ( typeid(*(sr->entity())) == typeid(entity::asteroid) )
                {
                    entity.push_stack(static_cast<int>(entity::scripted_drone::ASTEROID));
                }
            }
        }
    }
}
