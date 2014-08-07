#include <autonomy/standard/scan_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_SCAN_DEFAULT_HPP
#define AUTONOMY_ACTION_HANDLER_SCAN_DEFAULT_HPP

#include <autonomy/util/serialization.hpp>
#include <autonomy/standard/scan.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/universe.hpp>
#include <autonomy/standard/drone.hpp>

namespace autonomy { namespace standard
{
  class scan_default
    : public action_handler_base<scan, universe>
  {
    public:
      virtual ~scan_default(){}

      virtual void execute( universe & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(scan_handler_base_t);
        }
  };

  class scan_response_default
    : public action_handler_base<scan_response, scripted_drone>
  {
    public:
      virtual ~scan_response_default(){}

      virtual void execute( scripted_drone & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(scan_response_handler_base_t);
        }
  };
}}
#endif
