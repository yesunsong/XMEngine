#ifndef _HN_AUDIO_ENGINE_
#define _HN_AUDIO_ENGINE_

#include <string>
#include <vector>

namespace HN {

class HNAudioEngine {
public:
    HNAudioEngine();
    static HNAudioEngine* getInstance();

public:
    //播放音乐
    void playBackgroundMusic(const char* pszFilePath, bool bLoop = true);
    //停止音乐
    void stopBackgroundMusic(bool bReleaseData = false);
    //暂停音乐
    void pauseBackgroundMusic();
    //重置音乐
    void resumeBackgroundMusic();
    //是否有音乐在播放
    bool hasBackgroundMusic();
    //播放音效
    unsigned int playEffect(const char* pszFilePath, bool bLoop = false, float pitch = 1.0f, float pan = 0.0f, float gain = 1.0f);
    //停止所有声音
    void stopAllSound();

    //设置音效音量[volume range from 0.0 to 1.0]
    void setEffectsVolume(float volume);
    //获得音效音量
    float getEffectsVolume() const;

    //设置音乐音量
    void setBackgroundMusicVolume(float volume);
    //获得音乐音量
    float getBackgroundMusicVolume() const;

    //设置音乐开关
    void setSwitchOfMusic(bool isOpen);
    //获取音乐开关与否
    bool getSwitchOfMusic() const;

    //设置音效开关
    void setSwitchOfEffect(bool isOpen);
    //获取音效开关与否
    bool getSwitchOfEffect() const;

private:
    //true设置音乐为开
    bool			_switchOfMusic;
    //ture设置音效为开
    bool			_switchOfEffect;
    //当前音乐名称
    std::string		_currentMusicName;
    //音乐ID
    int             _musicID;
    // 是否正在播放音乐
    bool            _isPlayingMusic;
    //音效音量
    float effectVolume;
    //音效id数组
    std::vector<int> effectIDs;
};
}
#endif 		//_HN_AUDIO_ENGINE_