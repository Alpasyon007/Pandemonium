#ifndef PPCH_H
#define PPCH_H

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

#include <array>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <PandemoniumLog.h>

#include "Platform.h"

#include "Instrumentor.h"

#if defined(PANDEMONIUM_PLATFORM_WINDOWS)
	#include <Windows.h>
#endif

#endif /* PPCH_H */