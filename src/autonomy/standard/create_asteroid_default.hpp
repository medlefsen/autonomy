#include <autonomy/standard/create_asteroid_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_CREATE_ASTEROID_DEFAULT_HPP 
#define AUTONOMY_ACTION_HANDLER_CREATE_ASTEROID_DEFAULT_HPP 

#include <autonomy/standard/create_asteroid.hpp>
#include <autonomy/util/serialization.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/universe.hpp>
#include <autonomy/standard/drone.hpp>
#include <autonomy/standard/asteroid.hpp>

namespace autonomy { namespace standard
{
  class create_asteroid_default
    : public action_handler_base< create_asteroid, universe >
  {
    public:
      virtual ~create_asteroid_default(){}

      virtual void execute( universe & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(create_asteroid_handler_base_t);
        }
  };

  class create_asteroid_response_default
    : public action_handler_base< create_asteroid_response, drone >
  {
    public:
      virtual ~create_asteroid_response_default(){}

      virtual void execute( drone & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(create_asteroid_response_handler_base_t);
        }
  };
}}
#endif
