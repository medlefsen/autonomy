#include <autonomy/action_handler/move_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_MOVE_DEFAULT_HPP
#define AUTONOMY_ACTION_HANDLER_MOVE_DEFAULT_HPP

#include <autonomy/action/move.hpp>

namespace autonomy
{
    namespace action_handler
    {
        class move_direction_default
            : public action_handler_base<action::move_direction, entity::universe>
        {
            public:
                virtual ~move_direction_default(){}

                virtual void execute( entity::universe & entity, 
                                      size_t which_queue );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(move_direction_handler_base_t);
                }
        };

        class move_direction_response_default
            : public action_handler_base<action::move_direction_response, entity::scripted_drone>
        {
            public:
                virtual ~move_direction_response_default(){}

                virtual void execute( entity::scripted_drone & entity, size_t which_queue );

            private:
                friend class boost::serialization::access;
                template < class Archive >
                void serialize( Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(move_direction_response_handler_base_t);
                }
        };
    }
}
#endif
