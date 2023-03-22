#include <stdio.h>
#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <stdlib.h>
#include <string.h>

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
	PRINT_FUNC printFunc;
}AdptArray , *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
	pArr->printFunc = printFunc_;
	return pArr;
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{	
    if(pArr == NULL) return FAIL;
	if( idx < 0) return FAIL;
	if (pNewElem == NULL) return FAIL;

	if(idx >= pArr->ArrSize) 
	{
		PElement* newpElemArr;
		newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement)); 
		if(newpElemArr == NULL) 
		{
			return FAIL;
		}
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement)); 
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
		pArr->ArrSize = idx + 1;
	}

	if((pArr->pElemArr)[idx] != NULL)
		pArr->delFunc((pArr->pElemArr)[idx]);
		
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);
	return SUCCESS;
}


void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
		if((pArr->pElemArr)[i] != NULL)
			pArr->delFunc((pArr->pElemArr)[i]);
	}
	free(pArr->pElemArr);
	free(pArr);
}

PElement GetAdptArrayAt(PAdptArray pArr, int idx)
{
	if(pArr == NULL) return FAIL;
	if(pArr->ArrSize < idx || idx < 0) return FAIL;
	if((pArr->pElemArr[idx]) == NULL) return FAIL;

	return pArr->copyFunc((pArr->pElemArr)[idx]);
}

void PrintDB(PAdptArray pArr)
{
	if(pArr == NULL) return;
	int i = 0;
	for(i = 0; i<pArr->ArrSize; i++)
	{
		if((pArr->pElemArr)[i] != NULL)
		{
			pArr->printFunc((pArr->pElemArr)[i]);
		}
	}
}

int GetAdptArraySize(PAdptArray pArr)
{
	if(pArr == NULL)
		return FAIL;
	return pArr->ArrSize;
}

