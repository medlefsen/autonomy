#include <autonomy/standard/create_station.hpp>
#include <autonomy/universe.hpp>
BOOST_CLASS_EXPORT(autonomy::standard::create_station_handler_base_t);
BOOST_CLASS_EXPORT(autonomy::standard::create_station);

namespace autonomy { namespace standard
{
  action_handler_generic * create_station::default_handler() const
  {
    return new create_station_default;
  }
}}
