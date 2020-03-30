#pragma once
#include <array>
#include <cstdint>
#include <exception>
#include "proc6502.h"
#include <iostream>

class Bus
{
public:
	Bus();
	~Bus() = default;

	proc6502 cpu;
	std::array<std::uint8_t, 64 * 1024> ram;

	void write(std::uint16_t, std::uint8_t);
	std::uint8_t read(std::uint16_t);

};
