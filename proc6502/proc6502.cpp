#include "proc6502.h"
#include "Bus.h"

proc6502::proc6502()
{
	using p = proc6502;
	InstructionLookupTable =
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
	bus = b;
}


uint8_t proc6502::read(uint16_t addr)
{
	return bus->read(addr);
}

void proc6502::write(uint16_t addr, uint8_t data)
{
	bus->write(addr, data);
}

std::string proc6502::hex(uint32_t n, uint32_t d)
{
	std::string res(d, '0');
	for (int i = d - 1; i >= 0; i--, n >>= 4)
	{
		res[i] = "0123456789ABCDEF"[n & 0xF];
	}
	return res;
}

std::map<uint16_t, std::string> proc6502::disassemble(const uint16_t start, const uint16_t stop)
{
	uint32_t addr = start;
	uint8_t value = 0x00, lo = 0x00, hi = 0x00;
	std::map<uint16_t, std::string> MapLines;
	uint16_t LineAddress = 0;

	for (; addr <= static_cast<uint32_t>(stop);)
	{
		LineAddress = addr;
		std::string StringInstruction = "$" + proc6502::hex(addr, 4) + ": ";
		uint8_t instruction = bus->read(addr);
		addr++;
		StringInstruction += InstructionLookupTable[instruction].name + " ";

		auto AddrMode = InstructionLookupTable[instruction].AddressMode;

		using p = proc6502;
		if (AddrMode == &p::IMP)
		{
			StringInstruction += " {IMP}";
		}
		else if (AddrMode == &p::IMM)
		{
			value = bus->read(addr);
			++addr;
			StringInstruction += "#$" + proc6502::hex(value, 2) + "{IMM}";
		}
		else if (AddrMode == &p::ZP0)
		{
			lo = bus->read(addr);
			++addr;
			hi = 0x00;
			StringInstruction += "$" + proc6502::hex(lo, 2) + " {ZP0}";
		}
		else if (AddrMode == &p::ZPX)
		{
			lo = bus->read(addr);
			++addr;
			hi = 0x00;
			StringInstruction += " X {ZPX}";
		}
		else if (AddrMode == &p::ZPY)
		{
			lo = bus->read(addr);
			++addr;
			hi = 0x00;
			StringInstruction += " Y {ZPY}";
		}
		else if (AddrMode == &p::IZX)
		{
			lo = bus->read(addr);
			++addr;
			hi = 0x00;
			StringInstruction += "($" + proc6502::hex(lo, 2) + ", X) {IZX}";
		}
		else if (AddrMode == &p::IZY)
		{
			lo = bus->read(addr);
			++addr;
			hi = 0x00;
			StringInstruction += "($" + proc6502::hex(lo, 2) + ", Y) {IZY}";
		}
		else if (AddrMode == &p::ABS)
		{
			lo = bus->read(addr);
			addr++;
			hi = bus->read(addr);
			addr++;
			StringInstruction += "$" + proc6502::hex((static_cast<uint16_t>(hi) << 8 | lo), 4) + " {ABS}";
		}
		else if (AddrMode == &p::ABX)
		{
			lo = bus->read(addr);
			addr++;
			hi = bus->read(addr);
			addr++;
			StringInstruction += "$" + proc6502::hex((static_cast<uint16_t>(hi) << 8 | lo), 4) + " X {ABX}";
		}
		else if (AddrMode == &p::ABY)
		{
			lo = bus->read(addr);
			addr++;
			hi = bus->read(addr);
			addr++;
			StringInstruction += "$" + proc6502::hex((static_cast<uint16_t>(hi) << 8 | lo), 4) + " Y {ABY}";
		}
		else if (AddrMode == &p::IND)
		{
			lo = bus->read(addr);
			addr++;
			hi = bus->read(addr);
			addr++;
			StringInstruction += "($" + proc6502::hex((static_cast<uint16_t>(hi) << 8 | lo), 4) + ") {IND}";
		}
		else if (AddrMode == &p::REL)
		{
			value = bus->read(addr);
			addr++;
			StringInstruction += "$" + proc6502::hex(value, 2) + " [$" + proc6502::hex(addr + value, 4) + "] {REL}";
		}

		MapLines[LineAddress] = StringInstruction;
	}

	return MapLines;
}

void proc6502::LoadProgram(const std::string& FileName)
{
	const uint16_t start = 0x8000;
	std::ifstream file(FileName, std::ifstream::in);
	if (!file.good()) throw std::invalid_argument("Could not open the file.");

	std::string word;
	uint16_t offset = 0;
	while (file >> word)
	{
		uint16_t instruction = std::stoul(word, nullptr, 16);
		write(start + offset, instruction);
		++offset;
	}

	file.close();
}

void proc6502::clock()
{
	if (cycles == 0)
	{

		OpCode = read(pc);
		++pc;

		SetFlag(FLAGS6502::U, true);

		cycles = InstructionLookupTable[OpCode].cycles;
		
		auto AdditionalClockCycles1 = (this->*InstructionLookupTable[OpCode].AddressMode)();
		auto AdditionalClockCycles2 = (this->*InstructionLookupTable[OpCode].Operation)();
		
		cycles += (AdditionalClockCycles1 & AdditionalClockCycles2);
		
	}
	--cycles;
}

// Sets the processor to a known state.
// Clears registers and status, registers.
// Takes the new PC address from Memory[xFFFC].
void proc6502::reset()
{
	AbsoluteAddress = OriginLine;

	uint16_t lo = read(AbsoluteAddress + 0);
	uint16_t hi = read(AbsoluteAddress + 1);

	pc = (hi << 8) | lo;

	AC = 0;
	XReg = 0;
	YReg = 0;

	stkp = 0xFD;
	status = 0x00;

	SetFlag(FLAGS6502::U, true);

	AbsoluteAddress = 0x0000;
	RelativeAddress = 0x0000;

	FetchedData = 0x00;

	cycles = 8;
}


// Interrupt requests only can happen if the interrupt disable flag is set to false.
// It pushes pc and status to the stack, then reads  PC from a fixed address 0xFFFE.
// The program should return from the interrupt using RTI.
void proc6502::irq()
{
	auto InterruptMask = GetFlag(FLAGS6502::I);
	if (!InterruptMask) 
		return;

	write(StackStart + stkp, (pc >> 8) & 0x00FF);
	--stkp;
	write(StackStart + stkp, pc & 0x00FF);
	--stkp;

	SetFlag(FLAGS6502::U, true);
	SetFlag(FLAGS6502::B, false);
	SetFlag(FLAGS6502::I, true);

	write(StackStart + stkp, status);
	--stkp;

	AbsoluteAddress = 0xFFFE;
	uint8_t lo = read(AbsoluteAddress + 0);
	uint8_t hi = read(AbsoluteAddress + 1);

	pc = (hi << 8) | lo;

	cycles = 7;

}

uint8_t proc6502::BRK()
{
	++pc;

	SetFlag(FLAGS6502::I, 1);
	
	write(StackStart + stkp, (pc >> 8) & 0x00FF);
	--stkp;

	write(StackStart + stkp, pc & 0x00FF);
	--stkp;

	SetFlag(FLAGS6502::B, 1);

	write(StackStart + stkp, status);
	--stkp;

	SetFlag(FLAGS6502::B, 0);

	pc = static_cast<uint16_t>(read(0xFFFE)) | static_cast<uint16_t>(read(0xFFFE) << 8);
	
	return 0;
}

// Same as IRQ, inescapable, reads the new program counter address
// form location 0xFFFA.
void proc6502::nmi()
{
	write(StackStart + stkp, (pc >> 8) & 0x00FF);
	--stkp;
	write(StackStart + stkp, pc & 0x00FF);
	--stkp;

	SetFlag(FLAGS6502::U,  true);
	SetFlag(FLAGS6502::B, false);
	SetFlag(FLAGS6502::I,  true);

	write(StackStart + stkp, status);
	--stkp;

	AbsoluteAddress = 0xFFFA;
	uint8_t lo = read(AbsoluteAddress + 0);
	uint8_t hi = read(AbsoluteAddress + 1);

	pc = (hi << 8) | lo;

	cycles = 8;
}

bool proc6502::InstructionComplete()
{
	return cycles == 0;
}


uint8_t proc6502::GetFlag(FLAGS6502 f)
{
	return ((status & f) > 0) ? 1 : 0;
}


void proc6502::SetFlag(FLAGS6502 f, bool val)
{
	if (val) status |= f;
	else     status &= ~f;
}

// Addressing Modes

// Implied addressing mode.
// No extra data is taken from the instruction.
uint8_t proc6502::IMP()
{
	FetchedData = AC;
	return 0;
}

// Immediate addressing mode.
// Data is specified directly in the instruction itself.
uint8_t proc6502::IMM()
{
	AbsoluteAddress = pc;
	++pc;
	return 0;
}


// Zero page addressing mode.
// Data is in the zeroth page in memory.
// in the form of 0x00XX.
uint8_t proc6502::ZP0()
{
	AbsoluteAddress = read(pc);
	++pc;
	AbsoluteAddress &= 0x00FF;
	return 0;
}

// Zero page with offset x addressing mode.
// Data is in the zeroth page in memory
// offset by the content of the XReg.
uint8_t proc6502::ZPX()
{
	AbsoluteAddress = read(pc);
	AbsoluteAddress += XReg;
	++pc;
	AbsoluteAddress &= 0x00FF;
	return 0;
}

// Zero page with offset y addressing mode.
// Data is in the zeroth page in memory
// offset by the content of the YReg.
uint8_t proc6502::ZPY()
{
	AbsoluteAddress = read(pc);
	AbsoluteAddress += YReg;
	++pc;
	AbsoluteAddress &= 0x00FF;
	return 0;
}

uint8_t proc6502::REL()
{
	return 0;
}

// Absolute addressing mode, specifies 2 halves of PC
// in the next 2 bytes.
uint8_t proc6502::ABS()
{
	uint16_t lo = read(pc);
	++pc;

	uint16_t hi = read(pc);
	++pc;

	AbsoluteAddress = (hi << 8) | lo;
	return 0;
}

// Absolute addressing mode, with x offset.
uint8_t proc6502::ABX()
{
	uint16_t lo = read(pc);
	++pc;

	uint16_t hi = read(pc);
	++pc;

	AbsoluteAddress = (hi << 8) | lo;
	AbsoluteAddress += XReg;

	// Reguires 1 more cycle if the incrementation by x
	// resulting in an address in a different memory page.
	if ((AbsoluteAddress & 0xFF00) != (hi << 8)) return 1;
	else return 0;
}

// Absolute addressing mode with y offset.
uint8_t proc6502::ABY()
{
	uint16_t lo = read(pc);
	++pc;

	uint16_t hi = read(pc);
	++pc;

	AbsoluteAddress = (hi << 8) | lo;
	AbsoluteAddress += YReg;

	// Reguires 1 more cycle if the incrementation by x
	// resulting in an address in a different memory page.
	if ((AbsoluteAddress & 0xFF00) != (hi << 8)) return 1;
	else return 0;
}

// Indirect addressing mode.
uint8_t proc6502::IND()
{
	uint16_t PtrLo = read(pc);
	++pc;

	uint16_t PtrHi = read(pc);
	++pc;

	uint16_t ptr = ((PtrHi << 8) | PtrLo);

	if (PtrLo == 0x00FF)
	{
		AbsoluteAddress = (read(ptr & 0xFF00) << 8) | (read(ptr + 0));
	}
	else
	{
		AbsoluteAddress = (read(ptr + 1) << 8) | (read(ptr + 0));
	}

	return 0;
}


// fetches address from zero page using the address at Mem[PC].
// then offsets it by the content of XReg.
// if the offset makes it jump to another memory page, then it needs one more cycle.
uint8_t proc6502::IZX()
{
	uint16_t addr = read(pc);
	++pc;

	uint16_t lo = read(addr & 0x00FF);
	uint16_t hi = read((addr + 1) & 0x00FF);

	AbsoluteAddress = (hi << 8) | lo;

	if ((AbsoluteAddress & 0xFF00) != hi << 8)
	{
		return 1;
	}

	return 0;
}

// fetches address from zero page using the address at Mem[PC].
// then offsets it by the content of YReg.
// if the offset makes it jump to another page, then it needs one more cycle.
uint8_t proc6502::IZY()
{
	uint16_t addr = read(pc);
	++pc;

	uint16_t lo = read(addr & 0x00FF);
	uint16_t hi = read((addr + 1) & 0x00FF);

	AbsoluteAddress = (hi << 8) | lo;
	AbsoluteAddress += YReg;

	if ((AbsoluteAddress & 0xFF00) != hi << 8)
	{
		return 1;
	}

	return 0;
}

// Fetches data from Memory[AbsoluteAddress] only if the current OpCode doesn't use the implied addressing mode.
uint8_t proc6502::fetch()
{
	if (InstructionLookupTable[OpCode].AddressMode != &proc6502::IMP)
	{
		FetchedData = read(AbsoluteAddress);
	}
	return 0;
}

// Add operation on AC, fetched data
// from memory and the carry bit.
// Modifies flags C, Z and N.
// result is overflow if:
// AC(positve) + FetchedData(positive) = negative.
// AC(negative) + FetchedData(negative) = positive.
// The MSB of a binary 2's complement data can be 
// interpreted as a sign bit.
// Numbers of different signs don't overflow, as the absolute value 
// of the result will be always less than ABS(max((ABS(AC), ABS(FD)))
// impling that AC and FD are already fitting a 8 bit integer, then the
// result must also fit a 8 bit integer.
// 
//  MSB(AC)| MSB(FD)| MSB(R) | V
//       0 |      0 |      0 | 0
//       0 |      0 |      1 | 1
//       0 |      1 |      0 | 0
//       0 |      1 |      1 | 0 
//       1 |      0 |      0 | 0
//       1 |      0 |      1 | 0
//       1 |      1 |      0 | 1
//       1 |      1 |      1 | 0
//
// Overflow only happens at (AC' & FD' & R) | (AC & FD & R')
uint8_t proc6502::ADC()
{
	fetch();

	temp = static_cast<uint16_t>(FetchedData) + static_cast<uint16_t>(AC) + GetFlag(FLAGS6502::C);

	SetFlag(FLAGS6502::C, temp > 0x00FF);
	SetFlag(FLAGS6502::Z, temp == 0x0000);
	SetFlag(FLAGS6502::N, temp & 0x0080);

	bool ResMSB = temp & 0x0080;
	bool FetchedMSB = FetchedData & 0x0080;
	bool AcMSB = AC & 0x0080;

	SetFlag(FLAGS6502::V, (AcMSB & FetchedMSB & !ResMSB) | (!AcMSB & !FetchedMSB & ResMSB));
	AC = temp & 0x00FF;

	return 1;
}

uint8_t proc6502::AND()
{
	fetch();
	AC = AC & FetchedData;

	SetFlag(FLAGS6502::Z, AC == 0x00);
	SetFlag(FLAGS6502::N, AC &  0x80);

	return 0;
}

// Arithmetic shift left. 
// Modifies flags C, N and Z.
// Can use implied addressing mode.
// Then setting the result in the AC register.
uint8_t proc6502::ASL()
{
	fetch();
	temp = static_cast<uint16_t>(FetchedData) << 1;

	SetFlag(FLAGS6502::C, (temp & 0xFF00) > 0);
	SetFlag(FLAGS6502::N, (temp & 0x80));
	SetFlag(FLAGS6502::Z, (temp & 0x00FF) == 0);

	if (InstructionLookupTable[OpCode].AddressMode == &proc6502::IMP)
	{
		AC = static_cast<uint8_t>(temp) & 0xFF;
	}
	else
	{
		write(AbsoluteAddress, static_cast<uint8_t>(temp));
	}
	return 0;
}

// Branch on carry clear.
uint8_t proc6502::BCC()
{
	if (GetFlag(FLAGS6502::C) == 0)
	{
		++cycles;
		AbsoluteAddress = pc + RelativeAddress;

		if ((AbsoluteAddress & (0xFF00)) != (pc & (0xFF00)))
		{
			++cycles;
		}
		pc = AbsoluteAddress;
	}
	return 0;
}

// Branch on carry set.
uint8_t proc6502::BCS()
{
	if (GetFlag(FLAGS6502::C) == 1)
	{
		++cycles;
		AbsoluteAddress = pc + RelativeAddress;

		if ((AbsoluteAddress & (0xFF00)) != (pc & (0xFF00)))
		{
			++cycles;
		}
		pc = AbsoluteAddress;
	}
	return 0;
}

// Branch if the last operation implied equality.
uint8_t proc6502::BEQ()
{
	if (GetFlag(FLAGS6502::Z) == 1)
	{
		++cycles;
		AbsoluteAddress = pc + RelativeAddress;

		if ((AbsoluteAddress & (0xFF00)) != (pc & (0xFF00)))
		{
			++cycles;
		}
		pc = AbsoluteAddress;
	}
	return 0;

}

// Branch if the last operation didn't imply equality.
uint8_t proc6502::BNE()
{
	if (GetFlag(FLAGS6502::Z) == 0)
	{
		++cycles;
		AbsoluteAddress = pc + RelativeAddress;

		if ((AbsoluteAddress & 0xFF00) != (pc & 0xFF00))
			++cycles;

		pc = AbsoluteAddress;
	}
	return 0;
}

// Branch on result is positive.
uint8_t proc6502::BPL()
{
	if (GetFlag(FLAGS6502::N) == 0)
	{
		++cycles;
		AbsoluteAddress = pc + RelativeAddress;

		if ((AbsoluteAddress & 0xFF00) != (pc & 0xFF00))
			++cycles;

		pc = AbsoluteAddress;
	}
	return 0;
}

// Branch on result hasn't overflown.
uint8_t proc6502::BVC()
{
	if (GetFlag(FLAGS6502::V) == 0)
	{
		++cycles;
		AbsoluteAddress = pc + RelativeAddress;

		if ((AbsoluteAddress & 0xFF00) != (pc & 0xFF00))
			++cycles;

		pc = AbsoluteAddress;
	}
	return 0;
}

// Branch on result overflown.
uint8_t proc6502::BVS()
{
	if (GetFlag(FLAGS6502::V) == 1)
	{
		++cycles;
		AbsoluteAddress = pc + RelativeAddress;

		if ((AbsoluteAddress & 0xFF00) != (pc & 0xFF00))
			++cycles;

		pc = AbsoluteAddress;
	}
	return 0;
}

// Branch on result minus.
uint8_t proc6502::BMI()
{
	if (GetFlag(FLAGS6502::N) == 1)
	{
		++cycles;
		AbsoluteAddress = pc + RelativeAddress;

		if ((AbsoluteAddress & 0xFF00) != (pc & 0xFF00))
			++cycles;

		pc = AbsoluteAddress;
	}
	return 0;
}

// Test Bits in Memory with Accumulator 
// bits 7 and 6 of operand are transfered 
// to bit 7 and 6 of SR(N, V); 
// the zeroflag is set to the result of operand AND accumulator.
uint8_t proc6502::BIT()
{
	uint16_t AndedValue = AC & FetchedData;

	SetFlag(FLAGS6502::N, FetchedData & (1 << 7));
	SetFlag(FLAGS6502::V, FetchedData & (1 << 6));
	SetFlag(FLAGS6502::Z, (AndedValue & 0x00FF) == 0);

	return 0;
}

// Clears the carry flag.
uint8_t proc6502::CLC()
{
	SetFlag(FLAGS6502::C, false);
	return 0;
}

// Clears the interrupt flag.
uint8_t proc6502::CLI()
{
	SetFlag(FLAGS6502::I, false);
	return 0;
}

// Clears the deicmal flag.
uint8_t proc6502::CLD()
{
	SetFlag(FLAGS6502::D, false);
	return 0;
}

// Clears the overflow flag.
uint8_t proc6502::CLV()
{
	SetFlag(FLAGS6502::V, false);
	return 0;
}

// Compare AC register with fetched data and set flags accordingly.
uint8_t proc6502::CMP()
{
	fetch();
	temp = static_cast<uint16_t>(AC) - static_cast<uint16_t>(FetchedData);
	
	SetFlag(FLAGS6502::C, AC >= FetchedData);
	SetFlag(FLAGS6502::Z, (temp & 0x00FF) == 0);
	SetFlag(FLAGS6502::N, temp & 0x0080);

	return 0;
}
// Compare X register with fetched data and set flags accordingly.
uint8_t proc6502::CPX()
{
	fetch();
	temp = static_cast<uint16_t>(AC) - static_cast<uint16_t>(XReg);

	SetFlag(FLAGS6502::C, YReg >= FetchedData);
	SetFlag(FLAGS6502::Z, (temp & 0x00FF) == 0);
	SetFlag(FLAGS6502::N, temp & 0x0080);

	return 0;
}

// Compare Y register with fetched data and set flags accordingly.
uint8_t proc6502::CPY()
{
	fetch();
	temp = static_cast<uint16_t>(YReg) - static_cast<uint16_t>(YReg);

	SetFlag(FLAGS6502::C, YReg >= FetchedData);
	SetFlag(FLAGS6502::Z, (temp & 0x00FF) == 0);
	SetFlag(FLAGS6502::N, temp & 0x0080);

	return 0;
}


// Decrement at memory address.
// M[AbsoluteAddress] -= 1.
// Modifies flags Z and N.
uint8_t proc6502::DEC()
{
	fetch();
	
	temp = static_cast<uint16_t>(FetchedData) - 1;

	write(AbsoluteAddress, temp & 0x00FF);

	SetFlag(FLAGS6502::Z, temp == 0x0000);
	SetFlag(FLAGS6502::N, temp & 0x0080);

	return 0;
}


// Decrement XReg.
// Modifies flags Z and N.
uint8_t proc6502::DEX()
{
	--XReg;

	SetFlag(FLAGS6502::Z, XReg == 0x0000);
	SetFlag(FLAGS6502::N, XReg & 0x0080);

	return 0;
}


// Decrement YReg.
// Modifies flags Z and N.
uint8_t proc6502::DEY()
{
	--XReg;

	SetFlag(FLAGS6502::Z, YReg == 0x0000);
	SetFlag(FLAGS6502::N, YReg & 0x0080);

	return 0;
}


// XOR AC register with the fetched data.
// Modifies flags Z and N.
uint8_t proc6502::EOR()
{
	fetch();

	AC = AC ^ FetchedData;

	SetFlag(FLAGS6502::Z, AC == 0x0000);
	SetFlag(FLAGS6502::N, AC  & 0x0080);

	return 0;
}

// Increments value at memory.
// Modifies flags N and Z.
uint8_t proc6502::INC()
{
	fetch();

	temp = static_cast<uint16_t>(FetchedData) + 1;

	write(AbsoluteAddress, temp & 0x00FF);

	SetFlag(FLAGS6502::Z, temp == 0x0000);
	SetFlag(FLAGS6502::N, temp & 0x0080);

	return 0;
}

// Increments value at XReg.
// Modifies flags N and Z.
uint8_t proc6502::INX()
{
	XReg = XReg + 1;

	SetFlag(FLAGS6502::Z, XReg == 0x0000);
	SetFlag(FLAGS6502::N, XReg  & 0x0080);

	return 0;
}


// Increments value at YReg.
// Modifies flags N and Z.
uint8_t proc6502::INY()
{
	YReg = YReg + 1;

	SetFlag(FLAGS6502::Z, YReg == 0x0000);
	SetFlag(FLAGS6502::N, YReg  & 0x0080);

	return 0;
}

// Jump unconditionally to address stored.
uint8_t proc6502::JMP()
{
	pc = AbsoluteAddress;
	return 0;
}

// Jump to sub routine address.
// Saves PC on the stack as two 8-bit halves.
uint8_t proc6502::JSR()
{
	--pc;
	
	write(StackStart + stkp, (pc >> 8) & 0x00FF);
	--stkp;

	write(StackStart + stkp, (pc & 0x00FF));
	--stkp;

	pc = AbsoluteAddress;

	return 0;
}

// Load data to the AC.
// Modifies flags Z and N.
uint8_t proc6502::LDA()
{
	fetch();

	AC = FetchedData;
	
	SetFlag(FLAGS6502::Z, AC == 0x00);
	SetFlag(FLAGS6502::N, AC & 0x80);

	return 0;
}

// Load data to the XReg.
// Modifies flags Z and N.
uint8_t proc6502::LDX()
{
	fetch();

	XReg = FetchedData;

	SetFlag(FLAGS6502::Z, XReg == 0x00);
	SetFlag(FLAGS6502::N, XReg & 0x80);

	return 0;
}

// Loads data to the YReg.
// Modifies flags Z, N.
uint8_t proc6502::LDY()
{
	fetch();

	YReg = FetchedData;

	SetFlag(FLAGS6502::Z, YReg == 0x00);
	SetFlag(FLAGS6502::N, YReg & 0x80);

	return 0;
}

// Logical shift right.
// Modifies flags C, Z, and N.
// it can be used with implied addressing mode
// it then will store the result in AC.
uint8_t proc6502::LSR()
{
	fetch();
	
	SetFlag(FLAGS6502::C, FetchedData & 0x0001);
	
	temp = FetchedData >> 1;
	
	SetFlag(FLAGS6502::Z, (temp & 0x00FF) == 0x0000);
	SetFlag(FLAGS6502::N, temp == 0x0080);
	
	if (InstructionLookupTable[OpCode].AddressMode == &proc6502::IMP)
	{
		AC = static_cast<uint8_t>(temp & 0x00FF);
	}
	else
	{
		write(AbsoluteAddress, static_cast<uint8_t>(temp & 0x00FF));
	}
	
	return 0;
}

// OR fetched data from Memory with Accumulator
// Modifies flags N and Z.
uint8_t proc6502::ORA()
{
	fetch();
	
	AC = AC | FetchedData;

	SetFlag(FLAGS6502::Z, AC == 0x00);
	SetFlag(FLAGS6502::N, AC & 0x80);

	return 1;
}

uint8_t proc6502::NOP()
{
	return 0;
}

// Pushes accumulator to the stack.
uint8_t proc6502::PHA()
{
	write(StackStart + stkp, AC);
	--stkp;

	return 0;
}

// Pushes status register to the stack.
// Break flag is set before pushing.
uint8_t proc6502::PHP()
{
	status |= FLAGS6502::B;
	status |= FLAGS6502::U;

	write(StackStart + stkp, status);

	SetFlag(FLAGS6502::B, false);
	SetFlag(FLAGS6502::U, false);

	--stkp;

	return 0;
}


// Pop accumulator from the stack and set flags.
// Modifies N and Z
uint8_t proc6502::PLA()
{
	++stkp;
	
	AC = read(StackStart + stkp);
	
	SetFlag(FLAGS6502::Z, AC == 0x00);
	SetFlag(FLAGS6502::N, AC & 0x80);

	return 0;
}


// Pop status register from the stack.
uint8_t proc6502::PLP()
{
	++stkp;

	status = read(StackStart + stkp);
	
	SetFlag(FLAGS6502::U, true);

	return 0;
}

// Rotates one bit to the left with carry flag.
// Sets N, C and Z flags.
uint8_t proc6502::ROL()
{
	fetch();
	
	temp = (FetchedData << 1) | GetFlag(FLAGS6502::C);

	SetFlag(FLAGS6502::N, temp & 0x0080);
	SetFlag(FLAGS6502::C, temp & 0xFF00);
	SetFlag(FLAGS6502::Z, (temp & 0x00FF) == 0);

	if (InstructionLookupTable[OpCode].AddressMode == &proc6502::IMP)
	{
		AC = static_cast<uint8_t>(temp & 0x00FF);
	}
	else
	{
		write(AbsoluteAddress, static_cast<uint8_t>(temp & 0x00FF));
	}
	return 0;
}

// Rotates one bit to the right with carry flag.
// Sets N, C and Z flags.
uint8_t proc6502::ROR()
{
	fetch();

	temp = (FetchedData >> 1) | (static_cast<uint16_t>(GetFlag(FLAGS6502::C )) << 7);

	SetFlag(FLAGS6502::N, temp & 0x0080);
	SetFlag(FLAGS6502::C, FetchedData & 0x01);
	SetFlag(FLAGS6502::Z, (temp & 0x00FF) == 0);

	if (InstructionLookupTable[OpCode].AddressMode == &proc6502::IMP)
	{
		AC = static_cast<uint8_t>(temp & 0x00FF);
	}
	else
	{
		write(AbsoluteAddress, static_cast<uint8_t>(temp & 0x00FF));
	}
	return 0;
}

// Return from inturrupt.
// Pops Status flags off the stack.
uint8_t proc6502::RTI()
{
	++stkp;
	status = read(StackStart + stkp);

	SetFlag(FLAGS6502::B, false);
	SetFlag(FLAGS6502::U, false);

	++stkp;
	pc = read(StackStart + stkp);

	++stkp;
	pc |= (read(StackStart + stkp) << 8);

	return 0;
}

// Return from subroutine.
// Pops the previous PC from the stack.
uint8_t proc6502::RTS()
{
	++stkp;
	pc = read(StackStart + stkp);

	++stkp;
	pc |= (read(StackStart + stkp) << 8);

	++pc;

	return 0;
}

// Subtracts Fetched data from the AC register.
uint8_t proc6502::SBC()
{
	fetch();

	uint16_t InvertedValue = FetchedData ^ 0x00FF;

	temp = InvertedValue + static_cast<uint16_t>(AC) + GetFlag(FLAGS6502::C);

	SetFlag(FLAGS6502::C, temp > 0x00FF);
	SetFlag(FLAGS6502::Z, temp == 0x0000);
	SetFlag(FLAGS6502::N, temp & 0x0080);

	bool ResMSB = temp & 0x0080;
	bool FetchedMSB = FetchedData & 0x0080;
	bool AcMSB = AC & 0x0080;

	SetFlag(FLAGS6502::V, (ResMSB ^ AcMSB) & ~(FetchedMSB ^ AcMSB));

	AC = temp & 0x00FF;

	return 1;
}

// Sets Carry flag.
uint8_t proc6502::SEC()
{
	SetFlag(FLAGS6502::C, true);

	return 0;
}

// Sets Decimal flag.
uint8_t proc6502::SED()
{
	SetFlag(FLAGS6502::D, true);

	return 0;
}

// Sets inturrupt flag.
uint8_t proc6502::SEI()
{
	SetFlag(FLAGS6502::I, true);

	return 0;
}

// Stores AC register in Memory[AbsoluteAddress].
uint8_t proc6502::STA()
{
	write(AbsoluteAddress, AC);

	return 0;
}

// Stores X register in Memory[AbsoluteAddress].
uint8_t proc6502::STX()
{
	write(AbsoluteAddress, XReg);

	return 0;
}

// Stores Y register in Memory[AbsoluteAddress].
uint8_t proc6502::STY()
{
	write(AbsoluteAddress, YReg);

	return 0;
}

// Puts AC register into X register
// Modifies flags Z and N.
uint8_t proc6502::TAX()
{
	XReg = AC;

	SetFlag(FLAGS6502::Z, AC == 0x00);
	SetFlag(FLAGS6502::N, AC & 0x80);

	return 0;
}

// Puts AC register into Y register
// Modifies flags Z and N.
uint8_t proc6502::TAY()
{
	YReg = AC;

	SetFlag(FLAGS6502::Z, AC == 0x00);
	SetFlag(FLAGS6502::N, AC & 0x80);

	return 0;
}


// Puts Stack Pointer register into X register
// Modifies flags Z and N.
uint8_t proc6502::TSX()
{
	XReg = stkp;
	
	SetFlag(FLAGS6502::N, stkp & 0x80);
	SetFlag(FLAGS6502::Z, stkp == 0x00);

	return 0;
}

// Puts X register into the AC register
// Modifies flags Z and N.
uint8_t proc6502::TXA()
{
	AC = XReg;
	
	SetFlag(FLAGS6502::Z, AC == 0x00);
	SetFlag(FLAGS6502::N, AC & 0x80);
	
	return 0;
}

// Puts X register into the stack pointer register
uint8_t proc6502::TXS()
{
	stkp = XReg;

	return 0;
}

// Puts Y register into the AC register
// Modifies flags Z and N.
uint8_t proc6502::TYA()
{
	AC = YReg;

	SetFlag(FLAGS6502::Z, AC == 0x00);
	SetFlag(FLAGS6502::N, AC & 0x80);

	return 0;
}

// catches all illegal opcodes.
uint8_t proc6502::XXX()
{
	return 0;
}
