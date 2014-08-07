#ifndef AUTONOMY_SCRIPT_COMMANDS_HPP
#define AUTONOMY_SCRIPT_COMMANDS_HPP
#include <boost/random.hpp>

#include <autonomy/script_instruction.hpp>
#include <autonomy/standard/scripted_drone.hpp>

namespace autonomy 
{
    //! \brief Move command.
    //! Takes 2 "directions", up and right.
    //! A direction is either positive, 0 or negative
    struct move : public script_instruction_base<move>
    {
        friend class boost::serialization::access;
        static std::string name() { return "move"; }
        unsigned int execute(standard::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<move>);
            }
    };

    struct get_x : public script_instruction_base<get_x>
    {
        friend class boost::serialization::access;
        static std::string name() { return "get_x"; }
        unsigned int execute(standard::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<get_x>);
            }
    };

    struct get_y : public script_instruction_base<get_y>
    {
        friend class boost::serialization::access;
        static std::string name() { return "get_y"; }
        unsigned int execute(standard::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<get_y>);
            }
    };

    //! \brief scan command
    //! Takes an x and a y and returns an "object type"
    struct scan : public script_instruction_base<scan>
    {
        friend class boost::serialization::access;
        static std::string name() { return "scan"; }
        unsigned int execute(standard::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<scan>);
            }
    };

    struct is_drone : public script_instruction_base<is_drone>
    {
        friend class boost::serialization::access;
        static std::string name() { return "is_drone"; }
        unsigned int execute(standard::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<is_drone>);
            }
    };

    struct is_asteroid : public script_instruction_base<is_asteroid>
    {
        friend class boost::serialization::access;
        static std::string name() { return "is_asteroid"; }
        unsigned int execute(standard::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<is_asteroid>);
            }
    };

    struct is_base : public script_instruction_base<is_base>
    {
        friend class boost::serialization::access;
        static std::string name() { return "is_base"; }
        unsigned int execute(standard::scripted_drone & drone );
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<is_base>);
            }
    };

    //! \brief Random direction command
    //! Returns a random "direction" which is either -1, 0, or 1
    struct rand_dir : public script_instruction_base<rand_dir>
    {
        friend class boost::serialization::access;
        rand_dir()
        {}
        static std::string name() { return "rand_dir"; }
        unsigned int execute(standard::scripted_drone & drone);
        static boost::mt19937 rng;
        static boost::uniform_int<> dir;
        static boost::variate_generator<boost::mt19937&, boost::uniform_int<> > _rand_dir;
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<rand_dir>);
            }
    };

    //! \brief Mine command
    //! Takes an x, and a y and mines an asteroid some set amount if there is one there
    struct mine : public script_instruction_base<mine>
    {
        friend class boost::serialization::access;
        static std::string name() { return "mine"; }
        unsigned int execute(standard::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<mine>);
            }
    };
    
    //! \brief Unload command
    //! Takes an x, and a y and unloads some set amount to a basestation
    struct unload : public script_instruction_base<unload>
    {
        friend class boost::serialization::access;
        static std::string name() { return "unload"; }
        unsigned int execute(standard::scripted_drone & drone);
        private:
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(script_instruction_base<unload>);
            }
    };
}
#endif
