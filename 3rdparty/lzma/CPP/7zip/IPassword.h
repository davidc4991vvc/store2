// IPassword.h

#ifndef __IPASSWORD_H
#define __IPASSWORD_H

<<<<<<< HEAD
#include "../Common/MyUnknown.h"
#include "../Common/Types.h"
=======
#include "../Common/MyTypes.h"
#include "../Common/MyUnknown.h"
>>>>>>> upstream/master

#include "IDecl.h"

#define PASSWORD_INTERFACE(i, x) DECL_INTERFACE(i, 5, x)

PASSWORD_INTERFACE(ICryptoGetTextPassword, 0x10)
{
  STDMETHOD(CryptoGetTextPassword)(BSTR *password) PURE;
};

PASSWORD_INTERFACE(ICryptoGetTextPassword2, 0x11)
{
  STDMETHOD(CryptoGetTextPassword2)(Int32 *passwordIsDefined, BSTR *password) PURE;
};

#endif
<<<<<<< HEAD

=======
>>>>>>> upstream/master
