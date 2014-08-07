//! \file
//! \brief Create action/response.  Needed by the Universe entity to add new entities.

#include <autonomy/standard/create_drone.fwd.hpp>

#ifndef AUTONOMY_ACTION_CREATE_DRONE_HPP
#define AUTONOMY_ACTION_CREATE_DRONE_HPP

#include <autonomy/action.hpp>
#include <autonomy/entity.hpp>
#include <autonomy/standard/scripted_drone.hpp>
#include <autonomy/util/serialization.hpp>
#include <autonomy/script_object.hpp>
#include <autonomy/util/coord_pair.hpp>
#include <autonomy/instruction_list.hpp>
#include <autonomy/standard/create_drone_default.hpp>

namespace autonomy { namespace standard
{
  class create_drone
    : public action_base<universe>
  {
    public:
      create_drone( int fuel,
          util::coord_pair location,
          boost::shared_ptr<instruction_list> script,
          entity_id_t subject )
        : _location(location), _fuel(fuel), _script(script),
        _subject(subject)
    {}

      virtual ~create_drone()
      {}

      virtual action_handler_id_t default_handler_type() const
      {
        return action_handler_id_t(static_cast<create_drone_default*>(NULL));
      }

      virtual action_handler_generic * default_handler() const;

      entity_id_t subject() const { return _subject; }
      util::coord_pair location() const { return _location; }
      int fuel() const { return _fuel; }
      boost::shared_ptr<instruction_list> script() const { return _script; }
    private:
      create_drone(){}
      util::coord_pair _location;
      int _fuel;
      boost::shared_ptr<instruction_list> _script;
      entity_id_t _subject;

      friend class boost::serialization::access;
      template < class Archive >
        void serialize(Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<universe>);
          ar & BOOST_SERIALIZATION_NVP(_subject);
          ar & BOOST_SERIALIZATION_NVP(_fuel);
          ar & BOOST_SERIALIZATION_NVP(_location);
          ar & BOOST_SERIALIZATION_NVP(_script);
        }
  };

  class create_drone_response
    : public action_base<drone>
  {
    public:
      create_drone_response( bool created )
        : _created(created)
      {}

      virtual ~create_drone_response()
      {}

      virtual action_handler_id_t default_handler_type() const
      {
        return action_handler_id_t(static_cast<create_drone_response_default*>(NULL));
      }

      virtual action_handler_generic * default_handler() const;

      bool is_created () const
      {
        return _created;
      }
    private:
      create_drone_response(){}
      bool _created;

      friend class boost::serialization::access;
      template < class Archive >
        void serialize(Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<drone>);
          ar & BOOST_SERIALIZATION_NVP(_created);
        }
  };
}}
#endif
