
#pragma once


#include <reflectionzeug/property/AbstractTypedProperty.h>
#include <reflectionzeug/property/AbstractBooleanInterface.h>


namespace reflectionzeug
{


/**
*  @brief
*    Property implementation for type bool
*/
class REFLECTIONZEUG_API PropertyBool : public AbstractTypedProperty<bool>, public AbstractBooleanInterface
{
public:
    /**
    *  @brief
    *    Constructor
    */
    template <typename... Args>
    PropertyBool(Args&&... args);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~PropertyBool();

    /**
    *  @brief
    *    Toggle boolean value
    */
    void toggleValue();

    // Virtual AbstractBooleanInterface interface
    virtual bool toBool() const override;
    virtual bool fromBool(bool value) override;

    // Virtual AbstractProperty interface
    virtual std::string toString() const override;
    virtual bool fromString(const std::string & string) override;
    virtual void accept(AbstractVisitor * visitor) override;
};


} // namespace reflectionzeug


#include <reflectionzeug/property/PropertyBool.hpp>
