#ifndef TYPE_TRAITS_HPP_EEF0693F
#define TYPE_TRAITS_HPP_EEF0693F

#include <cstddef>
#include <type_traits>

namespace lib {

	template < typename T >
	using Type = typename T::type;


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


	template < size_t A, size_t B >
	struct Less {
		static constexpr bool value = ( A < B );
	};

	template < size_t A, size_t B >
	struct LessEq {
		static constexpr bool value = ( A <= B );
	};

	template < size_t A, size_t B >
	struct Greater {
		static constexpr bool value = ( A > B );
	};

	template < size_t A, size_t B >
	struct GreaterEq {
		static constexpr bool value = ( A >= B );
	};

	template < size_t A, size_t B >
	struct Equal {
		static constexpr bool value = ( A == B );
	};

	template < size_t A, size_t B >
	struct NotEqual {
		static constexpr bool value = ( A != B );
	};

} // namespace lib

#endif
