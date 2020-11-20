#pragma once

// for client to include everything

// -- core --
#include "varak/core/application.h"
#include "varak/core/base.h"
#include "varak/core/input.h"
#include "varak/core/key_codes.h"
#include "varak/core/layer.h"
#include "varak/core/log.h"
#include "varak/core/mouse_codes.h"

// -- debug --
#include "varak/debug/instrumentor.h"

// -- imgui --
#include "varak/imgui/imgui_layer.h"

// -- rendering --
#include "varak/renderer/renderer.h"
#include "varak/renderer/renderer2d.h"

#include "varak/renderer/buffer.h"
#include "varak/renderer/framebuffer.h"
#include "varak/renderer/shader.h"
#include "varak/renderer/texture.h"
#include "varak/renderer/vertex_array.h"

#include "varak/renderer/orthographic_camera_controller.h"
