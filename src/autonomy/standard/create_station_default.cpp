#include <autonomy/standard/create_station_default.hpp>
#include <autonomy/universe.hpp>
#include <autonomy/standard/base_station.hpp>

BOOST_CLASS_EXPORT(autonomy::standard::create_station_default);

namespace autonomy { namespace standard
{
  void create_station_default::execute( universe & entity )
  {
    location_module & loc (entity.location_module());

    for(auto& cs : _action_group) 
      //for ( _action_group_t::iterator i(_action_group.begin());
      //        i != _action_group.end();
      //        ++i )
    {
#ifdef DEBUG
      std::cout << "Universe: Start create_station action handler.\n";
#endif
      entity_id_t      me(entity);

      // For now (I4) there will only ever be a single base station at 0,0.
      util::coord_pair base_loc(0,0);
      entity_id_t      new_station(static_cast<entity_generic*>(
            new base_station(me,
              entity.which_game(),
              cs->fuel())));

      if (loc.move(new_station, base_loc))
      {
#ifdef DEBUG
        std::cout << "Universe: Adding new_station to universe.\n";
#endif
        entity.add(new_station);
      }
    }

  }
}}
