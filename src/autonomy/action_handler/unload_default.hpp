#include <autonomy/action_handler/unload_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_UNLOAD_DEFAULT_HPP
#define AUTONOMY_ACTION_HANDLER_UNLOAD_DEFAULT_HPP

#include <autonomy/util/serialization.hpp>
#include <autonomy/action/unload.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/entity/universe.hpp>
#include <autonomy/entity/base_station.hpp>
#include <autonomy/entity/scripted_drone.hpp>
namespace autonomy
{
    namespace action_handler
    {
        class unload_default
            : public action_handler_base<actor::unload, entity::base_station>
        {
            public:
                virtual ~unload_default(){}

                virtual void execute( entity::base_station & entity );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(unload_handler_base_t);
                }
        };

        class unload_fuel_default
            : public action_handler_base<actor::unload_fuel, entity::universe>
        {
            public:
                virtual ~unload_fuel_default(){}

                virtual void execute( entity::universe & entity );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(unload_fuel_handler_base_t);
                }
        };

        class unload_response_default
            : public action_handler_base<actor::unload_response, entity::scripted_drone>
        {
            public:
                virtual ~unload_response_default(){}

                virtual void execute( entity::scripted_drone & entity );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(unload_response_handler_base_t);
                }
        };
    }
}
#endif
