#include <autonomy/standard/destroy_entity_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_DESTROY_ENTITY_DEFAULT_HPP
#define AUTONOMY_ACTION_HANDLER_DESTROY_ENTITY_DEFAULT_HPP

#include <autonomy/standard/destroy_entity.hpp>
#include <autonomy/universe.hpp>
#include <autonomy/util/serialization.hpp>
#include <autonomy/action_handler.hpp>
namespace autonomy { namespace standard
{
  class hide_entity_default
    : public action_handler_base< hide_entity, universe >
  {
    public:
      virtual ~hide_entity_default(){} 

      virtual void execute( universe & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(hide_entity_handler_base_t);
        }
  };

  class destroy_entity_default
    : public action_handler_base< destroy_entity, universe >
  {
    public:
      virtual ~destroy_entity_default(){}

      virtual void execute( universe & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(destroy_entity_handler_base_t);
        }

  };
}}
#endif
