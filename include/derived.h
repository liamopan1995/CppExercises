#ifndef DERIVED
#define DERIVED
#include "base.h"

namespace phx {

class Derived : public Base {
public:
    Derived() = default;
    ~Derived() = default;
    void DoJob () override;
    int m_id;
};
}
#endif



