#ifndef IPV4_H
#define IPV4_H

#include <string>
#include <cstdint>

class IPv4 {
public:
  IPv4();
  explicit IPv4(const std::string& s);
  explicit IPv4(uint32_t addr);
  uint32_t to_uint() const;
  std::string to_string() const;
private:
  uint32_t addr_;
};

#endif // IPV4_H 