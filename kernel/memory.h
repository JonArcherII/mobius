#include <libcore/logstream.h>
#include <libcore/types.h>

namespace kernel {

class PhysicalAddress {
public:
  explicit PhysicalAddress(GenericPointer address) : m_address(address) {}

  GenericPointer address() { return m_address; }

private:
  GenericPointer m_address{0};
};

inline const LogStream &operator<<(const LogStream &stream,
                                   PhysicalAddress addr) {
  char buffer[32];
  utoa(addr.address(), buffer, 16);
  stream.write(buffer, strlen(buffer));
  return stream;
}

}
