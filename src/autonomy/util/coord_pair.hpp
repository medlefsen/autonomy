//! \file
//! \brief Defines the coord_pair type.

#ifndef AUTONOMY_UTIL_LOCATION_HPP
#define AUTONOMY_UTIL_LOCATION_HPP

#include <iostream>
#include <boost/integer_traits.hpp>
#include <autonomy/util/serialization.hpp>

namespace autonomy
{
    namespace util
    {
        //! \class coord_pair
        //! \brief Class used to pass around object coord_pairs.
        class coord_pair
        {
            friend class boost::serialization::access;
            friend std::ostream &  operator<<( std::ostream & os, const coord_pair & coord );
            friend std::istream & operator >>( std::istream & is, coord_pair & coord );
            public:
                coord_pair(int x = int (), int y = int ())
                    : _x(x), _y(y)
                {}

                int& x()
                {
                    return _x;
                }

                int x() const
                {
                    return _x;
                }

                int& y()
                {
                    return _y;
                }

                int y() const
                {
                    return _y;
                }

            private:
                int _x;
                int _y;

                template < class Archive >
                    void serialize( Archive & ar, const unsigned int version )
                    {
                        ar & BOOST_SERIALIZATION_NVP(_x);
                        ar & BOOST_SERIALIZATION_NVP(_y);
                    }
        };

        inline
        bool operator==(coord_pair left, coord_pair right)
        {
            return (left.x() == right.x())
                   && (left.y() == right.y());
        }

        inline
        bool operator!=(coord_pair left, coord_pair right)
        {
            return !(left == right);
        }

        const coord_pair INVALID_LOCATION(
            boost::integer_traits< int >::const_max,
            boost::integer_traits< int >::const_max );

        inline
        std::ostream &  operator<<( std::ostream & os, const coord_pair & coord )
        {
            os << '(' <<  coord.x() << ',' << coord.y() << ')';
            return os;
        }

        inline
        std::istream & operator >>( std::istream & is, coord_pair & coord )
        {
            is >> coord._x >> coord._y;
            return is;
        }
    }
}
#endif
