#include <autonomy/action_handler/where_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_WHERE_DEFAULT_HPP
#define AUTONOMY_ACTION_HANDLER_WHERE_DEFAULT_HPP

#include <autonomy/action/where.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/entity/universe.hpp>
#include <autonomy/entity/scripted_drone.hpp>

namespace autonomy
{
    namespace action_handler
    {
        class where_default
            : public action_handler_base<action::where, entity::universe>
        {
            public:
                virtual ~where_default(){}

                virtual void execute( entity::universe & entity );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(where_handler_base_t);
                }
        };

        class where_response_default
            : public action_handler_base<action::where_response, entity::scripted_drone>
        {
            public:
                virtual ~where_response_default(){}

                virtual void execute( entity::scripted_drone & entity );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(where_response_handler_base_t);
                }
        };
    }
}
#endif
