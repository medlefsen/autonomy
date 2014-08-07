#include <autonomy/standard/create_drone_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_CREATE_DRONE_DEFAULT_HPP
#define AUTONOMY_ACTION_HANDLER_CREATE_DRONE_DEFAULT_HPP

#include <autonomy/standard/create_drone.hpp>
#include <autonomy/util/serialization.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/universe.hpp>
#include <autonomy/standard/drone.hpp>

namespace autonomy { namespace standard
{
  class create_drone_default
    : public action_handler_base<create_drone, universe>
  {
    public:
      virtual ~create_drone_default(){} 

      virtual void execute( universe & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(create_drone_handler_base_t);
        }
  };

  class create_drone_response_default
    : public action_handler_base<create_drone_response, drone>
  {
    public:
      virtual ~create_drone_response_default(){} 

      virtual void execute( drone & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(create_drone_response_handler_base_t); 
        }
  };
}}
#endif
