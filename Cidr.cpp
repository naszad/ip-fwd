#include "Cidr.h"
#include <stdexcept>
#include <sstream>

Cidr::Cidr(const std::string& s) {
    auto pos = s.find('/');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Invalid CIDR notation: " + s);
    }
    std::string ip_str = s.substr(0, pos);
    std::string prefix_str = s.substr(pos + 1);
    int prefix;
    try {
        prefix = std::stoi(prefix_str);
    } catch (...) {
        throw std::invalid_argument("Invalid CIDR notation: " + s);
    }
    if (prefix < 0 || prefix > 32) {
        throw std::invalid_argument("Invalid CIDR notation: " + s);
    }
    prefix_length_ = static_cast<uint8_t>(prefix);
    IPv4 ip(ip_str);
    uint32_t mask = prefix_length_ ? (uint32_t(~0U) << (32 - prefix_length_)) : 0;
    uint32_t net_addr = ip.to_uint() & mask;
    network_ = IPv4(net_addr);
}

bool Cidr::contains(const IPv4& ip) const {
    uint32_t mask = prefix_length_ ? (uint32_t(~0U) << (32 - prefix_length_)) : 0;
    return (ip.to_uint() & mask) == network_.to_uint();
}