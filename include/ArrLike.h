
#include <ae2f/Cast.h>
#include <ae2f/Call.h>

/** Vector name */
#define ArrLike_VName	v

/** Count Name */
#define ArrLike_CName	c

/** 
 * Having this means that it is Arrlike. \n
 * Which means that:
 * - it has `v` as vector name.
 * - it has `c` as size name.
 * */
#define ArrLike ae2f_NONE

/** 
 * @brief 
 * check `i` valid. `true` means ok. 
 * It contains null check.
 * */
#define ArrLikeIValid(a, i) ((a)->ArrLike_VName && (a)->ArrLike_CName > (i))

/**
 * @brief
 * Try indexing from arrlike. \n
 * Returns 0 when failed.
 * */
#define ArrLikeTryIdx(a, i) (ArrLikeIValid(a, i) ? (a)->ArrLike_VName + (i) : 0)

/** @brief Util Function for CXX */
#if ae2f_WhenCXX(!)0

#define ArrLikeInjection(p, eltype, ctype) \
	constexpr bool p##IValid(ctype i) { return ArrLikeIValid(this, i); } \
	constexpr eltype p##TryIdx(ctype i) { return ArrLikeTryIdx(this, i); } \

#else

#define ArrLikeInjection(p, eltype, ctype) ae2f_NONE

#endif
