#include "../include/derived.h"
#include <iostream>
#include "string"

namespace phx {

void Derived::DoJob ()
{
    std::cout << "this is what derived no: " << m_id << " do " << std::endl;
}
};


