
#include <reflectionzeug/property/PropertyString.h>

#include <reflectionzeug/property/AbstractVisitor.h>


namespace reflectionzeug
{


PropertyString::~PropertyString()
{
}

std::string PropertyString::toString() const
{
    return this->value();
}

bool PropertyString::fromString(const std::string & string)
{
    this->setValue(string);
    return true;
}

void PropertyString::accept(AbstractVisitor * visitor)
{
    visitor->callVisitor<PropertyString>(this);
    visitor->callVisitor<AbstractStringInterface>(this);
}


} // namespace reflectionzeug
