#include <autonomy/standard/create_station_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_CREATE_STATION_HPP
#define AUTONOMY_ACTION_HANDLER_CREATE_STATION_HPP

#include <autonomy/standard/create_station.hpp>
#include <autonomy/action_handler.hpp>

namespace autonomy { namespace standard
{
  class create_station_default
    : public action_handler_base<create_station, universe>
  {
    public:
      virtual ~create_station_default(){} 

      virtual void execute( universe & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(create_station_handler_base_t);
        }
  };
}}
#endif
