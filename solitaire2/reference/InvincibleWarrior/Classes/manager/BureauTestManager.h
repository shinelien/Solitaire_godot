//
//  BureauTestManager.h
//  NewSpaceCatSolitaire-mobile
//
//  Created by 陈 玉涛 on 2020/2/19.
//

#ifndef BureauTestManager_hpp
#define BureauTestManager_hpp

#include <cstdio>
#include "SqlCommon.h"
#include "SqlTable.h"
#include "SqlDatabase.h"
#include <external/json/document.h>
#include "cocos2d.h"

class Vec2Int {
public:
    int x, y;

    Vec2Int(int x, int y);
};

class BureauTestManager
{
public:
    static BureauTestManager *getInstance();
    cocos2d::ValueMap getBureauData(int steps = 50, int percent = 500);
    cocos2d::ValueMap getBureauData(const std::string &data);
    cocos2d::ValueMap getHardBureauData(int steps1, int steps2, int percent1, int percent2);
    int getHardBureauData(int percent1, int percent2);

	void moveFileToWriteablPath();
	void getXXXConfig();
private:
	BureauTestManager();
	virtual ~BureauTestManager();
    void init();
	
    static BureauTestManager *s_instance;
    std::shared_ptr<sql::Database> _db;
    std::shared_ptr<sql::Table> _dailyTb;
    std::shared_ptr<sql::Database> _db_o;
    std::unordered_map<int, std::shared_ptr<Vec2Int>> _bureauRangMap;
};

#endif /* BureauTestManager_hpp */
