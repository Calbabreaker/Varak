#pragma once

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

// -- data structures --
#include <array>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- Varak engine --
#include "varak/core/base.h"
#include "varak/core/log.h"
#include "varak/debug/instrumentor.h"

#ifdef VR_PLATFORM_WINDOWS
    #include <Windows.h>
#endif
