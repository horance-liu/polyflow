#ifndef H9721D5A2_FE82_4663_A909_76AF680EFB40
#define H9721D5A2_FE82_4663_A909_76AF680EFB40

#include "polyflow/core/model_loader.h"

struct TensorflowModel;

struct TensorflowModelLoader : ModelLoader {
private:
  void loadModel() override;
  void unloadModel() override;

private:
  TensorflowModel* tf = nullptr;
};

#endif
