#include "MoveData.h"

MoveData::MoveData(MOVE_TYPE m_moveType)
{
	this->m_moveType = m_moveType;
	this->beginPosId = 0;
	this->endPosId = 0;
	this->beginCol = 0;
	this->endCol = 0;
	this->moveNum = 1;
	//CCLOG("[SHUFFLE]");
}

MoveData::MoveData(MOVE_TYPE m_moveType, int beginPosId, int endPosId, int beginCol, int endCol, int moveNum)
{
	this->m_moveType = m_moveType;
	this->beginPosId = beginPosId;
	this->endPosId = endPosId;
	this->beginCol = beginCol;
	this->endCol = endCol;
	this->moveNum = moveNum;
}

MoveData::MoveData(MOVE_TYPE m_moveType, int beginCol)
{
	this->m_moveType = m_moveType;
	this->beginCol = beginCol;
	this->beginPosId = 0;
	this->endPosId = 0;
	this->endCol = 0;
	this->moveNum = 1;
	//CCLOG("[OPEN]: K(%d)", beginCol);
}

//操作类型
//enum MOVE_TYPE
//{
//	MType_Move_A_A, //移动   A-A K-A W-A A-K K-K W-K
//	MType_Move_K_A,
//	MType_Move_W_A,
//	MType_Move_A_K,
//	MType_Move_K_K,
//	MType_Move_W_K,
//	MType_Open,     //开牌  K
//	MType_Shuffle   //发牌  W
//};

MoveData * MoveData::createMoveDataByMove(int beginPosId, int endPosId, int beginCol, int endCol, int moveNum)
{
	MOVE_TYPE m_moveType;
	if (beginPosId == CARD_POS_K)
	{
		if (endPosId == CARD_POS_K)
		{
			//CCLOG("[MOVE]: K(%d) -> K(%d)", beginCol, endCol);
			m_moveType = MType_Move_K_K;
		}
		else if (endPosId == CARD_POS_A)
		{
			//CCLOG("[MOVE]: K(%d) -> A(%d)", beginCol, endCol);
			m_moveType = MType_Move_K_A;
		}
	}
	else if (beginPosId == CARD_POS_A)
	{
		if (endPosId == CARD_POS_K)
		{
			//CCLOG("[MOVE]: A(%d) -> K(%d)", beginCol, endCol);
			m_moveType = MType_Move_A_K;
		}
		else if (endPosId == CARD_POS_A)
		{
			//CCLOG("[MOVE]: A(%d) -> A(%d)", beginCol, endCol);
			m_moveType = MType_Move_A_A;
		}
	}
	else if (beginPosId == CARD_POS_WAIT_SHOW)
	{
		if (endPosId == CARD_POS_A)
		{
			m_moveType = MType_Move_W_A;
			//CCLOG("[MOVE]: W(%d) -> A(%d)", beginCol, endCol);
		}
		else if (endPosId == CARD_POS_K)
		{
			m_moveType = MType_Move_W_K;
			//CCLOG("[MOVE]: W(%d) -> K(%d)", beginCol, endCol);
		}
	}
	auto moveData = new MoveData(m_moveType, beginPosId, endPosId, beginCol, endCol, moveNum);
    moveData->autorelease();
	return moveData;
}

MoveData * MoveData::createMoveDataByOpen(int col)
{
	auto moveData = new MoveData(MType_Open,col);
    moveData->autorelease();
	return moveData;
}

MoveData * MoveData::createMoveDataByShuffle(int moveNum)
{
	auto moveData = new MoveData(MType_Shuffle, 0, 0, 0, 0, moveNum);
    moveData->autorelease();
	return moveData;
}

MoveData * MoveData::createMoveDataByReset()
{
	auto moveData = new MoveData(MType_Reset);
    moveData->autorelease();
	return moveData;
}
