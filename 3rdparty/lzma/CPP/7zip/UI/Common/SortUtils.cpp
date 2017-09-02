// SortUtils.cpp

#include "StdAfx.h"

<<<<<<< HEAD
#include "SortUtils.h"
#include "Common/Wildcard.h"

static int CompareStrings(const int *p1, const int *p2, void *param)
=======
#include "../../../Common/Wildcard.h"

#include "SortUtils.h"

static int CompareStrings(const unsigned *p1, const unsigned *p2, void *param)
>>>>>>> upstream/master
{
  const UStringVector &strings = *(const UStringVector *)param;
  return CompareFileNames(strings[*p1], strings[*p2]);
}

<<<<<<< HEAD
void SortFileNames(const UStringVector &strings, CIntVector &indices)
{
  indices.Clear();
  int numItems = strings.Size();
  indices.Reserve(numItems);
  for(int i = 0; i < numItems; i++)
    indices.Add(i);
=======
void SortFileNames(const UStringVector &strings, CUIntVector &indices)
{
  const unsigned numItems = strings.Size();
  indices.ClearAndSetSize(numItems);
  if (numItems == 0)
    return;
  unsigned *vals = &indices[0];
  for (unsigned i = 0; i < numItems; i++)
    vals[i] = i;
>>>>>>> upstream/master
  indices.Sort(CompareStrings, (void *)&strings);
}
