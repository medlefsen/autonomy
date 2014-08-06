//! \file
//! \brief defines the built-in capabilities of the drone language
//!
//! Each built-in capability in the drone language is implemented
//! as an object.  This object contains a method called execute
//! which acts upon the data stack or does work through some
//! other mechanism.

#ifndef AUTONOMY_SCRIPT_BUILTINS_HPP
#define AUTONOMY_SCRIPT_BUILTINS_HPP
#include <boost/lexical_cast.hpp>

#include <autonomy/script_instruction.hpp>
#include <autonomy/entity/scripted_drone.hpp>

namespace autonomy { namespace script_builtins{  
    //! \brief duplicate the top data element
    //!
    //! push a duplicate of the top stack element onto the stack
    struct dup : public script_instruction_base<dup> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "dup"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<dup>);
            }

    };

    //! \brief pop the top data element from the stack
    struct pop : public script_instruction_base<pop> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "pop"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<pop>);
            }

    };

    //! \brief add two data elements
    //!
    //! pop the top two elements from the stack and push their sum back 
    //! onto the stack
    struct add : public script_instruction_base<add> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "add"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<add>);
            }
    };

    //! \brief subtract one data element from another
    //!
    //! pop the top two elements from the stack. subtract the top element 
    //! from the next element and push the difference back onto the stack
    struct sub : public script_instruction_base<sub> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "sub"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<sub>);
            }
    };

    //! \brief multiply two data elements
    //!
    //! pop the top two elements from the stack and push their product 
    //! back onto the stack
    struct multiply : public script_instruction_base<multiply> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "multiply"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<multiply>);
            }
    };

    //! \brief divide a data element by another
    //!
    //! pop the top two elements from the stack. divide the top element 
    //! from the next element and push the difference back onto the stack
    struct divide : public script_instruction_base<divide> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "divide"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<divide>);
            }
    };

    //! \brief raise a data element to the power of another
    //!
    //! pop the first element from the stack, raise it to the power of the
    //! second item popped and push the result back onto the stack
    struct power : public script_instruction_base<power> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "power"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<power>);
            }
    };

    //! \brief jump to a given instruction based on an absolute location
    struct jump : public script_instruction_base<jump> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "jump"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<jump>);
            }
    };

    //! \brief jump to a given instruction based on a relative location
    struct rel_jump : public script_instruction_base<rel_jump> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "rel_jump"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<rel_jump>);
            }
    };

    //! \brief jump to a given instruction based on an abosolute location
    //! if a condition evaulates as true
    struct cond_jump : public script_instruction_base<cond_jump> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "cond_jump"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<cond_jump>);
            }
    };

    //! \brief jump to a given instruction based on a relative location
    //! if a condition evaulates as true
    struct cond_rel_jump : public script_instruction_base<cond_rel_jump> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "cond_rel_jump"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<cond_rel_jump>);
            }
    };

    //! \brief determine if two data elements are equal
    //!
    //! pop the top two elements off the stack and push 1 if equal else
    //! push 0 back onto the stack
    struct equals : public script_instruction_base<equals> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "equals"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<equals>);
            }
    };

    //! \brief determine if one data element is less than another
    //!
    //! pop the top two elements off the stack, if the second element
    //! is less than the first element, push 1, else pus 0 back onto the
    //! stack
    struct less_than : public script_instruction_base<less_than> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "less_than"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<less_than>);
            }
    };

    //! \brief logical AND comparison of two data elements
    struct logical_and : public script_instruction_base<logical_and> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "and"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<logical_and>);
            }
    };

    //! \brief logical OR comparison of two data elements
    struct logical_or : public script_instruction_base<logical_or> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "or"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<logical_or>);
            }
    };

    //! \brief logical NOT of a data element
    struct logical_not : public script_instruction_base<logical_not> 
    {
        friend class boost::serialization::access;
        static std::string name() { return "not"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<logical_not>);
            }
    };

    //! \brief a literal value (e.g. 5, 31, 12)
    class literal : public script_instruction_base<literal> 
    {
        friend class boost::serialization::access;
        public:
        literal(int val = 0)
            : _val(val)
        {}
        std::string name() const { return "literal " + boost::lexical_cast<std::string>(_val); }

        virtual unsigned int execute(entity::scripted_drone & drone);

        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<literal>);
                ar & BOOST_SERIALIZATION_NVP(_val);
            }
        int _val;
    };

    //! \brief load an instruction
    struct load : public script_instruction_base<load>
    {
        friend class boost::serialization::access;
        static std::string name() { return "load"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<load>);
            }
    };

    //! \brief store an instruction
    struct store : public script_instruction_base<store>
    {
        friend class boost::serialization::access;
        static std::string name() { return "store"; }
        virtual unsigned int execute(entity::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<store>);
            }
    };

}}
#endif
