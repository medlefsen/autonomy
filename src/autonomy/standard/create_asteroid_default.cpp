//! \file
//! \brief
//!
//! Contributing Author:  Aaron Weeden

#include <autonomy/standard/create_asteroid_default.hpp>

BOOST_CLASS_EXPORT(autonomy::standard::create_asteroid_default);
BOOST_CLASS_EXPORT(autonomy::standard::create_asteroid_response_default);

namespace autonomy { namespace standard
{
  void create_asteroid_default::execute( universe & entity )
  {
    location_module & loc  (entity.location_module());

    for(auto ca : _action_group)
    {
      entity_id_t      me(entity);
      util::coord_pair asteroid_loc(ca->location());
      entity_id_t      new_asteroid(static_cast<entity_generic*>(new asteroid(me, ca->fuel())));
      action           car;

      if (loc.move(new_asteroid, asteroid_loc))
      {
        car = action::create<create_asteroid_response>(true);
        entity.add(new_asteroid);
      }
      else
      {
        car = action::create<create_asteroid_response>(false);
        std::cerr << "Warning!  Asteroid lost (created on top of other entity)" << std::endl;
      }
      (ca->subject())->send_action(car);
    }
  }

  void create_asteroid_response_default::execute( drone & entity )
  {}
}}
