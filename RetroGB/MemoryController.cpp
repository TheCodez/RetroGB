#include "MemoryController.h"
#include "Memory.h"
#include "Cartridge.h"


MemoryController::MemoryController(Memory* memory, Cartridge* cartridge)
    : memory(memory), cartridge(cartridge)
{
}

MemoryController::~MemoryController()
{
}

void MemoryController::Write(uint16 address, uint8 value)
{
    memory->Write(address, value);
}

uint8 MemoryController::Read(uint16 address) const
{
    return memory->Read(address);
}