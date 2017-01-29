#include "CheckTextureLayer.h"
#include "UI/Base/ATableView.h"
#include "UI/Base/HNSprite.h"
#include <algorithm>
#include <string>
#include "tmp/FontSize.h"
#include "test/HNLog.h"

using namespace std;

CheckTextureLayer::CheckTextureLayer() : isMoved(false), downCount(0), upCount(0) {}

CheckTextureLayer::~CheckTextureLayer() {}

bool CheckTextureLayer::init() {
    if (!HNLayer::init()) {
        return false;
    }

    winSize = Director::getInstance()->getWinSize();
    //
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(CheckTextureLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(CheckTextureLayer::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(CheckTextureLayer::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //
    //string bg = "common/button1/5.png";
    //auto testBtn = AUIButton::create(bg, bg, bg);
    //testBtn->setPosition(Vec2(winSize.width / 2,
    //                          winSize.height - testBtn->getContentSize().height));
    //testBtn->setPressedActionEnabled(true);
    //testBtn->setEnabled(true);
    //addChild(testBtn);

    //createList();

    auto color = LayerColor::create(Color4B::BLACK);
    addChild(color);

    readTxt();

    return true;
}

void CheckTextureLayer::readTxt() {
    unsigned char* pBuffer = NULL;
    ssize_t bufferSize = 0;
    Data data = FileUtils::getInstance()->getDataFromFile("pvrfile.txt");

    std::vector<string> infos;
    string delim = "\n";
    int i = 0;

    pBuffer = data.getBytes();
    bufferSize = data.getSize();

    std::string tmp = StringUtils::format("%s", pBuffer);
    //tmp.replace();
    checkName(tmp);
    split(tmp, delim, infos);

    log("%ld", bufferSize);
    log("%s", pBuffer);

    int height = 0;
    int offset = 20;
    for (int i = 0; i < infos.size(); i++) {
        std::string tmp = infos[i];
        if (tmp.compare("")!=0) {

            if (FileUtils::getInstance()->isFileExist(tmp)) {
                auto sprite = Sprite::create(tmp);
                //
                if (sprite) {
                    sprite->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
                    sprite->setPosition(Vec2(0, height + offset));
                    addChild(sprite);
                    list.push_back(sprite);

                    height += sprite->getContentSize().height;

                    auto label = Label::createWithTTF(tmp, DEFAULT_FONT, FONT_SIZE_15);
                    label->setPosition(sprite->getPosition());
                    label->setOpacity(200);
                    addChild(label);
                    intros.push_back(label);
                }
            }
        }
    }
}

void CheckTextureLayer::checkName(string& name) {
    std::string::size_type startPos = 0;
    while (startPos!=std::string::npos) {
        startPos = name.find('\\');
        if (startPos!=std::string::npos) {
            name.replace(startPos, 1, "/");
        }
    }
}

bool CheckTextureLayer::onTouchBegan(Touch *touch, Event *unused_event) {
    beginPostion = touch->getLocation();
    //  HNLog::logInfo("down %f/%f", beginPostion.x, beginPostion.y);
    return true;
}

void CheckTextureLayer::onTouchMoved(Touch *touch, Event *unused_event) {
    isMoved = true;
    //
    Vec2 movedPosition = touch->getLocation();
    int offy = movedPosition.y - beginPostion.y;
    int offx = movedPosition.x - beginPostion.x;

    vector<Sprite *>::iterator textureIter;
    for (textureIter = list.begin(); textureIter != list.end(); textureIter++) {
        Sprite *tmp = *textureIter;
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

void CheckTextureLayer::onTouchEnded(Touch *touch, Event *unused_event) {
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

void CheckTextureLayer::createList() {
    TextureCache *cache = Director::getInstance()->getTextureCache();
    std::string cachedTextureInfo = cache->getCachedTextureInfo();
    HNLog::logInfo("description:%s", cachedTextureInfo.c_str());
    //
    std::vector<string> infos;
    string delim = "\"";
    split(cachedTextureInfo, delim, infos);

    vector<string>::iterator iter;
    for (iter = infos.begin(); iter != infos.end(); iter++) {
        string tmp = *iter;
        if (tmp.find("rc=") != -1 || tmp == "") {
            infos.erase(iter);
            iter--;
        }
    }
    //
    float baseWidth = 300.0f;

    int totalColumn = winSize.width / baseWidth;
    int totalRow = infos.size() / totalColumn + 1;

    for (int row = 0; row < totalRow; row++) {
        for (int column = 0; column < totalColumn; column++) {
            int startX = column * baseWidth;
            int endX = startX + baseWidth;

            int startY = row * baseWidth;
            int endY = startY + baseWidth;

            int index = column + row * totalColumn;
            //
            if (index > infos.size() - 1) {
                break;
            }

            std::string key = infos.at(index);

            string texture_name =
                key.substr(key.find_last_of("/") + 1, key.length() - 1);
            Texture2D *texture = cache->getTextureForKey(key);
            if (texture) {
                unsigned int totalBytes = 0;
                unsigned int bpp = texture->getBitsPerPixelForFormat();
                auto bytes =
                    texture->getPixelsWide() * texture->getPixelsHigh() * bpp / 8;
                totalBytes += bytes;
                //
                auto temp = HNSprite::createWithTexture(texture);
                float scale =
                    baseWidth / max(texture->getPixelsWide(), texture->getPixelsHigh());
                if (scale > 1.0f) {
                    scale = 1.0f;
                }
                temp->setScale(scale, scale);
                temp->setPosition(Vec2(startX + baseWidth / 2, startY + baseWidth / 2));
                addChild(temp);
                //
                auto label = Label::createWithTTF(
                                 StringUtils::format("%s rc=%d %d=%luKB\n", texture_name.c_str(),
                                                     texture->getReferenceCount(), bpp,
                                                     totalBytes / 1024),
                                 DEFAULT_FONT, FONT_SIZE_15);

                //          "%s rc=%d %lux%lu@%dbpp=>%luKB\n", texture_name.c_str(),
                //          texture->getReferenceCount(),
                //          (long)texture->getPixelsWide(),
                //          (long)texture->getPixelsHigh(), bpp, totalBytes / 1024

                label->setPosition(temp->getPosition());
                label->setOpacity(200);
                addChild(label);

                this->list.push_back(temp);
                this->intros.push_back(label);
            }
        }
    }

    //    CreateTableCellCallback callback =
    //        [&, infos](TableView *table, ssize_t idx) -> TableViewCell * {
    //      TableViewCell *Cell = table->dequeueCell();
    //      if (!Cell) {
    //        Cell = new TableViewCell();
    //        Cell->autorelease();
    //      }
    //      Cell->removeAllChildrenWithCleanup(false);
    //      //获取size的大小
    //      Size size = (dynamic_cast<ATableView
    //      *>(table))->cellSizeForTable(table);
    //
    //      TextureCache *cache = Director::getInstance()->getTextureCache();
    //
    //      std::string element = (infos).at(idx);
    //
    //      Texture2D *texture = cache->getTextureForKey(element);
    //      if (texture) {
    //        unsigned int totalBytes = 0;
    //        unsigned int bpp = texture->getBitsPerPixelForFormat();
    //        auto bytes =
    //            texture->getPixelsWide() * texture->getPixelsHigh() * bpp / 8;
    //        totalBytes += bytes;
    //
    //        auto temp = Sprite::createWithTexture(texture);
    //        float scale =
    //            baseWidth / max(texture->getPixelsWide(),
    //            texture->getPixelsHigh());
    //        temp->setScale(scale, scale);
    //        Cell->addChild(temp);
    //        this->list.push_back(temp);
    //
    //        HNLog::logInfo("rc=%d %lux%lu@%d bpp=>%lu KB\n",
    //                       texture->getReferenceCount(),
    //                       (long)texture->getPixelsWide(),
    //                       (long)texture->getPixelsHigh(), bpp, totalBytes /
    //                       1024);
    //      }
    //      return Cell;
    //    };
    //
    //    ATableView *tableView = ATableView::create(callback);
    //    tableView->setViewSize(winSize);
    //    tableView->setDirection(
    //        cocos2d::extension::ScrollView::Direction::VERTICAL);
    //    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    //    tableView->setTableCellSize(Size(200, 200));
    //    tableView->setNumberOfCellsInTableView(infos.size());
    //    tableView->reloadData();
    //    addChild(tableView);

    HNLog::logInfo("description:%s", Director::getInstance()
                   ->getTextureCache()
                   ->getCachedTextureInfo()
                   .c_str());
    //  }
}

void CheckTextureLayer::refreshList() {
    if (list.empty()) {
        return;
    }
    for (auto element : list) {
        this->removeChild(element);
    }
}

//注意：当字符串为空时，也会返回一个空字符串
void CheckTextureLayer::split(std::string &s, std::string &delim,
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