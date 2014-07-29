//! \file
//! \brief
//!
//! Primary Author:  Dylan Leeman

#include <autonomy/action.fwd.hpp>

#ifndef AUTONOMY_ACTION_HPP
#define AUTONOMY_ACTION_HPP

#include <memory>

#include <autonomy/util/serialization.hpp>
#include <autonomy/action_handler.hpp>

namespace autonomy
{
    //! \class
    //! \brief Fundamental base class of all actions.
    //!
    //! This class allows polymorphic collections of action objects.
    //!
    //! Classes deriving from action_base guarantee the following:
    //!   1.  default_handler_type() returns an action_handler_id_t 
    //!       corresponding to the handler retrieved with default_handler
    //!   2.  default_handler() returns a pointer to a handler that is
    //!       persistent for exactly the life of the action object
    class action_generic
    {
        public:
            action_generic()
            {}

            virtual ~action_generic(){}

            virtual action_handler_id_t default_handler_type() const  = 0;

            virtual action_handler_generic * default_handler() = 0;
        private:
            friend class boost::serialization::access;
            template < class Archive >
            void serialize( Archive & ar, const unsigned int version )
            {}
    };

    //! \class
    //! \brief Class from which to derive actions.
    //!
    //! All new action types should derive from this class.  The derivation
    //! should be parametrized with the type of entity this action targets.
    template < typename TargetT >
    class action_base
        : public action_generic
    {
        public:
            action_base()
            {}

            virtual ~action_base()
            {}

        private:
            friend class boost::serialization::access;
            template < class Archive >
            void serialize( Archive & ar, const unsigned int version )
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(action_generic);
            }
    };

    //! \class
    //! \brief StrictWeakOrdering functor for action_base, comparing default
    //!        handlers.
    template < typename TargetT >
    class action_default_handler_cmp
    {
        public:
            action_default_handler_cmp(){}

            bool operator() (const action_base< TargetT > & left,
                             const action_base< TargetT > & right)
            {
                return (left.default_handler_type() <
                        right.default_handler_type());
            }

            bool operator() (const action_base< TargetT > * left,
                             const action_base< TargetT > * right)
            {
                return (*this)(*left, *right);
            }
        private:
            friend class boost::serialization::access;
            template < class Archive >
            void serialize( Archive & ar, const unsigned int version )
            {}
    };
}
#endif
