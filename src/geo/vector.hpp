#ifndef VECTOR_HPP_DA39A3EE
#define VECTOR_HPP_DA39A3EE

#include "geo/detail/component_based.hpp"



namespace geo {

	namespace detail {

		template < typename Derived, typename Scalar, size_t Dim >
		struct VectorBase
				: public ComponentBased<
						VectorBase< Derived, Scalar, Dim >,
						Scalar,
						Dim
						>
		{
			using Base = ComponentBased<
					VectorBase< Derived, Scalar, Dim >,
					Scalar,
					Dim
					>;
			using Base::Base;

			Derived &operator +=( Derived const &other ) {
				return operatorPlusAssignment( *this, other );
			}
			friend
			Derived operator +( Derived const &lhs, Derived const &rhs ) {
				return Base::template operatorPlus<Derived>( lhs, rhs );
			}


		private:

			Derived & derived() { return *static_cast<Derived *>( this ); }
			Derived const & derived() const {
				return *static_cast<Derived const *>( this );
			}
		};

	} // namespace detail

	template < typename Scalar, size_t Dim >
	struct Vector
			: public detail::VectorBase< Vector<Scalar, Dim>, Scalar, Dim >
	{ };

	template < typename Scalar >
	struct Vector< Scalar, 3 >
			: public detail::VectorBase< Vector<Scalar, 3>, Scalar, 3 >
	{ };

	template < size_t Dim >
	using VectorF = Vector< float, Dim >;
	template < size_t Dim >
	using VectorD = Vector< double, Dim >;

	using VectorF2 = Vector< float, 2 >;
	using VectorD2 = Vector< double, 2 >;
	using VectorF3 = Vector< float, 3 >;
	using VectorD3 = Vector< double, 3 >;
	using VectorF4 = Vector< float, 4 >;
	using VectorD4 = Vector< double, 4 >;

} // namespace geo

#endif
