#include<autonomy/entity/base_station.hpp>

BOOST_CLASS_EXPORT(autonomy::entity_base<autonomy::entity::base_station>);

BOOST_CLASS_EXPORT(autonomy::entity::base_station);

namespace autonomy 
{ 
    namespace entity 
    {
        void base_station::controller()
        {
#ifndef DUI
            _which_game->update_ui();
#endif
        }

    }
}
