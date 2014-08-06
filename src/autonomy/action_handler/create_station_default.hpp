#include <autonomy/action_handler/create_station_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_CREATE_STATION_HPP
#define AUTONOMY_ACTION_HANDLER_CREATE_STATION_HPP

#include <autonomy/action/create_station.hpp>
#include <autonomy/action_handler.hpp>

namespace autonomy
{
    namespace action_handler
    {
        class create_station_default
            : public action_handler_base<action::create_station, entity::universe>
        {
            public:
                virtual ~create_station_default(){} 

                virtual void execute( entity::universe & entity );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(create_station_handler_base_t);
                }
        };
    }
}
#endif
