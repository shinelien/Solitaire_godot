/*
	音效管理器
	author:codehua
	time:2016年9月2日00:33:26
*/

# ifndef __SOUND_MANAGER__
# define __SOUND_MANAGER__

# include "cocos2d.h"
# include "UIUtils.h"
# include "DataManager.h"

# define SOUND_M SoundManager::getInstance()
//find . -type f -name '*.mp3' -exec bash -c 'ffmpeg -i "$0" -ab 128k -ar 44100 -acodec aac -y -strict -2 -q:a 4 "${0/%mp3/aac}"' '{}' \;
//find . -type f -name '*.mp3' -exec bash -c 'ffmpeg -i "$0" -ab 128k -ar 44100 -acodec libvorbis -y -strict -2 -q:a 4 "${0/%mp3/ogg}"' '{}' \;

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#define EffectPrefix ".ogg"
//#else
#define EffectPrefix ".mp3"
//#endif

static const auto EffectCoin = std::string("coin") + EffectPrefix;
static const auto EffectShuffle = std::string("shuffle") + EffectPrefix;
static const auto EffectMovePoker = std::string("movecard") + EffectPrefix;
static const auto EffectMovePoker0 = std::string("movecard0") + EffectPrefix;
static const auto EffectCover = std::string("Cover0") + EffectPrefix;
static const auto EffectCover1 = std::string("Cover1") + EffectPrefix;
static const auto EffectCover2 = std::string("Cover2") + EffectPrefix;
static const auto EffectNoMoreMove = std::string("nomove") + EffectPrefix;
static const auto EffectUndo = std::string("undo") + EffectPrefix;
static const auto EffectAutoplay = std::string("autoplay") + EffectPrefix;
static const auto EffectAuto = std::string("auto") + EffectPrefix;
static const auto EffectVictory = std::string("victory") + EffectPrefix;
static const auto EffectVictoryAuto = std::string("auto_victory") + EffectPrefix;
static const auto EffectCrownUp = std::string("Crown_up1") + EffectPrefix;
static const auto EffectThrophy = std::string("Trophy_1") + EffectPrefix;
static const auto EffectCrown = std::string("Crown_1") + EffectPrefix;
static const auto EffectMagic0 = std::string("Magic0") + EffectPrefix;
static const auto EffectTask = std::string("task") + EffectPrefix;
static const auto EffectGetStar = std::string("Get_star") + EffectPrefix;
static const auto EffectButtonStart = std::string("button_start") + EffectPrefix;
static const auto EffectGetCoin = std::string("Get_coin") + EffectPrefix;
static const auto EffectCashregister = std::string("cashregister") + EffectPrefix;
static const auto EffectGetAll = std::string("Get_all") + EffectPrefix;
static const auto EffectGetFly = std::string("Get_fly") + EffectPrefix;
static const auto EffectGetGem = std::string("Get_Gem") + EffectPrefix;
static const auto EffectGetWin = std::string("Get_win") + EffectPrefix;
static const auto EffectLevelup = std::string("Levelup") + EffectPrefix;
static const auto EffectBoxOpen = std::string("boxopen") + EffectPrefix;
static const auto EffectBuild =  std::string("build") + EffectPrefix;
static const auto EffectScore =  std::string("score%d") + EffectPrefix;
static const auto BGM =  std::string("bgm%d") + EffectPrefix;

//字母语音A-Z
static const auto EffectA =  std::string("yuyin/A") + EffectPrefix;
static const auto EffectB =  std::string("yuyin/B") + EffectPrefix;
static const auto EffectC =  std::string("yuyin/C") + EffectPrefix;
static const auto EffectD =  std::string("yuyin/D") + EffectPrefix;
static const auto EffectE =  std::string("yuyin/E") + EffectPrefix;
static const auto EffectF =  std::string("yuyin/F") + EffectPrefix;
static const auto EffectG =  std::string("yuyin/G") + EffectPrefix;
static const auto EffectH =  std::string("yuyin/H") + EffectPrefix;
static const auto EffectI =  std::string("yuyin/I") + EffectPrefix;
static const auto EffectJ =  std::string("yuyin/G") + EffectPrefix;
static const auto EffectK =  std::string("yuyin/K") + EffectPrefix;
static const auto EffectL =  std::string("yuyin/L") + EffectPrefix;
static const auto EffectM =  std::string("yuyin/M") + EffectPrefix;
static const auto EffectN =  std::string("yuyin/N") + EffectPrefix;
static const auto EffectO =  std::string("yuyin/O") + EffectPrefix;
static const auto EffectP =  std::string("yuyin/P") + EffectPrefix;
static const auto EffectQ =  std::string("yuyin/Q") + EffectPrefix;
static const auto EffectR =  std::string("yuyin/R") + EffectPrefix;
static const auto EffectS =  std::string("yuyin/S") + EffectPrefix;
static const auto EffectT =  std::string("yuyin/T") + EffectPrefix;
static const auto EffectU =  std::string("yuyin/U") + EffectPrefix;
static const auto EffectV =  std::string("yuyin/V") + EffectPrefix;
static const auto EffectW =  std::string("yuyin/W") + EffectPrefix;
static const auto EffectX =  std::string("yuyin/X") + EffectPrefix;
static const auto EffectY =  std::string("yuyin/Y") + EffectPrefix;
static const auto EffectZ =  std::string("yuyin/Z") + EffectPrefix;
USING_NS_CC;

class SoundManager : public Ref
{
public:
	static SoundManager * getInstance();

	void playGameBgMusic(const std::string &audioFileName, bool loop = true); //播放背景音效
    void stopGameBgMusic(); //停止背景音效
	void resumeGameBgMusic(); //恢复播放背景音效
	void pauseGameBgMusic(); //停止播放背景音效
    void resumeGameBgEffect(); //恢复播放音效
    void pauseGameBgEffect(); //停止播放音效
    void resumeDTEffect(); //恢复播放动态背景音效
    void pauseDTEffect(); //停止播放动态背景音效
    void stopDTEffect();//移除
	void playBtnClickAudio();//按钮点击音效

    unsigned int playEffectMusic(const std::string &audioFileName, bool loopp = false);	//其他音效
    void stopEffectMusic(unsigned int effectID);
	void stopAllEffectMusic();
    
	void preloadEffect();
    void setEffectVolume(int _effectVolume);
    
    void playTextEffect(char c);
private:
    int play2d(const std::string &audioFileName, bool loop = false);
    int playMusic2d(const std::string &audioFileName, bool loop = false);
	SoundManager();
	static SoundManager * soundManager;

	bool isPlayBg;
	int isPlayType, volume = 1, effectVolume,effectBgVolume = 1;//背景音乐类型
    std::unordered_map<int, int> _soundsDict;
    std::unordered_map<int, int> _musicsDict;
    int gameEffectId = -1;
};

# endif
