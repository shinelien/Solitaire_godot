//
//  GameKitHelper.h
//  hm_solitaire
//
//  Created by mbp2 on 2018/11/5.
//

#ifndef GameKitHelper_h
#define GameKitHelper_h
#include <string>

class GameKitHelper {
public:
    static void setRootViewController(void* viewController);
    static int authPlayer();
    static void saveHighScore(const std::string &leaderBoardID, int value);
    static void downLoadGameCenter(const std::string &ID, int range=100, const std::string &zoneType = "all");
    static void showLeaderBoard();
    static void shareApp();
    static void writComment();
    static void openMail();
};

#endif /* GameKitHelper_h */



