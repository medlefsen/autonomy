#ifndef AUTONOMY_UTIL_ID_HPP
#define AUTONOMY_UTIL_ID_HPP
#include <typeinfo>
#include <string>
namespace autonomy
{
    namespace util
    {
        template < typename IdentifiedT >
        class id
        {
            public:
                id()
                    : _type(typeid(IdentifiedT))
                {}

                id(const IdentifiedT & obj)
                    : _type(typeid(obj))
                {}

                template < typename FromIdentifiedT >
                id(const FromIdentifiedT & obj)
                    : _type(typeid(obj))
                {}

                template < typename OpIdentifiedT >
                friend bool operator< (const id<OpIdentifiedT> & left, const id<OpIdentifiedT> & right);

                template < typename OpIdentifiedT >
                friend bool operator ==(const id<OpIdentifiedT> & left, const id<OpIdentifiedT> & right);

                template < typename OpIdentifiedT >
                friend bool operator !=(const id<OpIdentifiedT> & left, const id<OpIdentifiedT> & right);

                // XXX:  need to figure out something cleaner to achieve this
                //       or alter the comparison functions to use this
                const std::type_info & type() const { return  _type; }

                const std::string name() const { return _type.name(); }
            private:
                const std::type_info & _type;
        };

        template < typename IdentifiedT >
        inline
        bool operator< (const id<IdentifiedT> & left, const id<IdentifiedT> & right)
        {
            return static_cast<bool>(left._type.before(right._type));
        }

        template < typename IdentifiedT >
        inline
        bool operator== (const id<IdentifiedT> & left, const id<IdentifiedT> & right)
        {
            return static_cast<bool>(left._type == right._type);
        }

        template < typename IdentifiedT >
        inline
        bool operator!= (const id<IdentifiedT> & left, const id<IdentifiedT> & right)
        {
            return static_cast<bool>(left._type != right._type);
        }

    }
}
#endif
