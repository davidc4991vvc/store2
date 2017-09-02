// UpdateProduce.cpp

#include "StdAfx.h"

#include "UpdateProduce.h"

using namespace NUpdateArchive;

static const char *kUpdateActionSetCollision = "Internal collision in update action set";

void UpdateProduce(
    const CRecordVector<CUpdatePair> &updatePairs,
    const CActionSet &actionSet,
    CRecordVector<CUpdatePair2> &operationChain,
    IUpdateProduceCallback *callback)
{
<<<<<<< HEAD
  for (int i = 0; i < updatePairs.Size(); i++)
=======
  FOR_VECTOR (i, updatePairs)
>>>>>>> upstream/master
  {
    const CUpdatePair &pair = updatePairs[i];

    CUpdatePair2 up2;
<<<<<<< HEAD
    up2.IsAnti = false;
    up2.DirIndex = pair.DirIndex;
    up2.ArcIndex = pair.ArcIndex;
    up2.NewData = up2.NewProps = true;
    
    switch(actionSet.StateActions[pair.State])
    {
      case NPairAction::kIgnore:
        /*
        if (pair.State != NPairState::kOnlyOnDisk)
          IgnoreArchiveItem(m_ArchiveItems[pair.ArcIndex]);
        // cout << "deleting";
        */
        if (callback)
=======
    up2.DirIndex = pair.DirIndex;
    up2.ArcIndex = pair.ArcIndex;
    up2.NewData = up2.NewProps = true;
    up2.UseArcProps = false;
    
    switch (actionSet.StateActions[(unsigned)pair.State])
    {
      case NPairAction::kIgnore:
        if (pair.ArcIndex >= 0 && callback)
>>>>>>> upstream/master
          callback->ShowDeleteFile(pair.ArcIndex);
        continue;

      case NPairAction::kCopy:
        if (pair.State == NPairState::kOnlyOnDisk)
          throw kUpdateActionSetCollision;
<<<<<<< HEAD
        up2.NewData = up2.NewProps = false;
=======
        if (pair.State == NPairState::kOnlyInArchive)
        {
          if (pair.HostIndex >= 0)
          {
            /*
              ignore alt stream if
                1) no such alt stream in Disk
                2) there is Host file in disk
            */
            if (updatePairs[pair.HostIndex].DirIndex >= 0)
              continue;
          }
        }
        up2.NewData = up2.NewProps = false;
        up2.UseArcProps = true;
>>>>>>> upstream/master
        break;
      
      case NPairAction::kCompress:
        if (pair.State == NPairState::kOnlyInArchive ||
            pair.State == NPairState::kNotMasked)
          throw kUpdateActionSetCollision;
        break;
      
      case NPairAction::kCompressAsAnti:
        up2.IsAnti = true;
<<<<<<< HEAD
        break;
    }
    operationChain.Add(up2);
  }
=======
        up2.UseArcProps = (pair.ArcIndex >= 0);
        break;
    }

    operationChain.Add(up2);
  }
  
>>>>>>> upstream/master
  operationChain.ReserveDown();
}
