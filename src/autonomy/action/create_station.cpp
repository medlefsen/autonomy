#include <autonomy/action/create_station.hpp>
#include <autonomy/entity/universe.hpp>
namespace autonomy
{
    BOOST_CLASS_EXPORT(create_station_handler_base_t);

    namespace action
    {
        BOOST_CLASS_EXPORT(create_station);

        action_handler_generic * create_station::default_handler()
        {
            return new action_handler::create_station_default;
        }
    }
}
