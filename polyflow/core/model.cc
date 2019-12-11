#include "polyflow/core/model.h"
#include "polyflow/core/runtime_factory.h"

Model::Model(RuntimeType type) : runtime(create_runtime(type)) {
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
