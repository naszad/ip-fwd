#include "Cidr.h"
#include <stdexcept>
#include <sstream>

Cidr::Cidr(const std::string& s) {
    std::istringstream ss(s);
    std::string ip_str;
    char slash;
    int prefix;
    if (!(ss >> ip_str >> slash >> prefix) || slash != '/' || prefix < 0 || prefix > 32) {
        throw std::invalid_argument("Invalid CIDR notation: " + s);
    }
    prefix_length_ = static_cast<uint8_t>(prefix);
    IPv4 ip(ip_str);
    uint32_t mask = (prefix == 0) ? 0 : (0xFFFFFFFF << (32 - prefix));
    uint32_t net_addr = ip.to_uint() & mask;
    network_ = IPv4(net_addr);
}

bool Cidr::contains(const IPv4& ip) const {
    uint32_t mask = (prefix_length_ == 0) ? 0 : (0xFFFFFFFF << (32 - prefix_length_));
    return (ip.to_uint() & mask) == network_.to_uint();
} 