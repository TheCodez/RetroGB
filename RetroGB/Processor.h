#pragma once

#include "Definitions.h"
#include <functional>

#include "Memory.h"


const uint8 opcodeCycles[256] = 
{
    1, 3, 2, 2, 1, 1, 2, 1, 5, 2, 2, 2, 1, 1, 2, 1,
    1, 3, 2, 2, 1, 1, 2, 1, 3, 2, 2, 2, 1, 1, 2, 1,
    2, 3, 2, 2, 1, 1, 2, 1, 2, 2, 2, 2, 1, 1, 2, 1,
    2, 3, 2, 2, 3, 3, 3, 1, 2, 2, 2, 2, 1, 1, 2, 1,
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1,
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    2, 3, 3, 4, 3, 4, 2, 4, 2, 4, 3, 0, 3, 6, 2, 4,
    2, 3, 3, 0, 3, 4, 2, 4, 2, 4, 3, 0, 3, 0, 2, 4,
    3, 3, 2, 0, 0, 4, 2, 4, 4, 1, 4, 0, 0, 0, 2, 4,
    3, 3, 2, 1, 0, 4, 2, 4, 3, 2, 4, 1, 0, 0, 2, 4
};

const uint8 opcodeCBCycles[256] = 
{
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2,
    2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2,
    2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2,
    2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2,
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2
};

enum Interrupts
{
    VBlank = 0x01,
    LCDSTAT = 0x02,
    Timer = 0x04,
    Serial = 0x08,
    Joypad = 0x10
};

class Processor
{
public:
    Processor(Memory* mem);
    ~Processor();

    int Run();
    void Reset(bool color = false);
    void RequestInterrupt(Interrupts interrupt);
private:
    void InitOpcodes();
    void HandleInterrupts();
    void SetFlag(uint8 flag);
    void EnableFlag(uint8 flag);
    void DisableFlag(uint8 flag);
    void InvertFlag(uint8 flag);
    void ClearFlags();
    bool IsFlagSet(uint8 flag);

    void UnknownOpcode();
    void InvalidOpcode();
    void StackPush(uint16& reg);
    void StackPop(uint16& reg);
    void Add(uint8 reg);
    void Adc(uint8 reg);
    void Sub(uint8 reg);
    void Sbc(uint8 reg);

    void AddHL(uint16 val);
    void AddSP(uint8 val);

public:
    Memory* memory;
    std::function<void()> opcodes[256];
    std::function<void()> opcodesCB[256];

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
    void NOP();
    void LD_BC_nn();
    void LD_MEM_BC_A();
    void INC_BC();
    void INC_B();
    void DEC_B();
    void LD_B_n();
    void RLCA();
    void LD_MEM_nn_SP();
    void ADD_HL_BC();
    void LD_A_MEM_BC();
    void DEC_BC();
    void INC_C();
    void DEC_C();
    void LD_C_n();
    void RRCA();
    void STOP();
    void LD_DE_nn();
    void LD_MEM_DE_A();
    void INC_DE();
    void INC_D();
    void DEC_D();
    void LD_D_n();
    void RLA();
    void JR_n();
    void ADD_HL_DE();
    void LD_A_MEM_DE();
    void DEC_DE();
    void INC_E();
    void DEC_E();
    void LD_E_n();
    void RRA();
    void JR_NZ_n();
    void LD_HL_nn();
    void LD_MEM_HLI_A();
    void INC_HL();
    void INC_H();
    void DEC_H();
    void LD_H_n();
    void DAA();
    void JR_Z_n();
    void ADD_HL_HL();
    void LD_A_MEM_HLI();
    void DEC_HL();
    void INC_L();
    void DEC_L();
    void LD_L_n();
    void CPL();
    void JR_NC_n();
    void LD_SP_nn();
    void LD_MEM_HLD_A();
    void INC_SP();
    void INC_MEM_HL();
    void DEC_MEM_HL();
    void LD_MEM_HL_n();
    void SCF();
    void JR_C_n();
    void ADD_HL_SP();
    void LD_A_MEM_HLD();
    void DEC_SP();
    void INC_A();
    void DEC_A();
    void LD_A_n();
    void CCF();
    void LD_B_B();
    void LD_B_C();
    void LD_B_D();
    void LD_B_E();
    void LD_B_H();
    void LD_B_L();
    void LD_B_MEM_HL();
    void LD_B_A();
    void LD_C_B();
    void LD_C_C();
    void LD_C_D();
    void LD_C_E();
    void LD_C_H();
    void LD_C_L();
    void LD_C_MEM_HL();
    void LD_C_A();
    void LD_D_B();
    void LD_D_C();
    void LD_D_D();
    void LD_D_E();
    void LD_D_H();
    void LD_D_L();
    void LD_D_MEM_HL();
    void LD_D_A();
    void LD_E_B();
    void LD_E_C();
    void LD_E_D();
    void LD_E_E();
    void LD_E_H();
    void LD_E_L();
    void LD_E_MEM_HL();
    void LD_E_A();
    void LD_H_B();
    void LD_H_C();
    void LD_H_D();
    void LD_H_E();
    void LD_H_H();
    void LD_H_L();
    void LD_H_MEM_HL();
    void LD_H_A();
    void LD_L_B();
    void LD_L_C();
    void LD_L_D();
    void LD_L_E();
    void LD_L_H();
    void LD_L_L();
    void LD_L_MEM_HL();
    void LD_L_A();
    void LD_MEM_HL_B();
    void LD_MEM_HL_C();
    void LD_MEM_HL_D();
    void LD_MEM_HL_E();
    void LD_MEM_HL_H();
    void LD_MEM_HL_L();
    void HALT();
    void LD_MEM_HL_A();
    void LD_A_B();
    void LD_A_C();
    void LD_A_D();
    void LD_A_E();
    void LD_A_H();
    void LD_A_L();
    void LD_A_MEM_HL();
    void LD_A_A();
    void ADD_A_B();
    void ADD_A_C();
    void ADD_A_D();
    void ADD_A_E();
    void ADD_A_H();
    void ADD_A_L();
    void ADD_A_MEM_HL();
    void ADD_A_A();
    void ADC_A_B();
    void ADC_A_C();
    void ADC_A_D();
    void ADC_A_E();
    void ADC_A_H();
    void ADC_A_L();
    void ADC_A_MEM_HL();
    void ADC_A_A();
    void SUB_B();
    void SUB_C();
    void SUB_D();
    void SUB_E();
    void SUB_H();
    void SUB_L();
    void SUB_MEM_HL();
    void SUB_A();
    void SBC_A_B();
    void SBC_A_C();
    void SBC_A_D();
    void SBC_A_E();
    void SBC_A_H();
    void SBC_A_L();
    void SBC_A_MEM_HL();
    void SBC_A_A();
    void AND_B();
    void AND_C();
    void AND_D();
    void AND_E();
    void AND_H();
    void AND_L();
    void AND_MEM_HL();
    void AND_A();
    void XOR_B();
    void XOR_C();
    void XOR_D();
    void XOR_E();
    void XOR_H();
    void XOR_L();
    void XOR_MEM_HL();
    void XOR_A();
    void OR_B();
    void OR_C();
    void OR_D();
    void OR_E();
    void OR_H();
    void OR_L();
    void OR_MEM_HL();
    void OR_A();
    void CP_B();
    void CP_C();
    void CP_D();
    void CP_E();
    void CP_H();
    void CP_L();
    void CP_MEM_HL();
    void CP_A();
    void RET_NZ();
    void POP_BC();
    void JP_NZ_nn();
    void JP_nn();
    void CALL_NZ_nn();
    void PUSH_BC();
    void ADD_A_n();
    void RST();
    void RET_Z();
    void RET();
    void JP_Z_nn();
    void CALL_Z_nn();
    void CALL_nn();
    void ADC_A_n();
    void RST_0x0008();
    void RET_NC();
    void POP_DE();
    void JP_NC_nn();
    void CALL_NC_nn();
    void PUSH_DE();
    void SUB_n();
    void RST_0x0010();
    void RET_C();
    void RETI();
    void JP_C_nn();
    void CALL_C_nn();
    void SBC_A_n();
    void RST_0x0018();
    void LD_MEM_0xFF00_n_A();
    void POP_HL();
    void LD_MEM_0xFF00_C_A();
    void PUSH_HL();
    void AND_n();
    void RST_0x0020();
    void ADD_SP_n();
    void JP_MEM_HL();
    void LD_MEM_nn_A();
    void XOR_n();
    void RST_0x0028();
    void LD_A_MEM_0xFF00_n();
    void POP_AF();
    void LD_A_MEM_0xFF00_C();
    void DI();
    void PUSH_AF();
    void OR_n();
    void RST_0x0030();
    void LD_HL_SP_n();
    void LD_SP_HL();
    void LD_A_MEM_nn();
    void EI();
    void CP_n();
    void RST_0x0038();

    // CB Obcodes
    void RLC_B();
    void RLC_C();
    void RLC_D();
    void RLC_E();
    void RLC_H();
    void RLC_L();
    void RLC_MEM_HL();
    void RLC_A();
    void RRC_B();
    void RRC_C();
    void RRC_D();
    void RRC_E();
    void RRC_H();
    void RRC_L();
    void RRC_MEM_HL();
    void RRC_A();
    void RL_B();
    void RL_C();
    void RL_D();
    void RL_E();
    void RL_H();
    void RL_L();
    void RL_MEM_HL();
    void RL_A();
    void RR_B();
    void RR_C();
    void RR_D();
    void RR_E();
    void RR_H();
    void RR_L();
    void RR_MEM_HL();
    void RR_A();
    void SLA_B();
    void SLA_C();
    void SLA_D();
    void SLA_E();
    void SLA_H();
    void SLA_L();
    void SLA_MEM_HL();
    void SLA_A();
    void SRA_B();
    void SRA_C();
    void SRA_D();
    void SRA_E();
    void SRA_H();
    void SRA_L();
    void SRA_MEM_HL();
    void SRA_A();
    void SWAP_B();
    void SWAP_C();
    void SWAP_D();
    void SWAP_E();
    void SWAP_H();
    void SWAP_L();
    void SWAP_MEM_HL();
    void SWAP_A();
    void SRL_B();
    void SRL_C();
    void SRL_D();
    void SRL_E();
    void SRL_H();
    void SRL_L();
    void SRL_MEM_HL();
    void SRL_A();
    void BIT_0_B();
    void BIT_0_C();
    void BIT_0_D();
    void BIT_0_E();
    void BIT_0_H();
    void BIT_0_L();
    void BIT_0_MEM_HL();
    void BIT_0_A();
    void BIT_1_B();
    void BIT_1_C();
    void BIT_1_D();
    void BIT_1_E();
    void BIT_1_H();
    void BIT_1_L();
    void BIT_1_MEM_HL();
    void BIT_1_A();
    void BIT_2_B();
    void BIT_2_C();
    void BIT_2_D();
    void BIT_2_E();
    void BIT_2_H();
    void BIT_2_L();
    void BIT_2_MEM_HL();
    void BIT_2_A();
    void BIT_3_B();
    void BIT_3_C();
    void BIT_3_D();
    void BIT_3_E();
    void BIT_3_H();
    void BIT_3_L();
    void BIT_3_MEM_HL();
    void BIT_3_A();
    void BIT_4_B();
    void BIT_4_C();
    void BIT_4_D();
    void BIT_4_E();
    void BIT_4_H();
    void BIT_4_L();
    void BIT_4_MEM_HL();
    void BIT_4_A();
    void BIT_5_B();
    void BIT_5_C();
    void BIT_5_D();
    void BIT_5_E();
    void BIT_5_H();
    void BIT_5_L();
    void BIT_5_MEM_HL();
    void BIT_5_A();
    void BIT_6_B();
    void BIT_6_C();
    void BIT_6_D();
    void BIT_6_E();
    void BIT_6_H();
    void BIT_6_L();
    void BIT_6_MEM_HL();
    void BIT_6_A();
    void BIT_7_B();
    void BIT_7_C();
    void BIT_7_D();
    void BIT_7_E();
    void BIT_7_H();
    void BIT_7_L();
    void BIT_7_MEM_HL();
    void BIT_7_A();
    void RES_0_B();
    void RES_0_C();
    void RES_0_D();
    void RES_0_E();
    void RES_0_H();
    void RES_0_L();
    void RES_0_MEM_HL();
    void RES_0_A();
    void RES_1_B();
    void RES_1_C();
    void RES_1_D();
    void RES_1_E();
    void RES_1_H();
    void RES_1_L();
    void RES_1_MEM_HL();
    void RES_1_A();
    void RES_2_B();
    void RES_2_C();
    void RES_2_D();
    void RES_2_E();
    void RES_2_H();
    void RES_2_L();
    void RES_2_MEM_HL();
    void RES_2_A();
    void RES_3_B();
    void RES_3_C();
    void RES_3_D();
    void RES_3_E();
    void RES_3_H();
    void RES_3_L();
    void RES_3_MEM_HL();
    void RES_3_A();
    void RES_4_B();
    void RES_4_C();
    void RES_4_D();
    void RES_4_E();
    void RES_4_H();
    void RES_4_L();
    void RES_4_MEM_HL();
    void RES_4_A();
    void RES_5_B();
    void RES_5_C();
    void RES_5_D();
    void RES_5_E();
    void RES_5_H();
    void RES_5_L();
    void RES_5_MEM_HL();
    void RES_5_A();
    void RES_6_B();
    void RES_6_C();
    void RES_6_D();
    void RES_6_E();
    void RES_6_H();
    void RES_6_L();
    void RES_6_MEM_HL();
    void RES_6_A();
    void RES_7_B();
    void RES_7_C();
    void RES_7_D();
    void RES_7_E();
    void RES_7_H();
    void RES_7_L();
    void RES_7_MEM_HL();
    void RES_7_A();
    void SET_0_B();
    void SET_0_C();
    void SET_0_D();
    void SET_0_E();
    void SET_0_H();
    void SET_0_L();
    void SET_0_MEM_HL();
    void SET_0_A();
    void SET_1_B();
    void SET_1_C();
    void SET_1_D();
    void SET_1_E();
    void SET_1_H();
    void SET_1_L();
    void SET_1_MEM_HL();
    void SET_1_A();
    void SET_2_B();
    void SET_2_C();
    void SET_2_D();
    void SET_2_E();
    void SET_2_H();
    void SET_2_L();
    void SET_2_MEM_HL();
    void SET_2_A();
    void SET_3_B();
    void SET_3_C();
    void SET_3_D();
    void SET_3_E();
    void SET_3_H();
    void SET_3_L();
    void SET_3_MEM_HL();
    void SET_3_A();
    void SET_4_B();
    void SET_4_C();
    void SET_4_D();
    void SET_4_E();
    void SET_4_H();
    void SET_4_L();
    void SET_4_MEM_HL();
    void SET_4_A();
    void SET_5_B();
    void SET_5_C();
    void SET_5_D();
    void SET_5_E();
    void SET_5_H();
    void SET_5_L();
    void SET_5_MEM_HL();
    void SET_5_A();
    void SET_6_B();
    void SET_6_C();
    void SET_6_D();
    void SET_6_E();
    void SET_6_H();
    void SET_6_L();
    void SET_6_MEM_HL();
    void SET_6_A();
    void SET_7_B();
    void SET_7_C();
    void SET_7_D();
    void SET_7_E();
    void SET_7_H();
    void SET_7_L();
    void SET_7_MEM_HL();
    void SET_7_A();
};

