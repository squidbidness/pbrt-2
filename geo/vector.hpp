#ifndef VECTOR_HPP_DA39A3EE
#define VECTOR_HPP_DA39A3EE

#include "lib/loops.hpp"

#include <array>
#include <cinttypes>
#include <type_traits>


namespace geo {

    namespace detail {

        constexpr size_t MAX_DIM = 64u;

        template < size_t A, size_t B >
        struct LessThan {
            static constexpr bool value = ( A < B );
        };

        template < size_t A, size_t B >
        struct GreaterThan {
            static constexpr bool value = ( A > B );
        };

        // typename = typename std::enable_if<
        //         std::is_floating_point< Scalar >::value >::type,
        // typename = typename std::enable_if<
        //         detail::LessThan< Dim, MAX_DIM >::value >::type,
        // typename = typename std::enable_if<
        //         detail::GreaterThan< Dim, 0 >::value >::type

        template < typename Derived >
        struct VectorBase;

        template <
            template <typename, size_t> class Derived,
            typename Scalar,
            size_t Dim
        >
        struct VectorBase< Derived<Scalar, Dim> > {

            using V = Derived< Scalar, Dim >;

            friend
            V operator +( V const &u, V const &v ) {
                return V( u.m_data + v.m_data );
            }

            V & operator +=( V const &u ) {
                m_data += u.m_data;
                return *derived();
            }

            Scalar & operator []( size_t i ) {
                return m_data[i];
            }
            Scalar const & operator []( size_t i ) const {
                return m_data[i];
            }

            friend
            std::ostream & operator <<( std::ostream &o, V const &v ) {
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

            VectorBase() { }

            VectorBase( std::array< Scalar, Dim > const &data )
                : m_data( data )
            { }

        private:

            std::array< Scalar, Dim > m_data;

            V * derived() {
                return static_cast<V *>( this );
            }

            V const * derived() const {
                return static_cast<V const *>( this );
            }
        };

    } // namespace detail




    template < typename Scalar, size_t Dim >
    struct Vector : public detail::VectorBase< Vector<Scalar, Dim> > {

        using Base = detail::VectorBase< Vector<Scalar, Dim> >;
        using Base::Base;
        friend struct detail::VectorBase< Vector<Scalar, Dim> >;
    };

    template < typename Scalar >
    struct Vector< Scalar, 1 > : public detail::VectorBase< Vector<Scalar, 1> > {
        static constexpr size_t Dim = 1;
        using Base = detail::VectorBase< Vector<Scalar, Dim> >;
        using Base::Base;
        friend struct detail::VectorBase< Vector<Scalar, Dim> >;

        Scalar &x = (*this)[0];
    };

    template < typename Scalar >
    struct Vector< Scalar, 2 > : public detail::VectorBase< Vector<Scalar, 2> > {
        static constexpr size_t Dim = 2;
        using Base = detail::VectorBase< Vector<Scalar, Dim> >;
        using Base::Base;
        friend struct detail::VectorBase< Vector<Scalar, Dim> >;

        Scalar &x = (*this)[0];
        Scalar &y = (*this)[1];
    };

    template < typename Scalar >
    struct Vector< Scalar, 3 > : public detail::VectorBase< Vector<Scalar, 3> > {
        static constexpr size_t Dim = 3;
        using Base = detail::VectorBase< Vector<Scalar, Dim> >;
        using Base::Base;
        friend struct detail::VectorBase< Vector<Scalar, Dim> >;

        Scalar &x = (*this)[0];
        Scalar &y = (*this)[1];
        Scalar &z = (*this)[2];
    };

    template < typename Scalar >
    struct Vector< Scalar, 4 > : public detail::VectorBase< Vector<Scalar, 4> > {
        static constexpr size_t Dim = 4;
        using Base = detail::VectorBase< Vector<Scalar, Dim> >;
        using Base::Base;
        friend struct detail::VectorBase< Vector<Scalar, Dim> >;

        Scalar &x = (*this)[0];
        Scalar &y = (*this)[1];
        Scalar &z = (*this)[2];
        Scalar &w = (*this)[3];
    };


    using Vector3 = Vector< float, 3 >;
    using Vector3L = Vector< double, 3 >;
    using Vector4 = Vector< float, 4 >;
    using Vector$L = Vector< double, 4 >;

} // namespace geo

#endif
