#include "polyflow/core/model.h"
#include "cub/base/assertions.h"

struct TensorflowModel {};
struct TensorrtModel {};
struct OpenvinoModel {};

namespace {
inline cub::Status model_transfer(Model* model, ModelState from, ModelState to) {
  if (model->state == from) {
    model->state = to;
    return cub::Success;
  } else {
    model->state = ERROR;
    return cub::Failure;
  }
}
} // namespace

cub::Status model_load(Model* model) {
  switch (model->type) {
  case TENSORFLOW: {
    CUB_ASSERT_SUCC_CALL(model_transfer(model, NEW, LOADING));
    model->runtime.tf = new TensorflowModel;
    CUB_ASSERT_SUCC_CALL(model_transfer(model, LOADING, READY));
    return cub::Success;
  }
  case TENSORRT: {
    CUB_ASSERT_SUCC_CALL(model_transfer(model, NEW, LOADING));
    model->runtime.trt = new TensorrtModel;
    CUB_ASSERT_SUCC_CALL(model_transfer(model, LOADING, READY));
    return cub::Success;
  }
  case OPENVINO: {
    CUB_ASSERT_SUCC_CALL(model_transfer(model, NEW, LOADING));
    model->runtime.ov = new OpenvinoModel;
    CUB_ASSERT_SUCC_CALL(model_transfer(model, LOADING, READY));
    return cub::Success;
  }
  default:
    return cub::Failure;
  }
}

cub::Status model_unload(Model* model) {
  switch (model->type) {
  case TENSORFLOW: {
    CUB_ASSERT_SUCC_CALL(model_transfer(model, READY, UNLOADING));
    delete model->runtime.tf;
    CUB_ASSERT_SUCC_CALL(model_transfer(model, UNLOADING, DISABLED));
    return cub::Success;
  }
  case TENSORRT: {
    CUB_ASSERT_SUCC_CALL(model_transfer(model, READY, UNLOADING));
    delete model->runtime.trt;
    CUB_ASSERT_SUCC_CALL(model_transfer(model, UNLOADING, DISABLED));
    return cub::Success;
  }
  case OPENVINO: {
    CUB_ASSERT_SUCC_CALL(model_transfer(model, READY, UNLOADING));
    delete model->runtime.ov;
    CUB_ASSERT_SUCC_CALL(model_transfer(model, UNLOADING, DISABLED));
    return cub::Success;
  }
  default:
    return cub::Failure;
  }
}
