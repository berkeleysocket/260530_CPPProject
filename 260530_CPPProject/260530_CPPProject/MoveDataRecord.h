#pragma once
#include"MoveData.h"
#include<queue>


class MoveDataRecord
{
public:
	void Record(const MoveData& data)
	{
		m_record.push(data);
	}
	const std::queue<MoveData>& GetRecord() const
	{
		return m_record;
	}
private:
	std::queue<MoveData> m_record;
};