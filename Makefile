# Makefile for forwarding simulator project

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
SRCS = main.cpp IPv4.cpp Cidr.cpp Iface.cpp Forwarder.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = forwarder

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean 