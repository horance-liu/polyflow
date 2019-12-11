#include "polyflow/core/model_state.h"
#include "polyflow/core/model_loader.h"
#include "cub/base/assertions.h"

inline cub::Status ModelState::ok(State to) {
  state = to;
  return cub::Success;
}

inline cub::Status ModelState::err(State to) {
  state = to;
  return cub::Failure;
}

inline cub::Status ModelState::transfer(State from, State to) {
  return state == from ? ok(to) : err(ERROR);
}

cub::Status ModelState::onLoad(ModelLoader& loader) {
  CUB_ASSERT_SUCC_CALL(transfer(NEW, LOADING));
  CUB_ASSERT_SUCC_CALL(loader.loadModel());
  CUB_ASSERT_SUCC_CALL(transfer(LOADING, READY));
  return cub::Success;
}

cub::Status ModelState::onUnload(ModelLoader& loader) {
  CUB_ASSERT_SUCC_CALL(transfer(READY, UNLOADING));
  CUB_ASSERT_SUCC_CALL(loader.unloadModel());
  CUB_ASSERT_SUCC_CALL(transfer(UNLOADING, DISABLED));
  return cub::Success;
}
