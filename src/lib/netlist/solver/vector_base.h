// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * vector_base.h
 *
 * Base vector operations
 *
 */

#ifndef VECTOR_BASE_H_
#define VECTOR_BASE_H_

#include <algorithm>
<<<<<<< HEAD
#include "plib/pconfig.h"

#if 0
template <unsigned _storage_N>
=======
#include "../plib/pconfig.h"

#if 0
template <unsigned storage_N>
>>>>>>> upstream/master
struct pvector
{
	pvector(unsigned size)
	: m_N(size) { }

	unsigned size() {
<<<<<<< HEAD
		if (_storage_N)
	}

	double m_V[_storage_N];
=======
		if (storage_N)
	}

	double m_V[storage_N];
>>>>>>> upstream/master
private:
	unsigned m_N;
};
#endif

#if !defined(__clang__) && !defined(_MSC_VER) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 6))
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

<<<<<<< HEAD
template<typename T>
inline void vec_set (const std::size_t n, const T &scalar, T * RESTRICT result)
{
	for ( std::size_t i = 0; i < n; i++ )
		result[i] = scalar;
}

template<typename T>
inline T vecmult (const std::size_t n, const T * RESTRICT a1, const T * RESTRICT a2 )
{
	T value = 0.0;
	for ( std::size_t i = 0; i < n; i++ )
		value = value + a1[i] * a2[i];
	return value;
}

template<typename T>
inline T vecmult2 (const std::size_t n, const T *a1)
{
	T value = 0.0;
	for ( std::size_t i = 0; i < n; i++ )
	{
		const T temp = a1[i];
		value = value + temp * temp;
	}
	return value;
}

template<typename T>
inline void vec_mult_scalar (const std::size_t n, const T * RESTRICT v, const T scalar, T * RESTRICT result)
{
	for ( std::size_t i = 0; i < n; i++ )
	{
		result[i] = scalar * v[i];
	}
}

template<typename T>
inline void vec_add_mult_scalar (const std::size_t n, const T * RESTRICT v, const T scalar, T * RESTRICT result)
=======
template<typename T, std::size_t N>
inline static void vec_set (const std::size_t n, const T scalar, T (& RESTRICT v)[N])
{
	if (n != N)
		for ( std::size_t i = 0; i < n; i++ )
			v[i] = scalar;
	else
		for ( std::size_t i = 0; i < N; i++ )
			v[i] = scalar;
}

template<typename T, std::size_t N>
inline static T vec_mult (const std::size_t n, const T (& RESTRICT v1)[N], const T (& RESTRICT v2)[N] )
{
	T value = 0.0;
	if (n != N)
		for ( std::size_t i = 0; i < n; i++ )
			value += v1[i] * v2[i];
	else
		for ( std::size_t i = 0; i < N; i++ )
			value += v1[i] * v2[i];
	return value;
}

template<typename T, std::size_t N>
inline static T vec_mult2 (const std::size_t n, const T (& RESTRICT v)[N])
{
	T value = 0.0;
	if (n != N)
		for ( std::size_t i = 0; i < n; i++ )
			value += v[i] * v[i];
	else
		for ( std::size_t i = 0; i < N; i++ )
			value += v[i] * v[i];
	return value;
}

template<typename T, std::size_t N>
inline static void vec_mult_scalar (const std::size_t n, const T (& RESTRICT v)[N], const T & scalar, T (& RESTRICT result)[N])
{
	if (n != N)
		for ( std::size_t i = 0; i < n; i++ )
			result[i] = scalar * v[i];
	else
		for ( std::size_t i = 0; i < N; i++ )
			result[i] = scalar * v[i];
}

template<typename T, std::size_t N>
inline static void vec_add_mult_scalar (const std::size_t n, const T (& RESTRICT v)[N], const T scalar, T (& RESTRICT result)[N])
{
	if (n != N)
		for ( std::size_t i = 0; i < n; i++ )
			result[i] = result[i] + scalar * v[i];
	else
		for ( std::size_t i = 0; i < N; i++ )
			result[i] = result[i] + scalar * v[i];
}

template<typename T>
inline static void vec_add_mult_scalar_p(const std::size_t & n, const T * RESTRICT v, const T scalar, T * RESTRICT result)
>>>>>>> upstream/master
{
	for ( std::size_t i = 0; i < n; i++ )
		result[i] += scalar * v[i];
}

<<<<<<< HEAD
inline void vec_add_ip(const std::size_t n, const double * RESTRICT v, double * RESTRICT result)
=======
inline static void vec_add_ip(const std::size_t n, const double * RESTRICT v, double * RESTRICT result)
>>>>>>> upstream/master
{
	for ( std::size_t i = 0; i < n; i++ )
		result[i] += v[i];
}

<<<<<<< HEAD
template<typename T>
inline void vec_sub(const std::size_t n, const T * RESTRICT v1, const T * RESTRICT v2, T * RESTRICT result)
{
	for ( std::size_t i = 0; i < n; i++ )
		result[i] = v1[i] - v2[i];
}

template<typename T>
inline void vec_scale (const std::size_t n, T * RESTRICT v, const T scalar)
{
	for ( std::size_t i = 0; i < n; i++ )
		v[i] = scalar * v[i];
=======
template<typename T, std::size_t N>
inline void vec_sub(const std::size_t n, const T (& RESTRICT v1)[N], const T (& RESTRICT v2)[N], T (& RESTRICT result)[N])
{
	if (n != N)
		for ( std::size_t i = 0; i < n; i++ )
			result[i] = v1[i] - v2[i];
	else
		for ( std::size_t i = 0; i < N; i++ )
			result[i] = v1[i] - v2[i];
}

template<typename T, std::size_t N>
inline void vec_scale(const std::size_t n, T (& RESTRICT v)[N], const T scalar)
{
	if (n != N)
		for ( std::size_t i = 0; i < n; i++ )
			v[i] = scalar * v[i];
	else
		for ( std::size_t i = 0; i < N; i++ )
			v[i] = scalar * v[i];
>>>>>>> upstream/master
}

inline double vec_maxabs(const std::size_t n, const double * RESTRICT v)
{
	double ret = 0.0;
	for ( std::size_t i = 0; i < n; i++ )
		ret = std::max(ret, std::abs(v[i]));

	return ret;
}
#if !defined(__clang__) && !defined(_MSC_VER) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 6))
#pragma GCC diagnostic pop
#endif

#endif /* MAT_CR_H_ */
