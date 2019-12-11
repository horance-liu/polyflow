#ifndef HF9F842A4_C796_4725_8711_EA75EB36E484
#define HF9F842A4_C796_4725_8711_EA75EB36E484

#include "cub/base/status.h"

enum ModelType {
  TENSORFLOW, TENSORRT, OPENVINO,
};

struct TensorflowModel;
struct TensorrtModel;
struct OpenvinoModel;

struct Model {
  Model(ModelType type);

  cub::Status load();
  cub::Status unload();

private:
  enum State {
    NEW, LOADING, READY, UNLOADING, DISABLED, ERROR,
  };

  cub::Status transfer(State from, State to);

private:
  State state;
  ModelType type;
  union {
    TensorflowModel* tf;
    TensorrtModel* trt;
    OpenvinoModel* ov;
  } runtime;
};

#endif
