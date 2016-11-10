//
//  Effect.h
//  LibHNUI
//
//  Created by Sunsong Ye on 16/9/2.
//  Copyright © 2016年 redbird. All rights reserved.
//

#ifndef Effect_hpp
#define Effect_hpp

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
// spine所需要的文件
#include "spine/spine.h"
#include <spine/spine-cocos2dx.h>
using namespace spine;

USING_NS_CC;

namespace HN {

#define CSB_EFFECT 0
#define SPINE_EFFECT 1
#define PARTICLE_EFFECT 2

class Effect : public Node {
public:
  static Effect *createWithCSB(const char *filename);
  static Effect *createWithSpine(const std::string &skeletonDataFile,
                                 const std::string &atlasFile, float scale = 1);
  static Effect *createWithParticle(const char *filename);
  bool initWithCSB(const char *filename);
  bool initWithSpine(const std::string &skeletonDataFile,
                     const std::string &atlasFile, float scale = 1);
  bool initWithParticle(const char *filename);

private:
  int type;
  SkeletonAnimation *skeletonNode;
  ParticleSystemQuad *particle;
  Node *loader;
  const char *csb_name;

public:
  void play(const char *action, bool loop);
};
}

#endif /* Effect_hpp */
