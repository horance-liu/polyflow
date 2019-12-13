#ifndef H9721D5A2_FE82_4663_DEVH_76AF680EFADR
#define H9721D5A2_FE82_4663_DEVH_76AF680EFADR

#include "polyflow/core/model_loader.h"

struct OpenvinoModel;

struct OpenvinoModelLoader : ModelLoader {
private:
  void loadModel() override;
  void unloadModel() override;

private:
  OpenvinoModel* ov = nullptr;
};

#endif
