//! \file
//! \brief
//!
//! Contributing Author:  Aaron Weeden

#include <autonomy/standard/create_drone_default.hpp>

BOOST_CLASS_EXPORT(autonomy::standard::create_drone_default);
BOOST_CLASS_EXPORT(autonomy::standard::create_drone_response_default);

namespace autonomy { namespace standard
{
  void create_drone_default::execute( universe & entity )
  {
    location_module & loc (entity.location_module());

    for(auto& cd : _action_group)
    {
      entity_id_t      me(entity);
      util::coord_pair drone_loc(cd->location());
      entity_id_t      new_drone(static_cast<entity_generic*>
          (new scripted_drone(me, cd->script(), cd->fuel())));
      action           cdr;

      if (loc.move(new_drone, drone_loc))
      {
        cdr = action::create<create_drone_response>(true);
        entity.add(new_drone);
      }
      else
      {
        cdr = action::create<create_drone_response>(false);
        std::cerr << "Warning!  Drone lost (created on top of other entity)" << std::endl;
      }
      (cd->subject())->send_action(cdr);
    }
  }

  void create_drone_response_default::execute( drone & entity )
  {}
}}
