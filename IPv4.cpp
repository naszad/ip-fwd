#include "IPv4.h"
#include <sstream>
#include <stdexcept>

IPv4::IPv4() : addr_(0) {}

IPv4::IPv4(const std::string& s) {
    std::istringstream ss(s);
    uint32_t a, b, c, d;
    char dot1, dot2, dot3;
    if (!(ss >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d) ||
        dot1 != '.' || dot2 != '.' || dot3 != '.' ||
        a > 255 || b > 255 || c > 255 || d > 255) {
        throw std::invalid_argument("Invalid IPv4 address: " + s);
    }
    addr_ = (a << 24) | (b << 16) | (c << 8) | d;
}

IPv4::IPv4(uint32_t addr) : addr_(addr) {}

uint32_t IPv4::to_uint() const {
    return addr_;
}

std::string IPv4::to_string() const {
    std::ostringstream ss;
    ss << ((addr_ >> 24) & 0xFF) << '.'
       << ((addr_ >> 16) & 0xFF) << '.'
       << ((addr_ >> 8) & 0xFF) << '.'
       << (addr_ & 0xFF);
    return ss.str();
} 