/*
* RetroGB

* Copyright (C) 2016  Michael Kösel

* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>
*
*/

#pragma once

#include "Definitions.h"
#include "Memory.h"

#include <array>
#include <memory>

#define SIXTEEN_BIT_REGISTER(high, low) \
	union { \
		struct { \
			uint8 low; \
			uint8 high; \
		}; \
		uint16 high ## low; \
	}

enum Interrupt : uint8
{
    VBlank = 0x01,
    LCD_Stat = 0x02,
    Time = 0x04,
    Serial = 0x08,
    Joypad = 0x10
};

enum Flag : uint8
{
    Zero = 0x80,
    Sub = 0x40,
    Half_Carry = 0x20,
    Carry = 0x10,
    None = 0x00
};

class Processor
{
public:
    Processor(std::shared_ptr<Memory> memory);
    ~Processor();

    unsigned int Run();

	void Reset(bool color);
    void RequestInterrupt(Interrupt interrupt);
 
	bool IsFlagSet(uint8 flag);

private:
    unsigned int HandleInterrupts();

	void SetFlags(Flag flag);
    void EnableFlag(Flag flag);
    void DisableFlag(Flag flag);
    void InvertFlag(Flag flag);
    void ClearFlags();
	void ToggleFlag(Flag flag, bool condition);
	void KeepFlag(Flag flag);

	void InitOpcodes();
	
public:
	std::shared_ptr<Memory> memory;

	std::array<std::function<int()>, 256> opcodes;
	std::array<std::function<int()>, 256> opcodesCB;
	
	unsigned int clockCycles;
    bool ime;
    bool halted;

    uint16 PC;
    uint16 SP;

	SIXTEEN_BIT_REGISTER(A, F);
	SIXTEEN_BIT_REGISTER(B, C);
	SIXTEEN_BIT_REGISTER(D, E);
	SIXTEEN_BIT_REGISTER(H, L);

private:
	int UnknownOpcode();
	int InvalidOpcode();

	void PushToStack(uint16 reg);
	void PopFromStack(uint16& reg);

	uint8 Inc(uint8 reg);
	uint8 Dec(uint8 reg);

	void Add(uint8 reg);
	void Adc(uint8 reg);
	void Sub(uint8 reg);
	void Sbc(uint8 reg);

	void AddHL(uint16 val);
	void AddSP(int8 val);

	uint8 Rl(uint8 reg, bool registerA);
	uint8 Rlc(uint8 reg, bool registerA);
	uint8 Rr(uint8 reg, bool registerA);
	uint8 Rrc(uint8 reg, bool registerA);

	uint8 Sla(uint8 reg);
	uint8 Sra(uint8 reg);
	uint8 Srl(uint8 reg);
	void Bit(uint8 reg, int bit);

private:
	unsigned int NOP();
	unsigned int LD_BC_nn();
	unsigned int LD_MEM_BC_A();
	unsigned int INC_BC();
	unsigned int INC_B();
	unsigned int DEC_B();
	unsigned int LD_B_n();
	unsigned int RLCA();
	unsigned int LD_MEM_nn_SP();
	unsigned int ADD_HL_BC();
	unsigned int LD_A_MEM_BC();
	unsigned int DEC_BC();
	unsigned int INC_C();
	unsigned int DEC_C();
	unsigned int LD_C_n();
	unsigned int RRCA();
	unsigned int STOP();
	unsigned int LD_DE_nn();
	unsigned int LD_MEM_DE_A();
	unsigned int INC_DE();
	unsigned int INC_D();
	unsigned int DEC_D();
	unsigned int LD_D_n();
	unsigned int RLA();
	unsigned int JR_n();
	unsigned int ADD_HL_DE();
	unsigned int LD_A_MEM_DE();
	unsigned int DEC_DE();
	unsigned int INC_E();
	unsigned int DEC_E();
	unsigned int LD_E_n();
	unsigned int RRA();
	unsigned int JR_NZ_n();
	unsigned int LD_HL_nn();
	unsigned int LD_MEM_HLI_A();
	unsigned int INC_HL();
	unsigned int INC_H();
	unsigned int DEC_H();
	unsigned int LD_H_n();
	unsigned int DAA();
	unsigned int JR_Z_n();
	unsigned int ADD_HL_HL();
	unsigned int LD_A_MEM_HLI();
	unsigned int DEC_HL();
	unsigned int INC_L();
	unsigned int DEC_L();
	unsigned int LD_L_n();
	unsigned int CPL();
	unsigned int JR_NC_n();
	unsigned int LD_SP_nn();
	unsigned int LD_MEM_HLD_A();
	unsigned int INC_SP();
	unsigned int INC_MEM_HL();
	unsigned int DEC_MEM_HL();
	unsigned int LD_MEM_HL_n();
	unsigned int SCF();
	unsigned int JR_C_n();
	unsigned int ADD_HL_SP();
	unsigned int LD_A_MEM_HLD();
	unsigned int DEC_SP();
	unsigned int INC_A();
	unsigned int DEC_A();
	unsigned int LD_A_n();
	unsigned int CCF();
	unsigned int LD_B_B();
	unsigned int LD_B_C();
	unsigned int LD_B_D();
	unsigned int LD_B_E();
	unsigned int LD_B_H();
	unsigned int LD_B_L();
	unsigned int LD_B_MEM_HL();
	unsigned int LD_B_A();
	unsigned int LD_C_B();
	unsigned int LD_C_C();
	unsigned int LD_C_D();
	unsigned int LD_C_E();
	unsigned int LD_C_H();
	unsigned int LD_C_L();
	unsigned int LD_C_MEM_HL();
	unsigned int LD_C_A();
	unsigned int LD_D_B();
	unsigned int LD_D_C();
	unsigned int LD_D_D();
	unsigned int LD_D_E();
	unsigned int LD_D_H();
	unsigned int LD_D_L();
	unsigned int LD_D_MEM_HL();
	unsigned int LD_D_A();
	unsigned int LD_E_B();
	unsigned int LD_E_C();
	unsigned int LD_E_D();
	unsigned int LD_E_E();
	unsigned int LD_E_H();
	unsigned int LD_E_L();
	unsigned int LD_E_MEM_HL();
	unsigned int LD_E_A();
	unsigned int LD_H_B();
	unsigned int LD_H_C();
	unsigned int LD_H_D();
	unsigned int LD_H_E();
	unsigned int LD_H_H();
	unsigned int LD_H_L();
	unsigned int LD_H_MEM_HL();
	unsigned int LD_H_A();
	unsigned int LD_L_B();
	unsigned int LD_L_C();
	unsigned int LD_L_D();
	unsigned int LD_L_E();
	unsigned int LD_L_H();
	unsigned int LD_L_L();
	unsigned int LD_L_MEM_HL();
	unsigned int LD_L_A();
	unsigned int LD_MEM_HL_B();
	unsigned int LD_MEM_HL_C();
	unsigned int LD_MEM_HL_D();
	unsigned int LD_MEM_HL_E();
	unsigned int LD_MEM_HL_H();
	unsigned int LD_MEM_HL_L();
	unsigned int HALT();
	unsigned int LD_MEM_HL_A();
	unsigned int LD_A_B();
	unsigned int LD_A_C();
	unsigned int LD_A_D();
	unsigned int LD_A_E();
	unsigned int LD_A_H();
	unsigned int LD_A_L();
	unsigned int LD_A_MEM_HL();
	unsigned int LD_A_A();
	unsigned int ADD_A_B();
	unsigned int ADD_A_C();
	unsigned int ADD_A_D();
	unsigned int ADD_A_E();
	unsigned int ADD_A_H();
	unsigned int ADD_A_L();
	unsigned int ADD_A_MEM_HL();
	unsigned int ADD_A_A();
	unsigned int ADC_A_B();
	unsigned int ADC_A_C();
	unsigned int ADC_A_D();
	unsigned int ADC_A_E();
	unsigned int ADC_A_H();
	unsigned int ADC_A_L();
	unsigned int ADC_A_MEM_HL();
	unsigned int ADC_A_A();
	unsigned int SUB_B();
	unsigned int SUB_C();
	unsigned int SUB_D();
	unsigned int SUB_E();
	unsigned int SUB_H();
	unsigned int SUB_L();
	unsigned int SUB_MEM_HL();
	unsigned int SUB_A();
	unsigned int SBC_A_B();
	unsigned int SBC_A_C();
	unsigned int SBC_A_D();
	unsigned int SBC_A_E();
	unsigned int SBC_A_H();
	unsigned int SBC_A_L();
	unsigned int SBC_A_MEM_HL();
	unsigned int SBC_A_A();
	unsigned int AND_B();
	unsigned int AND_C();
	unsigned int AND_D();
	unsigned int AND_E();
	unsigned int AND_H();
	unsigned int AND_L();
	unsigned int AND_MEM_HL();
	unsigned int AND_A();
	unsigned int XOR_B();
	unsigned int XOR_C();
	unsigned int XOR_D();
	unsigned int XOR_E();
	unsigned int XOR_H();
	unsigned int XOR_L();
	unsigned int XOR_MEM_HL();
	unsigned int XOR_A();
	unsigned int OR_B();
	unsigned int OR_C();
	unsigned int OR_D();
	unsigned int OR_E();
	unsigned int OR_H();
	unsigned int OR_L();
	unsigned int OR_MEM_HL();
	unsigned int OR_A();
	unsigned int CP_B();
	unsigned int CP_C();
	unsigned int CP_D();
	unsigned int CP_E();
	unsigned int CP_H();
	unsigned int CP_L();
	unsigned int CP_MEM_HL();
	unsigned int CP_A();
	unsigned int RET_NZ();
	unsigned int POP_BC();
	unsigned int JP_NZ_nn();
	unsigned int JP_nn();
	unsigned int CALL_NZ_nn();
	unsigned int PUSH_BC();
	unsigned int ADD_A_n();
	unsigned int RST();
	unsigned int RET_Z();
	unsigned int RET();
	unsigned int JP_Z_nn();
	unsigned int CALL_Z_nn();
	unsigned int CALL_nn();
	unsigned int ADC_A_n();
	unsigned int RST_0x0008();
	unsigned int RET_NC();
	unsigned int POP_DE();
	unsigned int JP_NC_nn();
	unsigned int CALL_NC_nn();
	unsigned int PUSH_DE();
	unsigned int SUB_n();
	unsigned int RST_0x0010();
	unsigned int RET_C();
	unsigned int RETI();
	unsigned int JP_C_nn();
	unsigned int CALL_C_nn();
	unsigned int SBC_A_n();
	unsigned int RST_0x0018();
	unsigned int LD_MEM_0xFF00_n_A();
	unsigned int POP_HL();
	unsigned int LD_MEM_0xFF00_C_A();
	unsigned int PUSH_HL();
	unsigned int AND_n();
	unsigned int RST_0x0020();
	unsigned int ADD_SP_n();
	unsigned int JP_MEM_HL();
	unsigned int LD_MEM_nn_A();
	unsigned int XOR_n();
	unsigned int RST_0x0028();
	unsigned int LD_A_MEM_0xFF00_n();
	unsigned int POP_AF();
	unsigned int LD_A_MEM_0xFF00_C();
	unsigned int DI();
	unsigned int PUSH_AF();
	unsigned int OR_n();
	unsigned int RST_0x0030();
	unsigned int LD_HL_SP_n();
	unsigned int LD_SP_HL();
	unsigned int LD_A_MEM_nn();
	unsigned int EI();
	unsigned int CP_n();
	unsigned int RST_0x0038();

	// CB Obcodes
	unsigned int RLC_B();
	unsigned int RLC_C();
	unsigned int RLC_D();
	unsigned int RLC_E();
	unsigned int RLC_H();
	unsigned int RLC_L();
	unsigned int RLC_MEM_HL();
	unsigned int RLC_A();
	unsigned int RRC_B();
	unsigned int RRC_C();
	unsigned int RRC_D();
	unsigned int RRC_E();
	unsigned int RRC_H();
	unsigned int RRC_L();
	unsigned int RRC_MEM_HL();
	unsigned int RRC_A();
	unsigned int RL_B();
	unsigned int RL_C();
	unsigned int RL_D();
	unsigned int RL_E();
	unsigned int RL_H();
	unsigned int RL_L();
	unsigned int RL_MEM_HL();
	unsigned int RL_A();
	unsigned int RR_B();
	unsigned int RR_C();
	unsigned int RR_D();
	unsigned int RR_E();
	unsigned int RR_H();
	unsigned int RR_L();
	unsigned int RR_MEM_HL();
	unsigned int RR_A();
	unsigned int SLA_B();
	unsigned int SLA_C();
	unsigned int SLA_D();
	unsigned int SLA_E();
	unsigned int SLA_H();
	unsigned int SLA_L();
	unsigned int SLA_MEM_HL();
	unsigned int SLA_A();
	unsigned int SRA_B();
	unsigned int SRA_C();
	unsigned int SRA_D();
	unsigned int SRA_E();
	unsigned int SRA_H();
	unsigned int SRA_L();
	unsigned int SRA_MEM_HL();
	unsigned int SRA_A();
	unsigned int SWAP_B();
	unsigned int SWAP_C();
	unsigned int SWAP_D();
	unsigned int SWAP_E();
	unsigned int SWAP_H();
	unsigned int SWAP_L();
	unsigned int SWAP_MEM_HL();
	unsigned int SWAP_A();
	unsigned int SRL_B();
	unsigned int SRL_C();
	unsigned int SRL_D();
	unsigned int SRL_E();
	unsigned int SRL_H();
	unsigned int SRL_L();
	unsigned int SRL_MEM_HL();
	unsigned int SRL_A();
	unsigned int BIT_0_B();
	unsigned int BIT_0_C();
	unsigned int BIT_0_D();
	unsigned int BIT_0_E();
	unsigned int BIT_0_H();
	unsigned int BIT_0_L();
	unsigned int BIT_0_MEM_HL();
	unsigned int BIT_0_A();
	unsigned int BIT_1_B();
	unsigned int BIT_1_C();
	unsigned int BIT_1_D();
	unsigned int BIT_1_E();
	unsigned int BIT_1_H();
	unsigned int BIT_1_L();
	unsigned int BIT_1_MEM_HL();
	unsigned int BIT_1_A();
	unsigned int BIT_2_B();
	unsigned int BIT_2_C();
	unsigned int BIT_2_D();
	unsigned int BIT_2_E();
	unsigned int BIT_2_H();
	unsigned int BIT_2_L();
	unsigned int BIT_2_MEM_HL();
	unsigned int BIT_2_A();
	unsigned int BIT_3_B();
	unsigned int BIT_3_C();
	unsigned int BIT_3_D();
	unsigned int BIT_3_E();
	unsigned int BIT_3_H();
	unsigned int BIT_3_L();
	unsigned int BIT_3_MEM_HL();
	unsigned int BIT_3_A();
	unsigned int BIT_4_B();
	unsigned int BIT_4_C();
	unsigned int BIT_4_D();
	unsigned int BIT_4_E();
	unsigned int BIT_4_H();
	unsigned int BIT_4_L();
	unsigned int BIT_4_MEM_HL();
	unsigned int BIT_4_A();
	unsigned int BIT_5_B();
	unsigned int BIT_5_C();
	unsigned int BIT_5_D();
	unsigned int BIT_5_E();
	unsigned int BIT_5_H();
	unsigned int BIT_5_L();
	unsigned int BIT_5_MEM_HL();
	unsigned int BIT_5_A();
	unsigned int BIT_6_B();
	unsigned int BIT_6_C();
	unsigned int BIT_6_D();
	unsigned int BIT_6_E();
	unsigned int BIT_6_H();
	unsigned int BIT_6_L();
	unsigned int BIT_6_MEM_HL();
	unsigned int BIT_6_A();
	unsigned int BIT_7_B();
	unsigned int BIT_7_C();
	unsigned int BIT_7_D();
	unsigned int BIT_7_E();
	unsigned int BIT_7_H();
	unsigned int BIT_7_L();
	unsigned int BIT_7_MEM_HL();
	unsigned int BIT_7_A();
	unsigned int RES_0_B();
	unsigned int RES_0_C();
	unsigned int RES_0_D();
	unsigned int RES_0_E();
	unsigned int RES_0_H();
	unsigned int RES_0_L();
	unsigned int RES_0_MEM_HL();
	unsigned int RES_0_A();
	unsigned int RES_1_B();
	unsigned int RES_1_C();
	unsigned int RES_1_D();
	unsigned int RES_1_E();
	unsigned int RES_1_H();
	unsigned int RES_1_L();
	unsigned int RES_1_MEM_HL();
	unsigned int RES_1_A();
	unsigned int RES_2_B();
	unsigned int RES_2_C();
	unsigned int RES_2_D();
	unsigned int RES_2_E();
	unsigned int RES_2_H();
	unsigned int RES_2_L();
	unsigned int RES_2_MEM_HL();
	unsigned int RES_2_A();
	unsigned int RES_3_B();
	unsigned int RES_3_C();
	unsigned int RES_3_D();
	unsigned int RES_3_E();
	unsigned int RES_3_H();
	unsigned int RES_3_L();
	unsigned int RES_3_MEM_HL();
	unsigned int RES_3_A();
	unsigned int RES_4_B();
	unsigned int RES_4_C();
	unsigned int RES_4_D();
	unsigned int RES_4_E();
	unsigned int RES_4_H();
	unsigned int RES_4_L();
	unsigned int RES_4_MEM_HL();
	unsigned int RES_4_A();
	unsigned int RES_5_B();
	unsigned int RES_5_C();
	unsigned int RES_5_D();
	unsigned int RES_5_E();
	unsigned int RES_5_H();
	unsigned int RES_5_L();
	unsigned int RES_5_MEM_HL();
	unsigned int RES_5_A();
	unsigned int RES_6_B();
	unsigned int RES_6_C();
	unsigned int RES_6_D();
	unsigned int RES_6_E();
	unsigned int RES_6_H();
	unsigned int RES_6_L();
	unsigned int RES_6_MEM_HL();
	unsigned int RES_6_A();
	unsigned int RES_7_B();
	unsigned int RES_7_C();
	unsigned int RES_7_D();
	unsigned int RES_7_E();
	unsigned int RES_7_H();
	unsigned int RES_7_L();
	unsigned int RES_7_MEM_HL();
	unsigned int RES_7_A();
	unsigned int SET_0_B();
	unsigned int SET_0_C();
	unsigned int SET_0_D();
	unsigned int SET_0_E();
	unsigned int SET_0_H();
	unsigned int SET_0_L();
	unsigned int SET_0_MEM_HL();
	unsigned int SET_0_A();
	unsigned int SET_1_B();
	unsigned int SET_1_C();
	unsigned int SET_1_D();
	unsigned int SET_1_E();
	unsigned int SET_1_H();
	unsigned int SET_1_L();
	unsigned int SET_1_MEM_HL();
	unsigned int SET_1_A();
	unsigned int SET_2_B();
	unsigned int SET_2_C();
	unsigned int SET_2_D();
	unsigned int SET_2_E();
	unsigned int SET_2_H();
	unsigned int SET_2_L();
	unsigned int SET_2_MEM_HL();
	unsigned int SET_2_A();
	unsigned int SET_3_B();
	unsigned int SET_3_C();
	unsigned int SET_3_D();
	unsigned int SET_3_E();
	unsigned int SET_3_H();
	unsigned int SET_3_L();
	unsigned int SET_3_MEM_HL();
	unsigned int SET_3_A();
	unsigned int SET_4_B();
	unsigned int SET_4_C();
	unsigned int SET_4_D();
	unsigned int SET_4_E();
	unsigned int SET_4_H();
	unsigned int SET_4_L();
	unsigned int SET_4_MEM_HL();
	unsigned int SET_4_A();
	unsigned int SET_5_B();
	unsigned int SET_5_C();
	unsigned int SET_5_D();
	unsigned int SET_5_E();
	unsigned int SET_5_H();
	unsigned int SET_5_L();
	unsigned int SET_5_MEM_HL();
	unsigned int SET_5_A();
	unsigned int SET_6_B();
	unsigned int SET_6_C();
	unsigned int SET_6_D();
	unsigned int SET_6_E();
	unsigned int SET_6_H();
	unsigned int SET_6_L();
	unsigned int SET_6_MEM_HL();
	unsigned int SET_6_A();
	unsigned int SET_7_B();
	unsigned int SET_7_C();
	unsigned int SET_7_D();
	unsigned int SET_7_E();
	unsigned int SET_7_H();
	unsigned int SET_7_L();
	unsigned int SET_7_MEM_HL();
	unsigned int SET_7_A();
};
