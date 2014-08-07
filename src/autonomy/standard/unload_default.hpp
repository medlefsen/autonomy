#include <autonomy/standard/unload_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_UNLOAD_DEFAULT_HPP
#define AUTONOMY_ACTION_HANDLER_UNLOAD_DEFAULT_HPP

#include <autonomy/util/serialization.hpp>
#include <autonomy/standard/unload.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/universe.hpp>
#include <autonomy/standard/base_station.hpp>
#include <autonomy/standard/scripted_drone.hpp>
namespace autonomy { namespace standard
{
  class unload_default
    : public action_handler_base<unload, base_station>
  {
    public:
      virtual ~unload_default(){}

      virtual void execute( base_station & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(unload_handler_base_t);
        }
  };

  class unload_fuel_default
    : public action_handler_base<unload_fuel, universe>
  {
    public:
      virtual ~unload_fuel_default(){}

      virtual void execute( universe & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(unload_fuel_handler_base_t);
        }
  };

  class unload_response_default
    : public action_handler_base<unload_response, scripted_drone>
  {
    public:
      virtual ~unload_response_default(){}

      virtual void execute( scripted_drone & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(unload_response_handler_base_t);
        }
  };
}}
#endif
