// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#ifndef OBJECT_ATTRIBUTES_DWA2002615_HPP
# define OBJECT_ATTRIBUTES_DWA2002615_HPP

# include <boost/python/proxy.hpp>
# include <boost/python/object_core.hpp>
# include <boost/python/object_protocol.hpp>

namespace boost { namespace python { 

namespace detail
{
  struct const_attribute_policies
  {
      static object get(object const& target, object const& key);
  };
  
  struct attribute_policies : const_attribute_policies
  {
      static object const& set(object const& target, object const& key, object const& value);
  };
}

//
// implementation
//
inline object_attribute object::_(char const* name)
{
    return object_attribute(*this, object(name));
}

inline const_object_attribute object::_(char const* name) const
{
    return const_object_attribute(*this, object(name));
}

namespace detail
{
  inline object const_attribute_policies::get(object const& target, object const& key)
  {
      return python::getattr(target, key);
  }

  inline object const& attribute_policies::set(
      object const& target
      , object const& key
      , object const& value)
  {
      python::setattr(target, key, value);
      return value;
  }
}

namespace converter
{
  // These specializations are a lie; the proxies do not directly
  // manage an object. What actually happens is that the implicit
  // conversion to object takes hold and its conversion to_python is
  // used. That's OK in part because the object temporary *is*
  // actually managing the object during the duration of the
  // conversion.
  template <>
  struct is_object_manager<object_attribute>
  {
      BOOST_STATIC_CONSTANT(bool, value = true);
  };

  template <>
  struct is_object_manager<const_object_attribute>
  {
      BOOST_STATIC_CONSTANT(bool, value = true);
  };
}

}} // namespace boost::python

#endif // OBJECT_ATTRIBUTES_DWA2002615_HPP