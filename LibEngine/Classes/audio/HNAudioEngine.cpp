//#include "stdafx.h"
#include "HNAudioEngine.h"
#include "audio/include/AudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d::experimental;

namespace HN {

static HNAudioEngine* instant = nullptr;

HNAudioEngine::HNAudioEngine() {
    _musicID = AudioEngine::INVALID_AUDIO_ID;
    _switchOfMusic = true;
    _switchOfEffect = true;
    _isPlayingMusic = false;
}

HNAudioEngine* HNAudioEngine::getInstance() {
    if (!instant) {
        instant = new HNAudioEngine();
    }
    return instant;
}

//播放音乐
void HNAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop) {
    if (_switchOfMusic) {
        if (nullptr != pszFilePath) {
            if (0 != _currentMusicName.compare(pszFilePath)) {
                _currentMusicName = pszFilePath;
                _musicID = AudioEngine::play2d(pszFilePath, bLoop);
                _isPlayingMusic = true;
            }
        }
    }
}

void HNAudioEngine::stopBackgroundMusic(bool bReleaseData) {
    if (_musicID == AudioEngine::INVALID_AUDIO_ID) {
        return;
    }
    AudioEngine::stop(_musicID);
    AudioEngine::uncache(_currentMusicName);
    _currentMusicName = "";
    _isPlayingMusic = false;
    _musicID = AudioEngine::INVALID_AUDIO_ID;
}

void HNAudioEngine::pauseBackgroundMusic() {
    if (!_isPlayingMusic) {
        return;
    }
    if (_musicID == AudioEngine::INVALID_AUDIO_ID) {
        return;
    }
    AudioEngine::pause(_musicID);
    _isPlayingMusic = false;
}

void HNAudioEngine::resumeBackgroundMusic() {
    if (_isPlayingMusic) {
        return;
    }
    if (_musicID == AudioEngine::INVALID_AUDIO_ID) {
        return;
    }
    AudioEngine::resume(_musicID);
    _isPlayingMusic = true;
}

bool HNAudioEngine::hasBackgroundMusic() {
    return (_musicID != AudioEngine::INVALID_AUDIO_ID);
}

//播放音效
unsigned int HNAudioEngine::playEffect(const char* pszFilePath, bool bLoop, float pitch, float pan, float gain) {
    if (_switchOfEffect) {
        int   _effectMusicID = AudioEngine::play2d(pszFilePath, bLoop);
        AudioEngine::setVolume(_effectMusicID, effectVolume);
        effectIDs.push_back(_effectMusicID);
        AudioEngine::setFinishCallback(_effectMusicID, [&](int audioID, const std::string &filePath) {
            std::vector<int>::iterator iter;
            for (iter = effectIDs.begin(); iter != effectIDs.end(); iter++) {
                if (*iter==audioID) {
                    effectIDs.erase(iter);
                    break;
                }
            }
        });
        return _effectMusicID;
    }
    return 0;
}

void HNAudioEngine::stopAllSound() {
    AudioEngine::stopAll();
    AudioEngine::end();
}

void HNAudioEngine::setSwitchOfMusic(bool isOpen) {
    _switchOfMusic = isOpen;
}

bool HNAudioEngine::getSwitchOfMusic() const {
    return _switchOfMusic;
}

void HNAudioEngine::setSwitchOfEffect(bool isOpen) {
    _switchOfEffect = isOpen;
}

bool HNAudioEngine::getSwitchOfEffect() const {
    return _switchOfEffect;
}


void HNAudioEngine::setEffectsVolume(float volume) {
    effectVolume = volume;
    std::vector<int>::iterator iter;
    for (iter = effectIDs.begin(); iter != effectIDs.end(); iter++) {
        AudioEngine::setVolume(*iter, volume);
    }
}

float HNAudioEngine::getEffectsVolume() const {
    return effectVolume;
}

void HNAudioEngine::setBackgroundMusicVolume(float volume) {
    AudioEngine::setVolume(_musicID, volume);
}

float HNAudioEngine::getBackgroundMusicVolume() const {
    return AudioEngine::getVolume(_musicID);
}

}
