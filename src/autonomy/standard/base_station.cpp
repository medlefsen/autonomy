#include<autonomy/standard/base_station.hpp>

BOOST_CLASS_EXPORT(autonomy::entity_base<autonomy::standard::base_station>);

BOOST_CLASS_EXPORT(autonomy::standard::base_station);

namespace autonomy { namespace standard
{ 
  void base_station::controller()
  {
#ifndef DUI
    _which_game->update_ui();
#endif
  }
}}
