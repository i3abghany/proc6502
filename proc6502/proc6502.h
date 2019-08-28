#pragma once

#include <vector>
#include <map>
#include <string>
#include <functional>

class Bus;

class proc6502
{
public:
	proc6502();
	~proc6502() = default;

	enum FLAGS6502 : std::uint8_t
	{
		C = (1 << 0),	// Carry Bit
		Z = (1 << 1),	// Zero
		I = (1 << 2),	// Disable Interrupts
		D = (1 << 3),	// Decimal Mode (unused in this implementation)
		B = (1 << 4),	// Break
		U = (1 << 5),	// Unused
		V = (1 << 6),	// Overflow
		N = (1 << 7),	// Negative
	};

public:
	std::uint8_t  ACReg =   0x00; // accumulator register.
	std::uint8_t   XReg =   0x00; // X register.
	std::uint8_t   YReg =   0x00; // Y register.
	std::uint8_t  SPReg =   0x00; // Stack pointer register.
	std::uint8_t  STReg =   0x00; // Status register.
	std::uint16_t PCReg = 0x0000; // Program Counter register.

	static constexpr std::uint16_t StackStart = 0x0100; // Location of stack in the main memory.
	static constexpr std::uint16_t OriginLine = 0xFFFC; // Start location after the reset.

	void ConnectBus(Bus*);



	bool InstructionComplete();

	std::map<std::uint16_t, std::string> disassemble(const std::uint8_t start, const std::uint8_t stop);


private:
	Bus* bus = nullptr;
	uint8_t read(uint16_t a);
	void    write(uint16_t a, uint8_t d);

	std::uint8_t GetFlag(FLAGS6502);
	void SetFlag(FLAGS6502, bool);


private:

	//Addressing modes of 6502 processor.
	//these functions will change the mode of addressing
	//before executing the instruction. 
	std::uint8_t IMP();
	std::uint8_t IMM();
	std::uint8_t ZP0();
	std::uint8_t ZPX();
	std::uint8_t ZPY();
	std::uint8_t REL();
	std::uint8_t ABS();
	std::uint8_t ABX();
	std::uint8_t ABY();
	std::uint8_t IND();
	std::uint8_t IZX();
	std::uint8_t IZY();
private:
	// OPCODES
	// 6502 processor has 52 operations.
	std::uint8_t ADC();	std::uint8_t AND(); std::uint8_t ASL();	std::uint8_t BCC();
	std::uint8_t BCS();	std::uint8_t BEQ(); std::uint8_t BIT();	std::uint8_t BMI();
	std::uint8_t BNE();	std::uint8_t BPL(); std::uint8_t BRK();	std::uint8_t BVC();
	std::uint8_t BVS();	std::uint8_t CLC(); std::uint8_t CLD();	std::uint8_t CLI();
	std::uint8_t CLV();	std::uint8_t CMP(); std::uint8_t CPX();	std::uint8_t CPY();
	std::uint8_t DEC();	std::uint8_t DEX(); std::uint8_t DEY();	std::uint8_t EOR();
	std::uint8_t INC();	std::uint8_t INX(); std::uint8_t INY();	std::uint8_t JMP();
	std::uint8_t JSR();	std::uint8_t LDA(); std::uint8_t LDX();	std::uint8_t LDY();
	std::uint8_t LSR();	std::uint8_t NOP(); std::uint8_t ORA();	std::uint8_t PHA();
	std::uint8_t PHP();	std::uint8_t PLA(); std::uint8_t PLP();	std::uint8_t ROL();
	std::uint8_t ROR();	std::uint8_t RTI(); std::uint8_t RTS();	std::uint8_t SBC();
	std::uint8_t SEC();	std::uint8_t SED(); std::uint8_t SEI();	std::uint8_t STA();
	std::uint8_t STX();	std::uint8_t STY(); std::uint8_t TAX();	std::uint8_t TAY();
	std::uint8_t TSX();	std::uint8_t TXA(); std::uint8_t TXS();	std::uint8_t TYA();

	std::uint8_t XXX();

	void clock();
	void reset();
	void irq();
	void nmi();

	std::uint8_t fetch();

	std::uint8_t  FetchedData     =   0x00;
	std::uint16_t TempReg        =  0x0000;
	std::uint16_t AbsoluteAddress = 0x0000;
	std::uint16_t RelativeAddress =   0x00;
	std::uint8_t  OpCode          =   0x00;
	std::uint8_t  Cycles          =      0;
	
	struct INSTRUCTION
	{
		std::string name;
		std::uint8_t(proc6502::* Operation)(void) = nullptr;
		std::uint8_t(proc6502::* AddressMode)(void) = nullptr;
		std::uint8_t Cycles = 0;
	};

	std::vector<INSTRUCTION> InstructionLookupTable;
};

