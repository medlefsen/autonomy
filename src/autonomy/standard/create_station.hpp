//! \file
//! \brief Create action/response.  Needed by the Universe entity to add new entities.

#include <autonomy/standard/create_station.fwd.hpp>

#ifndef AUTONOMY_ACTION_CREATE_STATION_HPP
#define AUTONOMY_ACTION_CREATE_STATION_HPP

#include <autonomy/action.hpp>
#include <autonomy/entity.hpp>
#include <autonomy/util/serialization.hpp>
#include <autonomy/util/coord_pair.hpp>
#include <autonomy/standard/create_station_default.hpp>

namespace autonomy { namespace standard
{
  class create_station
    : public action_base<universe>
  {
    public:
      create_station( int fuel,
          util::coord_pair location )
        : _location(location), _fuel(fuel)
      {}

      virtual ~create_station()
      {}

      virtual action_handler_id_t default_handler_type() const
      {
        return action_handler_id_t(static_cast<create_station_default*>(NULL));
      }

      virtual action_handler_generic * default_handler() const;

      util::coord_pair location() const { return _location; }
      int fuel() const { return _fuel; }
    private:
      create_station(){}
      util::coord_pair _location;
      int _fuel;

      friend class boost::serialization::access;
      template < class Archive >
        void serialize(Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<universe>);
          ar & BOOST_SERIALIZATION_NVP(_fuel);
          ar & BOOST_SERIALIZATION_NVP(_location);
        }
  };
}}
#endif
