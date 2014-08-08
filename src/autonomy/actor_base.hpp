#ifndef AUTONOMY_ACTOR_BASE_HPP
#define AUTONOMY_ACTOR_BASE_HPP

#include <autonomy/actor.hpp>
#include <autonomy/actor_request.hpp>
#include <autonomy/actor_group.hpp>
#include <autonomy/actor_message.hpp>
#include <autonomy/actor_message_type.hpp>
#include <initializer_list>

#define AUTONOMY_ACTOR_HANDLERS(...) 

namespace autonomy
{
  class actor_base
  {
    protected:
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

      actor_message current()
      {
        return actor_message();
      }

      void forward_to(actor dest)
      {
      }

      void quit(unsigned int type = 0)
      {
      }

  };
}

#endif
