#ifndef AUTONOMY_ACTOR_MESSAGE_HPP
#define AUTONOMY_ACTOR_MESSAGE_HPP

#include <autonomy/actor_message_type.hpp>
#include <string>

namespace autonomy
{
  class actor_message
  {
    public:
      actor_message_type type()
      {
        return actor_message_type();
      }

      std::string name()
      {
        return "";
      }
  };
}

#endif
