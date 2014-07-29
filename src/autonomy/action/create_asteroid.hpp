//! \file
//! \brief Create action/response.  Needed by the Universe entity to add new entities.

#include <autonomy/action/create_asteroid.fwd.hpp>

#ifndef AUTONOMY_ACTION_CREATE_ASTEROID_HPP
#define AUTONOMY_ACTION_CREATE_ASTEROID_HPP

#include <autonomy/action.hpp>
#include <autonomy/entity.hpp>
#include <autonomy/entity/universe.hpp>
#include <autonomy/entity/drone.hpp>
#include <autonomy/util/serialization.hpp>
#include <autonomy/util/coord_pair.hpp>
#include <autonomy/instruction_list.hpp>
#include <autonomy/action_handler/create_asteroid_default.hpp>

namespace autonomy
{
    namespace action
    {
        class create_asteroid
            : public action_base<entity::universe>
        {
            public:
                create_asteroid( int fuel,
                                 util::coord_pair location,
                                 entity_id_t subject )
                    : _location(location), _fuel(fuel),  
                      _subject(subject)
                {}

                virtual ~create_asteroid()
                {}

                virtual action_handler_id_t default_handler_type() const
                {
                    return action_handler_id_t(static_cast<action_handler::create_asteroid_default*>(NULL));
                }

                virtual action_handler_generic * default_handler();

                entity_id_t subject() const { return _subject; }
                util::coord_pair location() const { return _location; }
                int fuel() const { return _fuel; }
            private:
                create_asteroid(){}
                util::coord_pair _location;
                int _fuel;
                entity_id_t _subject;

                friend class boost::serialization::access;
                template < class Archive >
                void serialize(Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<entity::universe>);
                    ar & BOOST_SERIALIZATION_NVP(_subject);
                    ar & BOOST_SERIALIZATION_NVP(_fuel);
                    ar & BOOST_SERIALIZATION_NVP(_location);
                }
        };

        class create_asteroid_response
            : public action_base<entity::drone>
        {
            public:
                create_asteroid_response( bool created )
                    : _created(created)
                {}

                virtual ~create_asteroid_response()
                {}

                virtual action_handler_id_t default_handler_type() const
                {
                    return action_handler_id_t(static_cast<action_handler::create_asteroid_response_default*>(NULL));
                }

                virtual action_handler_generic * default_handler();

                bool is_created () const
                {
                    return _created;
                }
            private:
                create_asteroid_response(){}
                bool _created;

                friend class boost::serialization::access;
                template < class Archive >
                void serialize(Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<entity::drone>);
                    ar & BOOST_SERIALIZATION_NVP(_created);
                }
        };
    }
}
#endif
