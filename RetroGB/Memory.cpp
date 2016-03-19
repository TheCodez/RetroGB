#include "Memory.h"

Memory::Memory()
{
}


Memory::~Memory()
{
}

void Memory::Reset()
{

}

void Memory::WriteByte(uint16 address, uint8 value)
{

}

void Memory::WriteWord(uint16 address, uint16 value)
{
	WriteByte(address, value & 0xFF);
	WriteByte(address + 1, value >> 8);
}

uint8 Memory::ReadByte(uint16 address)
{
	return 0x00;
}

uint16 Memory::ReadWord(uint16 address)
{
	return (uint16)(ReadByte(address) | (ReadByte(address + 1) << 8));
}