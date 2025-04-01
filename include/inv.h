#ifndef inv_h
#define inv_h

#include "./act.h"
#include "./inv.auto.h"
#include "./str.h"
#include "./ArrLike.h"

/** @brief count integer for item stack. */
typedef INV_ITEMC_T inv_itemc_t;

/** @brief count integer for inventory */
typedef INVC_T invc_t;

/** @brief Item */
typedef struct Inv_Item {
	/** @brief What will it do */
	Act act;

	/** 
	 * @brief How much does item exist 
	 * */
	inv_itemc_t count;
} Inv_Item;

/** @brief Inventory */
typedef struct Inv {
	Inv_Item v[INV_MAX];
	invc_t c;

	ArrLikeInjection(
			, Inv_Item
			, invc_t
			);
} Inv;

#endif
