#include <autonomy/action_handler/scan_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_SCAN_DEFAULT_HPP
#define AUTONOMY_ACTION_HANDLER_SCAN_DEFAULT_HPP

#include <autonomy/util/serialization.hpp>
#include <autonomy/action/scan.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/entity/universe.hpp>
#include <autonomy/entity/drone.hpp>

namespace autonomy
{
    namespace action_handler
    {
        class scan_default
            : public action_handler_base<action::scan, entity::universe>
        {
            public:
                virtual ~scan_default(){}

                virtual void execute( entity::universe & entity, size_t which_queue );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(scan_handler_base_t);
                }
        };

        class scan_response_default
            : public action_handler_base<action::scan_response, entity::scripted_drone>
        {
            public:
                virtual ~scan_response_default(){}

                virtual void execute( entity::scripted_drone & entity, size_t which_queue );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(scan_response_handler_base_t);
                }
        };
    }
}
#endif
