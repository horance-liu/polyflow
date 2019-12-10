#include "polyflow/core/model.h"

struct TensorflowModel {};
struct TensorrtModel {};
struct OpenvinoModel {};

cub::Status model_load(Model* model) {
  switch (model->type) {
  case TENSORFLOW: {
    if (model->state == NEW) {
      model->state = LOADING;
    } else {
      model->state = ERROR;
      return cub::Failure;
    }
    model->runtime.tf = new TensorflowModel;
    if (model->state == LOADING) {
      model->state = READY;
      return cub::Success;
    } else {
      model->state = ERROR;
      return cub::Failure;
    }
  }
  case TENSORRT: {
    if (model->state == NEW) {
      model->state = LOADING;
    } else {
      model->state = ERROR;
      return cub::Failure;
    }
    model->runtime.trt = new TensorrtModel;
    if (model->state == LOADING) {
      model->state = READY;
      return cub::Success;
    } else {
      model->state = ERROR;
      return cub::Failure;
    }
  }
  case OPENVINO: {
    if (model->state == NEW) {
      model->state = LOADING;
    } else {
      model->state = ERROR;
      return cub::Failure;
    }
    model->runtime.ov = new OpenvinoModel;
    if (model->state == LOADING) {
      model->state = READY;
      return cub::Success;
    } else {
      model->state = ERROR;
      return cub::Failure;
    }
  }
  default:
    return cub::Failure;
  }
}

cub::Status model_unload(Model* model) {
  switch (model->type) {
  case TENSORFLOW: {
    if (model->state == READY) {
      model->state = UNLOADING;
    } else {
      model->state = ERROR;
      return cub::Failure;
    }
    delete model->runtime.tf;
    if (model->state == UNLOADING) {
      model->state = DISABLED;
      return cub::Success;
    } else {
      model->state = ERROR;
      return cub::Failure;
    }
  }
  case TENSORRT: {
    if (model->state == READY) {
      model->state = UNLOADING;
    } else {
      model->state = ERROR;
      return cub::Failure;
    }
    delete model->runtime.trt;
    if (model->state == UNLOADING) {
      model->state = DISABLED;
      return cub::Success;
    } else {
      model->state = ERROR;
      return cub::Failure;
    }
  }
  case OPENVINO: {
    if (model->state == READY) {
      model->state = UNLOADING;
    } else {
      model->state = ERROR;
      return cub::Failure;
    }
    delete model->runtime.ov;
    if (model->state == UNLOADING) {
      model->state = DISABLED;
      return cub::Success;
    } else {
      model->state = ERROR;
      return cub::Failure;
    }
  }
  default:
    return cub::Failure;
  }
}
