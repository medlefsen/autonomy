#ifndef AUTONOMY_ENTITY_FUELED_HPP
#define AUTONOMY_ENTITY_FUELED_HPP
#include <autonomy/util/serialization.hpp>
namespace autonomy
{
    namespace entity
    {
        class fueled
        {
            friend class boost::serialization::access;
            public:
                fueled(int fuel = 0)
                    : _fuel(fuel)
                {}
                
                int  drain_fuel( int fuel_amount )
                {
                    _fuel -= fuel_amount;
                    return _fuel;
                }

                int add_fuel( int fuel_amount )
                {
                    _fuel += fuel_amount;
                    return _fuel;
                }

                int get_fuel () const
                {
                    return _fuel;
                }
            private:
                int _fuel;

                template < class Archive >
                    void serialize( Archive & ar, const unsigned int version )
                    {
                        ar & BOOST_SERIALIZATION_NVP(_fuel);
                    }
        };
    }
}
#endif
