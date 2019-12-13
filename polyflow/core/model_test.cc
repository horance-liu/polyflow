#include "polyflow/core/model.h"
#include "cctest/cctest.h"

FIXTURE(ModelTest) {
  TEST("load/unload tensorflow model") {
    Model model = TENSORFLOW;
    ASSERT_EQ(cub::Success, model.load());
    ASSERT_EQ(cub::Success, model.unload());
  }

  TEST("load/unload tensorrt model") {
    Model model = TENSORRT;
    ASSERT_EQ(cub::Success, model.load());
    ASSERT_EQ(cub::Success, model.unload());
  }

  TEST("load/unload openvino model") {
    Model model = OPENVINO;
    ASSERT_EQ(cub::Success, model.load());
    ASSERT_EQ(cub::Success, model.unload());
  }
};
