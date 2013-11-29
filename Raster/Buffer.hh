//
// Buffer.h - class Buffer
// KAS 91/06/23
//
#ifndef	__Raster_Buffer_hh
#define	__Raster_Buffer_hh

#include <string.h>	/* memcpy() */

class Buffer {
protected:
  size_t _size;
  unsigned char *_buffer;
  void	copy( const Buffer& B ) {
    _size = B._size;
    _buffer = new unsigned char[_size];
    memcpy(_buffer, B._buffer, _size);
  }
	
public:
  Buffer() : _size(0), _buffer(0) {}
  Buffer(size_t size) : _size(size) { _buffer = new unsigned char[_size]; }
  Buffer(const Buffer &B) { copy(B); }
  Buffer& operator = (const Buffer &B) {
    delete _buffer;
    copy(B);
    return *this;
  }
			
  ~Buffer() { delete _buffer; _buffer = 0; _size = 0; }

  void *buffer() { return _buffer; }
  size_t size() { return _size; }
  void size(int s) {
    unsigned char *temp = new unsigned char[s];
    memcpy(temp, _buffer, s < _size ? s : _size);
    delete _buffer;
    _buffer = temp;
    _size = s;
  }
};

#endif
