#include <typeinfo>
#include <algorithm>

#include <boost/foreach.hpp>

#include <autonomy/entity/asteroid.hpp>
#include <autonomy/action/mine.hpp>
#include <autonomy/action/destroy_entity.hpp>

BOOST_CLASS_EXPORT(autonomy::entity_base<autonomy::entity::asteroid>);

BOOST_CLASS_EXPORT(autonomy::entity::asteroid);

namespace autonomy 
{ 
    namespace entity 
    {
        void asteroid::controller()
        {
            if ( get_fuel() == 0 )
            {
                universe()->send_action(action::create<actor::hide_entity>(*this));
                drain_fuel(1);
            }
            else if ( get_fuel() < 0 )
            {
                drain_fuel(1);
            }
            else if ( get_fuel() < -2 )
            {
                universe()->send_action(action::create<actor::destroy_entity>(*this));
            }
        }
    }
}
