#ifndef NDARRAY_H
#define NDARRAY_H

#include <array>
#include <type_traits>
#include <memory>

template<typename T, size_t D>
class ndarray {
public:

    ndarray(T* data_, std::array<size_t, D> sz_) : data(data_), sz(sz_) {}
    
    size_t shape(size_t dim) const { return sz[dim]; }
    size_t ndim() const { return D; }
    size_t size() const { 
        size_t count = 1;
	for (size_t i = 0; i < ndim(); i++) {
            count *= shape(i);
	}
	return count;
    }
    
    template<size_t Rank = D>
    inline std::enable_if_t<Rank == 0, const T&>
    operator()() const { return data[0]; }
    
    template<size_t Rank = D>
    inline std::enable_if_t<Rank == 0, T&>
    operator()() { return data[0]; }
    
    template<size_t Rank = D>
    inline std::enable_if_t<Rank == 1, const T&>
    operator()(size_t i) const { return data[i]; }
    
    template<size_t Rank = D>
    inline std::enable_if_t<Rank == 1, T&>
    operator()(size_t i) { return data[i]; }
    
    template<size_t Rank = D>
    inline std::enable_if_t<Rank == 2, const T&>
    operator()(size_t i, size_t j) const { return data[sz[1]*i + j]; }
    
    template<size_t Rank = D>
    inline std::enable_if_t<Rank == 2, T&>
    operator()(size_t i, size_t j) { return data[sz[1]*i + j]; }
    
    template<size_t Rank = D>
    inline std::enable_if_t<Rank == 3, const T&>
    operator()(size_t i, size_t j, size_t k) const { 
        return data[sz[1]*sz[2]*i + sz[2]*j + k]; 
    }

    template<size_t Rank = D>
    inline std::enable_if_t<Rank == 3, T&>
    operator()(size_t i, size_t j, size_t k) { 
        return data[sz[1]*sz[2]*i + sz[2]*j + k]; 
    }
    
    template<size_t Rank = D>
    inline std::enable_if_t<Rank == 4, const T&>
    operator()(size_t i, size_t j, size_t k, size_t l) const { 
        return data[sz[1]*sz[2]*sz[3]*i + sz[2]*sz[3]*j + sz[3]*k + l]; 
    }
      
    template<size_t Rank = D>
    inline std::enable_if_t<Rank == 4, T&>
    operator()(size_t i, size_t j, size_t k, size_t l) { 
        return data[sz[1]*sz[2]*sz[3]*i + sz[2]*sz[3]*j + sz[3]*k + l]; 
    }
    
    template<size_t Rank = D>
    inline std::enable_if_t<Rank == 5, const T&>
    operator()(size_t i, size_t j, size_t k, size_t l, size_t m) const { 
        return data[sz[1]*sz[2]*sz[3]*sz[4]*i + 
                    sz[2]*sz[3]*sz[4]*j + 
		    sz[3]*sz[4]*k + 
		    sz[4]*l + 
		    m]; 
    }
    
    template<size_t Rank = D>
    inline std::enable_if_t<Rank == 5, T&>
    operator()(size_t i, size_t j, size_t k, size_t l, size_t m) { 
        return data[sz[1]*sz[2]*sz[3]*sz[4]*i + 
                    sz[2]*sz[3]*sz[4]*j + 
		    sz[3]*sz[4]*k + 
		    sz[4]*l + 
		    m]; 
    }

private:
    T* data;
    std::array<size_t, D> sz;

};

#endif
