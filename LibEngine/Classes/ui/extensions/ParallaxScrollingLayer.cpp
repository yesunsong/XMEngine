#include "ParallaxScrollingLayer.h"

ParallaxScrollingLayer::ParallaxScrollingLayer() :
    m_background(nullptr), m_foreground(nullptr), m_speed(15) {
}

bool ParallaxScrollingLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    scheduleUpdate();

    return true;
}

ParallaxScrollingLayer::~ParallaxScrollingLayer() {
}

void ParallaxScrollingLayer::update(float delta) {
    moveBackgroud();
    moveForeground();
}

void ParallaxScrollingLayer::moveForeground() {
    if (m_foreground) {
        float tmpX = m_foreground->getPositionX() - m_speed;

        m_foreground->setPositionX(tmpX);

        float right = m_foreground->getPositionX()
                      + m_foreground->getContentSize().width;

        if (right <= m_visibleSize.width) {
            m_foreground->setPositionX(right - m_visibleSize.width);
        }
    }
}

void ParallaxScrollingLayer::moveBackgroud() {
    if (m_background) {
        float tmpX = m_background->getPositionX() - m_speed / 3;

        m_background->setPositionX(tmpX);

        float right = m_background->getPositionX()
                      + m_background->getContentSize().width;

        if (right <= m_visibleSize.width) {
            m_background->setPositionX(right - m_visibleSize.width);
        }
    }
}

void ParallaxScrollingLayer::setBackground(Sprite* background) {
    CC_SAFE_RETAIN(background);
    CC_SAFE_RELEASE(m_background);
    m_background = background;

    if (m_background) {
        addChild(m_background, 0);
    }
}

void ParallaxScrollingLayer::setForeground(Sprite* foreground) {
    CC_SAFE_RETAIN(foreground);
    CC_SAFE_RELEASE(m_foreground);
    m_foreground = foreground;

    if (m_foreground) {
        addChild(m_foreground, 1);
    }

}

void ParallaxScrollingLayer::setVisibleSize(Size size) {
    m_visibleSize = size;
}

void ParallaxScrollingLayer::setSpeed(float speed) {
    m_speed = speed;
}
