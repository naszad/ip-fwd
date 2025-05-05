#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "IPv4.h"
#include "Cidr.h"
#include "Iface.h"
#include "Forwarder.h"

int main() {
    // Initialize interfaces with networks
    std::vector<Iface> ifaces = {
        Iface(0, Cidr("192.168.1.0/28")),
        Iface(1, Cidr("192.168.1.0/24")),
        Iface(2, Cidr("10.0.1.0/24")),
        Iface(3, Cidr("10.0.2.0/23")),
        Iface(4, Cidr("10.0.0.0/21")),
        Iface(5, Cidr("172.16.0.0/20")),
        Iface(6, Cidr("159.242.0.0/16")),
        // Default route
        Iface(7, Cidr("0.0.0.0/0"))
    };

    Forwarder forwarder(ifaces);

    std::ifstream infile("destinations.txt");
    if (!infile) {
        std::cerr << "Error: Could not open destinations.txt" << std::endl;
        return 1;
    }
    std::string ip_str;
    while (infile >> ip_str) {
        try {
            IPv4 ip(ip_str);
            int iface_id = forwarder.forward(ip);
            if (iface_id >= 0) {
                std::cout << iface_id << std::endl;
            } else {
                std::cout << "No route for " << ip_str << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Invalid IP " << ip_str << ": " << e.what() << std::endl;
        }
    }

    // Report summary counts
    forwarder.report();
    return 0;
} 