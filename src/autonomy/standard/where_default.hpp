#include <autonomy/standard/where_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_WHERE_DEFAULT_HPP
#define AUTONOMY_ACTION_HANDLER_WHERE_DEFAULT_HPP

#include <autonomy/standard/where.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/universe.hpp>
#include <autonomy/standard/scripted_drone.hpp>

namespace autonomy { namespace standard
{
  class where_default
    : public action_handler_base<where, universe>
  {
    public:
      virtual ~where_default(){}

      virtual void execute( universe & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(where_handler_base_t);
        }
  };

  class where_response_default
    : public action_handler_base<where_response, scripted_drone>
  {
    public:
      virtual ~where_response_default(){}

      virtual void execute( scripted_drone & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(where_response_handler_base_t);
        }
  };
}}
#endif
