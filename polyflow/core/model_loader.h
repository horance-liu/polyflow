#ifndef H129DFBD2_6735_498D_86F1_158B37048175
#define H129DFBD2_6735_498D_86F1_158B37048175

struct ModelLoader {
  virtual void loadModel() = 0;
  virtual void unloadModel() = 0;
  virtual ~ModelLoader() {}
};

#endif
