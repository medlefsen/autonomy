//! \file
//! \brief Simple scan action/response pair.  

#include <autonomy/action/scan.fwd.hpp>

#ifndef AUTONOMY_ACTION_SCAN_HPP
#define AUTONOMY_ACTION_SCAN_HPP

#include <autonomy/util/serialization.hpp>
#include <autonomy/util/coord_pair.hpp>
#include <autonomy/action.hpp>
#include <autonomy/entity.hpp>
#include <autonomy/entity/universe.hpp>
#include <autonomy/entity/scripted_drone.hpp>
#include <autonomy/action_handler/scan_default.hpp>

namespace autonomy
{
    namespace action
    {
        class scan 
            : public action_base<entity::universe>
        {
            public:
                scan(util::coord_pair location, entity_id_t subject)
                    : _location(location), _subject(subject)
                {}

                virtual ~scan()
                {}

                virtual action_handler_id_t default_handler_type() const
                {
                    return action_handler_id_t(static_cast<action_handler::scan_default*>(NULL));
                }

                virtual action_handler_generic * default_handler();

                util::coord_pair location () const { return _location; }
                entity_id_t subject () const { return _subject; }
            private:
                scan() {}
                util::coord_pair _location;
                entity_id_t _subject;

                friend class boost::serialization::access;
                template <class Archive>
                void serialize(Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<entity::universe>);
                    ar & BOOST_SERIALIZATION_NVP(_subject);
                    ar & BOOST_SERIALIZATION_NVP(_location);
                }
        };

        class scan_response 
            : public action_base<entity::scripted_drone>
        {
            public:
                scan_response(entity_id_t en)
                    : _entity(en)
                {}

                virtual ~scan_response()
                {}

                virtual action_handler_id_t default_handler_type() const
                {
                    return action_handler_id_t(static_cast<action_handler::scan_response_default*>(NULL));
                }

                virtual action_handler_generic * default_handler();

                entity_id_t entity () const { return _entity; }
            private:
                scan_response() {}
                entity_id_t _entity;

                friend class boost::serialization::access;
                template <class Archive>
                void serialize(Archive & ar, const unsigned int version )
                {
                    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<entity::scripted_drone>);
                    ar & BOOST_SERIALIZATION_NVP(_entity);
                }
        };
    }
}
#endif
