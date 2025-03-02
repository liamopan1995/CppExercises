#ifndef BASE
#define BASE

namespace phx {

class Base {
public:
    Base() = default;
    ~Base() = default;
    virtual void DoJob () = 0;
};
}
#endif



