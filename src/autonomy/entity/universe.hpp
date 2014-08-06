//! \file
//! \brief Universe class declaration.
//! 
//! Primary Author: Dylan Leeman
//! Contributing Authors: Andrew Fitz-Gibbon, Dylan Parkhurst

#include <autonomy/entity/universe.fwd.hpp>
#ifndef AUTONOMY_UNIVERSE_HPP
#define AUTONOMY_UNIVERSE_HPP
#include <boost/shared_ptr.hpp>

#include <autonomy/util/serialization.hpp>
#include <autonomy/game.hpp>
#include <autonomy/entity.hpp>

namespace autonomy { namespace entity
{
  class universe
      : public entity_base<universe>
  {
      public:
      universe(game& g)
          : entity_base<universe>(), game_(&g)
      {}

      virtual ~universe()
      {}

      void add(entity_id_t entity_ptr);
    
      void remove(entity_id_t entity_ptr);

      location_module & location_module() const;
      game& which_game();

      private:
      universe(){}
      game* game_;

      virtual void controller();

      friend class boost::serialization::access;
      template < class Archive >
      void serialize(Archive & ar, const unsigned int version )
      {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(entity_base<universe>);
          ar & BOOST_SERIALIZATION_NVP(game_);
      }
  };
}}
#endif
