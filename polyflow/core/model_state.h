#ifndef H486F7A56_990D_441D_848F_4149763FF802
#define H486F7A56_990D_441D_848F_4149763FF802

#include "cub/base/status.h"

struct ModelLoader;

struct ModelState {
  cub::Status onLoad(ModelLoader&);
  cub::Status onUnload(ModelLoader&);

private:
  enum State {
    NEW, LOADING, READY, UNLOADING, DISABLED, ERROR,
  } state = NEW;

  cub::Status transfer(State from, State to);
};

#endif
