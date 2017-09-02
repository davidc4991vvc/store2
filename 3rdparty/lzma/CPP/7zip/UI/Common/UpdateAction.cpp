// UpdateAction.cpp

#include "StdAfx.h"

#include "UpdateAction.h"

namespace NUpdateArchive {

<<<<<<< HEAD
const CActionSet kAddActionSet =
=======
const CActionSet k_ActionSet_Add =
>>>>>>> upstream/master
{{
  NPairAction::kCopy,
  NPairAction::kCopy,
  NPairAction::kCompress,
  NPairAction::kCompress,
  NPairAction::kCompress,
  NPairAction::kCompress,
  NPairAction::kCompress
}};

<<<<<<< HEAD
const CActionSet kUpdateActionSet =
=======
const CActionSet k_ActionSet_Update =
>>>>>>> upstream/master
{{
  NPairAction::kCopy,
  NPairAction::kCopy,
  NPairAction::kCompress,
  NPairAction::kCopy,
  NPairAction::kCompress,
  NPairAction::kCopy,
  NPairAction::kCompress
}};

<<<<<<< HEAD
const CActionSet kFreshActionSet =
=======
const CActionSet k_ActionSet_Fresh =
>>>>>>> upstream/master
{{
  NPairAction::kCopy,
  NPairAction::kCopy,
  NPairAction::kIgnore,
  NPairAction::kCopy,
  NPairAction::kCompress,
  NPairAction::kCopy,
  NPairAction::kCompress
}};

<<<<<<< HEAD
const CActionSet kSynchronizeActionSet =
=======
const CActionSet k_ActionSet_Sync =
>>>>>>> upstream/master
{{
  NPairAction::kCopy,
  NPairAction::kIgnore,
  NPairAction::kCompress,
  NPairAction::kCopy,
  NPairAction::kCompress,
  NPairAction::kCopy,
  NPairAction::kCompress,
}};

<<<<<<< HEAD
const CActionSet kDeleteActionSet =
=======
const CActionSet k_ActionSet_Delete =
>>>>>>> upstream/master
{{
  NPairAction::kCopy,
  NPairAction::kIgnore,
  NPairAction::kIgnore,
  NPairAction::kIgnore,
  NPairAction::kIgnore,
  NPairAction::kIgnore,
  NPairAction::kIgnore
}};

}
