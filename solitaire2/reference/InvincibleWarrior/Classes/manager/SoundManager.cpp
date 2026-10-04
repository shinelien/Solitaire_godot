# include "SoundManager.h"
#include "GameViewHD.hpp"


#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

SoundManager * SoundManager::soundManager = nullptr;

SoundManager::SoundManager()
{
    //初始为0。禁止播放背景音效
    //effectBgVolume = 0;
}

SoundManager * SoundManager::getInstance()
{
	if (soundManager == nullptr)
	{
		soundManager = new SoundManager();
		soundManager->isPlayBg = false;
		soundManager->isPlayType = 0;
//        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
//        SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
        soundManager->volume = IS_MUSIC?1:0;
        soundManager->effectVolume = IS_SOUND?1:0;
        soundManager->effectBgVolume = IS_SOUND?1:0;
	}
	return soundManager;
}

void SoundManager::preloadEffect()
{
	AudioEngine::preload(EffectCoin);
	AudioEngine::preload(EffectShuffle);
	AudioEngine::preload(EffectMovePoker);
	AudioEngine::preload(EffectMovePoker0);
	AudioEngine::preload(EffectCover);
    AudioEngine::preload(EffectCover1);
    AudioEngine::preload(EffectCover2);
	AudioEngine::preload(EffectNoMoreMove);
	AudioEngine::preload(EffectUndo);
	AudioEngine::preload(EffectAutoplay);
    AudioEngine::preload(EffectAuto);
	AudioEngine::preload(EffectVictory);
    AudioEngine::preload(EffectVictoryAuto);
    AudioEngine::preload(EffectCrownUp);
    AudioEngine::preload(EffectThrophy);
    AudioEngine::preload(EffectCrown);
    AudioEngine::preload(EffectMagic0);
    AudioEngine::preload(EffectTask);
    AudioEngine::preload(EffectGetStar);
    AudioEngine::preload(EffectButtonStart);
    AudioEngine::preload(EffectGetCoin);
    AudioEngine::preload(EffectCashregister);
    AudioEngine::preload(EffectGetAll);
    AudioEngine::preload(EffectGetFly);
    AudioEngine::preload(EffectGetGem);
    AudioEngine::preload(EffectGetWin);
    AudioEngine::preload(EffectLevelup);
    AudioEngine::preload(EffectBoxOpen);
    AudioEngine::preload(EffectBuild);
    
    AudioEngine::preload(EffectA);
    AudioEngine::preload(EffectB);
    AudioEngine::preload(EffectC);
    AudioEngine::preload(EffectD);
    AudioEngine::preload(EffectE);
    AudioEngine::preload(EffectF);
    AudioEngine::preload(EffectG);
    AudioEngine::preload(EffectH);
    AudioEngine::preload(EffectI);
    AudioEngine::preload(EffectJ);
    AudioEngine::preload(EffectK);
    AudioEngine::preload(EffectL);
    AudioEngine::preload(EffectM);
    AudioEngine::preload(EffectN);
    AudioEngine::preload(EffectO);
    AudioEngine::preload(EffectP);
    AudioEngine::preload(EffectQ);
    AudioEngine::preload(EffectR);
    AudioEngine::preload(EffectS);
    AudioEngine::preload(EffectT);
    AudioEngine::preload(EffectU);
    AudioEngine::preload(EffectV);
    AudioEngine::preload(EffectW);
    AudioEngine::preload(EffectX);
    AudioEngine::preload(EffectY);
    AudioEngine::preload(EffectZ);
    
    for (auto i=1;i<=10;i++) {
        AudioEngine::preload(StringUtils::format(EffectScore.c_str(), i).c_str());
    }
}

//播放背景音效
static int MusicID = -1;
void SoundManager::playGameBgMusic(const std::string &audioFileName, bool loop)
{
//    if (IS_MUSIC)
//    {
        stopGameBgMusic();
        MusicID = playMusic2d(audioFileName, loop);
//    }
}

void SoundManager::stopGameBgMusic()
{
    if (MusicID != -1) {
        AudioEngine::stop(MusicID);
    }
}

//恢复播放背景音效
void SoundManager::resumeGameBgMusic()
{
    volume = 1;
    for (auto &it: _musicsDict) {
        AudioEngine::setVolume(it.first, volume);
    }
}

//停止播放背景音效
void SoundManager::pauseGameBgMusic()
{
    volume = 0;
    for (auto &it: _musicsDict) {
        //筛选出音乐暂停
        AudioEngine::setVolume(it.first, volume);
    }
}

//恢复播放背景音效
void SoundManager::resumeGameBgEffect()
{
    effectVolume = 1;
    for (auto &it: _soundsDict) {
        AudioEngine::setVolume(it.first, effectVolume);
    }
}

//停止播放背景音效
void SoundManager::pauseGameBgEffect()
{
    
    effectVolume = 0;
    for (auto &it: _soundsDict) {
        //筛选出音乐暂停
        AudioEngine::setVolume(it.first, effectVolume);
        CCLOG("pauseGameBgEffect play effectid:%d_pause(%d)", it.first, effectVolume);
    }
}

//恢复播放背景音效
void SoundManager::resumeDTEffect()
{
    effectBgVolume = 1;
    if(gameEffectId != -1)
    {
        auto id = _soundsDict.at(gameEffectId);
        AudioEngine::setVolume(id, effectVolume == 1&&effectBgVolume==1?1:0);
    }
    
    
}

//停止播放背景音效
void SoundManager::pauseDTEffect()
{
    effectBgVolume = 0;
    if(gameEffectId != -1)
    {
        auto id = _soundsDict.at(gameEffectId);
        AudioEngine::setVolume(id, effectVolume == 1&&effectBgVolume==1?1:0);
    }
}

void SoundManager::stopDTEffect()
{
    if(gameEffectId != -1)
    {
        auto id = _soundsDict.at(gameEffectId);
        AudioEngine::stop(id);
    }
    
}


//按钮点击音效
void SoundManager::playBtnClickAudio()
{
//	if (IS_SOUND)
//	{
        play2d(EffectMovePoker);
//	}
}

unsigned int SoundManager::playEffectMusic(const std::string &audioFileName, bool loopp)
{
//	if (IS_SOUND)
//	{
        CCLOG("[AudioEngine] play effect:%s_loop(%d)", audioFileName.c_str(), loopp);
		return play2d(audioFileName, loopp);
//	}
    return -1;
}

void SoundManager::stopEffectMusic(unsigned int effectID)
{
    AudioEngine::stop(effectID);
}

void SoundManager::stopAllEffectMusic()
{
//	if (IS_MUSIC)
//	{
        AudioEngine::stopAll();
//	}
}

int SoundManager::play2d(const std::string &audioFileName, bool loop)
{
    if(loop&&audioFileName.find("Ambient/scene") == string::npos)
    {
        return playMusic2d(audioFileName,loop);
    }
    else
    {
        int id;

        if(audioFileName.find("Ambient/scene") != string::npos)
        {
            id = AudioEngine::play2d(audioFileName, loop, effectBgVolume);
            if(gameEffectId != -1)
            {
                _soundsDict.erase(gameEffectId);
                AudioEngine::stop(gameEffectId);
            }
            
            gameEffectId = id;
        }
        else
        {
            id = AudioEngine::play2d(audioFileName, loop, effectVolume);
        }
        
        _soundsDict[id] = id;
        AudioEngine::setFinishCallback(id, [this](int finishId, const std::string &){
            if(gameEffectId != finishId)
            _soundsDict.erase(finishId);
        });
        return id;
    }
}

int SoundManager::playMusic2d(const std::string &audioFileName, bool loop)
{
    _musicsDict.clear();
    auto id = AudioEngine::play2d(audioFileName, loop, volume);
    _musicsDict[id] = id;
    AudioEngine::setFinishCallback(id, [this](int finishId, const std::string &){
        
    });
    return id;
}

void SoundManager::setEffectVolume(int _effectVolume)
{
    effectVolume = _effectVolume;
    if(_effectVolume == 1)
    {
        resumeDTEffect();
    }
    else
    {
        pauseDTEffect();
    }
}

void SoundManager::playTextEffect(char c)
{
    switch (c) {
        case 'a':
        case 'A':
        {
            playEffectMusic(EffectA);
        }
            break;
        case 'b':
        case 'B':
        {
            playEffectMusic(EffectB);
        }
            break;
        case 'c':
        case 'C':
        {
            playEffectMusic(EffectC);
        }
            break;
        case 'd':
        case 'D':
        {
            playEffectMusic(EffectD);
        }
            break;
            
        case 'e':
        case 'E':
        {
            playEffectMusic(EffectE);
        }
            break;
        case 'f':
        case 'F':
        {
            playEffectMusic(EffectF);
        }
            break;
        case 'g':
        case 'G':
        {
            playEffectMusic(EffectG);
        }
            break;
        case 'h':
        case 'H':
        {
            playEffectMusic(EffectH);
        }
            break;
        case 'i':
        case 'I':
        {
            playEffectMusic(EffectI);
        }
            break;
        case 'j':
        case 'J':
        {
            playEffectMusic(EffectJ);
        }
            break;
        case 'k':
        case 'K':
        {
            playEffectMusic(EffectK);
        }
            break;
        case 'l':
        case 'L':
        {
            playEffectMusic(EffectL);
        }
            break;
        case 'm':
        case 'M':
        {
            playEffectMusic(EffectM);
        }
            break;
        case 'n':
        case 'N':
        {
            playEffectMusic(EffectN);
        }
            break;
        case 'o':
        case 'O':
        {
            playEffectMusic(EffectO);
        }
            break;
        case 'p':
        case 'P':
        {
            playEffectMusic(EffectP);
        }
            break;
        case 'q':
        case 'Q':
        {
            playEffectMusic(EffectQ);
        }
            break;
        case 'r':
        case 'R':
        {
            playEffectMusic(EffectR);
        }
            break;
        case 's':
        case 'S':
        {
            playEffectMusic(EffectS);
        }
            break;
        case 't':
        case 'T':
        {
            playEffectMusic(EffectT);
        }
            break;
        case 'u':
        case 'U':
        {
            playEffectMusic(EffectU);
        }
            break;
        case 'v':
        case 'V':
        {
            playEffectMusic(EffectV);
        }
            break;
        case 'w':
        case 'W':
        {
            playEffectMusic(EffectW);
        }
            break;
            
        case 'x':
        case 'X':
        {
            playEffectMusic(EffectX);
        }
            break;
        case 'y':
        case 'Y':
        {
            playEffectMusic(EffectY);
        }
            break;
        case 'z':
        case 'Z':
        {
            playEffectMusic(EffectZ);
        }
            break;
        default:
            break;
    }
}
