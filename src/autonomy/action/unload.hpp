//! \file
//! \brief Unload action/response pair
//!
//! Primary Author:  Andrew Fitz Gibbon
//! Contributing Author:  Aaron Weeden

#include <autonomy/action/unload.fwd.hpp>

#ifndef AUTONOMY_ACTION_UNLOAD_HPP
#define AUTONOMY_ACTION_UNLOAD_HPP

#include <autonomy/action.hpp>
#include <autonomy/entity.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/util/serialization.hpp>
#include <autonomy/util/coord_pair.hpp>
#include <autonomy/action_handler/unload_default.hpp>

namespace autonomy
{
    namespace actor
    {
        class unload
            : public action_base<entity::base_station>
        {
            friend class boost::serialization::access;
            public:
                unload( int fuel, entity_id_t subject )
                    : action_base<entity::base_station>(), _fuel(fuel), 
                      _subject(subject)

                {}
                
                virtual ~unload()
                {}

                virtual action_handler_id_t default_handler_type() const
                {
                    return action_handler_id_t(static_cast<action_handler::unload_default*>(NULL));
                }

                virtual action_handler_generic * default_handler() const;

                int fuel() const { return _fuel; }
                entity_id_t subject() const { return _subject; }
            private:
                unload(){}
                int _fuel;
                entity_id_t _subject;

                template <class Archive>
                    void serialize(Archive & ar, const  unsigned int version )
                    {
                        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<entity::base_station>);
                        ar & BOOST_SERIALIZATION_NVP(_fuel);
                        ar & BOOST_SERIALIZATION_NVP(_subject);
                    }
        };

        class unload_fuel
            : public action_base<entity::universe>
        {
            
            friend class boost::serialization::access;
            public:
                unload_fuel( util::coord_pair location, 
                               int fuel, entity_id_t subject )
                    : action_base<entity::universe>(), _location(location),
                      _fuel(fuel), _subject(subject)
                {}

                virtual ~unload_fuel()
                {}

                virtual action_handler_id_t default_handler_type() const
                {
                    return action_handler_id_t(static_cast<action_handler::unload_fuel_default*>(NULL));
                }

                virtual action_handler_generic * default_handler() const;

                util::coord_pair location() const { return _location; }
                int fuel() const { return _fuel; }
                entity_id_t subject() const { return _subject; }
            private:
                unload_fuel(){}
                util::coord_pair _location;
                int _fuel;
                entity_id_t _subject;

                template <class Archive>
                    void serialize(Archive & ar, const  unsigned int version )
                    {
                        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<entity::universe>);
                        ar & BOOST_SERIALIZATION_NVP(_location);
                        ar & BOOST_SERIALIZATION_NVP(_fuel);
                        ar & BOOST_SERIALIZATION_NVP(_subject);
                    }
        };

        class unload_response 
            : public action_base<entity::scripted_drone>
        {
            friend class boost::serialization::access;
            public:
                unload_response( int fuel )
                    : action_base<entity::scripted_drone>(), _fuel(fuel)
                {}

                virtual ~unload_response()
                {}

                virtual action_handler_id_t default_handler_type() const
                {
                    return action_handler_id_t(static_cast<action_handler::unload_response_default*>(NULL));
                }

                virtual action_handler_generic * default_handler() const;
               
                int fuel() const { return _fuel; }
            private:
                unload_response(){}
                int _fuel;

                template <class Archive>
                    void serialize(Archive & ar, const  unsigned int version )
                    {
                        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<entity::scripted_drone>);
                        ar & BOOST_SERIALIZATION_NVP(_fuel);
                    }
        };
    }
}
#endif
