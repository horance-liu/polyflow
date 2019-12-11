#include "polyflow/core/model.h"
#include "cctest/cctest.h"

FIXTURE(ModelTest) {
  Model model {TENSORFLOW};

  TEST("load/unload tensorflow model") {
    ASSERT_EQ(cub::Success, model.load());
    ASSERT_EQ(cub::Success, model.unload());
  }
};
