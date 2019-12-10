#include "polyflow/core/model.h"
#include "cctest/cctest.h"

FIXTURE(ModelTest) {
  Model model;

  SETUP {
    model.type = TENSORFLOW;
    model.state = NEW;
  }

  TEST("load/unload tensorflow model") {
    ASSERT_EQ(cub::Success, model_load(&model));
    ASSERT_EQ(cub::Success, model_unload(&model));
  }
};
