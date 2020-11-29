#pragma once

#include "varak/scene/entity.h"

#include <variant>

namespace Varak {

    class Inspectable
    {
    public:
        Inspectable() = default;
        Inspectable(Entity entity) { m_variant = entity; }

        template <typename InspectableType>
        operator InspectableType() const
        {
            if (auto inspectable = std::get_if<InspectableType>(&m_variant))
                return *inspectable;
            else
                return InspectableType();
        }

        template <typename InspectableType>
        bool operator==(const InspectableType& other) const 
        {
            return static_cast<InspectableType>(*this) == other;
        }

    private:
        std::variant<Entity> m_variant;
    };

    class InspectorPanel
    {
    public:
        InspectorPanel() = default;

        void setSelected(const Inspectable& inspectable) { m_selectedInspectable = inspectable; }
        const Inspectable& getSelected() { return m_selectedInspectable; }

        void onImGuiRender();

    private:
        void drawProperties(Entity entity);

    private:
        Inspectable m_selectedInspectable;
    };

} // namespace Varak
