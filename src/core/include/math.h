#ifndef STRUCTURES_H_IESIJQDA
#define STRUCTURES_H_IESIJQDA

#include "model/Global"

namespace Baukasten {

	template<class T>
	struct vec2 {
		T data[2];

		vec2() { vec2( (T)0, (T)0 ); }
		vec2( T _f, T _s ) : data({_f, _s }) {}
		vec2( const vec2<T> &other )
		{
			data = { other.data[0], other.data[1] };
		}

		vec2<T>& operator=( const vec2<T> &other )
		{
			data = { other.data[0], other.data[1] };
			return *this;
		}

		bool operator==( const vec2<T> &other )
		{
			return (
				data[0] == other.data[0] &&
				data[1] == other.data[1]
			);
		}

		bool operator!=( const vec2<T> &other )
		{
			return !operator==(other);
		}

		vec2<T>& operator+( const vec2<T> &other )
		{
			data[0] += other.data[0];
			data[1] += other.data[1];
			return *this;
		}

		T operator[]( const int i ) const
		{
			if ( i > 1 || i < 0 ) return -1;
			return data[i];
		}

		inline T first() const { return data[0]; }
		inline T second() const { return data[1]; }

		void set( int i, const T &value )
		{
			if ( i > 1 || i < 0 ) return;
			data[i] = value;
		}
	};

	template<class T>
	struct vec3 {
		T data[3];

		vec3() { vec3( (T)0, (T)0, (T)0 ); }
		vec3( T _f, T _s, T _t ) : data({ _f, _s, _t }) {}
		vec3( const vec3<T> &other )
		{
			data = { other.data[0], other.data[1], other[2] };
		}

		vec3<T>& operator=( const vec3<T> &other )
		{
			data = { other.data[0], other.data[1], other[2] };
			return *this;
		}

		vec3<T>& operator+( const vec3<T> &other )
		{
			data[0] += other.data[0];
			data[1] += other.data[1];
			data[2] += other.data[2];
			return *this;
		}

		T operator[]( const unsigned int i ) const
		{
			if ( i > 2 || i < 0 ) return -1;
			return data[i];
		}

		inline T first() const { return data[0]; }
		inline T second() const { return data[1]; }
		inline T third() const { return data[2]; }

		void set( int i, const T &value )
		{
			if ( i > 2 || i < 0 ) return;
			data[i] = value;
		}
	};
} /* Baukasten */

#endif /* end of include guard: STRUCTURES_H_IESIJQDA */

