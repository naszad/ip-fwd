#include "Forwarder.h"
#include <algorithm>
#include <iostream>

Forwarder::Forwarder(const std::vector<Iface>& ifaces) : ifaces_(ifaces) {
    // No need to sort as we'll consider prefix lengths during matching
}

int Forwarder::forward(const IPv4& ip) {
    int best_match_id = -1;
    uint8_t best_prefix_length = 0;
    int default_route_id = -1;

    for (auto& iface : ifaces_) {
        // Special handling for default route (0.0.0.0/0)
        if (iface.network().prefix_length() == 0) {
            default_route_id = iface.id();
            continue; // Skip default route in normal matching
        }

        if (iface.network().contains(ip)) {
            uint8_t prefix = iface.network().prefix_length();
            if (prefix > best_prefix_length) {
                best_prefix_length = prefix;
                best_match_id = iface.id();
            }
        }
    }

    // If no match was found, use default route if available
    if (best_match_id == -1 && default_route_id != -1) {
        best_match_id = default_route_id;
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