#include "include/libtoh/toh_model.h"
#include "buildinfo.h"

const std::string_view getMessage() { return BuildInfo::Branch; }
