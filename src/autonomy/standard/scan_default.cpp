#include <autonomy/standard/scan_default.hpp>
#include <autonomy/standard/base_station.hpp>
#include <autonomy/standard/scripted_drone.hpp>
#include <autonomy/standard/asteroid.hpp>

BOOST_CLASS_EXPORT(autonomy::standard::scan_default);
BOOST_CLASS_EXPORT(autonomy::standard::scan_response_default);

namespace autonomy { namespace standard
{
  void scan_default::execute( universe & entity )
  {
    location_module & loc(entity.location_module());
    for(auto& s : _action_group)
    {
#ifdef DEBUG
      std::cout << "Universe: Start scan action handler.\n";
#endif
      s->subject()->send_action<scan_response>(loc.query(s->location()));
    }
  }

  void scan_response_default::execute( scripted_drone & entity )
  {
    for(auto& sr : _action_group)
    {
      if ( entity_id_t(sr->entity()) == entity_id_t() )
      {
        entity.push_stack(static_cast<int>(scripted_drone::EMPTY));
      }
      else if ( typeid(*(sr->entity())) == typeid(scripted_drone) )
      {
        entity.push_stack(static_cast<int>(scripted_drone::DRONE));
      }
      else if ( typeid(*(sr->entity())) == typeid(base_station) )
      {
        entity.push_stack(static_cast<int>(scripted_drone::BASE));
      }
      else if ( typeid(*(sr->entity())) == typeid(asteroid) )
      {
        entity.push_stack(static_cast<int>(scripted_drone::ASTEROID));
      }
    }
  }
}}
