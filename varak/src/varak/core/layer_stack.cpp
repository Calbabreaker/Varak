#include "varak/core/layer_stack.h"

namespace Varak {

    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_layers)
        {
            layer->onDetach();
            delete layer;
        }
    }

    void LayerStack::pushLayer(Layer* layer)
    {
        m_layers.emplace(m_layers.begin() + m_layersInsertIndex, layer);
        m_layersInsertIndex++;
    }

    void LayerStack::pushOverlay(Layer* overlay)
    {
        m_layers.emplace_back(overlay); //
    }

    void LayerStack::popLayer(Layer* layer)
    {
        auto it = std::find(m_layers.begin(),
                            m_layers.begin() + m_layersInsertIndex, layer);
        if (it != m_layers.begin() + m_layersInsertIndex)
        {
            layer->onDetach();
            m_layers.erase(it);
            m_layersInsertIndex--;
        }
    }

    void LayerStack::popOverlay(Layer* overlay)
    {
        auto it = std::find(m_layers.begin() + m_layersInsertIndex,
                            m_layers.end(), overlay);
        if (it != m_layers.end())
        {
            overlay->onDetach();
            m_layers.erase(it);
        }
    }

} // namespace Varak