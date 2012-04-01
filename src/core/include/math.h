#ifndef STRUCTURES_H_IESIJQDA
#define STRUCTURES_H_IESIJQDA

#include "core/Global"

#include <cmath>

namespace Baukasten {

	template<class T>
	struct vec2 {
		T data[2];

		vec2() { vec2( (T)0, (T)0 ); }
		vec2( T _f, T _s ) : data{_f, _s } {}
		vec2( const vec2<T> &other ) : data{ other.data[0], other.data[1] }
		{
		}

		vec2<T>& operator=( const vec2<T> &other )
		{
			if ( this == &other )
				return *this;

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

		vec2<T>& operator+( const T value )
		{
			data[0] += value;
			data[1] += value;

			return *this;
		}

		vec2<T>& operator*( const vec2<T> &other )
		{
			data[0] *= other.data[0];
			data[1] *= other.data[1];

			return *this;
		}

		vec2<T>& operator*( const T value )
		{
			data[0] *= value;
			data[1] *= value;

			return *this;
		}

		T mag() const
		{
			return sqrt(
				data[0] * data[0] +
				data[1] * data[1]
			);
		}

		T magSqr() const
		{
			return(
				data[0]*data[0]+
				data[1]*data[1]
			);
		}

		vec2<T> norm() const
		{
			vec2<T> t( *this );
			T n = 1/t.mag();

			return ( t*n );
		}

		T dot( const vec2<T> &other )
		{
			return (
				data[0] * other.data[0] +
				data[1] * other.data[1]
			);
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
			if ( this == &other )
				return *this;

			data = { other.data[0], other.data[1], other[2] };
			return *this;
		}

		bool operator==( const vec3<T> &other )
		{
			return (
				data[0] == other.data[0] &&
				data[1] == other.data[1] &&
				data[2] == other.data[2]
			);
		}

		bool operator!=( const vec3<T> &other )
		{
			return !operator==(other);
		}

		vec3<T>& operator+( const vec3<T> &other )
		{
			data[0] += other.data[0];
			data[1] += other.data[1];
			data[2] += other.data[2];

			return *this;
		}

		vec3<T>& operator+( const T value )
		{
			data[0] += value;
			data[1] += value;
			data[2] += value;

			return *this;
		}

		vec3<T>& operator*( const vec3<T> &other )
		{
			data[0] *= other.data[0];
			data[1] *= other.data[1];
			data[2] *= other.data[2];

			return *this;
		}

		vec3<T>& operator*( const T value )
		{
			data[0] *= value;
			data[1] *= value;
			data[2] *= value;

			return *this;
		}

		T mag() const
		{
			return sqrt(
				data[0] * data[0] +
				data[1] * data[1] +
				data[2] * data[2]
			);
		}

		T magSqr() const
		{
			return(
				data[0]*data[0]+
				data[1]*data[1]+
				data[2]*data[2]
			);
		}

		vec3<T> norm() const
		{
			vec3<T> t( *this );
			T n = 1/t.mag();

			return ( t*n );
		}

		T dot( const vec3<T> &other )
		{
			return (
				data[0] * other.data[0] +
				data[1] * other.data[1] +
				data[2] * other.data[2]
			);
		}

		/*!
		 * \brief cross product of two vectors.
		 */
		vec3<T> cross( const vec3<T> &other )
		{
			return {
				data[BK_Y]*other.data[BK_Z] - data[BK_Z]*other.data[BK_Y],
				data[BK_Z]*other.data[BK_X] - data[BK_X]*other.data[BK_Z],
				data[BK_X]*other.data[BK_Y] - data[BK_Y]*other.data[BK_X]
			};
		}

		T operator[]( const u32 i ) const
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

	typedef vec2<u32> vec2i;
	typedef vec2<f32> vec2f;
	typedef vec3<u32> vec3i;
	typedef vec3<f32> vec3f;
} /* Baukasten */

#endif /* end of include guard: STRUCTURES_H_IESIJQDA */

