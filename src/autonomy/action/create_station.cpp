#include <autonomy/action/create_station.hpp>
#include <autonomy/entity/universe.hpp>
BOOST_CLASS_EXPORT(autonomy::create_station_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::action::create_station);

namespace autonomy
{
    namespace action
    {
        action_handler_generic * create_station::default_handler()
        {
            return new action_handler::create_station_default;
        }
    }
}
