#include "DAQPackets.h"

FreeDaqPacket::FreeDaqPacket() : CommandPacket()
{
	m_PID = CTOMasterToSlaveCommands::FREE_DAQ;
	m_Data = nullptr;
	m_DataLength = 0;
	m_PacketSize = 1;
}

FreeDaqPacket::~FreeDaqPacket()
{
}

//-----------------------------------------------------------------

AllocDaqPacket::AllocDaqPacket() : CommandPacket()
{
	m_PID = CTOMasterToSlaveCommands::ALLOC_DAQ;
	m_Data = new uint8_t[3];
	m_DataLength = 3;
	m_PacketSize = 4;
}

AllocDaqPacket::~AllocDaqPacket()
{
	delete[] m_Data;
	m_Data = nullptr;
}

void AllocDaqPacket::SetDaqCount(uint16_t DaqCount, bool LittleEndian)
{
	uint8_t t1, t2;
	t1 = DaqCount & 0xFF;
	t2 = (DaqCount >> 8) & 0xFF;

	if (LittleEndian)
	{
		m_Data[BytePositions::DAQ_COUNT] = t1;
		m_Data[BytePositions::DAQ_COUNT + 1] = t2;
	}
	else
	{
		m_Data[BytePositions::DAQ_COUNT] = t2;
		m_Data[BytePositions::DAQ_COUNT + 1] = t1;
	}
}

uint16_t AllocDaqPacket::GetDaqCount(bool LittleEndian)
{
	uint16_t Retval;
	uint16_t t1, t2;
	t1 = m_Data[BytePositions::DAQ_COUNT];
	t2 = m_Data[BytePositions::DAQ_COUNT + 1];

	if (LittleEndian)
	{
		Retval = (t2 << 8) | t1;
	}
	else
	{
		Retval = (t1 << 8) | t2;
	}

	return Retval;
}
