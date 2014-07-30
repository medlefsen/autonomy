//! \file
//! \brief UI generic
//!
//! Primary Author:  Matt Edlefsen

#ifndef AUTONOMY_GENERIC_UI_HPP
#define AUTONOMY_GENERIC_UI_HPP

#include <memory>
#include <type_traits>

namespace autonomy
{
  template<typename Parent>
  class generic_ui
  {
    private:
      struct adapter_base
      {
        virtual void init(Parent& parent) = 0;
        virtual void do_update() = 0;
      };
      template<typename T>
        struct adapter : adapter_base
      {
        public:
          template<typename... Args>
          adapter(Args&&... args) : value_(std::forward<Args>(args)...) { }

          virtual void init(Parent& parent)
          {
            value_.init(parent);
          }
          virtual void do_update()
          {
            value_.do_update();
          }
        private:
          T value_;
      };

    public:
      template<typename T>
      explicit generic_ui(typename std::enable_if<!std::is_same<typename std::remove_reference<T>::type,std::shared_ptr<adapter_base>>::value,T&&>::type t)
        : adapter_(std::make_shared<adapter<typename std::remove_reference<T>::type>>(std::forward<T>(t)))
      {
      }


      template<typename T, typename... Args>
        static generic_ui create(Args&&... args) {
          return generic_ui(std::make_shared<adapter<typename std::remove_reference<T>::type>>(std::forward<Args>(args)...));
        }

      void init(Parent& parent)
      {
        adapter_->init(parent);
      }

      void do_update()
      {
        adapter_->do_update();
      }

    private:
      explicit generic_ui(std::shared_ptr<adapter_base> value) : adapter_(value)
      {
      }

      std::shared_ptr<adapter_base> adapter_;
  };

}

#endif
