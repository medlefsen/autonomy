#ifndef ATUONOMY_UTIL_SERIALIZATION_HPP
#define ATUONOMY_UTIL_SERIALIZATION_HPP
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <vector>
#include <boost/serialization/vector.hpp>
#include <list>
#include <boost/serialization/list.hpp>
#include <map>
#include <boost/serialization/map.hpp>
#include <set>
#include <boost/serialization/set.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <string>
#include <boost/serialization/string.hpp>

#include <boost/serialization/export.hpp>

#endif
