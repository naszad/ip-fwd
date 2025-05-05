#include "Forwarder.h"
#include <algorithm>
#include <iostream>

Forwarder::Forwarder(const std::vector<Iface>& ifaces) : ifaces_(ifaces) {
    std::sort(ifaces_.begin(), ifaces_.end(), [](const Iface& a, const Iface& b) {
        return a.network().prefix_length() > b.network().prefix_length();
    });
}

int Forwarder::forward(const IPv4& ip) {
    for (auto& iface : ifaces_) {
        if (iface.network().contains(ip)) {
            iface.increment_count();
            return iface.id();
        }
    }
    return -1; // Should not happen if a default route is provided
}

void Forwarder::report() const {
    for (const auto& iface : ifaces_) {
        std::cout << "Interface " << iface.id() << ": " << iface.count() << " packets\n";
    }
} 