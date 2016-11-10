#ifndef __HN_HNLayer_H__
#define __HN_HNLayer_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <fstream>

#include "render/GraphicsUtils.h"
#include "test/WireframeOnOff.h"

USING_NS_CC;
using namespace ui;
using namespace std;
using namespace HN;

#define WIN_SIZE Director::getInstance()->getWinSize()
#define Visible_Size Director::getInstance()->getVisibleSize()
#define Visible_Origin Director::getInstance()->getVisibleOrigin()

namespace HN {

class HNLayer : public Layer {
public:
    HNLayer(void);
    virtual ~HNLayer(void);

    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void draw(Renderer *renderer, const Mat4 &transform,
                      uint32_t flags) override;
    // virtual void visit(Renderer *renderer, const Mat4& parentTransform,
    // uint32_t parentFlags);

public:
    void setBackGroundImage(const std::string &name);
    void enableKeyboard();
    void startShade(int opacity = 100);
    void quicklyShade(int opacity = 100);
    float getRealScaleX(int designWidth);
    float getRealScaleY(int designHeight);
    bool switchToLayoutControl(Layout *layout, const std::string &controlName,
                               Node *newControl);

    CC_SYNTHESIZE(bool, _drawRect, DrawRect);

private:
    void updateOpacity(float dt);

private:
    Layer *_colorLayer;
    unsigned char _opacity;

    CustomCommand _customCommand;
    void onDrawPrimatives(const cocos2d::Mat4 &transform, uint32_t flags);
    DrawNode *drawNode;

    // virtual void visit()override;
public:
    Node *m_pUIRoot;
};
};

#endif //__HN_HNLayer_H__
