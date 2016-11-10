#ifndef __HN_HNSprite_H__
#define __HN_HNSprite_H__
#include "cocos2d.h"
#include "render/GraphicsUtils.h"

USING_NS_CC;

namespace HN {

class HNSprite : public Sprite {
public:
    HNSprite(void);
    static HNSprite* create(const std::string& filename);
    virtual ~HNSprite(void);

    virtual bool initWithFile(const std::string& filename)override;
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags)override;
    CC_SYNTHESIZE(bool, _drawRect,DrawRect);
private:
    CustomCommand _customCommand;
    void onDrawPrimatives(const cocos2d::Mat4 &transform, uint32_t flags);
    DrawNode* drawNode;
    std::string mFilename;
};

};

#endif	//__HN_HNSprite_H__

