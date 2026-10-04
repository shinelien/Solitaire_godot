#ifndef __MOVEDATA_H__
#define __MOVEDATA_H__
# include "CardSprite.h"

//²Ù×÷ÀàÐÍ
enum MOVE_TYPE
{
	MType_Move_A_A, //ÒÆ¶¯   A-A K-A W-A A-K K-K W-K
	MType_Move_K_A,
	MType_Move_W_A,
	MType_Move_A_K,
	MType_Move_K_K,
	MType_Move_W_K,
	MType_Open,      //¿ªÅÆ  K
	MType_Shuffle,   //·¢ÅÆ  W
	MType_Reset,      //ÖØÖÃÅÆ
	MType_None
};

class MoveData : public Ref
{
public:
	MoveData(MOVE_TYPE m_moveType, int beginPosId, int endPosId, int beginCol, int endCol,int moveNum);
	MoveData(MOVE_TYPE m_moveType, int beginCol);
	MoveData(MOVE_TYPE m_moveType);
	static MoveData * createMoveDataByMove(int beginPosId, int endPosId, int beginCol, int endCol, int moveNum = 1);
	static MoveData * createMoveDataByOpen(int col);
	static MoveData * createMoveDataByShuffle(int moveNum = 1);/*移动数量代表牌数*/
	static MoveData * createMoveDataByReset();

	MOVE_TYPE m_moveType;

	int beginPosId;
	int endPosId;
	int beginCol;
	int endCol;
	int moveNum;
private:

};

#endif
