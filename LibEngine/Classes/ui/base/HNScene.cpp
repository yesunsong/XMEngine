//#include "stdafx.h"
#include "HNScene.h"
#include "ui/extensions/TextureLayer.h"
#include "test/HNLog.h"

namespace HN {

HNScene::HNScene(void) : isMoved(false), downCount(0), upCount(0) {}

HNScene::~HNScene(void) {}

HNScene *HNScene::create() {
    HNScene *scene = new HNScene();
    if (scene && scene->init()) {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

void HNScene::onEnter() {
    Scene::onEnter();
}

void HNScene::onEnterTransitionDidFinish() {
    Scene::onEnterTransitionDidFinish();
    schedule(schedule_selector(HNScene::releaseLastScene), 1.0f);
}

void HNScene::onExit() {
    Scene::onExit();
}

void HNScene::onExitTransitionDidStart() {
    Scene::onExitTransitionDidStart();
    stopAllActions();
    unscheduleAllCallbacks();
    AnimationCache::getInstance()->destroyInstance();
    SpriteFrameCache::getInstance()->removeSpriteFrames();
    Director::getInstance()->getTextureCache()->removeAllTextures();
    this->unschedule(schedule_selector(HNScene::releaseLastScene));
}

void HNScene::releaseLastScene(float dt) {
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    HNLog::logInfo("release last scene");
}

bool HNScene::init() {
    if (!Scene::init()) {
        return false;
    }

    if (TEXTURE_ONOFF) {
        EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = CC_CALLBACK_2(HNScene::onTouchBegan, this);
        listener->onTouchEnded = CC_CALLBACK_2(HNScene::onTouchEnded, this);
        listener->onTouchMoved = CC_CALLBACK_2(HNScene::onTouchMoved, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }
    return true;
}

bool HNScene::onTouchBegan(Touch *touch, Event *unused_event) {
    return true;
}

void HNScene::onTouchMoved(Touch *touch, Event *unused_event) {
    isMoved = true;
}

void HNScene::onTouchEnded(Touch *touch, Event *unused_event) {
    if (!isMoved) {
        int height = Director::getInstance()->getWinSize().height;
        Vec2 endPosition = touch->getLocation();
        if (endPosition.y < height / 3) { //下区域
            downCount++;
        } else if (endPosition.y > height * 2 / 3 &&
                   endPosition.y < height) { //上区域
            upCount++;
        }

        if (downCount >= 2 && upCount >= 2) {
            addChild(TextureLayer::create());
            downCount = 0;
            upCount = 0;
        }
    }
    isMoved = false;
}
}
