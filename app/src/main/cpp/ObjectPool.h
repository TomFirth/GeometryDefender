#ifndef GEOMETRY_DEFENDER_OBJECT_POOL_H
#define GEOMETRY_DEFENDER_OBJECT_POOL_H

#include <vector>
#include <memory>
#include <functional>

template <typename T>
class ObjectPool {
public:
    explicit ObjectPool(size_t initialCapacity, std::function<T*()> factory)
        : factory_(factory) {
        pool_.reserve(initialCapacity);
        for (size_t i = 0; i < initialCapacity; ++i) {
            pool_.push_back(factory_());
        }
    }

    ~ObjectPool() {
        for (auto* ptr : pool_) {
            delete ptr;
        }
        pool_.clear();
    }

    T* acquire() {
        if (!pool_.empty()) {
            T* ptr = pool_.back();
            pool_.pop_back();
            return ptr;
        }
        return factory_();
    }

    void release(T* ptr) {
        if (ptr) {
            pool_.push_back(ptr);
        }
    }

private:
    std::vector<T*> pool_;
    std::function<T*()> factory_;
};

#endif // GEOMETRY_DEFENDER_OBJECT_POOL_H
