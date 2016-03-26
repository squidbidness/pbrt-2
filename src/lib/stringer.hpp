#ifndef STRINGER_HPP_1802EEDB
#define STRINGER_HPP_1802EEDB

#include <sstream>
#include <string>
#include <type_traits>


namespace lib {

    template< typename... Args >
    std::string stringer( Args &&...args ) {
        std::ostringstream oss;
        ( oss << ... << args );
        return oss.str();
    }

}

#endif
