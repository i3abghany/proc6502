#include "proc6502.h"
#include "Bus.h"

proc6502::proc6502()
{
	using p = proc6502;
	this->InstructionLookupTable = std::vector<INSTRUCTION>
	{
		{ "BRK", &p::BRK, &p::IMM, 7 }, { "ORA", &p::ORA, &p::IZX, 6 }, { "???", &p::XXX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 8 }, { "???", &p::NOP, &p::IMP, 3 }, { "ORA", &p::ORA, &p::ZP0, 3 }, { "ASL", &p::ASL, &p::ZP0, 5 }, { "???", &p::XXX, &p::IMP, 5 }, { "PHP", &p::PHP, &p::IMP, 3 }, { "ORA", &p::ORA, &p::IMM, 2 }, { "ASL", &p::ASL, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 2 }, { "???", &p::NOP, &p::IMP, 4 }, { "ORA", &p::ORA, &p::ABS, 4 }, { "ASL", &p::ASL, &p::ABS, 6 }, { "???", &p::XXX, &p::IMP, 6 },
		{ "BPL", &p::BPL, &p::REL, 2 }, { "ORA", &p::ORA, &p::IZY, 5 }, { "???", &p::XXX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 8 }, { "???", &p::NOP, &p::IMP, 4 }, { "ORA", &p::ORA, &p::ZPX, 4 }, { "ASL", &p::ASL, &p::ZPX, 6 }, { "???", &p::XXX, &p::IMP, 6 }, { "CLC", &p::CLC, &p::IMP, 2 }, { "ORA", &p::ORA, &p::ABY, 4 }, { "???", &p::NOP, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 7 }, { "???", &p::NOP, &p::IMP, 4 }, { "ORA", &p::ORA, &p::ABX, 4 }, { "ASL", &p::ASL, &p::ABX, 7 }, { "???", &p::XXX, &p::IMP, 7 },
		{ "JSR", &p::JSR, &p::ABS, 6 }, { "AND", &p::AND, &p::IZX, 6 }, { "???", &p::XXX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 8 }, { "BIT", &p::BIT, &p::ZP0, 3 }, { "AND", &p::AND, &p::ZP0, 3 }, { "ROL", &p::ROL, &p::ZP0, 5 }, { "???", &p::XXX, &p::IMP, 5 }, { "PLP", &p::PLP, &p::IMP, 4 }, { "AND", &p::AND, &p::IMM, 2 }, { "ROL", &p::ROL, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 2 }, { "BIT", &p::BIT, &p::ABS, 4 }, { "AND", &p::AND, &p::ABS, 4 }, { "ROL", &p::ROL, &p::ABS, 6 }, { "???", &p::XXX, &p::IMP, 6 },
		{ "BMI", &p::BMI, &p::REL, 2 }, { "AND", &p::AND, &p::IZY, 5 }, { "???", &p::XXX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 8 }, { "???", &p::NOP, &p::IMP, 4 }, { "AND", &p::AND, &p::ZPX, 4 }, { "ROL", &p::ROL, &p::ZPX, 6 }, { "???", &p::XXX, &p::IMP, 6 }, { "SEC", &p::SEC, &p::IMP, 2 }, { "AND", &p::AND, &p::ABY, 4 }, { "???", &p::NOP, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 7 }, { "???", &p::NOP, &p::IMP, 4 }, { "AND", &p::AND, &p::ABX, 4 }, { "ROL", &p::ROL, &p::ABX, 7 }, { "???", &p::XXX, &p::IMP, 7 },
		{ "RTI", &p::RTI, &p::IMP, 6 }, { "EOR", &p::EOR, &p::IZX, 6 }, { "???", &p::XXX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 8 }, { "???", &p::NOP, &p::IMP, 3 }, { "EOR", &p::EOR, &p::ZP0, 3 }, { "LSR", &p::LSR, &p::ZP0, 5 }, { "???", &p::XXX, &p::IMP, 5 }, { "PHA", &p::PHA, &p::IMP, 3 }, { "EOR", &p::EOR, &p::IMM, 2 }, { "LSR", &p::LSR, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 2 }, { "JMP", &p::JMP, &p::ABS, 3 }, { "EOR", &p::EOR, &p::ABS, 4 }, { "LSR", &p::LSR, &p::ABS, 6 }, { "???", &p::XXX, &p::IMP, 6 },
		{ "BVC", &p::BVC, &p::REL, 2 }, { "EOR", &p::EOR, &p::IZY, 5 }, { "???", &p::XXX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 8 }, { "???", &p::NOP, &p::IMP, 4 }, { "EOR", &p::EOR, &p::ZPX, 4 }, { "LSR", &p::LSR, &p::ZPX, 6 }, { "???", &p::XXX, &p::IMP, 6 }, { "CLI", &p::CLI, &p::IMP, 2 }, { "EOR", &p::EOR, &p::ABY, 4 }, { "???", &p::NOP, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 7 }, { "???", &p::NOP, &p::IMP, 4 }, { "EOR", &p::EOR, &p::ABX, 4 }, { "LSR", &p::LSR, &p::ABX, 7 }, { "???", &p::XXX, &p::IMP, 7 },
		{ "RTS", &p::RTS, &p::IMP, 6 }, { "ADC", &p::ADC, &p::IZX, 6 }, { "???", &p::XXX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 8 }, { "???", &p::NOP, &p::IMP, 3 }, { "ADC", &p::ADC, &p::ZP0, 3 }, { "ROR", &p::ROR, &p::ZP0, 5 }, { "???", &p::XXX, &p::IMP, 5 }, { "PLA", &p::PLA, &p::IMP, 4 }, { "ADC", &p::ADC, &p::IMM, 2 }, { "ROR", &p::ROR, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 2 }, { "JMP", &p::JMP, &p::IND, 5 }, { "ADC", &p::ADC, &p::ABS, 4 }, { "ROR", &p::ROR, &p::ABS, 6 }, { "???", &p::XXX, &p::IMP, 6 },
		{ "BVS", &p::BVS, &p::REL, 2 }, { "ADC", &p::ADC, &p::IZY, 5 }, { "???", &p::XXX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 8 }, { "???", &p::NOP, &p::IMP, 4 }, { "ADC", &p::ADC, &p::ZPX, 4 }, { "ROR", &p::ROR, &p::ZPX, 6 }, { "???", &p::XXX, &p::IMP, 6 }, { "SEI", &p::SEI, &p::IMP, 2 }, { "ADC", &p::ADC, &p::ABY, 4 }, { "???", &p::NOP, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 7 }, { "???", &p::NOP, &p::IMP, 4 }, { "ADC", &p::ADC, &p::ABX, 4 }, { "ROR", &p::ROR, &p::ABX, 7 }, { "???", &p::XXX, &p::IMP, 7 },
		{ "???", &p::NOP, &p::IMP, 2 }, { "STA", &p::STA, &p::IZX, 6 }, { "???", &p::NOP, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 6 }, { "STY", &p::STY, &p::ZP0, 3 }, { "STA", &p::STA, &p::ZP0, 3 }, { "STX", &p::STX, &p::ZP0, 3 }, { "???", &p::XXX, &p::IMP, 3 }, { "DEY", &p::DEY, &p::IMP, 2 }, { "???", &p::NOP, &p::IMP, 2 }, { "TXA", &p::TXA, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 2 }, { "STY", &p::STY, &p::ABS, 4 }, { "STA", &p::STA, &p::ABS, 4 }, { "STX", &p::STX, &p::ABS, 4 }, { "???", &p::XXX, &p::IMP, 4 },
		{ "BCC", &p::BCC, &p::REL, 2 }, { "STA", &p::STA, &p::IZY, 6 }, { "???", &p::XXX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 6 }, { "STY", &p::STY, &p::ZPX, 4 }, { "STA", &p::STA, &p::ZPX, 4 }, { "STX", &p::STX, &p::ZPY, 4 }, { "???", &p::XXX, &p::IMP, 4 }, { "TYA", &p::TYA, &p::IMP, 2 }, { "STA", &p::STA, &p::ABY, 5 }, { "TXS", &p::TXS, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 5 }, { "???", &p::NOP, &p::IMP, 5 }, { "STA", &p::STA, &p::ABX, 5 }, { "???", &p::XXX, &p::IMP, 5 }, { "???", &p::XXX, &p::IMP, 5 },
		{ "LDY", &p::LDY, &p::IMM, 2 }, { "LDA", &p::LDA, &p::IZX, 6 }, { "LDX", &p::LDX, &p::IMM, 2 }, { "???", &p::XXX, &p::IMP, 6 }, { "LDY", &p::LDY, &p::ZP0, 3 }, { "LDA", &p::LDA, &p::ZP0, 3 }, { "LDX", &p::LDX, &p::ZP0, 3 }, { "???", &p::XXX, &p::IMP, 3 }, { "TAY", &p::TAY, &p::IMP, 2 }, { "LDA", &p::LDA, &p::IMM, 2 }, { "TAX", &p::TAX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 2 }, { "LDY", &p::LDY, &p::ABS, 4 }, { "LDA", &p::LDA, &p::ABS, 4 }, { "LDX", &p::LDX, &p::ABS, 4 }, { "???", &p::XXX, &p::IMP, 4 },
		{ "BCS", &p::BCS, &p::REL, 2 }, { "LDA", &p::LDA, &p::IZY, 5 }, { "???", &p::XXX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 5 }, { "LDY", &p::LDY, &p::ZPX, 4 }, { "LDA", &p::LDA, &p::ZPX, 4 }, { "LDX", &p::LDX, &p::ZPY, 4 }, { "???", &p::XXX, &p::IMP, 4 }, { "CLV", &p::CLV, &p::IMP, 2 }, { "LDA", &p::LDA, &p::ABY, 4 }, { "TSX", &p::TSX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 4 }, { "LDY", &p::LDY, &p::ABX, 4 }, { "LDA", &p::LDA, &p::ABX, 4 }, { "LDX", &p::LDX, &p::ABY, 4 }, { "???", &p::XXX, &p::IMP, 4 },
		{ "CPY", &p::CPY, &p::IMM, 2 }, { "CMP", &p::CMP, &p::IZX, 6 }, { "???", &p::NOP, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 8 }, { "CPY", &p::CPY, &p::ZP0, 3 }, { "CMP", &p::CMP, &p::ZP0, 3 }, { "DEC", &p::DEC, &p::ZP0, 5 }, { "???", &p::XXX, &p::IMP, 5 }, { "INY", &p::INY, &p::IMP, 2 }, { "CMP", &p::CMP, &p::IMM, 2 }, { "DEX", &p::DEX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 2 }, { "CPY", &p::CPY, &p::ABS, 4 }, { "CMP", &p::CMP, &p::ABS, 4 }, { "DEC", &p::DEC, &p::ABS, 6 }, { "???", &p::XXX, &p::IMP, 6 },
		{ "BNE", &p::BNE, &p::REL, 2 }, { "CMP", &p::CMP, &p::IZY, 5 }, { "???", &p::XXX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 8 }, { "???", &p::NOP, &p::IMP, 4 }, { "CMP", &p::CMP, &p::ZPX, 4 }, { "DEC", &p::DEC, &p::ZPX, 6 }, { "???", &p::XXX, &p::IMP, 6 }, { "CLD", &p::CLD, &p::IMP, 2 }, { "CMP", &p::CMP, &p::ABY, 4 }, { "NOP", &p::NOP, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 7 }, { "???", &p::NOP, &p::IMP, 4 }, { "CMP", &p::CMP, &p::ABX, 4 }, { "DEC", &p::DEC, &p::ABX, 7 }, { "???", &p::XXX, &p::IMP, 7 },
		{ "CPX", &p::CPX, &p::IMM, 2 }, { "SBC", &p::SBC, &p::IZX, 6 }, { "???", &p::NOP, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 8 }, { "CPX", &p::CPX, &p::ZP0, 3 }, { "SBC", &p::SBC, &p::ZP0, 3 }, { "INC", &p::INC, &p::ZP0, 5 }, { "???", &p::XXX, &p::IMP, 5 }, { "INX", &p::INX, &p::IMP, 2 }, { "SBC", &p::SBC, &p::IMM, 2 }, { "NOP", &p::NOP, &p::IMP, 2 }, { "???", &p::SBC, &p::IMP, 2 }, { "CPX", &p::CPX, &p::ABS, 4 }, { "SBC", &p::SBC, &p::ABS, 4 }, { "INC", &p::INC, &p::ABS, 6 }, { "???", &p::XXX, &p::IMP, 6 },
		{ "BEQ", &p::BEQ, &p::REL, 2 }, { "SBC", &p::SBC, &p::IZY, 5 }, { "???", &p::XXX, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 8 }, { "???", &p::NOP, &p::IMP, 4 }, { "SBC", &p::SBC, &p::ZPX, 4 }, { "INC", &p::INC, &p::ZPX, 6 }, { "???", &p::XXX, &p::IMP, 6 }, { "SED", &p::SED, &p::IMP, 2 }, { "SBC", &p::SBC, &p::ABY, 4 }, { "NOP", &p::NOP, &p::IMP, 2 }, { "???", &p::XXX, &p::IMP, 7 }, { "???", &p::NOP, &p::IMP, 4 }, { "SBC", &p::SBC, &p::ABX, 4 }, { "INC", &p::INC, &p::ABX, 7 }, { "???", &p::XXX, &p::IMP, 7 }
	};	
}

void proc6502::ConnectBus(Bus* b)

{
	this->bus = b;
}


std::uint8_t proc6502::read(std::uint16_t addr)
{
	return this->bus->read(addr, false);
}

void proc6502::write(std::uint16_t addr, std::uint8_t data)
{
	this->bus->ram[addr] = data;
}

void proc6502::clock()
{
	if (this->Cycles == 0)
	{
		this->OpCode = this->read(PCReg);
		++PCReg;
		this->Cycles = this->InstructionLookupTable[this->OpCode].Cycles;
		auto AdditionalClockCycles1 = (this->InstructionLookupTable[this->OpCode].AddressMode)(this);
		auto AdditionalClockCycles2 = (this->InstructionLookupTable[this->OpCode].Operation)(this);
		this->Cycles += (AdditionalClockCycles1 & AdditionalClockCycles2);
		
	}
	--this->Cycles;
}

std::uint8_t proc6502::GetFlag(proc6502::FLAGS6502 f)
{
	return ((this->STReg & f) > 0) ? 1 : 0;
}

void proc6502::SetFlag(proc6502::FLAGS6502 f, bool val)
{
	if (val)
	{
		this->STReg |= f;
	} 
	else
	{
		this->STReg &= ~f;
	}
}

// Addressing Modes

std::uint8_t proc6502::IMP()
{
	this->FetchedData = this->ACReg;
	return 0;
}

std::uint8_t proc6502::IMM()
{
	this->AbsoluteAddress = this->PCReg;
	++this->PCReg;
	return 0;
}

std::uint8_t proc6502::ZP0()
{
	this->AbsoluteAddress = this->read(PCReg);
	++this->PCReg;
	this->AbsoluteAddress &= 0x00FF;
	return 0;
}

std::uint8_t proc6502::ZPX()
{
	this->AbsoluteAddress = this->read(PCReg);
	this->AbsoluteAddress += this->XReg;
	++this->PCReg;
	this->AbsoluteAddress &= 0x00FF;
	return 0;
}

std::uint8_t proc6502::ZPY()
{
	this->AbsoluteAddress = this->read(PCReg);
	this->AbsoluteAddress += this->YReg;
	++this->PCReg;
	this->AbsoluteAddress &= 0x00FF;
	return 0;
}

std::uint8_t proc6502::REL()
{
	return std::uint8_t();
}

//Gets the address stored as two halves in the two
//words following the instruction opcode.
std::uint8_t proc6502::ABS()
{
	std::uint16_t lo = this->read(PCReg);
	++this->PCReg;

	std::uint16_t hi = this->read(PCReg);
	++this->PCReg;

	this->AbsoluteAddress = (hi << 8) | lo;
	return 0;
}

std::uint8_t proc6502::ABX()
{
	std::uint16_t lo = this->read(PCReg);
	++this->PCReg;

	std::uint16_t hi = this->read(PCReg);
	++this->PCReg;

	this->AbsoluteAddress = (hi << 8) | lo;
	this->AbsoluteAddress += this->XReg;

	if ((this->AbsoluteAddress & 0xFF00) != (hi << 8))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

std::uint8_t proc6502::ABY()
{
	std::uint16_t lo = this->read(PCReg);
	++this->PCReg;

	std::uint16_t hi = this->read(PCReg);
	++this->PCReg;

	this->AbsoluteAddress = (hi << 8) | lo;
	this->AbsoluteAddress += this->YReg;

	if ((this->AbsoluteAddress & 0xFF00) != (hi << 8))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

std::uint8_t proc6502::IND()
{
	std::uint16_t PtrLo = read(this->PCReg);
	++this->PCReg;

	std::uint16_t PtrHi = read(this->PCReg);
	++this->PCReg;

	std::uint16_t ptr = ((PtrHi << 8) | PtrLo);

	if (PtrLo == 0x00FF)
	{
		this->AbsoluteAddress = (read(ptr & 0xFF00) << 8) | (read(ptr + 0));
	}
	else
	{
		this->AbsoluteAddress = (read(ptr + 1) << 8) | (read(ptr + 0));
	}

	return 0;
}

std::uint8_t proc6502::IZX()
{
	std::uint16_t addr = this->read(this->PCReg);
	++this->PCReg;

	std::uint16_t lo = this->read(static_cast<std::uint16_t>(addr + this->XReg) & 0x00FF);
	std::uint16_t hi = this->read(static_cast<std::uint16_t>(addr + this->XReg + 1) & 0x00FF);
	this->AbsoluteAddress = (hi << 8) | lo;

	return 0;
}

std::uint8_t proc6502::IZY()
{
	std::uint16_t addr = this->read(this->PCReg);
	++this->PCReg;

	std::uint16_t lo = this->read(static_cast<std::uint16_t>(addr + this->YReg) & 0x00FF);
	std::uint16_t hi = this->read(static_cast<std::uint16_t>(addr + this->YReg + 1) & 0x00FF);

	return 0;
}


std::uint8_t proc6502::fetch()
{
	if (this->GetAddress(this->InstructionLookupTable[this->OpCode].AddressMode) != &this->IMP)
	{
		this->FetchedData = this->read(this->AbsoluteAddress);
	}
	return 0;
}


std::uint8_t proc6502::AND()
{
	this->fetch();
	this->ACReg = this->ACReg & this->FetchedData;

	this->SetFlag(proc6502::FLAGS6502::Z, this->ACReg == 0x00);
	this->SetFlag(proc6502::FLAGS6502::N, this->ACReg &  0x80);

	return 0;
}

std::uint8_t proc6502::ASL()
{
	this->fetch();
	this->TempReg = static_cast<std::uint16_t>(this->FetchedData) << 1;

	this->SetFlag(proc6502::FLAGS6502::C, (this->TempReg & 0xFF00) > 0);
	this->SetFlag(proc6502::FLAGS6502::N, (this->TempReg & 0x80));
	this->SetFlag(proc6502::FLAGS6502::Z, (this->TempReg & 0x00FF) == 0);

	if (this->GetAddress(this->InstructionLookupTable[OpCode].AddressMode) == &this->IMP)
	{
		this->ACReg = static_cast<std::uint8_t>(this->TempReg) & 0xFF;
	}
	else
	{
		this->write(this->AbsoluteAddress, static_cast<uint8_t>(this->TempReg));
	}
	return 0;
}

std::uint8_t proc6502::BCC()
{
	if (this->GetFlag(proc6502::FLAGS6502::C) == 0)
	{
		++this->Cycles;
		this->AbsoluteAddress = this->PCReg + this->RelativeAddress;

		if ((this->AbsoluteAddress & (0xFF00)) != (this->PCReg & (0xFF00)))
		{
			++this->Cycles;
		}
		this->PCReg = this->AbsoluteAddress;
	}
	return 0;
}

std::uint8_t proc6502::BCS()
{
	if (this->GetFlag(proc6502::FLAGS6502::C) == 1)
	{
		++this->Cycles;
		this->AbsoluteAddress = this->PCReg + this->RelativeAddress;

		if ((this->AbsoluteAddress & (0xFF00)) != (this->PCReg & (0xFF00)))
		{
			++this->Cycles;
		}
		this->PCReg = this->AbsoluteAddress;
	}
	return 0;
}

std::uint8_t proc6502::BEQ()
{
	if (this->GetFlag(proc6502::FLAGS6502::Z) == 1)
	{
		++this->Cycles;
		this->AbsoluteAddress = this->PCReg + this->RelativeAddress;

		if ((this->AbsoluteAddress & (0xFF00)) != (this->PCReg & (0xFF00)))
		{
			++this->Cycles;
		}
		this->PCReg = this->AbsoluteAddress;
	}
	return 0;

}

std::uint8_t proc6502::BNE()
{
	if (this->GetFlag(proc6502::FLAGS6502::Z) == 0)
	{
		++this->Cycles;
		this->AbsoluteAddress = this->PCReg + this->RelativeAddress;

		if ((this->AbsoluteAddress & 0xFF00) != (this->PCReg & 0xFF00))
			++this->Cycles;

		this->PCReg = this->AbsoluteAddress;
	}
	return 0;
}

std::uint8_t proc6502::BPL()
{
	if (this->GetFlag(proc6502::FLAGS6502::Z) == 1)
	{
		++this->Cycles;
		this->AbsoluteAddress = this->PCReg + this->RelativeAddress;

		if ((this->AbsoluteAddress & 0xFF00) != (this->PCReg & 0xFF00))
			++this->Cycles;

		this->PCReg = this->AbsoluteAddress;
	}
	return 0;
}

std::uint8_t proc6502::BVC()
{
	if (this->GetFlag(proc6502::FLAGS6502::V) == 0)
	{
		++this->Cycles;
		this->AbsoluteAddress = this->PCReg + this->RelativeAddress;

		if ((this->AbsoluteAddress & 0xFF00) != (this->PCReg & 0xFF00))
			++this->Cycles;

		this->PCReg = this->AbsoluteAddress;
	}
	return 0;
}

std::uint8_t proc6502::BVS()
{
	if (this->GetFlag(proc6502::FLAGS6502::V) == 1)
	{
		++this->Cycles;
		this->AbsoluteAddress = this->PCReg + this->RelativeAddress;

		if ((this->AbsoluteAddress & 0xFF00) != (this->PCReg & 0xFF00))
			++this->Cycles;

		this->PCReg = this->AbsoluteAddress;
	}
	return 0;
}

std::uint8_t proc6502::CLC()
{
	this->SetFlag(proc6502::FLAGS6502::C, false);
	return 0;
}

std::uint8_t proc6502::CLI()
{
	this->SetFlag(proc6502::FLAGS6502::I, false);
	return 0;
}

std::uint8_t proc6502::CLC()
{
	this->SetFlag(proc6502::FLAGS6502::C, false);
	return 0;
}

