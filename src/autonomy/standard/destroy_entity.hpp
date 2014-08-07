//! \file
//! \brief Destroy entity action.  Signals the universe to destroy an entity.
//! 
//! Primary Author:  Dylan Leeman

#include <autonomy/standard/destroy_entity.fwd.hpp>

#ifndef AUTONOMY_ACTION_DESTROY_ENTITY_HPP
#define AUTONOMY_ACTION_DESTROY_ENTITY_HPP

#include <autonomy/util/serialization.hpp>
#include <autonomy/action.hpp>
#include <autonomy/entity.hpp>
#include <autonomy/universe.hpp>
#include <autonomy/standard/destroy_entity_default.hpp>

namespace autonomy { namespace standard
{
  class hide_entity
    : public action_base<universe>
  {
    public:
      hide_entity( entity_id_t entity )
        : _entity(entity)
      { }

      virtual ~hide_entity()
      {}

      virtual action_handler_id_t default_handler_type() const
      {
        return action_handler_id_t(static_cast<hide_entity_default*>(NULL));
      }

      virtual action_handler_generic * default_handler() const;

      entity_id_t entity() const { return _entity; }
    private:
      hide_entity(){}

      entity_id_t _entity;

      friend class boost::serialization::access;
      template <class Archive>
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<universe>);
          ar & BOOST_SERIALIZATION_NVP(_entity);
        }
  };

  class destroy_entity
    : public action_base<universe>
  {
    public:
      destroy_entity( entity_id_t entity )
        : _entity(entity)
      {}

      virtual ~destroy_entity()
      {}

      virtual action_handler_id_t default_handler_type() const 
      {
        return action_handler_id_t(static_cast<destroy_entity_default*>(NULL));
      }

      virtual action_handler_generic * default_handler() const;

      entity_id_t entity() const { return _entity; }
    private:
      destroy_entity(){}

      entity_id_t _entity;

      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<universe>);
          ar & BOOST_SERIALIZATION_NVP(_entity);
        }
  };
}}
#endif
