#include <autonomy/action/create_station.hpp>
#include <autonomy/entity/universe.hpp>
BOOST_CLASS_EXPORT(autonomy::create_station_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::actor::create_station);

namespace autonomy
{
    namespace actor
    {
        action_handler_generic * create_station::default_handler() const
        {
            return new action_handler::create_station_default;
        }
    }
}
