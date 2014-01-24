#pragma once


#include <v8.h>
#include <scriptzeug/Backend/AbstractScriptEnvironment.h>


namespace scriptzeug
{


/** \brief JavaScript script environment
 */
class SCRIPTZEUG_API JSScriptEnvironment : public AbstractScriptEnvironment
{
public:
    JSScriptEnvironment();
    virtual ~JSScriptEnvironment();

    virtual void registerObject(const std::string & name, Scriptable * obj);
    virtual Value evaluate(const std::string & code);

protected:
    void registerObj(v8::Handle<v8::Object> parent, const std::string & name, Scriptable * obj);

protected:
    v8::Persistent<v8::Context>  m_context;
    v8::Isolate                 *m_isolate;
};


} // namespace zeug
