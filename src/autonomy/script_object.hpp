//! \file script_object.hpp
//! \brief Header for script object

#ifndef AUTONOMY_SCRIPT_OBJECT_HPP
#define AUTONOMY_SCRIPT_OBJECT_HPP

#include <string>
#include <vector>

#include <istream>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread/mutex.hpp>

#include <autonomy/standard/scripted_drone.hpp>
#include <autonomy/instruction_list.hpp>
#include <autonomy/compiler/constants.hpp>
#include <autonomy/util/serialization.hpp>

namespace autonomy 
{
    typedef size_t script_object_id_t;
    class script_object
    {
        friend class boost::serialization::access;
        public:
            //! Default constructor.  Creates empty script object with the next
            //! available id
            script_object()
                : _name("script " + boost::lexical_cast< std::string >(_next_id))
            {
                _next_id_mutex.lock();
                _id = _next_id++;
                _next_id_mutex.unlock();
            }

            //! script_object constructor taking a name an optionally raw text
            //! to load the script_object with
            script_object(const std::string & name,
                          const std::string & adl_text = std::string())
                : _name(name),
                  _raw_form(adl_text)
            {
                _next_id_mutex.lock();
                _id = (_next_id++);
                _next_id_mutex.unlock();
            }

            //! Returns the unique id of the script object
            script_object_id_t id() const
            {
                return _id;
            }

            //! Returns the name of the script_object
            std::string name () const
            {
                return _name;
            }

            //! Returns a reference to the name of the script_object to allow
            //! the name to be set, should be used carefully with threads
            std::string & name()
            {
                return _name;
            }

            //! Returns a boost::shared_ptr to the compiled form of the script
            boost::shared_ptr< instruction_list > compiled_script() const
            {
                return _compiled_form;
            }

            //! compiles the contained raw script, returns a string containing
            //! any compiler errors
            std::string compile();

            //! sets the raw form of the script (ADL source)
            void set_raw( const std::string & raw_text );

            //! reads ADL source directly from an input stream into the object
            friend std::istream& operator>>( std::istream& is,
                                             script_object & so );
        private:
            std::string _name;
            script_object_id_t _id;
            std::string _raw_form;
            boost::shared_ptr< instruction_list > _compiled_form;
            template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                    ar & BOOST_SERIALIZATION_NVP(_name);
                    ar & BOOST_SERIALIZATION_NVP(_id);
                    ar & BOOST_SERIALIZATION_NVP(_raw_form);
                    ar & BOOST_SERIALIZATION_NVP(_compiled_form);
                    if (_id >= _next_id)
                        _next_id = _id + 1;
                }

            static script_object_id_t _next_id;
            static boost::mutex       _next_id_mutex;
    };

}

#endif
