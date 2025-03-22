#ifndef modern_CPP
#define modern_CPP
#include <vector>
#include <memory>
// #include <string.h>
namespace phx {
class SmartPointerContainer
{
    public:
    explicit SmartPointerContainer ()
    {
        
    };
    SmartPointerContainer (const std::vector<std::string>& strs)
    {
        for (const auto& s: strs) {
            m_container.push_back(std::make_unique<std::string>(s));
        }
    };
    SmartPointerContainer(const SmartPointerContainer& ) = delete;
    SmartPointerContainer(SmartPointerContainer&&) = delete;
    SmartPointerContainer& operator= (const SmartPointerContainer&) = delete;
    SmartPointerContainer& operator= (SmartPointerContainer&&) = delete;

    ~SmartPointerContainer()
    {

    }
    private:
    public:
    std::vector<std::unique_ptr<std::string>> m_container;

};
}
#endif



