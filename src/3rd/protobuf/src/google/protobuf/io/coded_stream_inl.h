
#ifndef GOOGLE_PROTOBUF_IO_CODED_STREAM_INL_H__
#define GOOGLE_PROTOBUF_IO_CODED_STREAM_INL_H__

#include <google/protobuf/stubs/logging.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <string>
#include <google/protobuf/stubs/stl_util.h>

namespace google {
namespace protobuf {
namespace io {

inline bool CodedInputStream::InternalReadStringInline(string* buffer,
                                                       int size) {
  if (size < 0) return false;  // security: size is often user-supplied

  if (BufferSize() >= size) {
    STLStringResizeUninitialized(buffer, size);
    std::pair<char*, bool> z = as_string_data(buffer);
    if (z.second) {
      // Oddly enough, memcpy() requires its first two args to be non-NULL even
      // if we copy 0 bytes.  So, we have ensured that z.first is non-NULL here.
      GOOGLE_DCHECK(z.first != NULL);
      memcpy(z.first, buffer_, size);
      Advance(size);
    }
    return true;
  }

  return ReadStringFallback(buffer, size);
}

inline bool CodedInputStream::InternalReadRawInline(void* buffer, int size) {
  int current_buffer_size;
  while ((current_buffer_size = BufferSize()) < size) {
    // Reading past end of buffer.  Copy what we have, then refresh.
    memcpy(buffer, buffer_, current_buffer_size);
    buffer = reinterpret_cast<uint8*>(buffer) + current_buffer_size;
    size -= current_buffer_size;
    Advance(current_buffer_size);
    if (!Refresh()) return false;
  }

  memcpy(buffer, buffer_, size);
  Advance(size);

  return true;
}

}  // namespace io
}  // namespace protobuf
}  // namespace google
#endif  // GOOGLE_PROTOBUF_IO_CODED_STREAM_INL_H__
