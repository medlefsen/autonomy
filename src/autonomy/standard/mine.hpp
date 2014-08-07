//! \file
//! \brief Mine action/response pair, recognized by asteroid entities.

#include <autonomy/standard/mine.fwd.hpp>

#ifndef AUTONOMY_ACTION_MINE_HPP
#define AUTONOMY_ACTION_MINE_HPP

#include <autonomy/action.hpp>
#include <autonomy/entity.hpp>
#include <autonomy/action_handler.hpp>
#include <autonomy/util/serialization.hpp>
#include <autonomy/util/coord_pair.hpp>
#include <autonomy/standard/mine_default.hpp>

namespace autonomy { namespace standard
{
  class mine 
    : public action_base<asteroid>
  {
    friend class boost::serialization::access;
    public:
    mine( int fuel, entity_id_t subject )
      : action_base<asteroid>(), _fuel(fuel), 
      _subject(subject)

    {}

    virtual ~mine()
    {}

    virtual action_handler_id_t default_handler_type() const
    {
      return action_handler_id_t(static_cast<mine_default*>(NULL));
    }

    virtual action_handler_generic * default_handler() const;

    int fuel() const { return _fuel; }
    entity_id_t subject() const { return _subject; }
    private:
    mine(){}
    int _fuel;
    entity_id_t _subject;

    template <class Archive>
      void serialize(Archive & ar, const  unsigned int version )
      {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<asteroid>);
        ar & BOOST_SERIALIZATION_NVP(_fuel);
        ar & BOOST_SERIALIZATION_NVP(_subject);
      }
  };

  class mine_location 
    : public action_base<universe>
  {

    friend class boost::serialization::access;
    public:
    mine_location( util::coord_pair location, 
        int fuel, entity_id_t subject )
      : action_base<universe>(), _location(location),
      _fuel(fuel), _subject(subject)
    {}

    virtual ~mine_location()
    {}

    virtual action_handler_id_t default_handler_type() const
    {
      return action_handler_id_t(static_cast<mine_location_default*>(NULL));
    }

    virtual action_handler_generic * default_handler() const;

    util::coord_pair location() const { return _location; }
    int fuel() const { return _fuel; }
    entity_id_t subject() const { return _subject; }
    private:
    mine_location(){}
    util::coord_pair _location;
    int _fuel;
    entity_id_t _subject;

    template <class Archive>
      void serialize(Archive & ar, const  unsigned int version )
      {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<universe>);
        ar & BOOST_SERIALIZATION_NVP(_location);
        ar & BOOST_SERIALIZATION_NVP(_fuel);
        ar & BOOST_SERIALIZATION_NVP(_subject);
      }
  };

  class mine_response 
    : public action_base<scripted_drone>
  {
    friend class boost::serialization::access;
    public:
    mine_response( int fuel )
      : action_base<scripted_drone>(), _fuel(fuel)
    {}

    virtual ~mine_response()
    {}

    virtual action_handler_id_t default_handler_type() const
    {
      return action_handler_id_t(static_cast<mine_response_default*>(NULL));
    }

    virtual action_handler_generic * default_handler() const;

    int fuel() const { return _fuel; }
    private:
    mine_response(){}
    int _fuel;

    template <class Archive>
      void serialize(Archive & ar, const  unsigned int version )
      {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<scripted_drone>);
        ar & BOOST_SERIALIZATION_NVP(_fuel);
      }
  };
}}
#endif
