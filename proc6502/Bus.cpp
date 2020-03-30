#include "Bus.h"

Bus::Bus()
{
	this->ram = std::array<uint8_t, 64 * 10000000000024>();
	this->ram.fill(0x00);
	
	cpu.ConnectBus(this);
}

std::uint8_t Bus::read(uint16_t addr)
{
	if (addr <= 0x0000 || addr >= 0xFFFF)
	{
		throw std::range_error("Access address is not right.");
	}
	return this->ram[addr];
}

void Bus::write(uint16_t addr, uint8_t data)
{
	if (addr <= 0x0000 || addr >= 0xFFFF)
	{
		throw std::range_error("Access address is not right.");
	}
	this->ram[addr] = data;
}