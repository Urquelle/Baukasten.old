#ifndef VECTOR_H_LYM4MXR7
#define VECTOR_H_LYM4MXR7

#include "core/Assert"
#include "math/Global"

namespace Baukasten {
	/*!
	 * \break Vector class declaration.
	 */
	template<class T, u32 size>
	class BAUKASTEN_EXPORT Vector {
	public:

		friend class VectorProxy;
		class VectorProxy {
		public:
			VectorProxy( Vector<T, size> &v, u32 index ) :
				m_v( &v ), m_index( index )
			{
			}

			VectorProxy& operator=( const VectorProxy &other )
			{
				m_v->m_data[ m_index ] = other.m_v[ other.m_index ];
			}

			VectorProxy& operator=( T value )
			{
				m_v->m_data[ m_index ] = value;
			}

			operator T() const
			{
				return m_v->m_data[m_index];
			}

		private:
			Vector<T, size>* m_v;
			u32              m_index;
		};

		Vector() : m_data{ 0 }
		{
		}

		Vector( const Vector<T, size> &other )
		{
			if ( &other == this ) return;
			for ( size_t i = 0; i < size; ++i ) {
				m_data[ i ] = other[ i ];
			}
		}

		virtual ~Vector()
		{
		}

		Vector& operator=( const Vector &other )
		{
			if ( &other == this ) return *this;
			for ( size_t i = 0; i < size; ++i ) {
				m_data[ i ] = other[ i ];
			}

			return *this;
		}

		Vector& operator=( const T &value )
		{
			for ( size_t i = 0; i < size; ++i ) {
				m_data[ i ] = value;
			}

			return *this;
		}

		Vector<T,size> operator+( const Vector &other )
		{
			Vector<T, size> v;
			for ( size_t i = 0; i < size; ++i ) {
				v[ i ] = m_data[ i ] + other[ i ];
			}

			return v;
		}

		Vector<T,size> operator+( const T &value )
		{
			Vector<T, size> v;
			for ( size_t i = 0; i < size; ++i ) {
				v[ i ] = m_data[ i ] + value;
			}

			return v;
		}

		Vector<T,size> operator*( const Vector &other )
		{
			Vector<T, size> v;
			for ( size_t i = 0; i < size; ++i ) {
				v[ i ] = m_data[ i ] * other[ i ];
			}

			return v;
		}

		Vector<T,size> operator*( const T &value )
		{
			Vector<T, size> v;
			for ( size_t i = 0; i < size; ++i ) {
				v[ i ] = m_data[ i ] * value;
			}

			return v;
		}

		const VectorProxy operator[]( const u32 index ) const
		{
			BK_ASSERT( index < size && index >= 0, "index out of bounds." );
			return VectorProxy( const_cast<Vector<T,size>&>( *this ), index );
		}

		VectorProxy operator[]( const u32 index )
		{
			BK_ASSERT( index < size && index >= 0, "index out of bounds." );
			return VectorProxy( *this, index );
		}

	private:
		T m_data[size];
	};
} /* Baukasten */

#endif /* end of include guard: VECTOR_H_LYM4MXR7 */

