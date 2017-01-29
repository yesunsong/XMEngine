#ifndef  __MyProgressTimer_H__
#define __MyProgressTimer_H__

#include "cocos2d.h"
#include <stdio.h>

#define  kMyProgressTextureCoordsCount 4
const char kMyProgressTextureCoords = 0x4b;
USING_NS_CC;

class MyProgressFromTo : public ActionInterval {
public:
    static MyProgressFromTo* create(float duration, float fromPercentage, float toPercentage);

    virtual MyProgressFromTo* clone() const override;
    virtual MyProgressFromTo* reverse() const override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
    MyProgressFromTo() {}
    virtual ~MyProgressFromTo() {}

    bool initWithDuration(float duration, float fromPercentage, float toPercentage);

protected:
    float _to;
    float _from;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(MyProgressFromTo);
};

enum ProgressType {
    None,
    Start,
    Step1,
    Circle1_1,
    Circle1_2,
    Step2,
    Circle2_1,
    Circle2_2,
    Step3,
    Circle3_1,
    Circle3_2,
    Step4,
    Circle4_1,
    Circle4_2,
    Step5,
    End
};

class MyProgressTimer : public cocos2d::Node {
public:
    MyProgressTimer();
    ~MyProgressTimer();
    static MyProgressTimer* create(Sprite* sp);

    bool initWithSprite(Sprite* sp);

    void onDraw(const Mat4 &transform, uint32_t flags);

    void setSprite(Sprite *sprite);
    void setForebackground(Sprite *sprite);
    void setWarningPercent(float value);

    void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);

    virtual void updateColor(void) override;

    void updateProgress(void);

    Vec2 boundaryTexCoord(char index);

    Tex2F textureCoordFromAlphaPoint(Vec2 alpha);
    Vec2 vertexFromAlphaPoint(Vec2 alpha);

    void setPercentage(float percentage);

    void setOrigin(Vec2 _vOrigin);
    void setTop(Vec2 _vTop);

    float getPercentage();

    ProgressType percentToStep(float &_pos);

private:
    float m_fPercentage;
    float m_WarningPercent;

    CustomCommand _customCommand;

    Sprite* m_pSpr;
    Sprite* m_Forebackground;
    bool isDrawForebackground;
    int m_displayedAlpha;
    int count;
    float prePercent;
    int opac[2];

    int _vertexDataCount;
    V2F_C4B_T2F *_vertexData;

    ProgressType m_type;

    Vec2 m_vOrigin;
    Vec2 m_vTop;
};

#endif