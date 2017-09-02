// MyCom.h

<<<<<<< HEAD
#ifndef __MYCOM_H
#define __MYCOM_H

#include "MyWindows.h"
=======
#ifndef __MY_COM_H
#define __MY_COM_H

#include "MyWindows.h"
#include "NewHandler.h"
>>>>>>> upstream/master

#ifndef RINOK
#define RINOK(x) { HRESULT __result_ = (x); if (__result_ != S_OK) return __result_; }
#endif

template <class T>
class CMyComPtr
{
  T* _p;
public:
<<<<<<< HEAD
  // typedef T _PtrClass;
  CMyComPtr() { _p = NULL;}
  CMyComPtr(T* p) {if ((_p = p) != NULL) p->AddRef(); }
  CMyComPtr(const CMyComPtr<T>& lp)
  {
    if ((_p = lp._p) != NULL)
      _p->AddRef();
  }
=======
  CMyComPtr(): _p(NULL) {}
  CMyComPtr(T* p) throw() { if ((_p = p) != NULL) p->AddRef(); }
  CMyComPtr(const CMyComPtr<T>& lp) throw() { if ((_p = lp._p) != NULL) _p->AddRef(); }
>>>>>>> upstream/master
  ~CMyComPtr() { if (_p) _p->Release(); }
  void Release() { if (_p) { _p->Release(); _p = NULL; } }
  operator T*() const {  return (T*)_p;  }
  // T& operator*() const {  return *_p; }
  T** operator&() { return &_p; }
  T* operator->() const { return _p; }
  T* operator=(T* p)
  {
<<<<<<< HEAD
    if (p != 0)
=======
    if (p)
>>>>>>> upstream/master
      p->AddRef();
    if (_p)
      _p->Release();
    _p = p;
    return p;
  }
  T* operator=(const CMyComPtr<T>& lp) { return (*this = lp._p); }
  bool operator!() const { return (_p == NULL); }
  // bool operator==(T* pT) const {  return _p == pT; }
<<<<<<< HEAD
  // Compare two objects for equivalence
=======
>>>>>>> upstream/master
  void Attach(T* p2)
  {
    Release();
    _p = p2;
  }
  T* Detach()
  {
    T* pt = _p;
    _p = NULL;
    return pt;
  }
  #ifdef _WIN32
  HRESULT CoCreateInstance(REFCLSID rclsid, REFIID iid, LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL)
  {
    return ::CoCreateInstance(rclsid, pUnkOuter, dwClsContext, iid, (void**)&_p);
  }
  #endif
  /*
  HRESULT CoCreateInstance(LPCOLESTR szProgID, LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL)
  {
    CLSID clsid;
    HRESULT hr = CLSIDFromProgID(szProgID, &clsid);
    ATLASSERT(_p == NULL);
    if (SUCCEEDED(hr))
      hr = ::CoCreateInstance(clsid, pUnkOuter, dwClsContext, __uuidof(T), (void**)&_p);
    return hr;
  }
  */
  template <class Q>
<<<<<<< HEAD
  HRESULT QueryInterface(REFGUID iid, Q** pp) const
=======
  HRESULT QueryInterface(REFGUID iid, Q** pp) const throw()
>>>>>>> upstream/master
  {
    return _p->QueryInterface(iid, (void**)pp);
  }
};

//////////////////////////////////////////////////////////

inline HRESULT StringToBstr(LPCOLESTR src, BSTR *bstr)
{
  *bstr = ::SysAllocString(src);
<<<<<<< HEAD
  return (*bstr != 0) ? S_OK : E_OUTOFMEMORY;
=======
  return (*bstr) ? S_OK : E_OUTOFMEMORY;
>>>>>>> upstream/master
}

class CMyComBSTR
{
<<<<<<< HEAD
public:
  BSTR m_str;
  CMyComBSTR(): m_str(NULL) {}
=======
  BSTR m_str;

public:
  CMyComBSTR(): m_str(NULL) {}
  ~CMyComBSTR() { ::SysFreeString(m_str); }
  BSTR* operator&() { return &m_str; }
  operator LPCOLESTR() const { return m_str; }
  // operator bool() const { return m_str != NULL; }
  // bool operator!() const { return m_str == NULL; }
private:
  // operator BSTR() const { return m_str; }

>>>>>>> upstream/master
  CMyComBSTR(LPCOLESTR src) { m_str = ::SysAllocString(src); }
  // CMyComBSTR(int nSize) { m_str = ::SysAllocStringLen(NULL, nSize); }
  // CMyComBSTR(int nSize, LPCOLESTR sz) { m_str = ::SysAllocStringLen(sz, nSize);  }
  CMyComBSTR(const CMyComBSTR& src) { m_str = src.MyCopy(); }
<<<<<<< HEAD
=======
  
>>>>>>> upstream/master
  /*
  CMyComBSTR(REFGUID src)
  {
    LPOLESTR szGuid;
    StringFromCLSID(src, &szGuid);
    m_str = ::SysAllocString(szGuid);
    CoTaskMemFree(szGuid);
  }
  */
<<<<<<< HEAD
  ~CMyComBSTR() { ::SysFreeString(m_str); }
=======
  
>>>>>>> upstream/master
  CMyComBSTR& operator=(const CMyComBSTR& src)
  {
    if (m_str != src.m_str)
    {
      if (m_str)
        ::SysFreeString(m_str);
      m_str = src.MyCopy();
    }
    return *this;
  }
<<<<<<< HEAD
=======
  
>>>>>>> upstream/master
  CMyComBSTR& operator=(LPCOLESTR src)
  {
    ::SysFreeString(m_str);
    m_str = ::SysAllocString(src);
    return *this;
  }
<<<<<<< HEAD
  unsigned int Length() const { return ::SysStringLen(m_str); }
  operator BSTR() const { return m_str; }
  BSTR* operator&() { return &m_str; }
  BSTR MyCopy() const
  {
    int byteLen = ::SysStringByteLen(m_str);
    BSTR res = ::SysAllocStringByteLen(NULL, byteLen);
    memcpy(res, m_str, byteLen);
    return res;
  }
=======
  
  unsigned Len() const { return ::SysStringLen(m_str); }

  BSTR MyCopy() const
  {
    // We don't support Byte BSTRs here
    return ::SysAllocStringLen(m_str, ::SysStringLen(m_str));
    /*
    UINT byteLen = ::SysStringByteLen(m_str);
    BSTR res = ::SysAllocStringByteLen(NULL, byteLen);
    if (res && byteLen != 0 && m_str)
      memcpy(res, m_str, byteLen);
    return res;
    */
  }
  
>>>>>>> upstream/master
  /*
  void Attach(BSTR src) { m_str = src; }
  BSTR Detach()
  {
    BSTR s = m_str;
    m_str = NULL;
    return s;
  }
  */
<<<<<<< HEAD
=======

>>>>>>> upstream/master
  void Empty()
  {
    ::SysFreeString(m_str);
    m_str = NULL;
  }
<<<<<<< HEAD
  bool operator!() const {  return (m_str == NULL); }
=======
>>>>>>> upstream/master
};

//////////////////////////////////////////////////////////

class CMyUnknownImp
{
public:
  ULONG __m_RefCount;
  CMyUnknownImp(): __m_RefCount(0) {}
<<<<<<< HEAD
};

#define MY_QUERYINTERFACE_BEGIN STDMETHOD(QueryInterface) \
    (REFGUID iid, void **outObject) {

#define MY_QUERYINTERFACE_ENTRY(i) if (iid == IID_ ## i) \
    { *outObject = (void *)(i *)this; AddRef(); return S_OK; }

#define MY_QUERYINTERFACE_ENTRY_UNKNOWN(i) if (iid == IID_IUnknown) \
    { *outObject = (void *)(IUnknown *)(i *)this; AddRef(); return S_OK; }
=======

  // virtual ~CMyUnknownImp() {};
};

#define MY_QUERYINTERFACE_BEGIN STDMETHOD(QueryInterface) \
(REFGUID iid, void **outObject) throw() { *outObject = NULL;

#define MY_QUERYINTERFACE_ENTRY(i) else if (iid == IID_ ## i) \
    { *outObject = (void *)(i *)this; }

#define MY_QUERYINTERFACE_ENTRY_UNKNOWN(i) if (iid == IID_IUnknown) \
    { *outObject = (void *)(IUnknown *)(i *)this; }
>>>>>>> upstream/master

#define MY_QUERYINTERFACE_BEGIN2(i) MY_QUERYINTERFACE_BEGIN \
    MY_QUERYINTERFACE_ENTRY_UNKNOWN(i) \
    MY_QUERYINTERFACE_ENTRY(i)

<<<<<<< HEAD
#define MY_QUERYINTERFACE_END return E_NOINTERFACE; }

#define MY_ADDREF_RELEASE \
STDMETHOD_(ULONG, AddRef)() { return ++__m_RefCount; } \
=======
#define MY_QUERYINTERFACE_END else return E_NOINTERFACE; ++__m_RefCount; /* AddRef(); */ return S_OK; }

#define MY_ADDREF_RELEASE \
STDMETHOD_(ULONG, AddRef)() throw() { return ++__m_RefCount; } \
>>>>>>> upstream/master
STDMETHOD_(ULONG, Release)() { if (--__m_RefCount != 0)  \
  return __m_RefCount; delete this; return 0; }

#define MY_UNKNOWN_IMP_SPEC(i) \
  MY_QUERYINTERFACE_BEGIN \
  i \
  MY_QUERYINTERFACE_END \
  MY_ADDREF_RELEASE


#define MY_UNKNOWN_IMP MY_QUERYINTERFACE_BEGIN \
  MY_QUERYINTERFACE_ENTRY_UNKNOWN(IUnknown) \
  MY_QUERYINTERFACE_END \
  MY_ADDREF_RELEASE

#define MY_UNKNOWN_IMP1(i) MY_UNKNOWN_IMP_SPEC( \
  MY_QUERYINTERFACE_ENTRY_UNKNOWN(i) \
  MY_QUERYINTERFACE_ENTRY(i) \
  )

#define MY_UNKNOWN_IMP2(i1, i2) MY_UNKNOWN_IMP_SPEC( \
  MY_QUERYINTERFACE_ENTRY_UNKNOWN(i1) \
  MY_QUERYINTERFACE_ENTRY(i1) \
  MY_QUERYINTERFACE_ENTRY(i2) \
  )

#define MY_UNKNOWN_IMP3(i1, i2, i3) MY_UNKNOWN_IMP_SPEC( \
  MY_QUERYINTERFACE_ENTRY_UNKNOWN(i1) \
  MY_QUERYINTERFACE_ENTRY(i1) \
  MY_QUERYINTERFACE_ENTRY(i2) \
  MY_QUERYINTERFACE_ENTRY(i3) \
  )

#define MY_UNKNOWN_IMP4(i1, i2, i3, i4) MY_UNKNOWN_IMP_SPEC( \
  MY_QUERYINTERFACE_ENTRY_UNKNOWN(i1) \
  MY_QUERYINTERFACE_ENTRY(i1) \
  MY_QUERYINTERFACE_ENTRY(i2) \
  MY_QUERYINTERFACE_ENTRY(i3) \
  MY_QUERYINTERFACE_ENTRY(i4) \
  )

#define MY_UNKNOWN_IMP5(i1, i2, i3, i4, i5) MY_UNKNOWN_IMP_SPEC( \
  MY_QUERYINTERFACE_ENTRY_UNKNOWN(i1) \
  MY_QUERYINTERFACE_ENTRY(i1) \
  MY_QUERYINTERFACE_ENTRY(i2) \
  MY_QUERYINTERFACE_ENTRY(i3) \
  MY_QUERYINTERFACE_ENTRY(i4) \
  MY_QUERYINTERFACE_ENTRY(i5) \
  )

<<<<<<< HEAD
=======
#define MY_UNKNOWN_IMP6(i1, i2, i3, i4, i5, i6) MY_UNKNOWN_IMP_SPEC( \
  MY_QUERYINTERFACE_ENTRY_UNKNOWN(i1) \
  MY_QUERYINTERFACE_ENTRY(i1) \
  MY_QUERYINTERFACE_ENTRY(i2) \
  MY_QUERYINTERFACE_ENTRY(i3) \
  MY_QUERYINTERFACE_ENTRY(i4) \
  MY_QUERYINTERFACE_ENTRY(i5) \
  MY_QUERYINTERFACE_ENTRY(i6) \
  )

#define MY_UNKNOWN_IMP7(i1, i2, i3, i4, i5, i6, i7) MY_UNKNOWN_IMP_SPEC( \
  MY_QUERYINTERFACE_ENTRY_UNKNOWN(i1) \
  MY_QUERYINTERFACE_ENTRY(i1) \
  MY_QUERYINTERFACE_ENTRY(i2) \
  MY_QUERYINTERFACE_ENTRY(i3) \
  MY_QUERYINTERFACE_ENTRY(i4) \
  MY_QUERYINTERFACE_ENTRY(i5) \
  MY_QUERYINTERFACE_ENTRY(i6) \
  MY_QUERYINTERFACE_ENTRY(i7) \
  )

const HRESULT k_My_HRESULT_WritingWasCut = 0x20000010;

>>>>>>> upstream/master
#endif
