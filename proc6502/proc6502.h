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
	std::uint16_t PCReg = 0x0000; // Program Counter register.
	std::uint8_t  STReg =   0x00; // Status register.


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
/*
	Addressing modes of 6502 processor.
	these functions will change the mode of addressing
	before executing the instruction. 

*/
	template<typename T, typename... U>
	std::size_t GetAddress(std::function<T(U...)> f) {
		typedef T(fnType)(U...);
		fnType** fnPointer = f.template target<fnType*>();
		return (size_t)* fnPointer;
	}

	uint8_t IMP();
	uint8_t IMM();
	uint8_t ZP0();
	uint8_t ZPX();
	uint8_t ZPY();
	uint8_t REL();
	uint8_t ABS();
	uint8_t ABX();
	uint8_t ABY();
	uint8_t IND();
	uint8_t IZX();
	uint8_t IZY();

private:
	// OPCODES
	// 6502 processor has 52 operations.
	uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
	uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
	uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
	uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
	uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
	uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
	uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
	uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
	uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
	uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
	uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
	uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
	uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
	uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

	uint8_t XXX();

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
		std::function<std::uint8_t(proc6502*)> Operation = std::function<std::uint8_t(proc6502*)>();
		std::function<std::uint8_t(proc6502*)> AddressMode = std::function<std::uint8_t(proc6502*)>();
		std::uint8_t Cycles = 0;
	};

	std::vector<INSTRUCTION> InstructionLookupTable;
};

