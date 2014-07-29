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
      universe(game & which_game)
          : entity_base<universe>(), _which_game(&which_game)
      {}

      virtual ~universe()
      {}

      location_module<game> & location_module() const;

      autonomy::processor & processor() const;

      autonomy::game & which_game() const
      {
          return (*_which_game);
      }

      private:
      universe(){}
      game * _which_game;

      virtual void controller(size_t actv);

      friend class boost::serialization::access;
      template < class Archive >
      void serialize(Archive & ar, const unsigned int version )
      {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(entity_base<universe>);
          ar & BOOST_SERIALIZATION_NVP(_which_game);
      }
  };
}}
#endif
