#include "include/libsee/see_model.h"
#include "buildinfo.h"

const std::string_view getMessage() { return BuildInfo::Branch; }
