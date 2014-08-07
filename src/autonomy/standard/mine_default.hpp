#include <autonomy/standard/mine_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_MINE_DEFAULT_HPP
#define AUTONOMY_ACTION_HANDLER_MINE_DEFAULT_HPP

#include <autonomy/util/serialization.hpp>
#include <autonomy/standard/mine.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/universe.hpp>
#include <autonomy/standard/scripted_drone.hpp>
#include <autonomy/standard/asteroid.hpp>
namespace autonomy { namespace standard
{
  class mine_default
    : public action_handler_base<mine, asteroid>
  {
    public:
      virtual ~mine_default(){}

      virtual void execute( asteroid & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(mine_handler_base_t);
        }
  };

  class mine_location_default
    : public action_handler_base<mine_location, universe>
  {
    public:
      virtual ~mine_location_default(){}

      virtual void execute( universe & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(mine_location_handler_base_t);
        }
  };

  class mine_response_default
    : public action_handler_base<mine_response, scripted_drone>
  {
    public:
      virtual ~mine_response_default(){}

      virtual void execute( scripted_drone & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(mine_response_handler_base_t);
        }
  };
}}
#endif
