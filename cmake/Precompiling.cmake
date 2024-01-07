include_guard(GLOBAL)

add_library(precompiled INTERFACE)

target_precompile_headers(precompiled INTERFACE
	<cstddef>
	<iostream>
	<memory>
	<stdexcept>
	<math.h>
	<string>
	<iomanip>
)
