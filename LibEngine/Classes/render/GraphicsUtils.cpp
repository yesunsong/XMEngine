//#include "stdafx.h"
#include "GraphicsUtils.h"

namespace HN {

GraphicsUtils::GraphicsUtils() {
}

GraphicsUtils::~GraphicsUtils() {
}

void GraphicsUtils::createDrawNode(bool isIgnore, Vec2 anchorPoint, Vec2 position, Size contentSize, Node* parent, DrawNode* node) {
    float anchorX = (isIgnore ? 0 : anchorPoint.x);
    float anchorY = (isIgnore ? 0 : anchorPoint.y);
    float x = position.x;
    float y = position.y;
    float width = contentSize.width;
    float height = contentSize.height;
    float nx = x - anchorX*width;
    float ny = y - anchorY*height;
    Vec2 vc1[4] = { parent->convertToNodeSpace(Vec2(nx, ny)), parent->convertToNodeSpace(Vec2(nx + width, ny)), parent->convertToNodeSpace(Vec2(nx + width, ny + height)), parent->convertToNodeSpace(Vec2(nx, ny + height)) };
    if (!node) {
        node = DrawNode::create();
        //node->setTag(tag);
        parent->addChild(node);
    }
    //红色：区域范�?
    node->drawPolygon(vc1, 4, Color4F(1, 0, 0, 0), 1, Color4F::RED);
    //黄色：锚�?
    node->drawDot(Vec2(width * anchorPoint.x, height * anchorPoint.y), 2.0, Color4F::YELLOW);
    //绿色：位置点
    node->drawDot(parent->convertToNodeSpace(position), 2.0, Color4F::GREEN);
}

void GraphicsUtils::drawOutline(bool isIgnore, Vec2 anchorPoint, Vec2 position, Size contentSize, Node* parent, const cocos2d::Mat4 &transform) {
    //初始�?
    Director* director = Director::getInstance();
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    ////
    float anchorX = (isIgnore ? 0 : anchorPoint.x);
    float anchorY = (isIgnore ? 0 : anchorPoint.y);
    float x = position.x;
    float y = position.y;
    float width = contentSize.width;
    float height = contentSize.height;
    float nx = x - anchorX*width;
    float ny = y - anchorY*height;
    Vec2 vc1[4] = { parent->convertToNodeSpace(Vec2(nx, ny)), parent->convertToNodeSpace(Vec2(nx + width, ny)), parent->convertToNodeSpace(Vec2(nx + width, ny + height)), parent->convertToNodeSpace(Vec2(nx, ny + height)) };
    //Vec2 vc1[4] = { Vec2(nx, ny), Vec2(nx + width, ny), Vec2(nx + width, ny + height), Vec2(nx, ny + height) };
    //红色：区域范围
    CHECK_GL_ERROR_DEBUG();
    glLineWidth(2);
    //DrawPrimitives::setDrawColor4F(1, 0, 0, 1);
    //DrawPrimitives::drawRect(vc1[0], vc1[2]);
    ////DrawPrimitives::drawPoly(vc1, 4, true);
    ////绿色：位置点
    //CHECK_GL_ERROR_DEBUG();
    //DrawPrimitives::setPointSize(5);
    //DrawPrimitives::setDrawColor4F(0, 1, 0, 1);
    //DrawPrimitives::drawPoint(parent->convertToNodeSpace(position));
    ////黄色：锚点
    //CHECK_GL_ERROR_DEBUG();
    //DrawPrimitives::setPointSize(10);
    //DrawPrimitives::setDrawColor4F(1, 1, 0, 1);
    ////DrawPrimitives::drawPoint(Vec2(width * anchorX, height * anchorY));

    //glLineWidth(1);
    //DrawPrimitives::setDrawColor4B(255, 255, 255, 255);
    //DrawPrimitives::setPointSize(1);

    CHECK_GL_ERROR_DEBUG();
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void GraphicsUtils::graySprite(Sprite* sprite) {
    if (sprite) {
        GLProgram * p = new GLProgram();
        p->initWithFilenames("gray.vsh", "gray.fsh");
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        p->link();
        p->updateUniforms();
        sprite->setGLProgram(p);
    }
}

void GraphicsUtils::recoverySprite(Sprite* sprite) {
    if (sprite != NULL) {
        std::string str = GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP;
        GLProgram * pProgram = CCShaderCache::getInstance()->getGLProgram(str);
        sprite->setGLProgram(pProgram);
    }
}

bool GraphicsUtils::isSpriteInstance(Node* node) {
    return (dynamic_cast<Sprite*>(node) ? true : false);
}

void GraphicsUtils::gray(Vector<Node*> children) {
    Node* node = nullptr;
    for (int i = 0; i < children.size(); i++) {
        node = children.at(i);
        if (isSpriteInstance(node)) {
            graySprite((Sprite*)node);
        }
    }
}

void GraphicsUtils::recovery(Vector<Node*> children) {
    Node* node = nullptr;
    for (int i = 0; i < children.size(); i++) {
        node = children.at(i);
        if (isSpriteInstance(node)) {
            recoverySprite(dynamic_cast<Sprite*>(node));
        }
    }
}

}
