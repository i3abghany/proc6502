#include "Bus.h"

Bus::Bus()
{
	this->ram = std::array<std::uint8_t, 64 * 1024>();
	this->ram.fill(0x00);
	
	cpu.ConnectBus(this);
}

std::uint8_t Bus::read(std::uint16_t addr, bool readOnly)
{
	if (addr <= 0x0000 || addr >= 0xFFFF)
	{
		throw std::range_error("Access address is not right.");
	}
	return this->ram[addr];
}

void Bus::write(std::uint16_t addr, std::uint8_t data)
{
	if (addr <= 0x0000 || addr >= 0xFFFF)
	{
		throw std::range_error("Access address is not right.");
	}
	this->ram[addr] = data;
}