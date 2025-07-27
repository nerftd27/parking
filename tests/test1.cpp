#include <gtest/gtest.h>
#include "include/impl.h"

TEST(BrakeParkingTest, BaseImplTest) {
  
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
