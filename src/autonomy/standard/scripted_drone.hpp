#include <autonomy/standard/scripted_drone.fwd.hpp>
#ifndef AUTONOMY_ENTITY_SCRIPTED_DRONE_HPP
#define AUTONOMY_ENTITY_SCRIPTED_DRONE_HPP

#include <map>
#include <typeinfo>

#include <autonomy/util/serialization.hpp>
#include <autonomy/standard/drone.hpp>
#include <autonomy/instruction_list.hpp>
#include <autonomy/standard/script_stack.hpp>

namespace autonomy { namespace standard
{
  class scripted_drone
    : public drone
  {
    public:
      scripted_drone(entity_id_t uni,
          boost::shared_ptr< instruction_list > script,
          int fuel = 0)
        : drone(uni, fuel), _script(script), 
        _pc(0), _wait_ticks(0)
    { }

      virtual ~scripted_drone(){}

      int pop_stack()
      {
        int top = _stack.back();
        _stack.pop_back();
        return top;
      }

      void push_stack(int i)
      {
        _stack.push_back(i);
      }

      void set_local_var(int id, int val)
      {
        _local_variable_store[id] = val;
      }

      int get_local_var(int id) const
      {
        return _local_variable_store.find(id)->second;
      }

      void goto_inst(int line);
      void move_inst(int off);
    private:
      scripted_drone(){}

      script_stack _stack;
      std::map< int, int > _local_variable_store;

      boost::shared_ptr< instruction_list > _script;
      int _pc;
      unsigned int _wait_ticks;

      virtual void controller();
#if 0
      template <class Archive>
        void save( Archive & ar, const unsigned int version )
        {
          ar << boost::serialization::base_object<const drone>(*this);
          ar << _local_variable_store;
          ar << _stack;
          ar << _wait_ticks;
          ar << _script;
          ar << (_next_inst - (*_script).begin());
        }

      template < class Archive >
        void load( Archive & ar, const unsigned int version )
        {
          size_t pc;
          ar >> boost::serialization::base_object<drone>(*this);
          ar >> _local_variable_store;
          ar >> _stack;
          ar >> _wait_ticks;
          ar >> _script;
          ar >> pc;
          _next_inst = (*_script).begin() + pc;
        }
#endif
      friend class boost::serialization::access;
      template < class Archive >
        void serialize ( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(drone);
          ar & BOOST_SERIALIZATION_NVP(_local_variable_store);
          ar & BOOST_SERIALIZATION_NVP(_stack);
          ar & BOOST_SERIALIZATION_NVP(_wait_ticks);
          ar & BOOST_SERIALIZATION_NVP(_script);
          ar & BOOST_SERIALIZATION_NVP(_pc);
        }
      //BOOST_SERIALIZATION_SPLIT_MEMBER();
    public:
      // XXX:  this is temporary it is meant only to serve until
      // ADL can support non-integral types, the values are here
      // assigned explicitly to be absolutely certain that different
      // machines/compilations will interpret the values in the
      // same way
      enum entity_type { EMPTY    = 0, 
        ASTEROID = 1, 
        DRONE    = 2, 
        BASE     = 3};
  };
}}
#endif
