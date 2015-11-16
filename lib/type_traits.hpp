#ifndef TYPE_TRAITS_HPP_EEF0693F
#define TYPE_TRAITS_HPP_EEF0693F

#include <type_traits>

namespace lib {

    template <bool B>
    using bool_constant = std::integral_constant< bool, B >;


    template< class... > struct disjunction
        : std::false_type { };

    template< class B1 > struct disjunction< B1 >
        : B1 { };

    template< class B1, class... Bn >
    struct disjunction< B1, Bn... >
        : std::conditional_t< B1::value != false, B1, disjunction< Bn... > >
    { };


    template< class... > struct conjunction
        : std::true_type
    { };

    template< class B1 > struct conjunction< B1 >
        : B1
    { };

    template< class B1, class... Bn >
    struct conjunction< B1, Bn... >
        : std::conditional_t< B1::value != false, conjunction<Bn... >, B1>
    { };


    template< class B >
    struct negation
        : bool_constant< !B::value >
    { };

} // namespace lib

#endif
