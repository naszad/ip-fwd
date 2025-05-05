#include "Iface.h"

Iface::Iface(int id, const Cidr& network)
    : id_(id), network_(network), count_(0) {}

int Iface::id() const {
    return id_;
}

const Cidr& Iface::network() const {
    return network_;
}

void Iface::increment_count() {
    ++count_;
}

size_t Iface::count() const {
    return count_;
} 