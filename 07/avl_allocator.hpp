#pragma once

#include <memory>
#include <cmath>


namespace avl {

    template <class Key, class Value>
    struct Node;

    template <class Key, class Value>
    class AVLAllocator {

        private:
        using T = avl::Node<Key, Value>;
        using PtrT = T*;
        using LinkObject = std::pair<PtrT, std::size_t>;

        std::allocator<T> allocator_;
        std::vector<LinkObject> links_;

        public:
        PtrT allocate(std::size_t n) {
            return allocator_.allocate(n);
        }
        void deallocate(PtrT p, std::size_t n) {
            allocator_.deallocate(p, n);
        }

    };

}