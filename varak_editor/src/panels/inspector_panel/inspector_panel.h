#pragma once

#include "varak/ecs/entity.h"

#include <variant>

namespace Varak {

    class InspectorPanel
    {
    public:
        InspectorPanel() = default;

        void clearSelected() { m_selectedItem.clear(); }

        template <typename T>
        T& getSelected()
        {
            return m_selectedItem.get_value<T>();
        }

        template <typename T>
        bool matchesSelected(const T& item)
        {
            return m_selectedItem.is_type<Entity>() && getSelected<T>() == item;
        }

        template <typename T>
        void setSelected(T& item)
        {
            m_selectedItem = item;
        }

        void onImGuiRender();

    private:
        template <typename T>
        void inspectItem(T& item);

    private:
        rttr::variant m_selectedItem;
    };

} // namespace Varak
