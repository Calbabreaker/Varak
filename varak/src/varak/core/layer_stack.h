#pragma once

#include "varak/core/layer.h"

#include <vector>

namespace Varak {

    class LayerStack
    {
    public:
        LayerStack() = default;

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);
        bool popLayer(Layer* layer);
        bool popOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_layers.end(); }
        std::vector<Layer*>::reverse_iterator rbegin() { return m_layers.rbegin(); }
        std::vector<Layer*>::reverse_iterator rend() { return m_layers.rend(); }

        std::vector<Layer*>::const_iterator begin() const { return m_layers.begin(); }
        std::vector<Layer*>::const_iterator end() const { return m_layers.end(); }
        std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_layers.rbegin(); }
        std::vector<Layer*>::const_reverse_iterator rend() const { return m_layers.rend(); }

    private:
        std::vector<Layer*> m_layers;
        uint32_t m_layersInsertIndex = 0;
    };

} // namespace Varak
