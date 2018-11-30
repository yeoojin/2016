#include <iostream>
#include <stdio.h>
#include <list>
#include <iterator>
#include <limits>

template<typename T>
class Allocator {
public:
    //    typedefs
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

public:
    //    convert an allocator<T> to allocator<U>
    template<typename U>
    struct rebind {
        typedef Allocator<U> other;
    };

public:
    inline explicit Allocator()
    {
    }
    inline ~Allocator() {}
    inline explicit Allocator(Allocator const&)
    {
    }
    template<typename U>
    inline explicit Allocator(Allocator<U> const&)
    {
    }

    //    address
    inline pointer address(reference r) { return &r; }
    inline const_pointer address(const_reference r) { return &r; }

    //    memory allocation
    inline pointer allocate(size_type cnt,
        typename std::allocator<void>::const_pointer = 0) {
        return reinterpret_cast<pointer>(::operator new(cnt * sizeof (T)));
    }
    inline void deallocate(pointer p, size_type) {
        ::operator delete(p);
    }

    inline size_type max_size() const {
        //return std::numeric_limits<size_type>::max() / sizeof(T);
        return INT_MAX / sizeof(T);
    }

    //    construction/destruction
    inline void construct(pointer p, const T& t) { new(p)T(t); }
    inline void destroy(pointer p) { p->~T(); }

    inline bool operator==(Allocator const&) 
    {
        return true; 
    }
    inline bool operator!=(Allocator const& a)
    { 
        return !operator==(a); 
    }
};

void main()
{
    std::ostream_iterator<int> out( std::cout, "," );

    std::list<int, Allocator<int>> list1={ 1, 3, 5, 7, 9 };
    std::copy( list1.begin(), list1.end(), out );
    std::cout << std::endl;

    std::list<int,Allocator<int>> list2 = { 10, 30, 50, 70, 90 };
 
    auto it = list1.begin();
    std::advance(it, 2);
 
    list1.splice(it, list2);
    std::copy( list1.begin(), list1.end(), out );
    std::cout << std::endl;
    std::copy( list2.begin(), list2.end(), out );
    std::cout << std::endl;
}