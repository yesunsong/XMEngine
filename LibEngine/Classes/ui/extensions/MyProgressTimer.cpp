#pragma once
#include "MyProgressTimer.h"

USING_NS_CC;

MyProgressTimer::MyProgressTimer() {
    m_pSpr = nullptr;
    _vertexData = nullptr;
    _vertexDataCount = 0;
    m_fPercentage = 0.0f;
};

MyProgressTimer::~MyProgressTimer() {
    if (m_pSpr) {
        CC_SAFE_RELEASE(m_pSpr);
    }
    if (_vertexData) {
        CC_SAFE_FREE(_vertexData);
    }
};

MyProgressTimer* MyProgressTimer::create(Sprite* sp) {
    MyProgressTimer *progressTimer = new (std::nothrow) MyProgressTimer();
    if (progressTimer->initWithSprite(sp)) {
        progressTimer->autorelease();
    } else {
        delete progressTimer;
        progressTimer = nullptr;
    }

    return progressTimer;
}

bool MyProgressTimer::initWithSprite(Sprite* sp) {
    setSprite(sp);

    setOrigin(Vec2(0.05f, 0.05f));
    setTop(Vec2(0.95f, 0.95f));

    setAnchorPoint(Vec2(0.5f,0.5f));

    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

    m_type = ProgressType::None;

    setPercentage(0.0f);
//    ProgressFromTo;

    m_Forebackground = nullptr;
    isDrawForebackground = false;
    count = 0;
    prePercent = 0;
    m_WarningPercent = 75.0f;

    opac[0] = 1;
    opac[0] = 127;

    return true;
}

void MyProgressTimer::onDraw(const Mat4 &transform, uint32_t flags) {

    getGLProgram()->use();
    getGLProgram()->setUniformsForBuiltins(transform);

    GL::blendFunc(m_pSpr->getBlendFunc().src, m_pSpr->getBlendFunc().dst);
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    GL::bindTexture2D(m_pSpr->getTexture()->getName());
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(_vertexData[0]), &_vertexData[0].vertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(_vertexData[0]), &_vertexData[0].texCoords);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(_vertexData[0]), &_vertexData[0].colors);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, _vertexDataCount);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _vertexDataCount);

    //
    if(isDrawForebackground) {
        if (_vertexData) {
            for (int i = 0; i < _vertexDataCount; ++i) {
                _vertexData[i].colors.a *= m_displayedAlpha/255.0f;
            }
        }

        GL::blendFunc(m_Forebackground->getBlendFunc().src, m_Forebackground->getBlendFunc().dst);
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
        GL::bindTexture2D(m_Forebackground->getTexture()->getName());
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(_vertexData[0]), &_vertexData[0].vertices);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(_vertexData[0]), &_vertexData[0].texCoords);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(_vertexData[0]), &_vertexData[0].colors);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, _vertexDataCount);
        CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _vertexDataCount);
    }
}

void MyProgressTimer::draw(Renderer *renderer, const Mat4& transform, uint32_t flags) {
    if (!_vertexData || !m_pSpr)
        return;

    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(MyProgressTimer::onDraw, this, transform, flags);
    renderer->addCommand(&_customCommand);
}

void MyProgressTimer::setSprite(Sprite *sprite) {
    if (m_pSpr != sprite) {
        CC_SAFE_RETAIN(sprite);
        CC_SAFE_RELEASE(m_pSpr);
        m_pSpr = sprite;
        setContentSize(m_pSpr->getContentSize());

        if (_vertexData) {
            CC_SAFE_FREE(_vertexData);
            _vertexDataCount = 0;
        }
    }
}

void MyProgressTimer::setForebackground(Sprite *sprite) {
    if (m_Forebackground != sprite) {
        CC_SAFE_RETAIN(sprite);
        CC_SAFE_RELEASE(m_Forebackground);
        m_Forebackground = sprite;
    }
}

void MyProgressTimer::updateColor(void) {
    if (!m_pSpr) {
        return;
    }

    if (_vertexData) {
        Color4B sc = m_pSpr->getQuad().tl.colors;
        for (int i = 0; i < _vertexDataCount; ++i) {
            _vertexData[i].colors = sc;
        }
    }
}

cocos2d::Tex2F MyProgressTimer::textureCoordFromAlphaPoint(Vec2 alpha) {
    Tex2F ret(0.0f, 0.0f);
    if (!m_pSpr) {
        return ret;
    }
    V3F_C4B_T2F_Quad quad = m_pSpr->getQuad();
    Vec2 min = Vec2(quad.bl.texCoords.u, quad.bl.texCoords.v);
    Vec2 max = Vec2(quad.tr.texCoords.u, quad.tr.texCoords.v);
    //  Fix bug #1303 so that progress timer handles sprite frame texture rotation
    if (m_pSpr->isTextureRectRotated()) {
        CC_SWAP(alpha.x, alpha.y, float);
    }
    return Tex2F(min.x * (1.f - alpha.x) + max.x * alpha.x, min.y * (1.f - alpha.y) + max.y * alpha.y);
}

cocos2d::Vec2 MyProgressTimer::vertexFromAlphaPoint(Vec2 alpha) {
    Vec2 ret(0.0f, 0.0f);
    if (!m_pSpr) {
        return ret;
    }
    V3F_C4B_T2F_Quad quad = m_pSpr->getQuad();
    Vec2 min = Vec2(quad.bl.vertices.x, quad.bl.vertices.y);
    Vec2 max = Vec2(quad.tr.vertices.x, quad.tr.vertices.y);
    ret.x = min.x * (1.f - alpha.x) + max.x * alpha.x;
    ret.y = min.y * (1.f - alpha.y) + max.y * alpha.y;
    return ret;
}

Vec2 MyProgressTimer::boundaryTexCoord(char index) {
    if (index < kMyProgressTextureCoordsCount) {
        if (true) {
            return Vec2((kMyProgressTextureCoords >> (7 - (index << 1))) & 1, (kMyProgressTextureCoords >> (7 - ((index << 1) + 1))) & 1);
        } else {
            return Vec2((kMyProgressTextureCoords >> ((index << 1) + 1)) & 1, (kMyProgressTextureCoords >> (index << 1)) & 1);
        }
    }
    return Vec2::ZERO;
}

void MyProgressTimer::setPercentage(float percentage) {
    m_fPercentage = clampf(percentage, 0, 100);
    updateProgress();
    updateColor();

    //

    if(m_fPercentage < m_WarningPercent) {
        m_displayedAlpha = 0;
        isDrawForebackground = false;
    } else if((m_fPercentage - prePercent) > 0.8) {
        isDrawForebackground = true;
        prePercent = m_fPercentage;
        count++;
        if(count > 10) {
            count = 0;
        }
        m_displayedAlpha = opac[count%2];
    }

    if(percentage == 100.0f) {
        m_displayedAlpha = 0;
        prePercent = 0;
        count = 0;
        isDrawForebackground = false;
    }

}

void MyProgressTimer::updateProgress(void) {
    if (!m_pSpr) {
        return;
    }

    Vec2 min = Vec2(0, 0);
    Vec2 max = Vec2(1, 1);
    Vec2 mid = Vec2(.5, .5);

    float pos = 0.0f;
    auto step = percentToStep(pos);
    if (ProgressType::Start == step) {
        if (!_vertexData) {
            _vertexDataCount = 12;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT(_vertexData, "CCProgressTimer. Not enough memory");
        }

        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, min.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(min.x, min.y));

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(max.x, min.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(max.x, min.y));

        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(min.x, max.y));

        for (int i = 3; i < _vertexDataCount; i++) {
            _vertexData[i].texCoords = textureCoordFromAlphaPoint(Vec2(max.x, max.y));
            _vertexData[i].vertices = vertexFromAlphaPoint(Vec2(max.x, max.y));
        }
    } else if (ProgressType::Step1 == step) {
        if (!_vertexData) {
            _vertexDataCount = 12;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT(_vertexData, "CCProgressTimer. Not enough memory");
        }

        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(mid.x, max.y));

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, m_vTop.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(mid.x, m_vTop.y));

        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(min.x, max.y));

        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));

        _vertexData[4].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, min.y));
        _vertexData[4].vertices = vertexFromAlphaPoint(Vec2(min.x, min.y));

        _vertexData[5].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));
        _vertexData[5].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));

        _vertexData[6].texCoords = textureCoordFromAlphaPoint(Vec2(max.x, min.y));
        _vertexData[6].vertices = vertexFromAlphaPoint(Vec2(max.x, min.y));

        _vertexData[7].texCoords = textureCoordFromAlphaPoint(Vec2(m_vTop.x, m_vOrigin.y));
        _vertexData[7].vertices = vertexFromAlphaPoint(Vec2(m_vTop.x, m_vOrigin.y));

        _vertexData[8].texCoords = textureCoordFromAlphaPoint(Vec2(max.x, max.y));
        _vertexData[8].vertices = vertexFromAlphaPoint(Vec2(max.x, max.y));

        _vertexData[9].texCoords = textureCoordFromAlphaPoint(Vec2(m_vTop.x, m_vTop.y));
        _vertexData[9].vertices = vertexFromAlphaPoint(Vec2(m_vTop.x, m_vTop.y));

        _vertexData[10].texCoords = textureCoordFromAlphaPoint(Vec2(pos, max.y));
        _vertexData[10].vertices = vertexFromAlphaPoint(Vec2(pos, max.y));

        _vertexData[11].texCoords = textureCoordFromAlphaPoint(Vec2(pos, m_vTop.y));
        _vertexData[11].vertices = vertexFromAlphaPoint(Vec2(pos, m_vTop.y));

    } else if (ProgressType::Circle1_1 == step) {
        if (!_vertexData) {
            _vertexDataCount = 12;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT(_vertexData, "CCProgressTimer. Not enough memory");
        }

        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(mid.x, max.y));

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, m_vTop.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(mid.x, m_vTop.y));

        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(min.x, max.y));

        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));

        _vertexData[4].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, min.y));
        _vertexData[4].vertices = vertexFromAlphaPoint(Vec2(min.x, min.y));

        _vertexData[5].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));
        _vertexData[5].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));

        _vertexData[6].texCoords = textureCoordFromAlphaPoint(Vec2(max.x, min.y));
        _vertexData[6].vertices = vertexFromAlphaPoint(Vec2(max.x, min.y));

        _vertexData[7].texCoords = textureCoordFromAlphaPoint(Vec2(m_vTop.x, m_vOrigin.y));
        _vertexData[7].vertices = vertexFromAlphaPoint(Vec2(m_vTop.x, m_vOrigin.y));

        _vertexData[8].texCoords = textureCoordFromAlphaPoint(Vec2(max.x, max.y));
        _vertexData[8].vertices = vertexFromAlphaPoint(Vec2(max.x, max.y));

        _vertexData[9].texCoords = textureCoordFromAlphaPoint(Vec2(m_vTop.x, m_vTop.y));
        _vertexData[9].vertices = vertexFromAlphaPoint(Vec2(m_vTop.x, m_vTop.y));

        for (int i = 10; i < _vertexDataCount; i++) {
            _vertexData[i].texCoords = textureCoordFromAlphaPoint(Vec2(pos, max.y));
            _vertexData[i].vertices = vertexFromAlphaPoint(Vec2(pos, max.y));
        }
    } else if (ProgressType::Circle1_2 == step) {
        if (!_vertexData) {
            _vertexDataCount = 12;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT(_vertexData, "CCProgressTimer. Not enough memory");
        }

        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(mid.x, max.y));

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, m_vTop.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(mid.x, m_vTop.y));

        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(min.x, max.y));

        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));

        _vertexData[4].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, min.y));
        _vertexData[4].vertices = vertexFromAlphaPoint(Vec2(min.x, min.y));

        _vertexData[5].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));
        _vertexData[5].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));

        _vertexData[6].texCoords = textureCoordFromAlphaPoint(Vec2(max.x, min.y));
        _vertexData[6].vertices = vertexFromAlphaPoint(Vec2(max.x, min.y));

        _vertexData[7].texCoords = textureCoordFromAlphaPoint(Vec2(m_vTop.x, m_vOrigin.y));
        _vertexData[7].vertices = vertexFromAlphaPoint(Vec2(m_vTop.x, m_vOrigin.y));

        _vertexData[8].texCoords = textureCoordFromAlphaPoint(Vec2(max.x, pos));
        _vertexData[8].vertices = vertexFromAlphaPoint(Vec2(max.x, pos));

        for (int i = 9; i < _vertexDataCount; i++) {
            _vertexData[i].texCoords = textureCoordFromAlphaPoint(Vec2(m_vTop.x, m_vTop.y));
            _vertexData[i].vertices = vertexFromAlphaPoint(Vec2(m_vTop.x, m_vTop.y));
        }
    } else if (ProgressType::Step2 == step) {
        if (!_vertexData) {
            _vertexDataCount = 12;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT(_vertexData, "CCProgressTimer. Not enough memory");
        }

        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(mid.x, max.y));

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, m_vTop.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(mid.x, m_vTop.y));

        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(min.x, max.y));

        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));

        _vertexData[4].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, min.y));
        _vertexData[4].vertices = vertexFromAlphaPoint(Vec2(min.x, min.y));

        _vertexData[5].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));
        _vertexData[5].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));

        _vertexData[6].texCoords = textureCoordFromAlphaPoint(Vec2(max.x, min.y));
        _vertexData[6].vertices = vertexFromAlphaPoint(Vec2(max.x, min.y));

        _vertexData[7].texCoords = textureCoordFromAlphaPoint(Vec2(m_vTop.x, m_vOrigin.y));
        _vertexData[7].vertices = vertexFromAlphaPoint(Vec2(m_vTop.x, m_vOrigin.y));

        _vertexData[8].texCoords = textureCoordFromAlphaPoint(Vec2(max.x, pos));
        _vertexData[8].vertices = vertexFromAlphaPoint(Vec2(max.x, pos));

        for (int i = 9; i < _vertexDataCount; i++) {
            _vertexData[i].texCoords = textureCoordFromAlphaPoint(Vec2(m_vTop.x, pos));
            _vertexData[i].vertices = vertexFromAlphaPoint(Vec2(m_vTop.x, pos));
        }
    } else if (ProgressType::Circle2_1 == step) {
        if (!_vertexData) {
            _vertexDataCount = 12;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT(_vertexData, "CCProgressTimer. Not enough memory");
        }

        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(mid.x, max.y));

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, m_vTop.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(mid.x, m_vTop.y));

        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(min.x, max.y));

        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));

        _vertexData[4].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, min.y));
        _vertexData[4].vertices = vertexFromAlphaPoint(Vec2(min.x, min.y));

        _vertexData[5].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));
        _vertexData[5].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));

        _vertexData[6].texCoords = textureCoordFromAlphaPoint(Vec2(max.x, min.y));
        _vertexData[6].vertices = vertexFromAlphaPoint(Vec2(max.x, min.y));

        _vertexData[7].texCoords = textureCoordFromAlphaPoint(Vec2(m_vTop.x, m_vOrigin.y));
        _vertexData[7].vertices = vertexFromAlphaPoint(Vec2(m_vTop.x, m_vOrigin.y));

        for (int i = 8; i < _vertexDataCount; i++) {
            _vertexData[i].texCoords = textureCoordFromAlphaPoint(Vec2(max.x, pos));
            _vertexData[i].vertices = vertexFromAlphaPoint(Vec2(max.x, pos));
        }
    } else if (ProgressType::Circle2_2 == step) {
        if (!_vertexData) {
            _vertexDataCount = 12;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT(_vertexData, "CCProgressTimer. Not enough memory");
        }

        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(mid.x, max.y));

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, m_vTop.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(mid.x, m_vTop.y));

        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(min.x, max.y));

        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));

        _vertexData[4].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, min.y));
        _vertexData[4].vertices = vertexFromAlphaPoint(Vec2(min.x, min.y));

        _vertexData[5].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));
        _vertexData[5].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));

        _vertexData[6].texCoords = textureCoordFromAlphaPoint(Vec2(pos, min.y));
        _vertexData[6].vertices = vertexFromAlphaPoint(Vec2(pos, min.y));

        for (int i = 7; i < _vertexDataCount; i++) {
            _vertexData[i].texCoords = textureCoordFromAlphaPoint(Vec2(m_vTop.x, m_vOrigin.y));
            _vertexData[i].vertices = vertexFromAlphaPoint(Vec2(m_vTop.x, m_vOrigin.y));
        }
    } else if (ProgressType::Step3 == step) {
        if (!_vertexData) {
            _vertexDataCount = 12;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT(_vertexData, "CCProgressTimer. Not enough memory");
        }

        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(mid.x, max.y));

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, m_vTop.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(mid.x, m_vTop.y));

        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(min.x, max.y));

        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));

        _vertexData[4].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, min.y));
        _vertexData[4].vertices = vertexFromAlphaPoint(Vec2(min.x, min.y));

        _vertexData[5].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));
        _vertexData[5].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));

        _vertexData[6].texCoords = textureCoordFromAlphaPoint(Vec2(pos, min.y));
        _vertexData[6].vertices = vertexFromAlphaPoint(Vec2(pos, min.y));

        for (int i = 7; i < _vertexDataCount; i++) {
            _vertexData[i].texCoords = textureCoordFromAlphaPoint(Vec2(pos, m_vOrigin.y));
            _vertexData[i].vertices = vertexFromAlphaPoint(Vec2(pos, m_vOrigin.y));
        }
    } else if (ProgressType::Circle3_1 == step) {
        if (!_vertexData) {
            _vertexDataCount = 12;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT(_vertexData, "CCProgressTimer. Not enough memory");
        }

        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(mid.x, max.y));

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, m_vTop.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(mid.x, m_vTop.y));

        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(min.x, max.y));

        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));

        _vertexData[4].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, min.y));
        _vertexData[4].vertices = vertexFromAlphaPoint(Vec2(min.x, min.y));

        _vertexData[5].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));
        _vertexData[5].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));

        for (int i = 6; i < _vertexDataCount; i++) {
            _vertexData[i].texCoords = textureCoordFromAlphaPoint(Vec2(pos, min.y));
            _vertexData[i].vertices = vertexFromAlphaPoint(Vec2(pos, min.y));
        }
    } else if (ProgressType::Circle3_2 == step) {
        if (!_vertexData) {
            _vertexDataCount = 12;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT(_vertexData, "CCProgressTimer. Not enough memory");
        }

        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(mid.x, max.y));

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, m_vTop.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(mid.x, m_vTop.y));

        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(min.x, max.y));

        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));

        _vertexData[4].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, pos));
        _vertexData[4].vertices = vertexFromAlphaPoint(Vec2(min.x, pos));

        for (int i = 5; i < _vertexDataCount; i++) {
            _vertexData[i].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));
            _vertexData[i].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vOrigin.y));
        }
    } else if (ProgressType::Step4 == step) {
        if (!_vertexData) {
            _vertexDataCount = 12;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT(_vertexData, "CCProgressTimer. Not enough memory");
        }

        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(mid.x, max.y));

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, m_vTop.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(mid.x, m_vTop.y));

        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(min.x, max.y));

        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));

        _vertexData[4].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, pos));
        _vertexData[4].vertices = vertexFromAlphaPoint(Vec2(min.x, pos));

        for (int i = 5; i < _vertexDataCount; i++) {
            _vertexData[i].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, pos));
            _vertexData[i].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, pos));
        }
    } else if (ProgressType::Circle4_1 == step) {
        if (!_vertexData) {
            _vertexDataCount = 12;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT(_vertexData, "CCProgressTimer. Not enough memory");
        }

        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(mid.x, max.y));

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, m_vTop.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(mid.x, m_vTop.y));

        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(min.x, max.y));

        _vertexData[3].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));
        _vertexData[3].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));

        for (int i = 4; i < _vertexDataCount; i++) {
            _vertexData[i].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, pos));
            _vertexData[i].vertices = vertexFromAlphaPoint(Vec2(min.x, pos));
        }
    } else if (ProgressType::Circle4_2 == step) {
        if (!_vertexData) {
            _vertexDataCount = 12;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT(_vertexData, "CCProgressTimer. Not enough memory");
        }

        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(mid.x, max.y));

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, m_vTop.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(mid.x, m_vTop.y));

        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(pos, max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(pos, max.y));

        for (int i = 3; i < _vertexDataCount; i++) {
            _vertexData[i].texCoords = textureCoordFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));
            _vertexData[i].vertices = vertexFromAlphaPoint(Vec2(m_vOrigin.x, m_vTop.y));
        }
    } else if (ProgressType::Step5 == step) {
        if (!_vertexData) {
            _vertexDataCount = 12;
            _vertexData = (V2F_C4B_T2F*)malloc(_vertexDataCount * sizeof(V2F_C4B_T2F));
            CCASSERT(_vertexData, "CCProgressTimer. Not enough memory");
        }

        _vertexData[0].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, max.y));
        _vertexData[0].vertices = vertexFromAlphaPoint(Vec2(mid.x, max.y));

        _vertexData[1].texCoords = textureCoordFromAlphaPoint(Vec2(mid.x, m_vTop.y));
        _vertexData[1].vertices = vertexFromAlphaPoint(Vec2(mid.x, m_vTop.y));

        _vertexData[2].texCoords = textureCoordFromAlphaPoint(Vec2(pos, max.y));
        _vertexData[2].vertices = vertexFromAlphaPoint(Vec2(pos, max.y));

        for (int i = 3; i < _vertexDataCount; i++) {
            _vertexData[i].texCoords = textureCoordFromAlphaPoint(Vec2(pos, m_vTop.y));
            _vertexData[i].vertices = vertexFromAlphaPoint(Vec2(pos, m_vTop.y));
        }
    } else if (ProgressType::End == step) {
        for (int i = 0; i < _vertexDataCount; i++) {
            _vertexData[i].texCoords = textureCoordFromAlphaPoint(Vec2(min.x, min.y));
            _vertexData[i].vertices = vertexFromAlphaPoint(Vec2(min.x, min.y));
        }
    }
}

void MyProgressTimer::setOrigin(Vec2 _vOrigin) {
    if (m_pSpr) {
        float topX = clampf(_vOrigin.x, 0, 0.5);
        float topY = clampf(_vOrigin.y, 0, 0.5);

        auto thisSize = m_pSpr->getContentSize();
        auto max1 = thisSize.width * topX;
        auto max2 = thisSize.height * topY;
        auto max3 = MAX(max1, max2);
        m_vOrigin = Vec2(max3 / thisSize.width, max3 / thisSize.height);

        updateProgress();
    }
}

void MyProgressTimer::setTop(Vec2 _vTop) {
    if (m_pSpr) {
        float topX = clampf(_vTop.x, 0.5, 1);
        float topY = clampf(_vTop.y, 0.5, 1);

        auto thisSize = m_pSpr->getContentSize();
        auto max1 = thisSize.width * (1-topX);
        auto max2 = thisSize.height * (1-topY);
        auto max3 = MAX(max1, max2);
        m_vTop = Vec2(1- max3 / thisSize.width, 1 - max3 / thisSize.height);

        updateProgress();
    }

}

void MyProgressTimer::setWarningPercent(float value) {
    m_WarningPercent = value;
}

ProgressType MyProgressTimer::percentToStep(float &_pos) {
    if (m_fPercentage == 0) {
        return ProgressType::Start;
    } else if (m_fPercentage == 100) {
        return ProgressType::End;
    } else if (m_fPercentage > 0 && m_fPercentage < 100) {
        auto thisSize = this->getContentSize();
        auto topR1 = thisSize.width * (1 - m_vTop.x);
        auto topR2 = thisSize.height * (1 - m_vTop.y);
        auto originR1 = thisSize.width * m_vOrigin.x;
        auto originR2 = thisSize.height * m_vOrigin.y;

        auto pi = 3.1415926f;

        float posNode[13] = {
            thisSize.width / 2 - topR1,
            thisSize.width / 2 - topR1 + pi*topR2 / 4,
            thisSize.width / 2 - topR1 + pi*topR1 / 4 + pi*topR2 / 4,
            thisSize.width / 2 - topR1 + pi*topR1 / 4 + pi*topR2 / 4 + thisSize.height - topR2 - originR2,
            thisSize.width / 2 - topR1 + pi*topR1 / 4 + pi*topR2 / 4 + thisSize.height - topR2 - originR2 + pi*topR1 / 4,
            thisSize.width / 2 - topR1 + pi*topR1 / 4 + pi*topR2 / 4 + thisSize.height - topR2 - originR2 + pi*topR1 / 4 + pi*originR2 / 4,
            thisSize.width / 2 - topR1 + pi*topR1 / 4 + pi*topR2 / 4 + thisSize.height - topR2 - originR2 + pi*topR1 / 4 + pi*originR2 / 4 + thisSize.width - originR1 - topR1,
            thisSize.width / 2 - topR1 + pi*topR1 / 4 + pi*topR2 / 4 + thisSize.height - topR2 - originR2 + pi*topR1 / 4 + pi*originR2 / 4 + thisSize.width - originR1 - topR1 + pi*originR2 / 4,
            thisSize.width / 2 - topR1 + pi*topR1 / 4 + pi*topR2 / 4 + thisSize.height - topR2 - originR2 + pi*topR1 / 4 + pi*originR2 / 4 + thisSize.width - originR1 - topR1 + pi*originR2 / 4 + pi*originR1 / 4,
            thisSize.width / 2 - topR1 + pi*topR1 / 4 + pi*topR2 / 4 + thisSize.height - topR2 - originR2 + pi*topR1 / 4 + pi*originR2 / 4 + thisSize.width - originR1 - topR1 + pi*originR2 / 4 + pi*originR1 / 4 + thisSize.height - originR2 - topR2,
            thisSize.width / 2 - topR1 + pi*topR1 / 4 + pi*topR2 / 4 + thisSize.height - topR2 - originR2 + pi*topR1 / 4 + pi*originR2 / 4 + thisSize.width - originR1 - topR1 + pi*originR2 / 4 + pi*originR1 / 4 + thisSize.height - originR2 - topR2 + pi*originR1 / 4,
            thisSize.width / 2 - topR1 + pi*topR1 / 4 + pi*topR2 / 4 + thisSize.height - topR2 - originR2 + pi*topR1 / 4 + pi*originR2 / 4 + thisSize.width - originR1 - topR1 + pi*originR2 / 4 + pi*originR1 / 4 + thisSize.height - originR2 - topR2 + pi*originR1 / 4 + pi*topR2 / 4,
            thisSize.width / 2 - topR1 + pi*topR1 / 4 + pi*topR2 / 4 + thisSize.height - topR2 - originR2 + pi*topR1 / 4 + pi*originR2 / 4 + thisSize.width - originR1 - topR1 + pi*originR2 / 4 + pi*originR1 / 4 + thisSize.height - originR2 - topR2 + pi*originR1 / 4 + pi*topR2 / 4 + thisSize.width / 2 - originR1
        };

        auto allLength = posNode[12];

        auto nowPosLength = allLength * m_fPercentage / 100;

        if (nowPosLength <= posNode[0]) {
            _pos = (nowPosLength + thisSize.width / 2) / thisSize.width;

            if (_pos == 0.5f)
                return ProgressType::Start;
            return ProgressType::Step1;
        } else if (nowPosLength <= posNode[1]) {
            auto huchang = nowPosLength - posNode[0];
            auto angle = huchang / topR2;
            _pos = (topR2 * tanf(angle) + thisSize.width - topR1) / thisSize.width;

            return ProgressType::Circle1_1;
        } else if (nowPosLength <= posNode[2]) {
            auto huchang = pi*topR1 / 4 - (nowPosLength - posNode[1]);
            auto angle = huchang / topR1;
            _pos = (topR1 * tanf(angle) + thisSize.height - topR2) / thisSize.height;

            return ProgressType::Circle1_2;
        } else if (nowPosLength <= posNode[3]) {
            _pos = 1 - (nowPosLength - posNode[2] + topR2) / thisSize.height;

            return ProgressType::Step2;
        } else if (nowPosLength <= posNode[4]) {
            auto huchang = nowPosLength - posNode[3];
            auto angle = huchang / topR1;
            _pos = (originR2 - tanf(angle) * topR1) / thisSize.height;

            return ProgressType::Circle2_1;
        } else if (nowPosLength <= posNode[5]) {
            auto huchang = pi*originR2 / 4 - (nowPosLength - posNode[4]);
            auto angle = huchang / originR2;
            _pos = (tanf(angle) * originR2 + thisSize.width - topR1) / thisSize.width;

            return ProgressType::Circle2_2;
        } else if (nowPosLength <= posNode[6]) {
            auto nowPos = nowPosLength - posNode[5] + topR1;
            _pos = 1.0f - nowPos / thisSize.width;

            return ProgressType::Step3;
        } else if (nowPosLength < posNode[7]) {
            auto huchang = nowPosLength - posNode[6];
            auto angle = huchang / originR2;
            _pos = (originR1 - tanf(angle) * originR2) / thisSize.width;

            return ProgressType::Circle3_1;
        } else if (nowPosLength < posNode[8]) {
            auto huchang = pi*originR1 / 4 - (nowPosLength - posNode[7]);
            auto angle = huchang / originR1;
            _pos = (originR2 - tanf(angle) * originR2) / thisSize.height;

            return ProgressType::Circle3_2;
        } else if (nowPosLength < posNode[9]) {
            auto huchang = nowPosLength - posNode[8] + originR2;
            _pos = huchang / thisSize.height;

            return ProgressType::Step4;
        } else if (nowPosLength < posNode[10]) {
            auto huchang = (nowPosLength - posNode[9]);
            auto angle = huchang / originR1;
            _pos = (tanf(angle) * originR1 + thisSize.height - topR2) / thisSize.height;

            return ProgressType::Circle4_1;
        } else if (nowPosLength < posNode[11]) {
            auto huchang = pi*topR2 / 4 - (nowPosLength - posNode[10]);
            auto angle = huchang / topR2;
            _pos = (originR1 - tanf(angle) * topR2) / thisSize.width;

            return ProgressType::Circle4_2;
        } else if (nowPosLength < posNode[12]) {
            auto huchang = nowPosLength - posNode[11] + originR1;
            _pos = huchang / thisSize.width;

            return ProgressType::Step5;
        }
        return ProgressType::End;
    }

    return ProgressType::None;
}

float MyProgressTimer::getPercentage() {
    return m_fPercentage;
};

//==============================
MyProgressFromTo* MyProgressFromTo::create(float duration, float fromPercentage, float toPercentage) {
    MyProgressFromTo *progressFromTo = new (std::nothrow) MyProgressFromTo();
    progressFromTo->initWithDuration(duration, fromPercentage, toPercentage);
    progressFromTo->autorelease();

    return progressFromTo;
}

MyProgressFromTo* MyProgressFromTo::clone() const {
    auto a = new (std::nothrow) MyProgressFromTo();
    a->initWithDuration(_duration, _from, _to);
    a->autorelease();
    return a;
}

MyProgressFromTo* MyProgressFromTo::reverse() const {
    return MyProgressFromTo::create(_duration, _to, _from);
}

void MyProgressFromTo::startWithTarget(Node *target) {
    ActionInterval::startWithTarget(target);
}

void MyProgressFromTo::update(float time) {
    ((MyProgressTimer*)(_target))->setPercentage(_from + (_to - _from) * time);
}

bool MyProgressFromTo::initWithDuration(float duration, float fromPercentage, float toPercentage) {
    if (ActionInterval::initWithDuration(duration)) {
        _to = toPercentage;
        _from = fromPercentage;

        return true;
    }

    return false;
}


