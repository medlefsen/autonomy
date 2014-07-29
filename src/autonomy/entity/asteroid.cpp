#include <typeinfo>
#include <algorithm>

#include <boost/foreach.hpp>

#include <autonomy/entity/asteroid.hpp>
#include <autonomy/action/mine.hpp>
#include <autonomy/action/destroy_entity.hpp>

namespace autonomy 
{ 
    BOOST_CLASS_EXPORT(entity_base<entity::asteroid>);
    namespace entity 
    {
        BOOST_CLASS_EXPORT(asteroid);
        void asteroid::controller(size_t which_queue)
        {
            if ( get_fuel() == 0 )
            {
                universe()->send_action(which_queue, new action::hide_entity(*this));
                drain_fuel(1);
            }
            else if ( get_fuel() < 0 )
            {
                drain_fuel(1);
            }
            else if ( get_fuel() < -2 )
            {
                universe()->send_action(which_queue, new action::destroy_entity(*this));
            }
        }
    }
}
