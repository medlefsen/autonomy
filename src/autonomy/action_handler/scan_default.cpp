#include <autonomy/action_handler/scan_default.hpp>
#include <autonomy/entity/base_station.hpp>
#include <autonomy/entity/scripted_drone.hpp>
#include <autonomy/entity/asteroid.hpp>

BOOST_CLASS_EXPORT(autonomy::action_handler::scan_default);
BOOST_CLASS_EXPORT(autonomy::action_handler::scan_response_default);

namespace autonomy
{
    namespace action_handler
    {

        void scan_default::execute( entity::universe & entity )
        {
            location_module & loc(entity.location_module());
            for(auto& s : _action_group)
            {
#ifdef DEBUG
                std::cout << "Universe: Start scan action handler.\n";
#endif
                s->subject()->send_action<actor::scan_response>(loc.query(s->location()));
            }
        }

        void scan_response_default::execute( entity::scripted_drone & entity )
        {
            for(auto& sr : _action_group)
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
