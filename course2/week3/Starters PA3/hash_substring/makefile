# makefile for hash_substring

# variables to control makefile operation
CXX = g++
CXXFLAGS = -Wall -g -pipe -O2 -std=c++11 -I/usr/include/boost
LDFLAGS = -L/usr/include/boost

#####
# Targets needed to bring the executable up-to-date

hash_substring: hash_substring.o
	$(CXX) $(CXXFLAGS) -o hash_substring hash_substring.o $(LDFLAGS)

hash_substring.o: hash_substring.cpp
	$(CXX) $(CXXFLAGS) -c hash_substring.cpp
	
