#include <autonomy/action_handler/mine_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_MINE_DEFAULT_HPP
#define AUTONOMY_ACTION_HANDLER_MINE_DEFAULT_HPP

#include <autonomy/util/serialization.hpp>
#include <autonomy/action/mine.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/entity/universe.hpp>
#include <autonomy/entity/scripted_drone.hpp>
#include <autonomy/entity/asteroid.hpp>
namespace autonomy
{
    namespace action_handler
    {
        class mine_default
            : public action_handler_base<action::mine, entity::asteroid>
        {
            public:
                virtual ~mine_default(){}

                virtual void execute( entity::asteroid & entity, size_t which_queue );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(mine_handler_base_t);
                }
        };

        class mine_location_default
            : public action_handler_base<action::mine_location, entity::universe>
        {
            public:
                virtual ~mine_location_default(){}

                virtual void execute( entity::universe & entity, size_t which_queue );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(mine_location_handler_base_t);
                }
        };

        class mine_response_default
            : public action_handler_base<action::mine_response, entity::scripted_drone>
        {
            public:
                virtual ~mine_response_default(){}

                virtual void execute( entity::scripted_drone & entity, size_t which_queue );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(mine_response_handler_base_t);
                }
        };
    }
}
#endif
