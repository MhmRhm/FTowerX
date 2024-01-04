include(FetchContent)
set(BOOST_INCLUDE_LIBRARIES lockfree)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
	Boost
	GIT_REPOSITORY https://github.com/boostorg/boost.git
	GIT_TAG boost-1.84.0
	GIT_SHALLOW 1
)
FetchContent_MakeAvailable(Boost)
