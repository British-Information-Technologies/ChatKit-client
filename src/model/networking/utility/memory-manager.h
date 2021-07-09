#include <openssl/crypto.h>

#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>

namespace networking_utility {

template <typename T>
struct zallocator {
 public:
  typedef T value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  pointer address(reference v) const { return &v; }
  const_pointer address(const_reference v) const { return &v; }

  pointer allocate(size_type n, const void *hint = 0) {
    if (n > std::numeric_limits<size_type>::max() / sizeof(T))
      throw std::bad_alloc();
    return static_cast<pointer>(::operator new(n * sizeof(value_type)));
  }

  void deallocate(pointer p, size_type n) {
    OPENSSL_cleanse(p, n * sizeof(T));
    ::operator delete(p);
  }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(T);
  }

  template <typename U>
  struct rebind {
    typedef zallocator<U> other;
  };

  template <typename U, typename... Args>
  void construct(U *ptr, Args &&...args) {
    ::new (static_cast<void *>(ptr)) U(std::forward<Args>(args)...);
  }

  template <typename U>
  void destroy(U *ptr) {
    ptr->~U();
  }
};

typedef unsigned char byte;
typedef std::basic_string<char, std::char_traits<char>, zallocator<char> >
    secure_string;

}  // namespace networking_utility