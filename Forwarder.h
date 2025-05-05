#ifndef FORWARDER_H
#define FORWARDER_H

#include <vector>
#include "Iface.h"
#include "IPv4.h"

class Forwarder {
public:
    // Initialize with a list of interfaces; will sort by longest prefix first
    explicit Forwarder(const std::vector<Iface>& ifaces);

    // Forward the given IP to the best matching interface, increment its count, and return the interface ID
    int forward(const IPv4& ip);

    // Report the packet counts for each interface to stdout
    void report() const;

private:
    std::vector<Iface> ifaces_;
};

#endif // FORWARDER_H 