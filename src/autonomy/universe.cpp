//! \file
//! \brief Universe implementation details.

#include <autonomy/universe.hpp>

BOOST_CLASS_EXPORT(autonomy::entity_base<autonomy::universe>);

BOOST_CLASS_EXPORT(autonomy::universe);

namespace autonomy
{
  void universe::controller()
  {}

  void universe::add(entity_id_t entity_ptr)
  {
    game_->processor().add(entity_ptr);
  }


  void universe::remove(entity_id_t entity_ptr)
  {
    game_->processor().remove(entity_ptr);
  }

  game& universe::which_game() 
  {
    return *game_;
  }

  location_module & universe::location_module() const
  {
    return game_->location_module();
  }
}
