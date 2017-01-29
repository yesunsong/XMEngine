//#include "stdafx.h"
#include "HNLayer.h"
#include "HNLayerColor.h"
#include "globel/ApplicationMacro.h"

namespace HN {
HNLayer::HNLayer(void) : _drawRect(false), _colorLayer(nullptr), _opacity(0) {
    setDrawRect(_drawRect || LAYER_ONOFF);
}

HNLayer::~HNLayer(void) {}

bool HNLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    if (false) {
        drawNode = DrawNode::create();
        addChild(drawNode, 10000);
    }

    this->setAnchorPoint(Vec2(0.5f, 0.5f));

    return true;
}

void HNLayer::onEnter() {
    Layer::onEnter();
    // if (Director::getInstance()->isDisplayStats()){
    // log("onEnter");
    // log("texture_info:\n %s \n%s", typeid(this).name(),
    // Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str());
    ////ofstream fout("texture_info.txt", ios::app);
    //    fout <<
    //    Director::getInstance()->getTextureCache()->getCachedTextureInfo().c_str()
    //    << "\n";
    ////fout.close();
    //}
}

void HNLayer::onExit() {
    Layer::onExit();
}

void HNLayer::onExitTransitionDidStart() {
    Layer::onExitTransitionDidStart();
    stopAllActions();
    unscheduleAllCallbacks();
}

void HNLayer::setBackGroundImage(const std::string &name) {
    // Vec2 win32= Director::getInstance()->getWinSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
    //背景
    auto loadingBG = Sprite::create(name.c_str());
    loadingBG->setPosition(
        Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2)); // visibleOrigin +
    float _xScale = visibleSize.width / loadingBG->getContentSize().width;
    float _yScale = visibleSize.height / loadingBG->getContentSize().height;
    loadingBG->setScaleX(_xScale);
    loadingBG->setScaleY(_yScale);
    this->addChild(loadingBG, -1);
}

float HNLayer::getRealScaleX(int designWidth) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    return visibleSize.width / designWidth;
}

float HNLayer::getRealScaleY(int designHeight) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    return visibleSize.height / designHeight;
}

void HNLayer::enableKeyboard() {
    //对手机返回键的监听
    auto listener = EventListenerKeyboard::create();
    //和回调函数绑定
    listener->onKeyReleased = CC_CALLBACK_2(HNLayer::onKeyReleased, this);
    //添加到事件分发器中
    Director::getInstance()
    ->getEventDispatcher()
    ->addEventListenerWithSceneGraphPriority(listener, this);
}

bool HNLayer::switchToLayoutControl(Layout *layout,
                                    const std::string &controlName,
                                    Node *newControl) {
    auto tmp = (Text *)Helper::seekWidgetByName(layout, controlName);
    if (nullptr == tmp)
        return false;
    newControl->setPosition(tmp->getPosition());
    newControl->setTag(tmp->getTag());
    newControl->setLocalZOrder(tmp->getLocalZOrder());
    newControl->setScaleX(tmp->getScaleX());
    newControl->setScaleY(tmp->getScaleY());
    newControl->setAnchorPoint(tmp->getAnchorPoint());
    layout->addChild(newControl);
    return true;
}

void HNLayer::startShade(int opacity) {
    _opacity = opacity;
    if (nullptr == _colorLayer) {
        _colorLayer = HNLayerColor::create();
        addChild(_colorLayer, 1);
        schedule(schedule_selector(HNLayer::updateOpacity), 0.1f);
    }
}

void HNLayer::quicklyShade(int opacity) {
    _opacity = opacity;
    if (nullptr == _colorLayer) {
        _colorLayer = HNLayerColor::create();
        addChild(_colorLayer, 1);
        _colorLayer->setOpacity(_opacity);
    }
}

void HNLayer::updateOpacity(float dt) {
    static unsigned char i = _opacity;
    i = i + 10;

    _colorLayer->setOpacity(i);
    if (i >= _opacity) {
        i = 0;
        unschedule(schedule_selector(HNLayer::updateOpacity));
    }
}

void HNLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) {
    if (_drawRect) {
        _customCommand.init(_globalZOrder + 1);
        _customCommand.func =
            CC_CALLBACK_0(HNLayer::onDrawPrimatives, this, transform, flags);
        renderer->addCommand(&_customCommand);
    }

    if (false) {
        drawNode->clear();
        GraphicsUtils::createDrawNode(this->isIgnoreAnchorPointForPosition(),
                                      this->getAnchorPoint(), this->getPosition(),
                                      this->getContentSize(), this, drawNode);
    }
}

void HNLayer::onDrawPrimatives(const cocos2d::Mat4 &transform, uint32_t flags) {
    GraphicsUtils::drawOutline(this->isIgnoreAnchorPointForPosition(),
                               this->getAnchorPoint(), this->getPosition(),
                               this->getContentSize(), this, transform);
}
}
