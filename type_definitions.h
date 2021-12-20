#ifndef TYPE_DEFINITIONS_H
#define TYPE_DEFINITIONS_H

#include <boost/coroutine2/all.hpp>

namespace gtk {
template <class T>
using yield = typename boost::coroutines2::coroutine<T>::push_type;
template <class T>
using generator = typename boost::coroutines2::coroutine<T>::pull_type;
}

#endif // TYPE_DEFINITIONS_H
