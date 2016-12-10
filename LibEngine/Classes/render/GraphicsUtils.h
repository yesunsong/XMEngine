#ifndef __HN_GRAPHICSUTILS_H__
#define __HN_GRAPHICSUTILS_H__

#include "cocos2d.h"
USING_NS_CC;

namespace HN {
class GraphicsUtils {
public:
    GraphicsUtils();
    virtual ~GraphicsUtils();
public:
    /**
     @brief	Draw outline.

     @param	isIgnore		  	true if this object is ignore.
     @param	anchorPoint		  	The anchor point.
     @param	position		  	The position.
     @param	contentSize		  	Size of the content.
     @param [in,out]	parent	If non-null, the parent.
     @param	transform		  	The transform.
     */
    static void drawOutline(bool isIgnore, Vec2 anchorPoint, Vec2 position, Size contentSize, Node* parent, const cocos2d::Mat4 &transform);
    /**
     @BRIEF	灰化精灵

     @PARAM SPRITE	精灵
     */
    static void graySprite(Sprite* sprite);

    /**
     @brief	恢复灰化的精灵

     @param sprite	精灵
     */
    static void recoverySprite(Sprite* sprite);
    static bool isSpriteInstance(Node* node);
    static void gray(Vector<Node*> children);

    /**
     @brief	恢复父容器里所有的精灵

     @param children	父容器里的所有节点列表
     */
    static void recovery(Vector<Node*> children);
    static void createDrawNode(bool isIgnore, Vec2 anchorPoint, Vec2 position, Size contentSize, Node* parent, DrawNode* node);

private:
    /** @brief	The test. */
    int test;
};
}
#endif	///__HN_GRAPHICSUTILS_H__
