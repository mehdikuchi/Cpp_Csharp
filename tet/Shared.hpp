#pragma once
template <class T>
class Shared {
    const T *data;
    unsigned refcount { 0 };

public:
    Shared(const T *d) {
        data = d;
        refcount++;
    }
    Shared(const Shared &O) {
        refcount = O.refcount;
        refcount++;
        data = O.data;
    }
    Shared &operator=(const Shared &O) {
        refcount = O.refcount;
        refcount++;
        data = O.data;
        return this;
    }
    T getdata() { return *data; }
    ~Shared() {
        refcount--;
        if (refcount == 0) {
            delete data;
        }
    }
};