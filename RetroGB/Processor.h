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

enum Interrupts : uint8
{
    VBLANK = 0x01,
    LCDSTAT = 0x02,
    TIMER = 0x04,
    SERIAL = 0x08,
    JOYPAD = 0x10
};

enum Flags : uint8
{
    ZERO = 0x80,
    SUB = 0x40,
    HALFCARRY = 0x20,
    CARRY = 0x10,
    NONE = 0x00
};

class Processor
{
public:
    Processor(Memory* mem);
    ~Processor();

    int Run();
    void Reset(bool color);
    void RequestInterrupt(Interrupts interrupt);
    bool IsFlagSet(uint8 flag);
private:
    void InitOpcodes();
    void HandleInterrupts();
    void SetFlag(Flags flag);
    void EnableFlag(Flags flag);
    void DisableFlag(Flags flag);
    void InvertFlag(Flags flag);
    void ClearFlags();

    int UnknownOpcode();
    int InvalidOpcode();
    void StackPush(uint16 reg);
    void StackPop(uint16& reg);

    uint8 Inc(uint8 reg);
    uint8 Dec(uint8 reg);

    void Add(uint8 reg);
    void Adc(uint8 reg);
    void Sub(uint8 reg);
    void Sbc(uint8 reg);

    void AddHL(uint16 val);
    void AddSP(uint8 val);

    uint8 Rl(uint8 reg);
    uint8 Rlc(uint8 reg);
    uint8 Rr(uint8 reg);
    uint8 Rrc(uint8 reg);

    uint8 Sla(uint8 reg);
    uint8 Sra(uint8 reg);
    uint8 Srl(uint8 reg);
    void Bit(uint8 reg, uint8 bit);

    Memory* memory;
    std::array<std::function<int()>, 256> opcodes;
    std::array<std::function<int()>, 256> opcodesCB;

public:
    int clockCycles;
    bool ime;
    bool halted;

    uint16 PC;
    uint16 SP;

    union {
        struct {
            uint8 F;
            uint8 A;
        };
        uint16 AF;
    };

    union {
        struct {
            uint8 C;
            uint8 B;
        };
        uint16 BC;
    };

    union {
        struct {
            uint8 E;
            uint8 D;
        };
        uint16 DE;
    };

    union {
        struct {
            uint8 L;
            uint8 H;
        };
        uint16 HL;
    };

private:
	int NOP();
	int LD_BC_nn();
	int LD_MEM_BC_A();
	int INC_BC();
	int INC_B();
	int DEC_B();
	int LD_B_n();
	int RLCA();
	int LD_MEM_nn_SP();
	int ADD_HL_BC();
	int LD_A_MEM_BC();
	int DEC_BC();
	int INC_C();
	int DEC_C();
	int LD_C_n();
	int RRCA();
	int STOP();
	int LD_DE_nn();
	int LD_MEM_DE_A();
	int INC_DE();
	int INC_D();
	int DEC_D();
	int LD_D_n();
	int RLA();
	int JR_n();
	int ADD_HL_DE();
	int LD_A_MEM_DE();
	int DEC_DE();
	int INC_E();
	int DEC_E();
	int LD_E_n();
	int RRA();
	int JR_NZ_n();
	int LD_HL_nn();
	int LD_MEM_HLI_A();
	int INC_HL();
	int INC_H();
	int DEC_H();
	int LD_H_n();
	int DAA();
	int JR_Z_n();
	int ADD_HL_HL();
	int LD_A_MEM_HLI();
	int DEC_HL();
	int INC_L();
	int DEC_L();
	int LD_L_n();
	int CPL();
	int JR_NC_n();
	int LD_SP_nn();
	int LD_MEM_HLD_A();
	int INC_SP();
	int INC_MEM_HL();
	int DEC_MEM_HL();
	int LD_MEM_HL_n();
	int SCF();
	int JR_C_n();
	int ADD_HL_SP();
	int LD_A_MEM_HLD();
	int DEC_SP();
	int INC_A();
	int DEC_A();
	int LD_A_n();
	int CCF();
	int LD_B_B();
	int LD_B_C();
	int LD_B_D();
	int LD_B_E();
	int LD_B_H();
	int LD_B_L();
	int LD_B_MEM_HL();
	int LD_B_A();
	int LD_C_B();
	int LD_C_C();
	int LD_C_D();
	int LD_C_E();
	int LD_C_H();
	int LD_C_L();
	int LD_C_MEM_HL();
	int LD_C_A();
	int LD_D_B();
	int LD_D_C();
	int LD_D_D();
	int LD_D_E();
	int LD_D_H();
	int LD_D_L();
	int LD_D_MEM_HL();
	int LD_D_A();
	int LD_E_B();
	int LD_E_C();
	int LD_E_D();
	int LD_E_E();
	int LD_E_H();
	int LD_E_L();
	int LD_E_MEM_HL();
	int LD_E_A();
	int LD_H_B();
	int LD_H_C();
	int LD_H_D();
	int LD_H_E();
	int LD_H_H();
	int LD_H_L();
	int LD_H_MEM_HL();
	int LD_H_A();
	int LD_L_B();
	int LD_L_C();
	int LD_L_D();
	int LD_L_E();
	int LD_L_H();
	int LD_L_L();
	int LD_L_MEM_HL();
	int LD_L_A();
	int LD_MEM_HL_B();
	int LD_MEM_HL_C();
	int LD_MEM_HL_D();
	int LD_MEM_HL_E();
	int LD_MEM_HL_H();
	int LD_MEM_HL_L();
	int HALT();
	int LD_MEM_HL_A();
	int LD_A_B();
	int LD_A_C();
	int LD_A_D();
	int LD_A_E();
	int LD_A_H();
	int LD_A_L();
	int LD_A_MEM_HL();
	int LD_A_A();
	int ADD_A_B();
	int ADD_A_C();
	int ADD_A_D();
	int ADD_A_E();
	int ADD_A_H();
	int ADD_A_L();
	int ADD_A_MEM_HL();
	int ADD_A_A();
	int ADC_A_B();
	int ADC_A_C();
	int ADC_A_D();
	int ADC_A_E();
	int ADC_A_H();
	int ADC_A_L();
	int ADC_A_MEM_HL();
	int ADC_A_A();
	int SUB_B();
	int SUB_C();
	int SUB_D();
	int SUB_E();
	int SUB_H();
	int SUB_L();
	int SUB_MEM_HL();
	int SUB_A();
	int SBC_A_B();
	int SBC_A_C();
	int SBC_A_D();
	int SBC_A_E();
	int SBC_A_H();
	int SBC_A_L();
	int SBC_A_MEM_HL();
	int SBC_A_A();
	int AND_B();
	int AND_C();
	int AND_D();
	int AND_E();
	int AND_H();
	int AND_L();
	int AND_MEM_HL();
	int AND_A();
	int XOR_B();
	int XOR_C();
	int XOR_D();
	int XOR_E();
	int XOR_H();
	int XOR_L();
	int XOR_MEM_HL();
	int XOR_A();
	int OR_B();
	int OR_C();
	int OR_D();
	int OR_E();
	int OR_H();
	int OR_L();
	int OR_MEM_HL();
	int OR_A();
	int CP_B();
	int CP_C();
	int CP_D();
	int CP_E();
	int CP_H();
	int CP_L();
	int CP_MEM_HL();
	int CP_A();
	int RET_NZ();
	int POP_BC();
	int JP_NZ_nn();
	int JP_nn();
	int CALL_NZ_nn();
	int PUSH_BC();
	int ADD_A_n();
	int RST();
	int RET_Z();
	int RET();
	int JP_Z_nn();
	int CALL_Z_nn();
	int CALL_nn();
	int ADC_A_n();
	int RST_0x0008();
	int RET_NC();
	int POP_DE();
	int JP_NC_nn();
	int CALL_NC_nn();
	int PUSH_DE();
	int SUB_n();
	int RST_0x0010();
	int RET_C();
	int RETI();
	int JP_C_nn();
	int CALL_C_nn();
	int SBC_A_n();
	int RST_0x0018();
	int LD_MEM_0xFF00_n_A();
	int POP_HL();
	int LD_MEM_0xFF00_C_A();
	int PUSH_HL();
	int AND_n();
	int RST_0x0020();
	int ADD_SP_n();
	int JP_MEM_HL();
	int LD_MEM_nn_A();
	int XOR_n();
	int RST_0x0028();
	int LD_A_MEM_0xFF00_n();
	int POP_AF();
	int LD_A_MEM_0xFF00_C();
	int DI();
	int PUSH_AF();
	int OR_n();
	int RST_0x0030();
	int LD_HL_SP_n();
	int LD_SP_HL();
	int LD_A_MEM_nn();
	int EI();
	int CP_n();
	int RST_0x0038();

	// CB Obcodes
	int RLC_B();
	int RLC_C();
	int RLC_D();
	int RLC_E();
	int RLC_H();
	int RLC_L();
	int RLC_MEM_HL();
	int RLC_A();
	int RRC_B();
	int RRC_C();
	int RRC_D();
	int RRC_E();
	int RRC_H();
	int RRC_L();
	int RRC_MEM_HL();
	int RRC_A();
	int RL_B();
	int RL_C();
	int RL_D();
	int RL_E();
	int RL_H();
	int RL_L();
	int RL_MEM_HL();
	int RL_A();
	int RR_B();
	int RR_C();
	int RR_D();
	int RR_E();
	int RR_H();
	int RR_L();
	int RR_MEM_HL();
	int RR_A();
	int SLA_B();
	int SLA_C();
	int SLA_D();
	int SLA_E();
	int SLA_H();
	int SLA_L();
	int SLA_MEM_HL();
	int SLA_A();
	int SRA_B();
	int SRA_C();
	int SRA_D();
	int SRA_E();
	int SRA_H();
	int SRA_L();
	int SRA_MEM_HL();
	int SRA_A();
	int SWAP_B();
	int SWAP_C();
	int SWAP_D();
	int SWAP_E();
	int SWAP_H();
	int SWAP_L();
	int SWAP_MEM_HL();
	int SWAP_A();
	int SRL_B();
	int SRL_C();
	int SRL_D();
	int SRL_E();
	int SRL_H();
	int SRL_L();
	int SRL_MEM_HL();
	int SRL_A();
	int BIT_0_B();
	int BIT_0_C();
	int BIT_0_D();
	int BIT_0_E();
	int BIT_0_H();
	int BIT_0_L();
	int BIT_0_MEM_HL();
	int BIT_0_A();
	int BIT_1_B();
	int BIT_1_C();
	int BIT_1_D();
	int BIT_1_E();
	int BIT_1_H();
	int BIT_1_L();
	int BIT_1_MEM_HL();
	int BIT_1_A();
	int BIT_2_B();
	int BIT_2_C();
	int BIT_2_D();
	int BIT_2_E();
	int BIT_2_H();
	int BIT_2_L();
	int BIT_2_MEM_HL();
	int BIT_2_A();
	int BIT_3_B();
	int BIT_3_C();
	int BIT_3_D();
	int BIT_3_E();
	int BIT_3_H();
	int BIT_3_L();
	int BIT_3_MEM_HL();
	int BIT_3_A();
	int BIT_4_B();
	int BIT_4_C();
	int BIT_4_D();
	int BIT_4_E();
	int BIT_4_H();
	int BIT_4_L();
	int BIT_4_MEM_HL();
	int BIT_4_A();
	int BIT_5_B();
	int BIT_5_C();
	int BIT_5_D();
	int BIT_5_E();
	int BIT_5_H();
	int BIT_5_L();
	int BIT_5_MEM_HL();
	int BIT_5_A();
	int BIT_6_B();
	int BIT_6_C();
	int BIT_6_D();
	int BIT_6_E();
	int BIT_6_H();
	int BIT_6_L();
	int BIT_6_MEM_HL();
	int BIT_6_A();
	int BIT_7_B();
	int BIT_7_C();
	int BIT_7_D();
	int BIT_7_E();
	int BIT_7_H();
	int BIT_7_L();
	int BIT_7_MEM_HL();
	int BIT_7_A();
	int RES_0_B();
	int RES_0_C();
	int RES_0_D();
	int RES_0_E();
	int RES_0_H();
	int RES_0_L();
	int RES_0_MEM_HL();
	int RES_0_A();
	int RES_1_B();
	int RES_1_C();
	int RES_1_D();
	int RES_1_E();
	int RES_1_H();
	int RES_1_L();
	int RES_1_MEM_HL();
	int RES_1_A();
	int RES_2_B();
	int RES_2_C();
	int RES_2_D();
	int RES_2_E();
	int RES_2_H();
	int RES_2_L();
	int RES_2_MEM_HL();
	int RES_2_A();
	int RES_3_B();
	int RES_3_C();
	int RES_3_D();
	int RES_3_E();
	int RES_3_H();
	int RES_3_L();
	int RES_3_MEM_HL();
	int RES_3_A();
	int RES_4_B();
	int RES_4_C();
	int RES_4_D();
	int RES_4_E();
	int RES_4_H();
	int RES_4_L();
	int RES_4_MEM_HL();
	int RES_4_A();
	int RES_5_B();
	int RES_5_C();
	int RES_5_D();
	int RES_5_E();
	int RES_5_H();
	int RES_5_L();
	int RES_5_MEM_HL();
	int RES_5_A();
	int RES_6_B();
	int RES_6_C();
	int RES_6_D();
	int RES_6_E();
	int RES_6_H();
	int RES_6_L();
	int RES_6_MEM_HL();
	int RES_6_A();
	int RES_7_B();
	int RES_7_C();
	int RES_7_D();
	int RES_7_E();
	int RES_7_H();
	int RES_7_L();
	int RES_7_MEM_HL();
	int RES_7_A();
	int SET_0_B();
	int SET_0_C();
	int SET_0_D();
	int SET_0_E();
	int SET_0_H();
	int SET_0_L();
	int SET_0_MEM_HL();
	int SET_0_A();
	int SET_1_B();
	int SET_1_C();
	int SET_1_D();
	int SET_1_E();
	int SET_1_H();
	int SET_1_L();
	int SET_1_MEM_HL();
	int SET_1_A();
	int SET_2_B();
	int SET_2_C();
	int SET_2_D();
	int SET_2_E();
	int SET_2_H();
	int SET_2_L();
	int SET_2_MEM_HL();
	int SET_2_A();
	int SET_3_B();
	int SET_3_C();
	int SET_3_D();
	int SET_3_E();
	int SET_3_H();
	int SET_3_L();
	int SET_3_MEM_HL();
	int SET_3_A();
	int SET_4_B();
	int SET_4_C();
	int SET_4_D();
	int SET_4_E();
	int SET_4_H();
	int SET_4_L();
	int SET_4_MEM_HL();
	int SET_4_A();
	int SET_5_B();
	int SET_5_C();
	int SET_5_D();
	int SET_5_E();
	int SET_5_H();
	int SET_5_L();
	int SET_5_MEM_HL();
	int SET_5_A();
	int SET_6_B();
	int SET_6_C();
	int SET_6_D();
	int SET_6_E();
	int SET_6_H();
	int SET_6_L();
	int SET_6_MEM_HL();
	int SET_6_A();
	int SET_7_B();
	int SET_7_C();
	int SET_7_D();
	int SET_7_E();
	int SET_7_H();
	int SET_7_L();
	int SET_7_MEM_HL();
	int SET_7_A();
};
