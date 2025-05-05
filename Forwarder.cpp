#include "Forwarder.h"
#include <algorithm>
#include <iostream>

Forwarder::Forwarder(const std::vector<Iface>& ifaces) : ifaces_(ifaces) {
    // No need to sort as we'll consider prefix lengths during matching
}

int Forwarder::forward(const IPv4& ip) {
    int best_match_id = -1;
    uint8_t best_prefix_length = 0;

    for (auto& iface : ifaces_) {
        if (iface.network().contains(ip)) {
            uint8_t prefix = iface.network().prefix_length();
            if (prefix > best_prefix_length) {
                best_prefix_length = prefix;
                best_match_id = iface.id();
            }
        }
    }

    if (best_match_id != -1) {
        // Find the interface with this ID and increment its count
        for (auto& iface : ifaces_) {
            if (iface.id() == best_match_id) {
                iface.increment_count();
                break;
            }
        }
    }
    return best_match_id;
}

void Forwarder::report() const {
    for (const auto& iface : ifaces_) {
        std::cout << "Interface " << iface.id() << ": " << iface.count() << " packets\n";
    }
} 