#pragma once

#include "CProperty.h"

#include "WallpaperEngine/Core/Core.h"

namespace WallpaperEngine::Core::Projects
{
    using json = nlohmann::json;

    class CPropertySlider : public CProperty
    {
    public:
        static CPropertySlider* fromJSON (json data, const std::string& name);

        const double& getValue () const;
        const double& getMinValue () const;
        const double& getMaxValue () const;
        const double& getStep () const;
        std::string dump () const override;
        void update (const std::string& value) override;

        static const std::string Type;

    private:
        CPropertySlider (double value, const std::string& name, const std::string& text, double min, double max, double step);

        double m_value;
        double m_min;
        double m_max;
        double m_step;
    };
};
