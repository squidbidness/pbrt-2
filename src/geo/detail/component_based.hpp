#ifndef COMPONENT_BASED_HPP_9F2AAEA5
#define COMPONENT_BASED_HPP_9F2AAEA5

#include "lib/loops.hpp"

#include <array>
#include <cinttypes>
#include <iostream>
#include <type_traits>


namespace geo {

	namespace detail {

		constexpr size_t MAX_DIM = 64u;


		template <
				typename Scalar,
				size_t Dim,

				typename = std::enable_if_t<
						std::is_floating_point< Scalar >::value >,
				typename = std::enable_if_t<
						lib::LessEq< Dim, MAX_DIM >::value >,
				typename = std::enable_if_t<
						lib::Greater< Dim, 0 >::value >
				>
		struct ComponentBasedConcept {
		};


		template < typename Derived, typename Scalar, size_t Dim >
		struct ComponentBasedMixinCumulative
				: public ComponentBasedMixinCumulative<Derived, Scalar, Dim - 1>
		{ };

		template < typename Derived, typename Scalar >
		struct ComponentBasedMixinCumulative< Derived, Scalar, 0 > {
		protected:
			Derived & derived() { return *static_cast<Derived *>( this ); }
			Derived const & derived() const{ return *static_cast<Derived *>( this ); }
		};

		template < typename Derived, typename Scalar >
		struct ComponentBasedMixinCumulative< Derived, Scalar, 1  >
				: public ComponentBasedMixinCumulative< Derived, Scalar, 0 >
		{
			Scalar & x() { return this->derived()[0]; }
			Scalar const & x() const { return this->derived()[0]; }
		};

		template < typename Derived, typename Scalar >
		struct ComponentBasedMixinCumulative< Derived, Scalar, 2  >
				: public ComponentBasedMixinCumulative< Derived, Scalar, 1 >
		{
			Scalar & y() { return this->derived()[1]; }
			Scalar const & y() const { return this->derived()[1]; }
		};

		template < typename Derived, typename Scalar >
		struct ComponentBasedMixinCumulative< Derived, Scalar, 3  >
				: public ComponentBasedMixinCumulative< Derived, Scalar, 2 >
		{
			Scalar & z() { return this->derived()[2]; }
			Scalar const & z() const { return this->derived()[2]; }
		};

		template < typename Derived, typename Scalar >
		struct ComponentBasedMixinCumulative< Derived, Scalar, 4  >
				: public ComponentBasedMixinCumulative< Derived, Scalar, 3 >
		{
			Scalar & w() { return this->derived()[3]; }
			Scalar const & w() const { return this->derived()[3]; }
		};


		template <
			typename Derived,
			typename Scalar,
			size_t Dim
		>
		struct ComponentBased
				: public std::array< Scalar, Dim >
				, public ComponentBasedConcept< Scalar, Dim >
				, public ComponentBasedMixinCumulative<
						ComponentBased<Derived, Scalar, Dim>,
						Scalar,
						Dim
						>
		{
			friend
			std::ostream & operator <<( std::ostream &o, Derived const &v ) {
				using lib::forAndBetween;

				o << "(";
				forAndBetween(
						v.m_data,
						[&o] ( auto && scalar ) { o << scalar; },
						[&o] () { o << ", "; }
						);
				o << ")";

				return o;
			}


		protected:

			ComponentBased() { }

			ComponentBased( std::array< Scalar, Dim > const &data )
					: m_data( data )
			{ }

			ComponentBased( ComponentBased const &other )
					: m_data( other.m_data )
			{ }


			template < typename ComponentBasedReturn, typename Lhs, typename Rhs >
			static
			ComponentBasedReturn operatorPlus( Lhs const &lhs, Rhs const &rhs ) {
				return binaryOp<Lhs>(
						[] ( auto &&a, auto &&b ) { return a + b; },
						lhs,
						rhs
						);
			}
			template < typename Lhs, typename Rhs >
			static
			Lhs &operatorPlusAssignment( Lhs &lhs, Rhs const &rhs ) {
				return binaryAssignmentOp(
						[] ( auto &&a, auto &&b ) { return a + b; },
						lhs,
						rhs
						);
			}


			template < typename Op, typename A, typename B >
			static
			A &binaryAssignmentOp(
					Op op,
					A &a,
					B const &b
					) {

				lib::forIndexed(
						a,
						[&b, &op] ( auto &&value, size_t i ) {
							value = op( value, b[i] );
						} );
				return a;
			}

			template <
					typename ComponentBasedReturn,
					typename Op,
					typename A,
					typename B
					>
			static
			ComponentBasedReturn binaryOp( Op op, A const &a, B const &b ) {
				ComponentBasedReturn ret(a);
				return binaryAssignmentOp( op, ret, b );
			}


		private:

			std::array< Scalar, Dim > m_data;

			Derived & derived() { return *static_cast<Derived *>( this ); }
			Derived const & derived() const {
				return *static_cast<Derived const *>( this );
			}

		};


	} // namespace detail

} // namespace geo

#endif
