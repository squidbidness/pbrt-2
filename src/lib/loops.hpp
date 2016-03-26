#ifndef LOOPS_HPP_A200C79C
#define LOOPS_HPP_A200C79C


#include "lib/type_traits.hpp"

#include <functional>
#include <type_traits>


namespace lib::detail {

	template< typename Range >
	using RangeValueType = decltype( *std::begin(std::declval<Range>()) );

	template< typename Op >
	using IsNullaryOp =
			std::is_convertible< Op, std::function<void()> >;

	template< typename Range, typename Op >
	using IsRangeValueUnaryOp =
			std::is_convertible<
				Op,
				std::function< void( RangeValueType<Range> ) >
			>;

	template< typename Range, typename Op >
	using IsRangeValueBinaryOp =
			std::is_convertible<
				Op,
				std::function< void(
					RangeValueType<Range>,
					RangeValueType<Range>
				) >
			>;

	template<
			typename Range,
			typename Op,
			typename Value
	>
	std::enable_if_t<
			detail::IsNullaryOp<Op>::value,
			void
	>
	doBetweenOp( Range &&, Op &&op, Value &&, Value && ) {
		op();
	}

	template<
			typename Range,
			typename Op,
			typename Value
	>
	std::enable_if_t<
			detail::IsRangeValueBinaryOp<Range, Op>::value,
			void
	>
	doBetweenOp( Range &&, Op &&op, Value &&a, Value &&b ) {
		op( std::forward<Value>(a), std::forward<Value>(b) );
	}


	template<
			typename Range,
			typename Op
	>
	using IsIndexedForOp =
			std::is_convertible<
				Op,
				std::function< void(RangeValueType<Range>, size_t) >
			>;

} // namespace lib::detail

namespace lib {

	template<
			typename Range,
			typename Op,
			typename BetweenOp,

			typename = typename std::enable_if_t<
				detail::IsRangeValueUnaryOp< Range, Op >::value
			>,
			typename = typename std::enable_if_t<
				disjunction<
					detail::IsNullaryOp< BetweenOp >,
					detail::IsRangeValueBinaryOp< Range, BetweenOp >
				>::value
			>
	>
	void forAndBetween( Range &&range, Op &&op, BetweenOp &&betweenOp ) {

		auto curr = std::begin( std::forward<Range>(range) );
		auto end = std::end( std::forward<Range>(range) );
		decltype(curr) next = curr;

		if ( next != end )
			++next;
		else
			return;

		using detail::doBetweenOp;
		while ( next != end ) {
			op( *curr );
			doBetweenOp(
					std::forward<Range>( range ),
					std::forward<BetweenOp>( betweenOp ),
					*curr,
					*next
			);
			++curr;
			++next;
		}
		op( *curr );
	}


	template<
			typename Range,
			typename Op,

			typename = std::enable_if_t<
				detail::IsIndexedForOp< Range, Op >::value >
	>
	void forIndexed( Range &&range, Op &&op ) {
		size_t i = 0;
		for ( auto &&value : range ) {
			op( value, i++ );
		}
	}

} // namespace lib

#endif
