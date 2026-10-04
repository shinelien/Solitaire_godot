//
//  DBManager.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/6/29.
//

#ifndef DBManager_h
#define DBManager_h


#define DB_M DBManager::getInstance()

class DBManager
{
public:
    ~DBManager();
    static DBManager* getInstance();
    
    std::string getPlayerName();
    void getRank(std::string p);
    void queryMe();
    
    std::string getMe() { return _me; }
    
    int getP1() { return _p1; }
    int getP2() { return _p2; }
    long getDailyKeyTs() { return _dailyKeyTs; }
    
    void setUser(int p1, int p2, int playerLv, int fashTankIdx,std::string name);
private:
    DBManager();
    static DBManager* _DBManager;
    std::string _dailyKey,_uuid,_me;
    long _dailyKeyTs;
    vector<vector<std::string>> nameVec;
    int _p1,_p2;
};

#endif /* DBManager_h */
