#include <autonomy/action_handler/create_asteroid_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_CREATE_ASTEROID_DEFAULT_HPP 
#define AUTONOMY_ACTION_HANDLER_CREATE_ASTEROID_DEFAULT_HPP 

#include <autonomy/action/create_asteroid.hpp>
#include <autonomy/util/serialization.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/entity/universe.hpp>
#include <autonomy/entity/drone.hpp>

namespace autonomy
{
    namespace action_handler
    {
        class create_asteroid_default
            : public action_handler_base< action::create_asteroid, entity::universe >
        {
            public:
                virtual ~create_asteroid_default(){}

                virtual void execute( entity::universe & entity, size_t which_queue );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(create_asteroid_handler_base_t);
                }
        };

        class create_asteroid_response_default
            : public action_handler_base< action::create_asteroid_response, entity::drone >
        {
            public:
                virtual ~create_asteroid_response_default(){}

                virtual void execute( entity::drone & entity, size_t which_queue );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(create_asteroid_response_handler_base_t);
                }
        };
    }
}
#endif
