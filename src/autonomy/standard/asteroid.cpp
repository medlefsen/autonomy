#include <typeinfo>
#include <algorithm>

#include <boost/foreach.hpp>

#include <autonomy/standard/asteroid.hpp>
#include <autonomy/standard/mine.hpp>
#include <autonomy/standard/destroy_entity.hpp>

BOOST_CLASS_EXPORT(autonomy::entity_base<autonomy::standard::asteroid>);

BOOST_CLASS_EXPORT(autonomy::standard::asteroid);

namespace autonomy { namespace standard
{ 
  void asteroid::controller()
  {
    if ( get_fuel() == 0 )
    {
      universe()->send_action<hide_entity>(*this);
      drain_fuel(1);
    }
    else if ( get_fuel() < 0 )
    {
      drain_fuel(1);
    }
    else if ( get_fuel() < -2 )
    {
      universe()->send_action<destroy_entity>(*this);
    }
  }
}}
