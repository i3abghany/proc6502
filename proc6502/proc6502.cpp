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

		this->SetFlag(proc6502::FLAGS6502::U, true);

		this->Cycles = this->InstructionLookupTable[this->OpCode].Cycles;
		
		auto AdditionalClockCycles1 = (this->*InstructionLookupTable[this->OpCode].AddressMode)();
		auto AdditionalClockCycles2 = (this->*InstructionLookupTable[this->OpCode].Operation)();
		
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
	if (this->InstructionLookupTable[this->OpCode].AddressMode != &proc6502::IMP)
	{
		this->FetchedData = this->read(this->AbsoluteAddress);
	}
	return 0;
}

std::uint8_t proc6502::ADC()
{
	this->fetch();

	this->TempReg = static_cast<uint16_t>(this->FetchedData) + static_cast<uint16_t>(this->ACReg) + this->GetFlag(proc6502::FLAGS6502::C);

	this->SetFlag(proc6502::FLAGS6502::C, this->TempReg > 0x00FF);
	this->SetFlag(proc6502::FLAGS6502::Z, this->TempReg == 0x0000);
	this->SetFlag(proc6502::FLAGS6502::N, this->TempReg & 0x0080);

	bool ResMSB = this->TempReg & 0x0080;
	bool FetchedMSB = this->FetchedData & 0x0080;
	bool AcMSB = this->ACReg & 0x0080;

	this->SetFlag(proc6502::FLAGS6502::V, (ResMSB ^ AcMSB) & ~(FetchedMSB ^ AcMSB));
	
	this->ACReg = this->TempReg & 0x00FF;

	return 1;
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

	if (this->InstructionLookupTable[OpCode].AddressMode == &proc6502::IMP)
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
	if (this->GetFlag(proc6502::FLAGS6502::N) == 0)
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

std::uint8_t proc6502::BMI()
{
	if (this->GetFlag(proc6502::FLAGS6502::N) == 1)
	{
		++this->Cycles;
		this->AbsoluteAddress = this->PCReg + this->RelativeAddress;

		if ((this->AbsoluteAddress & 0xFF00) != (this->PCReg & 0xFF00))
			++this->Cycles;

		this->PCReg = this->AbsoluteAddress;
	}
	return 0;
}

std::uint8_t proc6502::BIT()
{
	std::uint16_t AndedValue = this->ACReg & this->FetchedData;

	this->SetFlag(proc6502::FLAGS6502::N, this->FetchedData & (1 << 7));
	this->SetFlag(proc6502::FLAGS6502::V, this->FetchedData & (1 << 6));
	this->SetFlag(proc6502::FLAGS6502::Z, (AndedValue & 0x0000) == 0);

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

std::uint8_t proc6502::CLD()
{
	this->SetFlag(proc6502::FLAGS6502::D, false);
	return 0;
}

std::uint8_t proc6502::CLV()
{
	this->SetFlag(proc6502::FLAGS6502::V, false);
	return 0;
}

// Compare AC register with fetched data and set flags accordingly.
std::uint8_t proc6502::CMP()
{
	this->fetch();
	this->TempReg = static_cast<std::uint16_t>(this->ACReg) - static_cast<std::uint16_t>(this->FetchedData);
	
	this->SetFlag(proc6502::FLAGS6502::C, this->ACReg >= this->FetchedData);
	this->SetFlag(proc6502::FLAGS6502::Z, (this->TempReg & 0x00FF) == 0);
	this->SetFlag(proc6502::FLAGS6502::N, this->TempReg & 0x0080);

	return 0;
}
// Compare X register with fetched data and set flags accordingly.
std::uint8_t proc6502::CPX()
{
	this->fetch();
	this->TempReg = static_cast<std::uint16_t>(this->ACReg) - static_cast<std::uint16_t>(this->XReg);

	this->SetFlag(proc6502::FLAGS6502::C, this->YReg >= this->FetchedData);
	this->SetFlag(proc6502::FLAGS6502::Z, (this->TempReg & 0x00FF) == 0);
	this->SetFlag(proc6502::FLAGS6502::N, this->TempReg & 0x0080);

	return 0;
}

// Compare Y register with fetched data and set flags accordingly.
std::uint8_t proc6502::CPY()
{
	this->fetch();
	this->TempReg = static_cast<std::uint16_t>(this->YReg) - static_cast<std::uint16_t>(this->YReg);

	this->SetFlag(proc6502::FLAGS6502::C, this->YReg >= this->FetchedData);
	this->SetFlag(proc6502::FLAGS6502::Z, (this->TempReg & 0x00FF) == 0);
	this->SetFlag(proc6502::FLAGS6502::N, this->TempReg & 0x0080);

	return 0;
}


// Decrement at memory address.
// M[AbsoluteAddress] -= 1.
// Sets flags Z and N.
std::uint8_t proc6502::DEC()
{
	this->fetch();
	
	this->TempReg = static_cast<std::uint16_t>(this->FetchedData) - 1;

	this->write(this->AbsoluteAddress, this->TempReg & 0x00FF);

	this->SetFlag(proc6502::FLAGS6502::Z, this->TempReg == 0x0000);
	this->SetFlag(proc6502::FLAGS6502::N, this->TempReg & 0x0080);

	return 0;
}


// Decrement XReg.
// XReg = XReg - 1.
// Sets flags Z and N.
std::uint8_t proc6502::DEX()
{
	--this->XReg;

	this->SetFlag(proc6502::FLAGS6502::Z, this->XReg == 0x0000);
	this->SetFlag(proc6502::FLAGS6502::N, this->XReg & 0x0080);

	return 0;
}


// Decrement YReg.
// YReg = YReg - 1.
// Sets flags Z and N.
std::uint8_t proc6502::DEY()
{
	--this->XReg;

	this->SetFlag(proc6502::FLAGS6502::Z, this->YReg == 0x0000);
	this->SetFlag(proc6502::FLAGS6502::N, this->YReg & 0x0080);

	return 0;
}


// XOR AC register with the fetched data.
// AC = AC ^ FetchedData.
// Sets flags Z and N.
std::uint8_t proc6502::EOR()
{
	this->fetch();

	this->ACReg = this->ACReg ^ this->FetchedData;

	this->SetFlag(proc6502::FLAGS6502::Z, this->ACReg == 0x0000);
	this->SetFlag(proc6502::FLAGS6502::N, this->ACReg  & 0x0080);

	return 0;
}

// Increments value at memory.
// M[AbsoluteValue]++
// Sets flags N and Z.
std::uint8_t proc6502::INC()
{
	this->fetch();

	this->TempReg = static_cast<std::uint16_t>(this->FetchedData) + 1;

	this->write(this->AbsoluteAddress, this->TempReg & 0x00FF);

	this->SetFlag(proc6502::FLAGS6502::Z, this->TempReg == 0x0000);
	this->SetFlag(proc6502::FLAGS6502::N, this->TempReg & 0x0080);

	return 0;

}

// Increments value at XReg.
// XReg = XReg + 1
// Sets flags N and Z.
std::uint8_t proc6502::INX()
{
	this->XReg = (this->XReg) + 1;

	this->SetFlag(proc6502::FLAGS6502::Z, this->XReg == 0x0000);
	this->SetFlag(proc6502::FLAGS6502::N, this->XReg  & 0x0080);

	return 0;
}


// Increments value at YReg.
// YReg = YReg + 1
// Sets flags N and Z.
std::uint8_t proc6502::INY()
{
	this->YReg = (this->YReg) + 1;

	this->SetFlag(proc6502::FLAGS6502::Z, this->YReg == 0x0000);
	this->SetFlag(proc6502::FLAGS6502::N, this->YReg  & 0x0080);

	return 0;
}

// Jump unconditionally to address stored.
std::uint8_t proc6502::JMP()
{
	this->PCReg = this->AbsoluteAddress;
	return 0;
}

// Jump to sub routine address.
// Saves PC on the stack as two 8-bit halves.
std::uint8_t proc6502::JSR()
{
	--this->PCReg;
	
	this->write(this->StackStart + this->SPReg, (this->PCReg >> 8) & 0x00FF);
	--this->SPReg;

	this->write(this->StackStart + this->SPReg, (this->PCReg & 0x00FF));
	--this->SPReg;

	this->PCReg = this->AbsoluteAddress;

	return 0;
}

// Load data to the ACReg.
// Sets flags Z and N.
std::uint8_t proc6502::LDA()
{
	this->fetch();

	this->ACReg = this->FetchedData;
	
	this->SetFlag(proc6502::FLAGS6502::Z, this->ACReg == 0x00);
	this->SetFlag(proc6502::FLAGS6502::N, this->ACReg & 0x80);

	return 0;
}

// Load data to the XReg.
// Sets flags Z and N.
std::uint8_t proc6502::LDX()
{
	this->fetch();

	this->XReg = this->FetchedData;

	this->SetFlag(proc6502::FLAGS6502::Z, this->XReg == 0x00);
	this->SetFlag(proc6502::FLAGS6502::N, this->XReg & 0x80);

	return 0;
}

// Loads data to the YReg.
// Sets flags Z, N.
std::uint8_t proc6502::LDY()
{
	this->fetch();

	this->YReg = this->FetchedData;

	this->SetFlag(proc6502::FLAGS6502::Z, this->YReg == 0x00);
	this->SetFlag(proc6502::FLAGS6502::N, this->YReg & 0x80);

	return 0;
}

// Logical shift right.
// Sets flags C, Z, and N.
// it can be used with implied addressing mode
// it then will store the result in ACReg.
std::uint8_t proc6502::LSR()
{
	this->fetch();
	
	this->SetFlag(proc6502::FLAGS6502::C, this->FetchedData & 0x0001);
	
	this->TempReg = this->FetchedData >> 1;
	
	this->SetFlag(proc6502::FLAGS6502::Z, (this->TempReg & 0x00FF) == 0x0000);
	this->SetFlag(proc6502::FLAGS6502::N, this->TempReg == 0x0080);
	
	if (this->InstructionLookupTable[this->OpCode].AddressMode == &proc6502::IMP)
	{
		this->ACReg = static_cast<std::uint8_t>(this->TempReg & 0x00FF);
	}
	else
	{
		this->write(this->AbsoluteAddress, static_cast<std::uint8_t>(this->TempReg & 0x00FF));
	}
	
	return 0;
}


// OR fetched data from Memory with Accumulator
// ACReg |= FetchedData.
// Sets flags N and Z.
std::uint8_t proc6502::ORA()
{
	this->fetch();
	
	this->ACReg = this->ACReg | this->FetchedData;

	this->SetFlag(proc6502::FLAGS6502::Z, this->ACReg == 0x00);
	this->SetFlag(proc6502::FLAGS6502::N, this->ACReg & 0x80);

	return 1;
}

// Pushes accumulator to the stack.
std::uint8_t proc6502::PHA()
{
	this->write(this->StackStart + this->SPReg, this->ACReg);
	--this->SPReg;

	return 0;
}

// Pushes status register to the stack.
// Break flag is set before pushing.
std::uint8_t proc6502::PHP()
{
	this->STReg |= proc6502::FLAGS6502::B;
	this->STReg |= proc6502::FLAGS6502::U;

	this->write(this->StackStart + this->SPReg, this->STReg);

	this->SetFlag(proc6502::FLAGS6502::B, false);
	this->SetFlag(proc6502::FLAGS6502::U, false);

	--this->SPReg;

	return 0;
}


// Pop accumulator from the stack and set flags.
std::uint8_t proc6502::PLA()
{
	++this->SPReg;
	
	this->ACReg = this->read(this->StackStart + this->SPReg);
	
	this->SetFlag(proc6502::FLAGS6502::Z, this->ACReg == 0x00);
	this->SetFlag(proc6502::FLAGS6502::N, this->ACReg & 0x80);

	return 0;
}


// Pop status register from the stack.
std::uint8_t proc6502::PLP()
{
	++this->SPReg;

	this->STReg = this->read(this->StackStart + this->SPReg);
	
	this->SetFlag(proc6502::FLAGS6502::U, true);

	return 0;
}

// Rotates one bit to the left with carry flag.
// Sets N, C and Z flags.
std::uint8_t proc6502::ROL()
{
	this->fetch();
	
	this->TempReg = (this->FetchedData << 1) | this->GetFlag(proc6502::FLAGS6502::C);

	this->SetFlag(proc6502::FLAGS6502::N, this->TempReg & 0x0080);
	this->SetFlag(proc6502::FLAGS6502::C, this->TempReg & 0xFF00);
	this->SetFlag(proc6502::FLAGS6502::Z, (this->TempReg & 0x00FF) == 0);

	if (this->InstructionLookupTable[this->OpCode].AddressMode == &proc6502::IMP)
	{
		this->ACReg = static_cast<std::uint8_t>(this->TempReg & 0x00FF);
	}
	else
	{
		this->write(this->AbsoluteAddress, static_cast<std::uint8_t>(this->TempReg & 0x00FF));
	}
	return 0;
}

// Rotates one bit to the right with carry flag.
// Sets N, C and Z flags.
std::uint8_t proc6502::ROR()
{
	this->fetch();

	this->TempReg = (this->FetchedData >> 1) | (static_cast<std::uint16_t>(this->GetFlag(proc6502::FLAGS6502::C )) << 7);

	this->SetFlag(proc6502::FLAGS6502::N, this->TempReg & 0x0080);
	this->SetFlag(proc6502::FLAGS6502::C, this->FetchedData & 0x01);
	this->SetFlag(proc6502::FLAGS6502::Z, (this->TempReg & 0x00FF) == 0);

	if (this->InstructionLookupTable[this->OpCode].AddressMode == &proc6502::IMP)
	{
		this->ACReg = static_cast<std::uint8_t>(this->TempReg & 0x00FF);
	}
	else
	{
		this->write(this->AbsoluteAddress, static_cast<std::uint8_t>(this->TempReg & 0x00FF));
	}
	return 0;
}

std::uint8_t proc6502::RTI()
{
	++this->SPReg;
	this->STReg = this->read(this->StackStart + this->SPReg);

	this->SetFlag(proc6502::FLAGS6502::B, false);
	this->SetFlag(proc6502::FLAGS6502::U, false);

	++this->SPReg;
	this->PCReg = this->read(this->StackStart + this->SPReg);

	++this->SPReg;
	this->PCReg |= (this->read(this->StackStart + this->SPReg) << 8);

	return 0;
}

std::uint8_t proc6502::RTS()
{
	++this->SPReg;
	this->PCReg = this->read(this->StackStart + this->SPReg);

	++this->SPReg;
	this->PCReg |= (this->read(this->StackStart + this->SPReg) << 8);

	++this->PCReg;

	return 0;
}


std::uint8_t proc6502::SBC()
{
	this->fetch();

	std::uint16_t InvertedValue = this->FetchedData ^ 0x00FF;

	this->TempReg = InvertedValue + static_cast<uint16_t>(this->ACReg) + this->GetFlag(proc6502::FLAGS6502::C);

	this->SetFlag(proc6502::FLAGS6502::C, this->TempReg > 0x00FF);
	this->SetFlag(proc6502::FLAGS6502::Z, this->TempReg == 0x0000);
	this->SetFlag(proc6502::FLAGS6502::N, this->TempReg & 0x0080);

	bool ResMSB = this->TempReg & 0x0080;
	bool FetchedMSB = this->FetchedData & 0x0080;
	bool AcMSB = this->ACReg & 0x0080;

	this->SetFlag(proc6502::FLAGS6502::V, (ResMSB ^ AcMSB) & ~(FetchedMSB ^ AcMSB));

	this->ACReg = this->TempReg & 0x00FF;

	return 1;
}

std::uint8_t proc6502::SEC()
{
	this->SetFlag(proc6502::FLAGS6502::C, true);
	return 0;
}

std::uint8_t proc6502::SED()
{
	this->SetFlag(proc6502::FLAGS6502::D, true);
	return 0;
}

std::uint8_t proc6502::SEI()
{
	this->SetFlag(proc6502::FLAGS6502::I, true);
	return 0;
}


std::uint8_t proc6502::STA()
{
	this->write(this->AbsoluteAddress, this->ACReg);
	return 0;
}

std::uint8_t proc6502::STX()
{
	this->write(this->AbsoluteAddress, this->XReg);
	return 0;
}

std::uint8_t proc6502::STY()
{
	this->write(this->AbsoluteAddress, this->YReg);
	return 0;
}

std::uint8_t proc6502::TAX()
{
	this->XReg = this->ACReg;
	return 0;
}

std::uint8_t proc6502::TAY()
{
	this->YReg = this->ACReg;
	return 0;
}


