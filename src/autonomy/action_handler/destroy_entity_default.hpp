#include <autonomy/action_handler/destroy_entity_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_DESTROY_ENTITY_DEFAULT_HPP
#define AUTONOMY_ACTION_HANDLER_DESTROY_ENTITY_DEFAULT_HPP

#include <autonomy/action/destroy_entity.hpp>
#include <autonomy/entity/universe.hpp>
#include <autonomy/util/serialization.hpp>
#include <autonomy/action_handler.hpp>
namespace autonomy
{
    namespace action_handler
    {
        class hide_entity_default
            : public action_handler_base< actor::hide_entity, entity::universe >
        {
            public:
                virtual ~hide_entity_default(){} 

                virtual void execute( entity::universe & entity );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(hide_entity_handler_base_t);
                }
        };

        class destroy_entity_default
            : public action_handler_base< actor::destroy_entity, entity::universe >
        {
            public:
                virtual ~destroy_entity_default(){}

                virtual void execute( entity::universe & entity );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(destroy_entity_handler_base_t);
                }

        };
    }
}
#endif
