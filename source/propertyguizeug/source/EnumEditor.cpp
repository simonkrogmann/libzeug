#include <propertyguizeug/EnumEditor.h>

#include <QComboBox>

#include <reflectionzeug/EnumPropertyInterface.h>

using namespace reflectionzeug;

namespace 
{

QStringList toQStringList(const std::vector<std::string> & list)
{
    auto qlist = QStringList{};
    for (auto string : list)
        qlist << QString::fromStdString(string);
    return qlist;
}

} // namespace

namespace propertyguizeug
{
    
EnumEditor::EnumEditor(
    reflectionzeug::EnumPropertyInterface * property, 
    QWidget * parent)
:   PropertyEditor{parent}
,   m_property{property}
{
    auto strings = std::vector<std::string>{};
    if (property->hasChoices())
        strings = property->choicesStrings();
    else
        strings = property->strings();
    
    auto comboBox = new QComboBox{this};
    comboBox->addItems(toQStringList(strings));
    comboBox->setCurrentText(QString::fromStdString(m_property->toString()));
    
    addWidget(comboBox);
    setFocusProxy(comboBox);
    
    connect(comboBox, &QComboBox::currentTextChanged, 
            this, &EnumEditor::setString);
}
    
void EnumEditor::setString(const QString & text)
{
    m_property->fromString(text.toStdString());
}

} // namespace propertyguizeug
