#include "vrpch.h"

#include "varak/core/layer_stack.h"

namespace Varak {

    void LayerStack::pushLayer(Layer* layer)
    {
        m_layers.emplace(m_layers.begin() + m_layersInsertIndex, layer);
        m_layersInsertIndex++;
    }

    void LayerStack::pushOverlay(Layer* overlay)
    {
        m_layers.emplace_back(overlay); //
    }

    bool LayerStack::popLayer(Layer* layer)
    {
        auto it = std::find(m_layers.begin(), m_layers.begin() + m_layersInsertIndex, layer);
        if (it != m_layers.begin() + m_layersInsertIndex)
        {
            m_layers.erase(it);
            m_layersInsertIndex--;
            return true;
        } else
        {
            return false;
        }
    }

    bool LayerStack::popOverlay(Layer* overlay)
    {
        auto it = std::find(m_layers.begin() + m_layersInsertIndex, m_layers.end(), overlay);
        if (it != m_layers.end())
        {
            m_layers.erase(it);
            return true;
        } else
        {
            return false;
        }
    }

} // namespace Varak
