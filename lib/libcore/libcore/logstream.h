#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

class LogStream {
public:
  LogStream() {}
  ~LogStream() {}

  virtual void write(const char *, size_t) const {}

private:
};

inline const LogStream &operator<<(const LogStream &stream, const char *value) {
  if (!value)
    return stream << "(null)";
  stream.write(value, strlen(value));
  return stream;
}

inline const LogStream &operator<<(const LogStream &stream, const char value) {
  stream.write(&value, 1);
  return stream;
}

inline const LogStream &operator<<(const LogStream &stream,
                                   const int32_t value) {
  char buffer[32];
  itoa(value, buffer, 10);
  stream.write(buffer, strlen(buffer));
  return stream;
}

inline const LogStream &operator<<(const LogStream &stream,
                                   const uint32_t value) {
  char buffer[32];
  utoa(value, buffer, 10);
  stream.write(buffer, strlen(buffer));
  return stream;
}

inline const LogStream &operator<<(const LogStream &stream,
                                   const int64_t value) {
  char buffer[32];
  if ((value >> 32) != 0) {
    itoa((value >> 32), buffer, 10);
    stream.write(buffer, strlen(buffer));
  }
  itoa((value & 0xffffffff), buffer, 10);
  stream.write(buffer, strlen(buffer));
  return stream;
}

inline const LogStream &operator<<(const LogStream &stream,
                                   const uint64_t value) {
  char buffer[32];
  if ((unsigned)(value >> 32) != 0) {
    utoa((unsigned)(value >> 32), buffer, 10);
    stream.write(buffer, strlen(buffer));
  }
  utoa((unsigned)(value & 0xffffffff), buffer, 10);
  stream.write(buffer, strlen(buffer));
  return stream;
}
