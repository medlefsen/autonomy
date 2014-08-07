#ifndef AUTONOMY_ASTEROID_HPP
#define AUTONOMY_ASTEROID_HPP
#include <typeinfo>

#include <autonomy/util/serialization.hpp>
#include <autonomy/entity.hpp>
#include <autonomy/standard/fueled.hpp>

namespace autonomy { namespace standard
{
  class asteroid
    : public entity_base<asteroid>,
    public fueled
  {
    friend class boost::serialization::access;
    public:
    asteroid(entity_id_t uni, int fuel = 0)
      : entity_base<asteroid>(), fueled(fuel), _uni(uni)
    {}

    virtual ~asteroid(){}

    entity_id_t universe() { return _uni; }
    private:
    asteroid(){}

    entity_id_t _uni;

    virtual void controller(); 

    template < class Archive >
      void serialize( Archive & ar, const unsigned int version )
      {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(entity_base<asteroid>);
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(fueled);
        ar & BOOST_SERIALIZATION_NVP(_uni);
      }

  };
}}

#endif
