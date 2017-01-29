#include "CheckCSBLayer.h"
//#include "HNNetExport.h"
#include "UI/Base/ATableView.h"
//#include "FontSize.h"
#include "UI/Base/HNSprite.h"
#include <algorithm>
#include <string>
#include "globel/ApplicationMacro.h"
#include "tmp/FontSize.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio;
using namespace std;

CheckCSBLayer::CheckCSBLayer() : isMoved(false), downCount(0), upCount(0) {}

CheckCSBLayer::~CheckCSBLayer() {}

bool CheckCSBLayer::init() {
    if (!HNLayer::init()) {
        return false;
    }

    //setContentSize(WIN_SIZE);
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    //listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(CheckCSBLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(CheckCSBLayer::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(CheckCSBLayer::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto color = LayerColor::create(Color4B::BLACK);
    addChild(color);

    readTxt();

    return true;
}

void CheckCSBLayer::readTxt() {
    Data data = FileUtils::getInstance()->getDataFromFile("csbfile.txt");

    unsigned char*  pBuffer = data.getBytes();
    std::string tmp = StringUtils::format("%s", pBuffer);
    checkName(tmp);

    std::vector<string> infos;
    string delim = "\n";
    split(tmp, delim, infos);

    int height = 0;
    int offset = WIN_SIZE.height;
    for (int i = 0; i < infos.size(); i++) {
        std::string tmp = infos[i];

        if (tmp.compare("")!=0) {
            if (FileUtils::getInstance()->isFileExist(tmp)) {
                auto csb = CSLoader::createNode(tmp);

                if (csb) {
                    csb->setContentSize(WIN_SIZE);
                    csb->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
                    csb->setPosition(Vec2(WIN_SIZE.width / 2, height + offset));
                    addChild(csb);
                    list.push_back(csb);

                    height += csb->getContentSize().height + offset ;

                    auto label = Label::createWithTTF(tmp, DEFAULT_FONT, FONT_SIZE_15);
                    label->setPosition(csb->getPosition());
                    label->setOpacity(200);
                    addChild(label);
                    intros.push_back(label);
                }
            }
        }
    }
}

void CheckCSBLayer::checkName(string& name) {
    std::string::size_type startPos = 0;
    while (startPos!=std::string::npos) {
        startPos = name.find('\\');
        if (startPos!=std::string::npos) {
            name.replace(startPos, 1, "/");
        }
    }
}

bool CheckCSBLayer::onTouchBegan(Touch *touch, Event *unused_event) {
    beginPostion = touch->getLocation();
    //  HNLog::logInfo("down %f/%f", beginPostion.x, beginPostion.y);
    return true;
}

void CheckCSBLayer::onTouchMoved(Touch *touch, Event *unused_event) {
    isMoved = true;
    //
    Vec2 movedPosition = touch->getLocation();
    int offy = movedPosition.y - beginPostion.y;
    int offx = movedPosition.x - beginPostion.x;

    vector<Node *>::iterator textureIter;
    for (textureIter = list.begin(); textureIter != list.end(); textureIter++) {
        Node *tmp = *textureIter;
        tmp->setPositionY(tmp->getPositionY() + offy);
        tmp->setPositionX(tmp->getPositionX() + offx);
    }
    //
    vector<Label *>::iterator labelIter;
    for (labelIter = intros.begin(); labelIter != intros.end(); labelIter++) {
        Label *tmp = *labelIter;
        tmp->setPositionY(tmp->getPositionY() + offy);
        tmp->setPositionX(tmp->getPositionX() + offx);
    }

    beginPostion = movedPosition;
}

void CheckCSBLayer::onTouchEnded(Touch *touch, Event *unused_event) {
    beginPostion = Vec2::ZERO;
    //
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
            this->removeFromParent();
            downCount = 0;
            upCount = 0;
        }
    }
    isMoved = false;
}

//注意：当字符串为空时，也会返回一个空字符串
void CheckCSBLayer::split(std::string &s, std::string &delim,
                          std::vector<std::string> &ret) {
    size_t last = 0;
    size_t index = s.find_first_of(delim, last);
    while (index != std::string::npos) {
        ret.push_back(s.substr(last, index - last));
        last = index + 1;
        index = s.find_first_of(delim, last);
    }
    if (index - last > 0) {
        ret.push_back(s.substr(last, index - last));
    }
}

//
//  std::string buffer;
//  char buftmp[4096];
//
//  unsigned int count = 0;
//  unsigned int totalBytes = 0;

//    for( auto it = _textures.begin(); it != _textures.end(); ++it ) {
//
//        memset(buftmp,0,sizeof(buftmp));
//
//
//        Texture2D* tex = it->second;
//        unsigned int bpp = tex->getBitsPerPixelForFormat();
//        // Each texture takes up width * height * bytesPerPixel bytes.
//        auto bytes = tex->getPixelsWide() * tex->getPixelsHigh() * bpp / 8;
//        totalBytes += bytes;
//        count++;
//        snprintf(buftmp,sizeof(buftmp)-1,"\"%s\" rc=%lu id=%lu %lu x %lu @
//        %ld bpp => %lu KB\n",
//                 it->first.c_str(),
//                 (long)tex->getReferenceCount(),
//                 (long)tex->getName(),
//                 (long)tex->getPixelsWide(),
//                 (long)tex->getPixelsHigh(),
//                 (long)bpp,
//                 (long)bytes / 1024);
//
//        buffer += buftmp;
//    }
//
//    snprintf(buftmp, sizeof(buftmp)-1, "TextureCache dumpDebugInfo: %ld
//    textures, for %lu KB (%.2f MB)\n", (long)count, (long)totalBytes / 1024,
//    totalBytes / (1024.0f*1024.0f));
//    buffer += buftmp;