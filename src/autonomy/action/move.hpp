#include <autonomy/action/move.fwd.hpp>
#ifndef AUTONOMY_ACTION_MOVE_HPP
#define AUTONOMY_ACTION_MOVE_HPP

#include <autonomy/util/serialization.hpp>
#include <autonomy/action.hpp>
#include <autonomy/entity.hpp>
#include <autonomy/entity/drone.hpp>
#include <autonomy/entity/scripted_drone.hpp>
#include <autonomy/entity/universe.hpp>
#include <autonomy/action_handler/move_default.hpp>

namespace autonomy
{
    namespace action
    {
        class move_direction
            : public action_base<entity::universe>
        {
            public:
                move_direction(int horizontal, int vertical, entity_id_t subject ) 
                    : _horizontal(horizontal), _vertical(vertical), 
                    _subject(subject)
            {}

                virtual ~move_direction()
                {}

                virtual action_handler_id_t default_handler_type() const
                {
                    return action_handler_id_t(static_cast<action_handler::move_direction_default*>(NULL));
                }

                virtual action_handler_generic * default_handler();

                int horizontal () const { return _horizontal; }
                int vertical () const { return _vertical; }
                entity_id_t subject() const { return _subject; }
            private:
                move_direction() {}
                int _horizontal;
                int _vertical;
                entity_id_t _subject;

                friend class boost::serialization::access;
                template <class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<entity::universe>);
                    ar & BOOST_SERIALIZATION_NVP(_horizontal);
                    ar & BOOST_SERIALIZATION_NVP(_vertical);
                    ar & BOOST_SERIALIZATION_NVP(_subject);
                }
        };

        class move_direction_response 
            : public action_base<entity::scripted_drone>
        {
            public:
                move_direction_response(bool success)
                    : action_base<entity::scripted_drone>(),
                      _success(success)
                {}

                virtual ~move_direction_response()
                {}

                virtual action_handler_id_t default_handler_type() const
                {
                    return action_handler_id_t(static_cast<action_handler::move_direction_response_default*>(NULL));
                }

                virtual action_handler_generic * default_handler();

                bool success () const { return _success; }
            private:
                move_direction_response() {}
                bool _success;

                friend class boost::serialization::access;
                template <class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<entity::scripted_drone>);
                    ar & BOOST_SERIALIZATION_NVP(_success);
                }
        };
    }
}
#endif
