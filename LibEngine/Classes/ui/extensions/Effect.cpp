//
//  Effect.cpp
//  LibHNUI
//
//  Created by Sunsong Ye on 16/9/2.
//  Copyright © 2016年 redbird. All rights reserved.
//
//#include "stdafx.h"
#include "Effect.h"

namespace HN {

Effect *Effect::createWithCSB(const char *filename) {
    Effect *pRet = new Effect();
    if (pRet && pRet->initWithCSB(filename)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

Effect *Effect::createWithSpine(const std::string &skeletonDataFile,
                                const std::string &atlasFile, float scale) {
    Effect *pRet = new Effect();
    if (pRet && pRet->initWithSpine(skeletonDataFile, atlasFile, scale)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

Effect *Effect::createWithParticle(const char *filename) {
    Effect *pRet = new Effect();
    if (pRet && pRet->initWithParticle(filename)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool Effect::initWithCSB(const char *filename) {
    if (!Node::init()) {
        return false;
    }
    //  this->ignoreAnchorPointForPosition(true);
    csb_name = filename;
    type = CSB_EFFECT;
    loader = CSLoader::createNode(filename);
    addChild(loader);
    return true;
}

bool Effect::initWithSpine(const std::string &skeletonDataFile,
                           const std::string &atlasFile, float scale) {
    if (!Node::init()) {
        return false;
    }
    //  this->ignoreAnchorPointForPosition(true);
    type = SPINE_EFFECT;
    skeletonNode =
        SkeletonAnimation::createWithFile(skeletonDataFile, atlasFile, scale);
    skeletonNode->setIgnoreAnchorPointForPosition(true);
    //  skeletonNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(skeletonNode);
    return true;
}

bool Effect::initWithParticle(const char *filename) {
    if (!Node::init()) {
        return false;
    }
    this->setIgnoreAnchorPointForPosition(true);
    type = PARTICLE_EFFECT;
    particle = ParticleSystemQuad::create(filename);
    addChild(particle);
    return true;
}

void Effect::play(const char *action, bool loop) {
    if (type == CSB_EFFECT) {
        auto antAction = CSLoader::createTimeline(csb_name);
        loader->runAction(antAction);
        antAction->play(action, loop);
    } else if (type == SPINE_EFFECT) {
        skeletonNode->setAnimation(0, action, loop);
    } else if (type == PARTICLE_EFFECT) {
    }
}
}
