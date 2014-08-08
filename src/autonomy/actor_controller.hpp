#ifndef AUTONOMY_ACTOR_CONTROLLER_HPP
#define AUTONOMY_ACTOR_CONTROLLER_HPP

#include <autonomy/actor.hpp>
#include <autonomy/actor_request.hpp>
#include <autonomy/actor_group.hpp>
#include <autonomy/actor_message_type.hpp>

namespace autonomy
{
  class actor_controller
  {
    public:
      static constexpr actor_message_type msg(const char* str)
      {
        return actor_message_type();
      }

      template<typename T, typename... Args>
        actor spawn(Args&&... args)
        {
          return actor();
        }

      template<int Msg, typename... Args>
        actor_request send(actor dest, Args&&... args)
        {
          return actor_request();
        }

      template<int Msg, typename... Args>
        actor_request send(actor_group dest, Args&&... args)
        {
          return actor_request();
        }

      actor_group create_group()
      {
        return actor_group();
      }

  };

}

#endif
