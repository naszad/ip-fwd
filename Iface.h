#ifndef IFACE_H
#define IFACE_H

#include "Cidr.h"
#include <cstddef>  // for size_t

class Iface {
public:
    Iface(int id, const Cidr& network);
    int id() const;
    const Cidr& network() const;
    void increment_count();
    size_t count() const;

private:
    int id_;
    Cidr network_;
    size_t count_;
};

#endif // IFACE_H 