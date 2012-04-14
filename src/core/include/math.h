#ifndef STRUCTURES_H_IESIJQDA
#define STRUCTURES_H_IESIJQDA

#include "core/Global"

#include <cmath>

namespace Baukasten {

	/*!
	 * \ingroup core
	 * @{
	 *
	 * \addtogroup math
	 * @{
	 *
	 * \class vec2
	 * \brief two dimension vector struct.
	 * \headerfile Math "core/Math"
	 *
	 * provides basic functionality for dealing with 2d vector
	 * manipulation.
	 */
	template<class T>
	struct vec2 {
		T data[2];

		/*! \brief constructor */
		vec2() { vec2( (T)0, (T)0 ); }

		/*!
		 * \brief constructor
		 *
		 * initialises internal data with the given values.
		 *
		 * \param _f value for the first component.
		 * \param _s value for the second component.
		 */
		vec2( T _f, T _s ) : data{_f, _s } {}

		/*!
		 * \brief copy constructor.
		 *
		 * copies the data from the given vec2 struct.
		 *
		 * \param other vec2 struct.
		 */
		vec2( const vec2<T> &other ) : data{ other.data[0], other.data[1] }
		{
		}

		/*!
		 * \brief assignment operator.
		 *
		 * assignes the data from the given vec2 struct.
		 *
		 * \param other vec2 struct to copy from.
		 * \return reference to altered vec2 struct.
		 */
		vec2<T>& operator=( const vec2<T> &other )
		{
			if ( this == &other )
				return *this;

			data = { other.data[0], other.data[1] };
			return *this;
		}

		/*!
		 * \brief equality operator.
		 *
		 * compare two vec2 structs.
		 *
		 * \param other vec2 struct to compare with.
		 * \return true if every component of the two structs are the same, false otherwise.
		 */
		bool operator==( const vec2<T> &other ) const
		{
			return (
				data[0] == other.data[0] &&
				data[1] == other.data[1]
			);
		}

		/*!
		 * \brief unequality operator.
		 *
		 * compare two vec2 structs for their unequality.
		 *
		 * \param other vec2 struct to compare with.
		 * \return false if at least one component differs, true otherwise.
		 */
		bool operator!=( const vec2<T> &other ) const
		{
			return !operator==(other);
		}

		/*!
		 * \brief addition operator.
		 *
		 * adds the given vec2 struct's components.
		 *
		 * \param other vec2 struct which components are added.
		 * \return new vec2 struct with the added values.
		 */
		vec2<T> operator+( const vec2<T> &other ) const
		{
			return vec2<T>{
				data[0] + other.data[0],
				data[1] + other.data[1]
			};
		}

		/*!
		 * \brief addition operator.
		 *
		 * adds the given value to each component of the vec2.
		 *
		 * \param value value that is added.
		 * \return new vec2 struct with the added values.
		 */
		vec2<T> operator+( const T value ) const
		{
			return vec2<T>{
				data[0] + value,
				data[1] + value
			};
		}

		/*!
		 * \brief multiplication operator.
		 *
		 * multiplicates every field i of the component with the field
		 * j of the given component.
		 *
		 * \param other vec2 struct.
		 * \return new vec2 struct with multiplied values.
		 */
		vec2<T> operator*( const vec2<T> &other ) const
		{
			return vec2<T>{
				data[0] * other.data[0],
				data[1] * other.data[1]
			};
		}

		/*!
		 * \brief multiplication operator.
		 *
		 * multiplicates every field of the component with the given value.
		 *
		 * \param value value that is added.
		 * \return new vec2 struct with multiplied values.
		 */
		vec2<T> operator*( const T value ) const
		{
			return vec2<T>{
				data[0] * value,
				data[1] * value
			};
		}

		/*!
		 * \brief calculates the magnitude.
		 *
		 * calculates the magnitude of the vec2 struct fields.
		 *
		 * \sqrt{ x^2 + y^2 }
		 * \return calculated magnitude scalar.
		 */
		T mag() const
		{
			return sqrt(
				data[0] * data[0] +
				data[1] * data[1]
			);
		}

		/*!
		 * \brief calculates the magnitude^2.
		 *
		 * calculates the magnitude^2 of the vec2 struct fields.
		 *
		 * x^2 + y^2
		 * \return calculated magnitude^2 scalar.
		 */
		T magSqr() const
		{
			return(
				data[0]*data[0]+
				data[1]*data[1]
			);
		}

		/*!
		 * \brief returns normalised vector.
		 *
		 * calculates and returns a normalised vector.
		 *
		 * \return normalised vec2 struct.
		 */
		vec2<T> norm() const
		{
			vec2<T> t( *this );
			T n = 1/t.mag();

			return ( t*n );
		}

		/*!
		 * \brief calculates the dot product.
		 *
		 * calculates the dot product with the given vec2.
		 *
		 * \param other vec2 struct.
		 * \return dot product scalar.
		 */
		T dot( const vec2<T> &other )
		{
			return (
				data[0] * other.data[0] +
				data[1] * other.data[1]
			);
		}

		/*! operator[] */
		T operator[]( const int i ) const
		{
			if ( i > 1 || i < 0 ) return -1;
			return data[i];
		}

		/*! getter for the first element. */
		inline T first() const { return data[0]; }

		/*! getter for the second element. */
		inline T second() const { return data[1]; }

		/*! set the i-th element to the given value. */
		void set( int i, const T &value )
		{
			if ( i > 1 || i < 0 ) return;
			data[i] = value;
		}
	};

	/*!
	 * \class vec3
	 * \brief three dimension vector struct.
	 * \headerfile Math "core/Math"
	 *
	 * provides basic functionality for dealing with 3d vector
	 * manipulation.
	 */
	template<class T>
	struct vec3 {
		T data[3];

		/*! \brief constructor */
		vec3() { vec3( (T)0, (T)0, (T)0 ); }

		/*!
		 * \brief constructor
		 *
		 * initialises internal data with the given values.
		 *
		 * \param _f value for the first component.
		 * \param _s value for the second component.
		 * \param _t value for the third component.
		 */
		vec3( T _f, T _s, T _t ) : data({ _f, _s, _t }) {}

		/*!
		 * \brief copy constructor.
		 *
		 * copies the data from the given vec3 struct.
		 *
		 * \param other vec3 struct.
		 */
		vec3( const vec3<T> &other )
		{
			data = { other.data[0], other.data[1], other[2] };
		}

		/*!
		 * \brief assignment operator.
		 *
		 * assignes the data from the given vec3 struct.
		 *
		 * \param other vec3 struct to copy from.
		 * \return reference to altered vec3 struct.
		 */
		vec3<T>& operator=( const vec3<T> &other )
		{
			if ( this == &other )
				return *this;

			data = { other.data[0], other.data[1], other[2] };
			return *this;
		}

		/*!
		 * \brief equality operator.
		 *
		 * compare two vec3 structs.
		 *
		 * \param other vec3 struct to compare with.
		 * \return true if every component of the two structs are the same, false otherwise.
		 */
		bool operator==( const vec3<T> &other ) const
		{
			return (
				data[0] == other.data[0] &&
				data[1] == other.data[1] &&
				data[2] == other.data[2]
			);
		}

		/*!
		 * \brief unequality operator.
		 *
		 * compare two vec3 structs for their unequality.
		 *
		 * \param other vec3 struct to compare with.
		 * \return false if at least one component differs, true otherwise.
		 */
		bool operator!=( const vec3<T> &other ) const
		{
			return !operator==(other);
		}

		/*!
		 * \brief addition operator.
		 *
		 * adds the given vec3 struct's components.
		 *
		 * \param other vec3 struct which components are added.
		 * \return new vec3 struct with the added values.
		 */
		vec3<T> operator+( const vec3<T> &other ) const
		{
			return vec3<T>{
				data[0] + other.data[0],
				data[1] + other.data[1],
				data[2] + other.data[2]
			};
		}

		/*!
		 * \brief addition operator.
		 *
		 * adds the given value to each component of the vec3.
		 *
		 * \param value value that is added.
		 * \return new vec3 struct with the added values.
		 */
		vec3<T> operator+( const T value ) const
		{
			return vec3<T>{
				data[0] + value,
				data[1] + value,
				data[2] + value
			};
		}

		/*!
		 * \brief multiplication operator.
		 *
		 * multiplicates every field i of the component with the field
		 * j of the given component.
		 *
		 * \param other vec3 struct.
		 * \return new vec3 struct with multiplied values.
		 */
		vec3<T> operator*( const vec3<T> &other ) const
		{
			return vec3<T>{
				data[0] * other.data[0],
				data[1] * other.data[1],
				data[2] * other.data[2]
			};
		}

		/*!
		 * \brief multiplication operator.
		 *
		 * multiplicates every field of the component with the given value.
		 *
		 * \param value value that is added.
		 * \return reference to an altered vec3 struct.
		 */
		vec3<T> operator*( const T value ) const
		{
			return vec3<T>{
				data[0] * value,
				data[1] * value,
				data[2] * value
			};
		}

		/*!
		 * \brief calculates the magnitude.
		 *
		 * calculates the magnitude of the vec3 struct fields.
		 *
		 * \sqrt{ x^2 + y^2 + z^2 }
		 * \return calculated magnitude scalar.
		 */
		T mag() const
		{
			return sqrt(
				data[0] * data[0] +
				data[1] * data[1] +
				data[2] * data[2]
			);
		}

		/*!
		 * \brief calculates the magnitude^2.
		 *
		 * calculates the magnitude^2 of the vec3 struct fields.
		 *
		 * x^2 + y^2 + z^2
		 * \return calculated magnitude^2 scalar.
		 */
		T magSqr() const
		{
			return(
				data[0]*data[0]+
				data[1]*data[1]+
				data[2]*data[2]
			);
		}

		/*!
		 * \brief returns normalised vector.
		 *
		 * calculates and returns a normalised vector.
		 *
		 * \return normalised vec3 struct.
		 */
		vec3<T> norm() const
		{
			vec3<T> t( *this );
			T n = 1/t.mag();

			return ( t*n );
		}

		/*!
		 * \brief calculates the dot product.
		 *
		 * calculates the dot product with the given vec3.
		 *
		 * \param other vec3 struct.
		 * \return dot product scalar.
		 */
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
		 * \param other vec3 struct.
		 * \return vec3 struct.
		 */
		vec3<T> cross( const vec3<T> &other )
		{
			return {
				data[BK_Y]*other.data[BK_Z] - data[BK_Z]*other.data[BK_Y],
				data[BK_Z]*other.data[BK_X] - data[BK_X]*other.data[BK_Z],
				data[BK_X]*other.data[BK_Y] - data[BK_Y]*other.data[BK_X]
			};
		}

		/*! operator[] */
		T operator[]( const u32 i ) const
		{
			if ( i > 2 || i < 0 ) return -1;
			return data[i];
		}

		/*! getter for the first element. */
		inline T first() const { return data[0]; }

		/*! getter for the second element. */
		inline T second() const { return data[1]; }

		/*! getter for the third element. */
		inline T third() const { return data[2]; }

		/*! set the i-th element to the given value. */
		void set( int i, const T &value )
		{
			if ( i > 2 || i < 0 ) return;
			data[i] = value;
		}
	};
	/** @} */
	/** @} */

	typedef vec2<u32> vec2i;
	typedef vec2<f32> vec2f;
	typedef vec3<u32> vec3i;
	typedef vec3<f32> vec3f;
} /* Baukasten */

#endif /* end of include guard: STRUCTURES_H_IESIJQDA */

