#ifndef modern_CPP
#define modern_CPP
#include <vector>
#include <memory>
// #include <string.h>
namespace phx {
class SmartPointerContainer
{
    explicit SmartPointerContainer () 
    {

    };
    ~SmartPointerContainer()
    {
        
    }
    private:
    std::vector<std::unique_ptr<std::string>> m_container;
    public:

};
}
#endif



