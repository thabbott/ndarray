#include <typeinfo>
#include <iostream>
#include <pybind11/pybind11.h>

#include "ndarray.hpp"

namespace py = pybind11;

template<typename T, size_t D>
std::string suffix() {
    
    if (D < 0 || D > 5) {
        throw std::runtime_error("D must be between 0 and 5 (inclusive)");
    }
    std::string dim = std::to_string(D);

    if (typeid(T) == typeid(float)) { return dim + std::string("f"); }
    if (typeid(T) == typeid(double)) { return dim + std::string("d"); }
    if (typeid(T) == typeid(int32_t)) { return dim + std::string("i"); }
    if (typeid(T) == typeid(int64_t)) { return dim + std::string("l"); }
    if (typeid(T) == typeid(bool)) { return dim + std::string("b"); }
    throw std::runtime_error("Unsupported type");
}
	    

template<typename T, size_t D>
void declare_initializer(py::module& m) {

    std::string pyclass = std::string("Array") + suffix<T, D>();
    
    py::class_<ndarray<T, D>>(m, pyclass.c_str(), py::buffer_protocol())
        .def(py::init([](py::buffer b) {
            
            // Get buffer descriptor 
            py::buffer_info info = b.request();

	    // Check dimensionality
	    if (info.ndim != static_cast<py::ssize_t>(D)) {
	        throw std::runtime_error("Dimensionality mismatch between buffer and array");
	    }

	    // Check format
	    if (info.format != py::format_descriptor<T>::format()) {
	        throw std::runtime_error("Format mismatch between buffer and array");
	    }

	    // Check strides 
	    py::ssize_t stride = static_cast<py::ssize_t>(sizeof(T));
	    for (size_t i = D; i --> 0; ) {
	        if (info.strides[i] != stride) {
	            throw std::runtime_error("Buffer not contiguous and column-major.");
		}
		stride *= info.shape[i];
	    }

	    std::array<size_t, D> sz;
	    for (size_t i = 0; i < D; i++) {
	        sz[i] = static_cast<size_t>(info.shape[i]);
	    }

	    return ndarray<T, D>(static_cast<T*>(info.ptr), sz);
	}));

}

PYBIND11_MODULE(ndarray, m) {

    // Define constructor allowing NDArrays to be instantiated in Python
    // from a Python buffer
    // Classes are ArrayDt
    // D can be 0, 1, 2, 3, 4, 5
    // t can be f (float32), d (float64), i (int32), l (int64)
    
    declare_initializer<float, 0>(m);
    declare_initializer<double, 0>(m);
    declare_initializer<int32_t, 0>(m);
    declare_initializer<int64_t, 0>(m);
    declare_initializer<bool, 0>(m);
    
    declare_initializer<float, 1>(m);
    declare_initializer<double, 1>(m);
    declare_initializer<int32_t, 1>(m);
    declare_initializer<int64_t, 1>(m);
    declare_initializer<bool, 1>(m);
    
    declare_initializer<float, 2>(m);
    declare_initializer<double, 2>(m);
    declare_initializer<int32_t, 2>(m);
    declare_initializer<int64_t, 2>(m);
    declare_initializer<bool, 2>(m);
    
    declare_initializer<float, 3>(m);
    declare_initializer<double, 3>(m);
    declare_initializer<int32_t, 3>(m);
    declare_initializer<int64_t, 3>(m);
    declare_initializer<bool, 3>(m);
    
    declare_initializer<float, 4>(m);
    declare_initializer<double, 4>(m);
    declare_initializer<int32_t, 4>(m);
    declare_initializer<int64_t, 4>(m);
    declare_initializer<bool, 4>(m);
    
    declare_initializer<float, 5>(m);
    declare_initializer<double, 5>(m);
    declare_initializer<int32_t, 5>(m);
    declare_initializer<int64_t, 5>(m);
    declare_initializer<bool, 5>(m);

}
