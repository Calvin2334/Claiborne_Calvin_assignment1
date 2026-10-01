Assignment 1

Language: C++
Graph type: Undirected
Development environment: MSYS2 UCRT64

Compile:
g++ -std=c++17 -Wall -Wextra graph_operations.cpp graph_simulator.cpp simulated_test.cpp -o simulated_test.exe

Run all experiments:
./simulated_test.exe

Run one experiment:
./simulated_test.exe cycle 1000
./simulated_test.exe complete 1000
./simulated_test.exe empty 1000

Peak memory measurement:
GNU time was used in MSYS2 UCRT64 to measure maximum resident set size.