all:
	c++ -O3 -Wall -shared -std=c++17 -fPIC $(shell python3 -m pybind11 --includes) \
		pybind_ndarray.cpp -o ndarray$(shell python3-config --extension-suffix)
