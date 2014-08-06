#include <autonomy/script_instruction.fwd.hpp>
#include <autonomy/entity/scripted_drone.fwd.hpp>
#ifndef AUTONOMY_SCRIPT_INSTRUCTION_HPP
#define AUTONOMY_SCRIPT_INSTRUCTION_HPP

#include <string>
#include <typeinfo>
#include <autonomy/util/serialization.hpp>

namespace autonomy {

    class script_instruction
    {
        friend class boost::serialization::access;
        private:
            virtual unsigned int virtual_execute(entity::scripted_drone & drone) = 0;
            virtual std::string virtual_name() const = 0;

        protected:
            script_instruction()
            {}
        public:
            virtual ~script_instruction()
            {}
            unsigned int execute(entity::scripted_drone & drone)
            {
                return virtual_execute(drone);
            }
            std::string name() const
            {
                return virtual_name();
            }
        private:
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
            }

    };

    inline
    bool operator== (const script_instruction& left,
                     const script_instruction& right)
    {
        return (left.name() == right.name());
    }

    template < typename subclass >
    class script_instruction_base
        : public script_instruction
    {
        friend class boost::serialization::access;
        virtual unsigned int virtual_execute( entity::scripted_drone & drone);
        virtual std::string virtual_name() const;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction);
            }

    };


    template < typename subclass >
    unsigned int script_instruction_base< subclass >::virtual_execute(
        entity::scripted_drone & drone)
    {
        return static_cast< subclass* >(this)->execute(drone);
    }

    template < typename subclass >
    std::string script_instruction_base< subclass >::virtual_name() const
    {
        return static_cast< const subclass* >(this)->name();
    }

}
#endif
