#ifndef VECTOR_H_LYM4MXR7
#define VECTOR_H_LYM4MXR7

#include "core/Assert"
#include "core/Debug"
#include "math/Global"

#include <vector>

namespace Baukasten {
	/*!
	 * \brief Vector class declaration.
	 */
	template<class T, u32 SIZE>
	class BAUKASTEN_EXPORT Vector {
	public:

		friend class VectorProxy;
		class VectorProxy {
		public:
			VectorProxy( Vector<T, SIZE> &v, u32 index ) :
				m_v( &v ), m_index( index )
			{
			}

			VectorProxy& operator=( const VectorProxy &other )
			{
				m_v->m_data[ m_index ] = other.m_v[ other.m_index ];
				return *this;
			}

			VectorProxy& operator=( T value )
			{
				m_v->m_data[ m_index ] = value;
				return *this;
			}

			operator T() const
			{
				return m_v->m_data[m_index];
			}

			T* operator&()
			{
				return &( m_v->m_data[ m_index ] );
			}

			const T* operator&() const
			{
				return &( m_v->m_data[ m_index ] );
			}

			bool operator==( const T value )
			{
				return ( value == m_v[ m_index ] );
			}

			bool operator!=( const T value )
			{
				return !operator==( value );
			}

		private:
			Vector<T, SIZE>* m_v;
			u32              m_index;
		};

		Vector()
		{
			m_data.reserve( SIZE );
			m_data.assign( SIZE, 0 );
		}

		Vector( initializer_list<T> list )
		{
			BK_ASSERT( list.size() == SIZE, "argument must contain " << SIZE <<
					" arguments." );

			m_data.reserve( SIZE );
			m_data = list;
		}

		Vector( const Vector<T, SIZE> &other )
		{
			if ( &other == this ) return;

			m_data.reserve( SIZE );
			for ( u32 i = 0; i < SIZE; ++i ) {
				m_data[ i ] = other[ i ];
			}
		}

		virtual ~Vector()
		{
		}

		u32 size() const
		{
			return SIZE;
		}

		Vector& operator=( const Vector &other )
		{
			if ( &other == this ) return *this;
			for ( u32 i = 0; i < SIZE; ++i ) {
				m_data[ i ] = other[ i ];
			}

			return *this;
		}

		Vector& operator=( const T &value )
		{
			for ( u32 i = 0; i < SIZE; ++i ) {
				m_data[ i ] = value;
			}

			return *this;
		}

		Vector<T,SIZE> operator+( const Vector &other )
		{
			Vector<T, SIZE> v;
			for ( u32 i = 0; i < SIZE; ++i ) {
				v[ i ] = m_data[ i ] + other[ i ];
			}

			return v;
		}

		Vector<T,SIZE> operator+( const T &value )
		{
			Vector<T, SIZE> v;
			for ( u32 i = 0; i < SIZE; ++i ) {
				v[ i ] = m_data[ i ] + value;
			}

			return v;
		}

		Vector<T,SIZE> operator*( const Vector &other )
		{
			Vector<T, SIZE> v;
			for ( u32 i = 0; i < SIZE; ++i ) {
				v[ i ] = m_data[ i ] * other[ i ];
			}

			return v;
		}

		Vector<T,SIZE> operator*( const T &value )
		{
			Vector<T, SIZE> v;
			for ( u32 i = 0; i < SIZE; ++i ) {
				v[ i ] = m_data[ i ] * value;
			}

			return v;
		}

		const VectorProxy operator[]( const u32 index ) const
		{
			BK_ASSERT( index < SIZE && index >= 0, "index out of bounds." );
			return VectorProxy( const_cast<Vector<T,SIZE>&>( *this ), index );
		}

		VectorProxy operator[]( const u32 index )
		{
			BK_ASSERT( index < SIZE && index >= 0, "index out of bounds." );
			return VectorProxy( *this, index );
		}

	private:
		vector<T> m_data;
	};
} /* Baukasten */

#endif /* end of include guard: VECTOR_H_LYM4MXR7 */

