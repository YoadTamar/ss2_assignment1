#include <stdio.h>
#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <stdlib.h>
#include <string.h>

/**
 * this is the sturct of the adaptive array
 */
typedef struct AdptArray_
{
	int size;
	PElement *elements_arr;
	DEL_FUNC del;
	COPY_FUNC copy;
	PRINT_FUNC print;
} AdptArray, *PAdptArray;

/**
 * this func create a new empty array
*/
PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC del, PRINT_FUNC print)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->size = 0;
	pArr->elements_arr = NULL;
	pArr->del = del;
	pArr->copy = copy;
	pArr->print = print;
	return pArr;
}

/**
 * this func free all the memory of the array and his all values
*/
void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for (i = 0; i < pArr->size; ++i)
	{
		if ((pArr->elements_arr)[i] != NULL)
			pArr->del((pArr->elements_arr)[i]);
	}
	free(pArr->elements_arr);
	free(pArr);
}

/**
 * this func get an index and an element and it add to the array 
 * the new element to the given index
*/
Result SetAdptArrayAt(PAdptArray pArr, int index, PElement pNewElem)
{
	if (pArr == NULL)
		return FAIL;
	if (index < 0)
		return FAIL;
	if (pNewElem == NULL)
		return FAIL;

	if (index >= pArr->size)
	{
		PElement *newpElemArr;
		newpElemArr = (PElement *)calloc((index + 1), sizeof(PElement));
		if (newpElemArr == NULL) return FAIL;
		memcpy(newpElemArr, pArr->elements_arr, (pArr->size) * sizeof(PElement));
		free(pArr->elements_arr);
		pArr->elements_arr = newpElemArr;
		pArr->size = index + 1;
	}

	if ((pArr->elements_arr)[index] != NULL)
		pArr->del((pArr->elements_arr)[index]);

	(pArr->elements_arr)[index] = pArr->copy(pNewElem);
	return SUCCESS;
}

/**
 * this func get an array and index and return the element in the given index	
*/
PElement GetAdptArrayAt(PAdptArray pArr, int index)
{
	if (pArr == NULL)
		return FAIL;
	if (pArr->size < index || index < 0)
		return FAIL;
	if ((pArr->elements_arr[index]) == NULL)
		return FAIL;

	return pArr->copy((pArr->elements_arr)[index]);
}

/**
 * this func print all the elements in the array
*/
void PrintDB(PAdptArray pArr)
{
	if (pArr == NULL)
		return;
	int i = 0;
	for (i = 0; i < pArr->size; i++)
	{
		if ((pArr->elements_arr)[i] != NULL)
		{
			pArr->print((pArr->elements_arr)[i]);
		}
	}
}

/**
 * this func return the size of the array
*/
int GetAdptArraySize(PAdptArray pArr)
{
	if (pArr == NULL)
		return FAIL;
	return pArr->size;
}
