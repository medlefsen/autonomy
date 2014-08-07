#ifndef AUTONOMY_DRONE_HPP
#define AUTONOMY_DRONE_HPP
#include <typeinfo>

#include <boost/shared_ptr.hpp>

#include <autonomy/util/serialization.hpp>
#include <autonomy/entity.hpp>
#include <autonomy/standard/fueled.hpp>

namespace autonomy { namespace standard
{
  class drone
    : public entity_base<drone>,
    public fueled
  {
    private:
      typedef boost::shared_ptr< action_handler_generic > 
        _action_handler_ptr_t;
      typedef std::pair<action_type_id_t, _action_handler_ptr_t> 
        _action_handler_pair_t;
      typedef std::map<action_type_id_t, _action_handler_ptr_t> 
        _action_handler_relation_t;
    public:
      drone(){}
      virtual ~drone()
      { }

      entity_id_t universe() const { return _uni; }

    protected:
      drone(entity_id_t uni, int fuel = 0)
        : entity_base<drone>(), fueled(fuel), _uni(uni)
      { }

    private:
      entity_id_t _uni;

      _action_handler_relation_t _action_handler_relation;

      virtual void controller() = 0;

      friend class boost::serialization::access;
      template < class Archive >
        void serialize( Archive & ar, const unsigned int version )
        {
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(entity_base<drone>);
          ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(fueled);
          ar & BOOST_SERIALIZATION_NVP(_uni);
        }
  };
}}

#endif
