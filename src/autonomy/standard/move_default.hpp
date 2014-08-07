#include <autonomy/standard/move_default.fwd.hpp>

#ifndef AUTONOMY_ACTION_HANDLER_MOVE_DEFAULT_HPP
#define AUTONOMY_ACTION_HANDLER_MOVE_DEFAULT_HPP

#include <autonomy/standard/move.hpp>

namespace autonomy { namespace standard
{
  class move_direction_default
    : public action_handler_base<move_direction, universe>
  {
    public:
      virtual ~move_direction_default(){}

      virtual void execute( universe & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(move_direction_handler_base_t);
        }
  };

  class move_direction_response_default
    : public action_handler_base<move_direction_response, scripted_drone>
  {
    public:
      virtual ~move_direction_response_default(){}

      virtual void execute( scripted_drone & entity );

    private:
      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(move_direction_response_handler_base_t);
        }
  };
}}
#endif
