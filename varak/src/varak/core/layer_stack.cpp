#include "layer_stack.h"

namespace Varak
{

    LayerStack::LayerStack()
    {
        m_layersInsert = m_layers.begin(); //
    }

    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_layers)
            delete layer;
    }

    void LayerStack::pushLayer(Layer* overlay)
    {
        m_layersInsert = m_layers.emplace(m_layersInsert, overlay);
    }

    void LayerStack::pushOverlay(Layer* layer)
    {
        m_layers.emplace_back(layer); //
    }

    void LayerStack::popLayer(Layer* layer)
    {
        auto it = std::find(m_layers.begin(), m_layers.end(), layer);
        if (it != m_layers.end())
        {
            m_layers.erase(it);
            m_layersInsert--;
        }
    }

    void LayerStack::popOverlay(Layer* overlay)
    {
        auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
        if (it != m_layers.end())
            m_layers.erase(it);
    }

} // namespace Varak