#ifndef STRINGER_HPP_1802EEDB
#define STRINGER_HPP_1802EEDB

#include <sstream>
#include <string>
#include <type_traits>


namespace lib {

    namespace detail {

        template < typename Stream >
        using IsStream =
                std::is_base_of<
                    std::ios_base,
                    std::remove_reference_t<Stream>
                >;

    }

    template <
        typename Stream,

        typename = std::enable_if_t< detail::IsStream<Stream>::value >
    >
    std::ostream & streamer( Stream &&stream ) {
        return stream;
    }

    template <
        typename Stream,
        typename Head,
        typename ...Args,

        typename = std::enable_if_t< detail::IsStream<Stream>::value >
    >
    std::ostream & streamer( Stream &&stream, Head &&head, Args && ...args ) {
        return streamer(
                stream << std::forward<Head>( head ),
                std::forward<Args>( args )... );
    }

    template < typename Head, typename ...Args >
    std::string stringer( Head &&head, Args && ...args ) {
        return streamer(
                std::ostringstream(),
                std::forward<Head>( head ),
                std::forward<Args>( args )... ).str();
    }

}

#endif
