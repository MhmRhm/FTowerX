#define BOOST_TEST_MODULE testlibtoh
#include "terminal_toh.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_getMessage) {
  // given
  bool result{};

  // when
  result = run_terminal_toh();

  // then
  BOOST_REQUIRE_EQUAL(result, true);
}
