#define BOOST_TEST_MODULE testlibsee
#include "terminal_see.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_getMessage) {
  // given
  bool result{};

  // when
  result = run_terminal_see();

  // then
  BOOST_REQUIRE_EQUAL(result, true);
}
