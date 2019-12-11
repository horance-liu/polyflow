#include "polyflow/core/runtime_factory.h"
#include "polyflow/tf/tf_runtime.h"
#include "polyflow/trt/trt_runtime.h"
#include "polyflow/ov/ov_runtime.h"

ModelRuntime* create_runtime(RuntimeType type) {
  switch (type) {
  case TENSORFLOW:
    return new TensorflowRuntime;
  case TENSORRT:
    return new TensorrtRuntime;
  case OPENVINO:
    return new OpenvinoRuntime;
  default:
    return nullptr;
  }
}
