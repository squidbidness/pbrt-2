#ifndef VECTOR_HPP_DA39A3EE
#define VECTOR_HPP_DA39A3EE

#include "geo/detail/component_based.hpp"



namespace geo {

    namespace detail {

        template < typename Scalar, size_t Dim >
        struct VectorBase : public ComponentBased< VectorBase<Scalar, Dim> > {
            using Base = ComponentBased< VectorBase<Scalar, Dim> >;

            using Base::operator +=;
        };

    } // namespace detail

    template < typename Scalar, size_t Dim >
    struct Vector : public detail::VectorBase< Scalar, Dim> {
    };

    template < typename Scalar >
    struct Vector< Scalar, 3 >
            : public detail::VectorBase< Scalar, 3 >
    {
    };

    using Vector3 = Vector< float, 3 >;
    using VectorD3 = Vector< double, 3 >;
    using Vector4 = Vector< float, 4 >;
    using VectorD4 = Vector< double, 4 >;

} // namespace geo

#endif
