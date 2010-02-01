/*****************************************************************************
*   "Gif-Lib" - Yet another gif library.				     *
*									     *
* Written by:  Gershon Elber			IBM PC Ver 0.1,	Jun. 1989    *
******************************************************************************
* Module to support the following operations:				     *
*									     *
* 1. InitHashTable - initialize hash table.				     *
* 2. ClearHashTable - clear the hash table to an empty state.		     *
* 2. InsertHashTable - insert one item into data structure.		     *
* 3. ExistsHashTable - test if item exists in data structure.		     *
*									     *
* This module is used to hash the GIF codes during encoding.		     *
******************************************************************************
* History:								     *
* 14 Jun 89 - Version 1.0 by Gershon Elber.				     *
*****************************************************************************/

#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "gif_lib.h"
#include "gif_hash.h"
#include "gif_lib_private.h"

static int KeyItem(uint32 Item);

/******************************************************************************
* Initialize HashTable - allocate the memory needed and clear it.	      *
******************************************************************************/
GifHashTableType *_InitHashTable(void)
{
    GifHashTableType *HashTable;

    if ((HashTable = (GifHashTableType *) malloc(sizeof(GifHashTableType)))
	== NULL)
	return NULL;

    _ClearHashTable(HashTable);

    return HashTable;
}

/******************************************************************************
* Routine to clear the HashTable to an empty state.			      *
* This part is a little machine depended. Use the commented part otherwise.   *
******************************************************************************/
void _ClearHashTable(GifHashTableType *HashTable)
{
    memset(HashTable -> HTable, 0xFF, HT_SIZE * sizeof(uint32));
}

/******************************************************************************
* Routine to insert a new Item into the HashTable. The data is assumed to be  *
* new one.								      *
******************************************************************************/
void _InsertHashTable(GifHashTableType *HashTable, uint32 Key, int Code)
{
    int HKey = KeyItem(Key);
    uint32 *HTable = HashTable -> HTable;

    while (HT_GET_KEY(HTable[HKey]) != 0xFFFFFL) {

	    	HKey = (HKey + 1) & HT_KEY_MASK;
    }
    HTable[HKey] = HT_PUT_KEY(Key) | HT_PUT_CODE(Code);
}

/******************************************************************************
* Routine to test if given Key exists in HashTable and if so returns its code *
* Returns the Code if key was found, -1 if not.				      *
******************************************************************************/
int _ExistsHashTable(GifHashTableType *HashTable, uint32 Key)
{
    int HKey = KeyItem(Key);
    uint32 *HTable = HashTable -> HTable, HTKey;


    while ((HTKey = HT_GET_KEY(HTable[HKey])) != 0xFFFFFL) {

	if (Key == HTKey) return HT_GET_CODE(HTable[HKey]);
	HKey = (HKey + 1) & HT_KEY_MASK;
    }

    return -1;
}

/******************************************************************************
* Routine to generate an HKey for the hashtable out of the given unique key.  *
* The given Key is assumed to be 20 bits as follows: lower 8 bits are the     *
* new postfix character, while the upper 12 bits are the prefix code.	      *
* Because the average hit ratio is only 2 (2 hash references per entry),      *
* evaluating more complex keys (such as twin prime keys) does not worth it!   *
******************************************************************************/
static int KeyItem(uint32 Item)
{
    return ((Item >> 12) ^ Item) & HT_KEY_MASK;
}