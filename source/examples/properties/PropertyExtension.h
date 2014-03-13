
#pragma once

#include <reflectionzeug/Property.h>
#include <reflectionzeug/EnumProperty.h>

enum class NormalMode : char { Vertex, LookAt, Custom };

namespace reflectionzeug
{

template <>
class Property<NormalMode> : public EnumProperty<NormalMode>
{
public:
    template <typename... Args>
    Property(const std::string & name, Args&&... args) :
        ValuePropertyInterface(name),
        EnumProperty<NormalMode>(name, std::forward<Args>(args)...) {}
    
protected:
    virtual std::vector<std::pair<NormalMode, std::string>> pairs() const
    {
        return {
            { NormalMode::Vertex, "Vertex" },
            { NormalMode::LookAt, "LookAt" },
            { NormalMode::Custom, "Custom" }
        };
    }

};

} // namespace reflectionzeug