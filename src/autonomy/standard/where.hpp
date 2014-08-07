#include <autonomy/standard/where.fwd.hpp>

#ifndef AUTONOMY_ACTION_WHERE_HPP
#define AUTONOMY_ACTION_WHERE_HPP

#include <autonomy/util/serialization.hpp>
#include <autonomy/entity.hpp>
#include <autonomy/action.hpp>
#include <autonomy/standard/scripted_drone.hpp>
#include <autonomy/universe.hpp>
#include <autonomy/standard/where_default.hpp>

namespace autonomy { namespace standard
{
  class where 
    : public action_base<universe>
  {
    public:
      enum dimension { X, Y };

      where(dimension query_dimension, entity_id_t subject)
        : _query_dimension(query_dimension), _subject(subject)
      {}

      virtual ~where()
      {}

      virtual action_handler_id_t default_handler_type() const
      {
        return action_handler_id_t(static_cast<where_default*>(NULL));
      }

      virtual action_handler_generic * default_handler() const;

      dimension query_dimension() const { return _query_dimension; }
      entity_id_t subject() const { return _subject; }
    private:
      where(){}
      dimension _query_dimension;
      entity_id_t _subject;

      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<universe>);
          ar & BOOST_SERIALIZATION_NVP(_query_dimension);
          ar & BOOST_SERIALIZATION_NVP(_subject);
        }
  };

  class where_response 
    : public action_base<scripted_drone>
  {
    public:
      where_response(int distance)
        : action_base<scripted_drone>(),
        _distance(distance)
    {}

      virtual ~where_response()
      {}

      virtual action_handler_id_t default_handler_type() const
      {
        return action_handler_id_t(static_cast<where_response_default*>(NULL));
      }

      virtual action_handler_generic * default_handler() const;

      int distance() const { return _distance; }
    private:
      where_response(){}
      int _distance;

      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_base<scripted_drone>);
          ar & BOOST_SERIALIZATION_NVP(_distance);
        }
  };
}}
#endif
