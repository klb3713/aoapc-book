@echo off
g++ gen1.cpp
echo Generating data...
a 1000 10000 > 1.in
g++ maxflow.cpp
echo Running maxflow
a < 1.in > 1.a
g++ maxflow2.cpp
echo Running maxflow2
a < 1.in > 1.b
fc 1.a 1.b
del a.exe
del 1.in
del 1.a
del 1.b
