#include "polyflow/core/model.h"
#include "cub/base/assertions.h"

struct TensorflowModel {};
struct TensorrtModel {};
struct OpenvinoModel {};

struct ModelRuntime {
  virtual cub::Status loadModel() = 0;
  virtual cub::Status unloadModel() = 0;
  virtual ~ModelRuntime() {}
};

struct TensorflowRuntime : ModelRuntime {
private:
  cub::Status loadModel() override {
    tf = new TensorflowModel;
    return cub::Success;
  }

  cub::Status unloadModel() override {
    delete tf;
    return cub::Success;
  }

private:
  TensorflowModel* tf = nullptr;
};

struct TensorrtRuntime : ModelRuntime {
private:
  cub::Status loadModel() override {
    trt = new TensorrtModel;
    return cub::Success;
  }

  cub::Status unloadModel() override {
    delete trt;
    return cub::Success;
  }

private:
  TensorrtModel* trt = nullptr;
};

struct OpenvinoRuntime : ModelRuntime {
private:
  cub::Status loadModel() override {
    ov = new OpenvinoModel;
    return cub::Success;
  }

  cub::Status unloadModel() override {
    delete ov;
    return cub::Success;
  }

private:
  OpenvinoModel* ov = nullptr;
};

ModelRuntime* Model::create(Type type) {
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

Model::Model(Type type) : runtime(create(type)) {
}

Model::~Model() {
  delete runtime;
}

cub::Status Model::load() {
  return state.onLoad(*this);
}

cub::Status Model::unload() {
  return state.onUnload(*this);
}

cub::Status Model::loadModel() {
  return runtime->loadModel();
}

cub::Status Model::unloadModel() {
  return runtime->unloadModel();
}
