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
	void ReSet()
	{
		while (!m_record.empty())
		{
			m_record.pop();
		}
	}
private:
	std::queue<MoveData> m_record;
};