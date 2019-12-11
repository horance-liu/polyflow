#include "polyflow/core/model_state.h"
#include "polyflow/core/model_loader.h"
#include "cub/base/assertions.h"

inline cub::Status ModelState::transfer(State from, State to) {
  if (state == from) {
    state = to;
    return cub::Success;
  } else {
    state = ERROR;
    return cub::Failure;
  }
}

cub::Status ModelState::onLoad(ModelLoader& loader) {
  CUB_ASSERT_SUCC_CALL(transfer(NEW, LOADING));
  loader.loadModel();
  CUB_ASSERT_SUCC_CALL(transfer(LOADING, READY));
  return cub::Success;
}

cub::Status ModelState::onUnload(ModelLoader& loader) {
  CUB_ASSERT_SUCC_CALL(transfer(READY, UNLOADING));
  loader.unloadModel();
  CUB_ASSERT_SUCC_CALL(transfer(UNLOADING, DISABLED));
  return cub::Success;
}
