#include <sstream>

#include "CPropertyCombo.h"

#include <utility>
#include "WallpaperEngine/Core/Core.h"

using namespace WallpaperEngine::Core::Projects;

CPropertyCombo* CPropertyCombo::fromJSON (json data, const std::string& name)
{
    auto value = data.find ("value");
    std::string text = jsonFindDefault <std::string> (data, "text", "");
    auto options = jsonFindRequired (data, "options", "Options for a property combo is required");

    CPropertyCombo* combo = new CPropertyCombo (
        name,
        text,
        *value
    );

    if (options->is_array () == false)
        throw std::runtime_error ("Property combo options should be an array");

    auto cur = (*options).begin ();
    auto end = (*options).end ();

    for (; cur != end; cur ++)
    {
        if ((*cur).is_object () == false)
        {
            // TODO: PROPERLY REPORT THESE ISSUES
            continue;
        }

        // check for label and value to ensure they're there
        auto label = jsonFindRequired (*cur, "label", "Label is required for a property combo option");
        auto value = jsonFindRequired (*cur, "value", "Value is required for a property combo option");

        combo->addValue (*label, *value);
    }

    return combo;
}

CPropertyCombo::CPropertyCombo (const std::string& name, const std::string& text, std::string  defaultValue) :
    CProperty (name, Type, text),
    m_defaultValue (std::move(defaultValue))
{
}

const std::string& CPropertyCombo::getValue () const
{
    return this->m_defaultValue;
}

std::string CPropertyCombo::dump () const
{
    std::stringstream ss;

    ss
        << this->m_name << " - combolist" << std::endl
        << "\t" << "Description: " << this->m_text << std::endl
        << "\t" << "Value: " << this->m_defaultValue << std::endl
        << "\t\t" << "Posible values:" << std::endl;

    for (auto cur : this->m_values)
    {
        ss << "\t\t" << cur->label << " -> " << cur->value << std::endl;
    }

    return ss.str();
}

void CPropertyCombo::addValue (std::string label, std::string value)
{
    CPropertyComboValue* prop = new CPropertyComboValue;

    prop->label = std::move (label);
    prop->value = std::move (value);

    this->m_values.push_back (prop);
}

const std::string CPropertyCombo::Type = "combo";