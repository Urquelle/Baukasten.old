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

		void add( const T scalar )
		{
			for ( u32 i = 0; i < SIZE; ++i ) {
				m_data[ i ] += scalar;
			}
		}

		void add( const Vector &other )
		{
			for ( u32 i = 0; i < SIZE; ++i ) {
				m_data[ i ] += other[ i ];
			}
		}

		void multiply( const T scalar )
		{
			for ( u32 i = 0; i < SIZE; ++i ) {
				m_data[ i ] *= scalar;
			}
		}

		void multiply( const Vector &other )
		{
			for ( u32 i = 0; i < SIZE; ++i ) {
				m_data[ i ] *= other[ i ];
			}
		}

		T get( const u32 index ) const
		{
			BK_ASSERT( index < SIZE, "index out of bounds." );
			return m_data[ index ];
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
			Vector<T, SIZE> v( *this );
			v.add( other );
			return v;
		}

		Vector<T,SIZE> operator+( const T &value )
		{
			Vector<T, SIZE> v( *this );
			v.add( value );
			return v;
		}

		Vector<T,SIZE> operator*( const Vector &other )
		{
			Vector<T, SIZE> v( *this );
			v.multiply( other );
			return v;
		}

		Vector<T,SIZE> operator*( const T &value )
		{
			Vector<T, SIZE> v( *this );
			v.multiply( value );
			return v;
		}

		const T operator[]( const u32 index ) const
		{
			BK_ASSERT( index < SIZE && index >= 0, "index out of bounds." );
			return m_data[ index ];
		}

		T& operator[]( const u32 index )
		{
			BK_ASSERT( index < SIZE && index >= 0, "index out of bounds." );
			return m_data[ index ];
		}

	protected:
		vector<T> m_data;
	};
} /* Baukasten */

#endif /* end of include guard: VECTOR_H_LYM4MXR7 */

