#ifndef CIDR_H
#define CIDR_H

#include <cstdint>
#include <string>
#include "IPv4.h"

class Cidr {
public:
    // Construct from a string like "192.168.1.0/24"
    explicit Cidr(const std::string& s);

    // Return the network address
    IPv4 network() const { return network_; }

    // Return the prefix length (0-32)
    uint8_t prefix_length() const { return prefix_length_; }

    // Return true if the given IP is in this network
    bool contains(const IPv4& ip) const;

private:
    IPv4 network_;
    uint8_t prefix_length_;
};

#endif // CIDR_H 