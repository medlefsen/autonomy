#include <autonomy/action_handler/create_drone_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_CREATE_DRONE_DEFAULT_HPP
#define AUTONOMY_ACTION_HANDLER_CREATE_DRONE_DEFAULT_HPP

#include <autonomy/action/create_drone.hpp>
#include <autonomy/util/serialization.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/entity/universe.hpp>
#include <autonomy/entity/drone.hpp>

namespace autonomy
{
    namespace action_handler
    {
        class create_drone_default
            : public action_handler_base<action::create_drone, entity::universe>
        {
            public:
                virtual ~create_drone_default(){} 

                virtual void execute( entity::universe & entity );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(create_drone_handler_base_t);
                }
        };

        class create_drone_response_default
            : public action_handler_base<action::create_drone_response, entity::drone>
        {
            public:
                virtual ~create_drone_response_default(){} 

                virtual void execute( entity::drone & entity );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(create_drone_response_handler_base_t); 
                }
        };
    }
}
#endif
