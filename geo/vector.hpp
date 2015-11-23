#ifndef VECTOR_HPP_DA39A3EE
#define VECTOR_HPP_DA39A3EE

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


        template < typename Derived >
        struct ComponentBased;

        template <
            template <typename, size_t> class Derived,
            typename Scalar,
            size_t Dim
        >
        struct ComponentBased< Derived<Scalar, Dim> >
                : public ComponentBasedConcept< Scalar, Dim >
                , public ComponentBasedMixinCumulative<
                        ComponentBased<Derived<Scalar, Dim>>, Scalar, Dim >
        {
            using V = Derived< Scalar, Dim >;

            Scalar & operator []( size_t i ) { return m_data[i]; }
            Scalar const & operator []( size_t i ) const { return m_data[i]; }

            //! @throw std::out_of_range if @arg i is too large
            Scalar & at( size_t i ) { return m_data.at(i); }
            Scalar const & at( size_t i ) const { return m_data.at(i); }


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

            ComponentBased() { }

            ComponentBased( std::array< Scalar, Dim > const &data )
                : m_data( data )
            { }

            // These are protected since not all derived classes will directly
            // support these operations, but still need a common implementation
            // available for internal use
            friend
            V operator +( V const &u, V const &v ) {
                return V( u.m_data + v.m_data );
            }
            V & operator +=( V const &u ) {
                m_data += u.m_data;
                return derived();
            }

        private:

            std::array< Scalar, Dim > m_data;

            V & derived() { return *static_cast<V *>( this ); }
            V const & derived() const { return *static_cast<V const *>( this ); }
        };

    } // namespace detail

    template < typename Scalar, size_t Dim >
    struct Vector : public detail::ComponentBased< Vector<Scalar, Dim> > {

        using Base = detail::ComponentBased< Vector<Scalar, Dim> >;
        using Base::Base;
        friend struct detail::ComponentBased< Vector<Scalar, Dim> >;
    };

    using Vector3 = Vector< float, 3 >;
    using VectorD3 = Vector< double, 3 >;
    using Vector4 = Vector< float, 4 >;
    using VectorD4 = Vector< double, 4 >;

} // namespace geo

#endif
