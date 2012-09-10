@echo off
g++ gen1.cpp
echo Generating data...
a 1000 10000 > 1.in
g++ dijkstra.cpp
echo Running dijkstra
a < 1.in > 1.a
g++ dijkstraheap.cpp
echo Running dijkstraheap
a < 1.in > 1.b
g++ bellman.cpp
echo Running bellman
a < 1.in > 1.c
fc 1.a 1.b
fc 1.a 1.c
del a.exe
del 1.in
del 1.a
del 1.b
del 1.c