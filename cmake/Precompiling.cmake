include_guard(GLOBAL)

add_library(precompiled INTERFACE)

target_precompile_headers(precompiled INTERFACE
	<iostream>
	<string>
	<memory>	
	<cstddef>
	<stdexcept>
)
