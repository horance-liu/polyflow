#include "polyflow/core/model.h"
#include "polyflow/core/model_runtime.h"
#include "cub/base/assertions.h"

struct TensorflowModel {};
struct TensorrtModel {};
struct OpenvinoModel {};

struct TensorflowRuntime : ModelRuntime {
private:
  void loadModel() override {
    tf = new TensorflowModel;
  }

  void unloadModel() override {
    delete tf;
  }

private:
  TensorflowModel* tf = nullptr;
};

struct TensorrtRuntime : ModelRuntime {
private:
  void loadModel() override {
    trt = new TensorrtModel;
  }

  void unloadModel() override {
    delete trt;
  }

private:
  TensorrtModel* trt = nullptr;
};

struct OpenvinoRuntime : ModelRuntime {
private:
  void loadModel() override {
    ov = new OpenvinoModel;
  }

  void unloadModel() override {
    delete ov;
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

template <typename Op>
cub::Status Model::op(Op op) {
  return runtime ? (op(*runtime), cub::Success) : cub::Failure;
}

cub::Status Model::loadModel() {
  return op([](ModelRuntime& runtime){
    return runtime.loadModel();
  });
}

cub::Status Model::unloadModel() {
  return op([](ModelRuntime& runtime){
    return runtime.unloadModel();
  });
}
