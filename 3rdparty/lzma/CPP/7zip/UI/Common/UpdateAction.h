// UpdateAction.h

#ifndef __UPDATE_ACTION_H
#define __UPDATE_ACTION_H

namespace NUpdateArchive {

  namespace NPairState
  {
<<<<<<< HEAD
    const int kNumValues = 7;
=======
    const unsigned kNumValues = 7;
>>>>>>> upstream/master
    enum EEnum
    {
      kNotMasked = 0,
      kOnlyInArchive,
      kOnlyOnDisk,
      kNewInArchive,
      kOldInArchive,
      kSameFiles,
      kUnknowNewerFiles
    };
  }
 
  namespace NPairAction
  {
    enum EEnum
    {
      kIgnore = 0,
      kCopy,
      kCompress,
      kCompressAsAnti
    };
  }
  
  struct CActionSet
  {
    NPairAction::EEnum StateActions[NPairState::kNumValues];
<<<<<<< HEAD
    bool NeedScanning() const
    {
      int i;
=======
    
    bool IsEqualTo(const CActionSet &a) const
    {
      for (unsigned i = 0; i < NPairState::kNumValues; i++)
        if (StateActions[i] != a.StateActions[i])
          return false;
      return true;
    }

    bool NeedScanning() const
    {
      unsigned i;
>>>>>>> upstream/master
      for (i = 0; i < NPairState::kNumValues; i++)
        if (StateActions[i] == NPairAction::kCompress)
          return true;
      for (i = 1; i < NPairState::kNumValues; i++)
        if (StateActions[i] != NPairAction::kIgnore)
          return true;
      return false;
    }
  };
  
<<<<<<< HEAD
  extern const CActionSet kAddActionSet;
  extern const CActionSet kUpdateActionSet;
  extern const CActionSet kFreshActionSet;
  extern const CActionSet kSynchronizeActionSet;
  extern const CActionSet kDeleteActionSet;
=======
  extern const CActionSet k_ActionSet_Add;
  extern const CActionSet k_ActionSet_Update;
  extern const CActionSet k_ActionSet_Fresh;
  extern const CActionSet k_ActionSet_Sync;
  extern const CActionSet k_ActionSet_Delete;
>>>>>>> upstream/master
}

#endif
