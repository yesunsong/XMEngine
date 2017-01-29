#ifndef __HN_HNSprite_H__
#define __HN_HNSprite_H__

#include "cocos2d.h"
USING_NS_CC;

namespace HN {

class HNSprite : public Sprite {
    CC_SYNTHESIZE(bool, _drawRect, DrawRect);

public:
    HNSprite(void);
    virtual ~HNSprite(void);
    static HNSprite* create(const std::string& filename);

public:
    virtual void onExitTransitionDidStart()override;
    virtual bool initWithFile(const std::string& filename)override;
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags)override;

private:
    CustomCommand _customCommand;
    void onDrawPrimatives(const cocos2d::Mat4 &transform, uint32_t flags);
    DrawNode* drawNode;
    std::string mFilename;
};

};

#endif	//__HN_HNSprite_H__

