#include<autonomy/entity/base_station.hpp>

namespace autonomy 
{ 
    BOOST_CLASS_EXPORT(entity_base<entity::base_station>);
    namespace entity 
    {
        BOOST_CLASS_EXPORT(base_station);
        void base_station::controller(size_t which_queue)
        {
#ifndef DUI
            _which_game->gui().do_update();
#endif
        }

    }
}
