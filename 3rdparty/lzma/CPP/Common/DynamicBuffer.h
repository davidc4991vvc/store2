// Common/DynamicBuffer.h

#ifndef __COMMON_DYNAMIC_BUFFER_H
#define __COMMON_DYNAMIC_BUFFER_H

<<<<<<< HEAD
#include "Buffer.h"

template <class T> class CDynamicBuffer: public CBuffer<T>
{
  void GrowLength(size_t size)
  {
    size_t delta;
    if (this->_capacity > 64)
      delta = this->_capacity / 4;
    else if (this->_capacity > 8)
      delta = 16;
    else
      delta = 4;
    delta = MyMax(delta, size);
    size_t newCap = this->_capacity + delta;
    if (newCap < delta)
      newCap = this->_capacity + size;
    SetCapacity(newCap);
  }
public:
  CDynamicBuffer(): CBuffer<T>() {};
  CDynamicBuffer(const CDynamicBuffer &buffer): CBuffer<T>(buffer) {};
  CDynamicBuffer(size_t size): CBuffer<T>(size) {};
  CDynamicBuffer& operator=(const CDynamicBuffer &buffer)
  {
    this->Free();
    if (buffer._capacity > 0)
    {
      SetCapacity(buffer._capacity);
      memmove(this->_items, buffer._items, buffer._capacity * sizeof(T));
    }
    return *this;
  }
  void EnsureCapacity(size_t capacity)
  {
    if (this->_capacity < capacity)
      GrowLength(capacity - this->_capacity);
  }
};

typedef CDynamicBuffer<char> CCharDynamicBuffer;
typedef CDynamicBuffer<wchar_t> CWCharDynamicBuffer;
=======
template <class T> class CDynamicBuffer
{
  T *_items;
  size_t _size;
  size_t _pos;

  CDynamicBuffer(const CDynamicBuffer &buffer);
  void operator=(const CDynamicBuffer &buffer);

  void Grow(size_t size)
  {
    size_t delta = _size >= 64 ? _size : 64;
    if (delta < size)
      delta = size;
    size_t newCap = _size + delta;
    if (newCap < delta)
    {
      newCap = _size + size;
      if (newCap < size)
        throw 20120116;
    }

    T *newBuffer = new T[newCap];
    if (_pos != 0)
      memcpy(newBuffer, _items, _pos * sizeof(T));
    delete []_items;
    _items = newBuffer;
    _size = newCap;
  }

public:
  CDynamicBuffer(): _items(0), _size(0), _pos(0) {}
  // operator T *() { return _items; }
  operator const T *() const { return _items; }
  ~CDynamicBuffer() { delete []_items; }

  T *GetCurPtrAndGrow(size_t addSize)
  {
    size_t rem = _size - _pos;
    if (rem < addSize)
      Grow(addSize - rem);
    T *res = _items + _pos;
    _pos += addSize;
    return res;
  }

  void AddData(const T *data, size_t size)
  {
    memcpy(GetCurPtrAndGrow(size), data, size * sizeof(T));
  }

  const size_t GetPos() const { return _pos; }

  // void Empty() { _pos = 0; }
};

>>>>>>> upstream/master
typedef CDynamicBuffer<unsigned char> CByteDynamicBuffer;

#endif
