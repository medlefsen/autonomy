#ifndef AUTONOMY_ACTOR_REQUEST_HPP
#define AUTONOMY_ACTOR_REQUEST_HPP

namespace autonomy
{
  class actor_request
  {
    public:
      void send() { 
      }

      void wait() {
      }

      template<typename T>
        T get() {
          return T();
        }

      template<typename F>
        actor_request& then(F&& f)
        {
          return *this;
        }

  };
}

#endif
