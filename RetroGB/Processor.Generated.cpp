#include "Processor.h"

void Processor::InitOpcodes()
{
	opcodes[0x00] = std::bind(&Processor::NOP, this);
	opcodes[0x01] = std::bind(&Processor::LD_BC_nn, this);
	opcodes[0x02] = std::bind(&Processor::LD_MEM_BC_A, this);
	opcodes[0x03] = std::bind(&Processor::INC_BC, this);
	opcodes[0x04] = std::bind(&Processor::INC_B, this);
	opcodes[0x05] = std::bind(&Processor::DEC_B, this);
	opcodes[0x06] = std::bind(&Processor::LD_B_n, this);
	opcodes[0x07] = std::bind(&Processor::RLCA, this);
	opcodes[0x08] = std::bind(&Processor::LD_MEM_nn_SP, this);
	opcodes[0x09] = std::bind(&Processor::ADD_HL_BC, this);
	opcodes[0x0A] = std::bind(&Processor::LD_A_MEM_BC, this);
	opcodes[0x0B] = std::bind(&Processor::DEC_BC, this);
	opcodes[0x0C] = std::bind(&Processor::INC_C, this);
	opcodes[0x0D] = std::bind(&Processor::DEC_C, this);
	opcodes[0x0E] = std::bind(&Processor::LD_C_n, this);
	opcodes[0x0F] = std::bind(&Processor::RRCA, this);
	opcodes[0x10] = std::bind(&Processor::STOP, this);
	opcodes[0x11] = std::bind(&Processor::LD_DE_nn, this);
	opcodes[0x12] = std::bind(&Processor::LD_MEM_DE_A, this);
	opcodes[0x13] = std::bind(&Processor::INC_DE, this);
	opcodes[0x14] = std::bind(&Processor::INC_D, this);
	opcodes[0x15] = std::bind(&Processor::DEC_D, this);
	opcodes[0x16] = std::bind(&Processor::LD_D_n, this);
	opcodes[0x17] = std::bind(&Processor::RLA, this);
	opcodes[0x18] = std::bind(&Processor::JR_n, this);
	opcodes[0x19] = std::bind(&Processor::ADD_HL_DE, this);
	opcodes[0x1A] = std::bind(&Processor::LD_A_MEM_DE, this);
	opcodes[0x1B] = std::bind(&Processor::DEC_DE, this);
	opcodes[0x1C] = std::bind(&Processor::INC_E, this);
	opcodes[0x1D] = std::bind(&Processor::DEC_E, this);
	opcodes[0x1E] = std::bind(&Processor::LD_E_n, this);
	opcodes[0x1F] = std::bind(&Processor::RRA, this);
	opcodes[0x20] = std::bind(&Processor::JR_NZ_n, this);
	opcodes[0x21] = std::bind(&Processor::LD_HL_nn, this);
	opcodes[0x22] = std::bind(&Processor::LD_MEM_HLI_A, this);
	opcodes[0x23] = std::bind(&Processor::INC_HL, this);
	opcodes[0x24] = std::bind(&Processor::INC_H, this);
	opcodes[0x25] = std::bind(&Processor::DEC_H, this);
	opcodes[0x26] = std::bind(&Processor::LD_H_n, this);
	opcodes[0x27] = std::bind(&Processor::DAA, this);
	opcodes[0x28] = std::bind(&Processor::JR_Z_n, this);
	opcodes[0x29] = std::bind(&Processor::ADD_HL_HL, this);
	opcodes[0x2A] = std::bind(&Processor::LD_A_MEM_HLI, this);
	opcodes[0x2B] = std::bind(&Processor::DEC_HL, this);
	opcodes[0x2C] = std::bind(&Processor::INC_L, this);
	opcodes[0x2D] = std::bind(&Processor::DEC_L, this);
	opcodes[0x2E] = std::bind(&Processor::LD_L_n, this);
	opcodes[0x2F] = std::bind(&Processor::CPL, this);
	opcodes[0x30] = std::bind(&Processor::JR_NC_n, this);
	opcodes[0x31] = std::bind(&Processor::LD_SP_nn, this);
	opcodes[0x32] = std::bind(&Processor::LD_MEM_HLD_A, this);
	opcodes[0x33] = std::bind(&Processor::INC_SP, this);
	opcodes[0x34] = std::bind(&Processor::INC_MEM_HL, this);
	opcodes[0x35] = std::bind(&Processor::DEC_MEM_HL, this);
	opcodes[0x36] = std::bind(&Processor::LD_MEM_HL_n, this);
	opcodes[0x37] = std::bind(&Processor::SCF, this);
	opcodes[0x38] = std::bind(&Processor::JR_C_n, this);
	opcodes[0x39] = std::bind(&Processor::ADD_HL_SP, this);
	opcodes[0x3A] = std::bind(&Processor::LD_A_MEM_HLD, this);
	opcodes[0x3B] = std::bind(&Processor::DEC_SP, this);
	opcodes[0x3C] = std::bind(&Processor::INC_A, this);
	opcodes[0x3D] = std::bind(&Processor::DEC_A, this);
	opcodes[0x3E] = std::bind(&Processor::LDA_n, this);
	opcodes[0x3F] = std::bind(&Processor::CCF, this);
	opcodes[0x40] = std::bind(&Processor::LD_B_B, this);
	opcodes[0x41] = std::bind(&Processor::LD_B_C, this);
	opcodes[0x42] = std::bind(&Processor::LD_B_D, this);
	opcodes[0x43] = std::bind(&Processor::LD_B_E, this);
	opcodes[0x44] = std::bind(&Processor::LD_B_H, this);
	opcodes[0x45] = std::bind(&Processor::LD_B_L, this);
	opcodes[0x46] = std::bind(&Processor::LD_B_MEM_HL, this);
	opcodes[0x47] = std::bind(&Processor::LD_B_A, this);
	opcodes[0x48] = std::bind(&Processor::LD_C_B, this);
	opcodes[0x49] = std::bind(&Processor::LD_C_C, this);
	opcodes[0x4A] = std::bind(&Processor::LD_C_D, this);
	opcodes[0x4B] = std::bind(&Processor::LD_C_E, this);
	opcodes[0x4C] = std::bind(&Processor::LD_C_H, this);
	opcodes[0x4D] = std::bind(&Processor::LD_C_L, this);
	opcodes[0x4E] = std::bind(&Processor::LD_C_MEM_HL, this);
	opcodes[0x4F] = std::bind(&Processor::LD_C_A, this);
	opcodes[0x50] = std::bind(&Processor::LD_D_B, this);
	opcodes[0x51] = std::bind(&Processor::LD_D_C, this);
	opcodes[0x52] = std::bind(&Processor::LD_D_D, this);
	opcodes[0x53] = std::bind(&Processor::LD_D_E, this);
	opcodes[0x54] = std::bind(&Processor::LD_D_H, this);
	opcodes[0x55] = std::bind(&Processor::LD_D_L, this);
	opcodes[0x56] = std::bind(&Processor::LD_D_MEM_HL, this);
	opcodes[0x57] = std::bind(&Processor::LD_D_A, this);
	opcodes[0x58] = std::bind(&Processor::LD_E_B, this);
	opcodes[0x59] = std::bind(&Processor::LD_E_C, this);
	opcodes[0x5A] = std::bind(&Processor::LD_E_D, this);
	opcodes[0x5B] = std::bind(&Processor::LD_E_E, this);
	opcodes[0x5C] = std::bind(&Processor::LD_E_H, this);
	opcodes[0x5D] = std::bind(&Processor::LD_E_L, this);
	opcodes[0x5E] = std::bind(&Processor::LD_E_MEM_HL, this);
	opcodes[0x5F] = std::bind(&Processor::LD_E_A, this);
	opcodes[0x60] = std::bind(&Processor::LD_H_B, this);
	opcodes[0x61] = std::bind(&Processor::LD_H_C, this);
	opcodes[0x62] = std::bind(&Processor::LD_H_D, this);
	opcodes[0x63] = std::bind(&Processor::LD_H_E, this);
	opcodes[0x64] = std::bind(&Processor::LD_H_H, this);
	opcodes[0x65] = std::bind(&Processor::LD_H_L, this);
	opcodes[0x66] = std::bind(&Processor::LD_H_MEM_HL, this);
	opcodes[0x67] = std::bind(&Processor::LD_H_A, this);
	opcodes[0x68] = std::bind(&Processor::LD_L_B, this);
	opcodes[0x69] = std::bind(&Processor::LD_L_C, this);
	opcodes[0x6A] = std::bind(&Processor::LD_L_D, this);
	opcodes[0x6B] = std::bind(&Processor::LD_L_E, this);
	opcodes[0x6C] = std::bind(&Processor::LD_L_H, this);
	opcodes[0x6D] = std::bind(&Processor::LD_L_L, this);
	opcodes[0x6E] = std::bind(&Processor::LD_L_MEM_HL, this);
	opcodes[0x6F] = std::bind(&Processor::LD_L_A, this);
	opcodes[0x70] = std::bind(&Processor::LD_MEM_HL_B, this);
	opcodes[0x71] = std::bind(&Processor::LD_MEM_HL_C, this);
	opcodes[0x72] = std::bind(&Processor::LD_MEM_HL_D, this);
	opcodes[0x73] = std::bind(&Processor::LD_MEM_HL_E, this);
	opcodes[0x74] = std::bind(&Processor::LD_MEM_HL_H, this);
	opcodes[0x75] = std::bind(&Processor::LD_MEM_HL_L, this);
	opcodes[0x76] = std::bind(&Processor::HALT, this);
	opcodes[0x77] = std::bind(&Processor::LD_MEM_HL_A, this);
	opcodes[0x78] = std::bind(&Processor::LD_A_B, this);
	opcodes[0x79] = std::bind(&Processor::LD_A_C, this);
	opcodes[0x7A] = std::bind(&Processor::LD_A_D, this);
	opcodes[0x7B] = std::bind(&Processor::LD_A_E, this);
	opcodes[0x7C] = std::bind(&Processor::LD_A_H, this);
	opcodes[0x7D] = std::bind(&Processor::LD_A_L, this);
	opcodes[0x7E] = std::bind(&Processor::LD_A_MEM_HL, this);
	opcodes[0x7F] = std::bind(&Processor::LD_A_A, this);
	opcodes[0x80] = std::bind(&Processor::ADD_A_B, this);
	opcodes[0x81] = std::bind(&Processor::ADD_A_C, this);
	opcodes[0x82] = std::bind(&Processor::ADD_A_D, this);
	opcodes[0x83] = std::bind(&Processor::ADD_A_E, this);
	opcodes[0x84] = std::bind(&Processor::ADD_A_H, this);
	opcodes[0x85] = std::bind(&Processor::ADD_A_L, this);
	opcodes[0x86] = std::bind(&Processor::ADD_A_MEM_HL, this);
	opcodes[0x87] = std::bind(&Processor::ADD_A_A, this);
	opcodes[0x88] = std::bind(&Processor::ADC_A_B, this);
	opcodes[0x89] = std::bind(&Processor::ADC_A_C, this);
	opcodes[0x8A] = std::bind(&Processor::ADC_A_D, this);
	opcodes[0x8B] = std::bind(&Processor::ADC_A_E, this);
	opcodes[0x8C] = std::bind(&Processor::ADC_A_H, this);
	opcodes[0x8D] = std::bind(&Processor::ADC_A_L, this);
	opcodes[0x8E] = std::bind(&Processor::ADC_A_MEM_HL, this);
	opcodes[0x8F] = std::bind(&Processor::ADC_A_A, this);
	opcodes[0x90] = std::bind(&Processor::SUB_B, this);
	opcodes[0x91] = std::bind(&Processor::SUB_C, this);
	opcodes[0x92] = std::bind(&Processor::SUB_D, this);
	opcodes[0x93] = std::bind(&Processor::SUB_E, this);
	opcodes[0x94] = std::bind(&Processor::SUB_H, this);
	opcodes[0x95] = std::bind(&Processor::SUB_L, this);
	opcodes[0x96] = std::bind(&Processor::SUB_MEM_HL, this);
	opcodes[0x97] = std::bind(&Processor::SUB_A, this);
	opcodes[0x98] = std::bind(&Processor::SBC_A_B, this);
	opcodes[0x99] = std::bind(&Processor::SBC_A_C, this);
	opcodes[0x9A] = std::bind(&Processor::SBC_A_D, this);
	opcodes[0x9B] = std::bind(&Processor::SBC_A_E, this);
	opcodes[0x9C] = std::bind(&Processor::SBC_A_H, this);
	opcodes[0x9D] = std::bind(&Processor::SBC_A_L, this);
	opcodes[0x9E] = std::bind(&Processor::SBC_A_MEM_HL, this);
	opcodes[0x9F] = std::bind(&Processor::SBC_A_A, this);
	opcodes[0xA0] = std::bind(&Processor::AND_B, this);
	opcodes[0xA1] = std::bind(&Processor::AND_C, this);
	opcodes[0xA2] = std::bind(&Processor::AND_D, this);
	opcodes[0xA3] = std::bind(&Processor::AND_E, this);
	opcodes[0xA4] = std::bind(&Processor::AND_H, this);
	opcodes[0xA5] = std::bind(&Processor::AND_L, this);
	opcodes[0xA6] = std::bind(&Processor::AND_MEM_HL, this);
	opcodes[0xA7] = std::bind(&Processor::AND_A, this);
	opcodes[0xA8] = std::bind(&Processor::XOR_B, this);
	opcodes[0xA9] = std::bind(&Processor::XOR_C, this);
	opcodes[0xAA] = std::bind(&Processor::XOR_D, this);
	opcodes[0xAB] = std::bind(&Processor::XOR_E, this);
	opcodes[0xAC] = std::bind(&Processor::XOR_H, this);
	opcodes[0xAD] = std::bind(&Processor::XOR_L, this);
	opcodes[0xAE] = std::bind(&Processor::XOR_MEM_HL, this);
	opcodes[0xAF] = std::bind(&Processor::XOR_A, this);
	opcodes[0xB0] = std::bind(&Processor::OR_B, this);
	opcodes[0xB1] = std::bind(&Processor::OR_C, this);
	opcodes[0xB2] = std::bind(&Processor::OR_D, this);
	opcodes[0xB3] = std::bind(&Processor::OR_E, this);
	opcodes[0xB4] = std::bind(&Processor::OR_H, this);
	opcodes[0xB5] = std::bind(&Processor::OR_L, this);
	opcodes[0xB6] = std::bind(&Processor::OR_MEM_HL, this);
	opcodes[0xB7] = std::bind(&Processor::OR_A, this);
	opcodes[0xB8] = std::bind(&Processor::CP_B, this);
	opcodes[0xB9] = std::bind(&Processor::CP_C, this);
	opcodes[0xBA] = std::bind(&Processor::CP_D, this);
	opcodes[0xBB] = std::bind(&Processor::CP_E, this);
	opcodes[0xBC] = std::bind(&Processor::CP_H, this);
	opcodes[0xBD] = std::bind(&Processor::CP_L, this);
	opcodes[0xBE] = std::bind(&Processor::CP_MEM_HL, this);
	opcodes[0xBF] = std::bind(&Processor::CP_A, this);
	opcodes[0xC0] = std::bind(&Processor::RET_NZ, this);
	opcodes[0xC1] = std::bind(&Processor::POP_BC, this);
	opcodes[0xC2] = std::bind(&Processor::JP_NZ_nn, this);
	opcodes[0xC3] = std::bind(&Processor::JP_nn, this);
	opcodes[0xC4] = std::bind(&Processor::CALL_NZ_nn, this);
	opcodes[0xC5] = std::bind(&Processor::PUSH_BC, this);
	opcodes[0xC6] = std::bind(&Processor::ADD_A_n, this);
	opcodes[0xC7] = std::bind(&Processor::RST, this);
	opcodes[0xC8] = std::bind(&Processor::RET_Z, this);
	opcodes[0xC9] = std::bind(&Processor::RET, this);
	opcodes[0xCA] = std::bind(&Processor::JP_Z_nn, this);
	opcodes[0xCC] = std::bind(&Processor::CALL_Z_nn, this);
	opcodes[0xCD] = std::bind(&Processor::CALL_nn, this);
	opcodes[0xCE] = std::bind(&Processor::ADC_A_n, this);
	opcodes[0xCF] = std::bind(&Processor::RST_0x08, this);
	opcodes[0xD0] = std::bind(&Processor::RET_NC, this);
	opcodes[0xD1] = std::bind(&Processor::POP_DE, this);
	opcodes[0xD2] = std::bind(&Processor::JP_NC_nn, this);
	opcodes[0xD4] = std::bind(&Processor::CALL_NC_nn, this);
	opcodes[0xD5] = std::bind(&Processor::PUSH_DE, this);
	opcodes[0xD6] = std::bind(&Processor::SUB_n, this);
	opcodes[0xD7] = std::bind(&Processor::RST_0x10, this);
	opcodes[0xD8] = std::bind(&Processor::RET_C, this);
	opcodes[0xD9] = std::bind(&Processor::RETI, this);
	opcodes[0xDA] = std::bind(&Processor::JP_C_nn, this);
	opcodes[0xDC] = std::bind(&Processor::CALL_C_nn, this);
	opcodes[0xDE] = std::bind(&Processor::SBC_A_n, this);
	opcodes[0xDF] = std::bind(&Processor::RST_0x18, this);
	opcodes[0xE0] = std::bind(&Processor::LD_MEM_0xFF00_n_A, this);
	opcodes[0xE1] = std::bind(&Processor::POP_HL, this);
	opcodes[0xE2] = std::bind(&Processor::LD_MEM_0xFF00_C_A, this);
	opcodes[0xE5] = std::bind(&Processor::PUSH_HL, this);
	opcodes[0xE6] = std::bind(&Processor::AND_n, this);
	opcodes[0xE7] = std::bind(&Processor::RST_0x20, this);
	opcodes[0xE8] = std::bind(&Processor::ADD_SP_n, this);
	opcodes[0xE9] = std::bind(&Processor::JP_MEM_HL, this);
	opcodes[0xEA] = std::bind(&Processor::LD_MEM_nn_A, this);
	opcodes[0xEE] = std::bind(&Processor::XOR_n, this);
	opcodes[0xEF] = std::bind(&Processor::RST_0x28, this);
	opcodes[0xF0] = std::bind(&Processor::LD_A_MEM_0xFF00_n, this);
	opcodes[0xF1] = std::bind(&Processor::POP_AF, this);
	opcodes[0xF2] = std::bind(&Processor::LD_A_MEM_0xFF00_C, this);
	opcodes[0xF3] = std::bind(&Processor::DI, this);
	opcodes[0xF5] = std::bind(&Processor::PUSH_AF, this);
	opcodes[0xF6] = std::bind(&Processor::OR_n, this);
	opcodes[0xF7] = std::bind(&Processor::RST_0x30, this);
	opcodes[0xF8] = std::bind(&Processor::LD_HL_SP, this);
	opcodes[0xF9] = std::bind(&Processor::LD_SP_HL, this);
	opcodes[0xFA] = std::bind(&Processor::LD_A_MEM_nn, this);
	opcodes[0xFB] = std::bind(&Processor::EI, this);
	opcodes[0xFE] = std::bind(&Processor::CP_n, this);
	opcodes[0xFF] = std::bind(&Processor::RST_0x38, this);

	// CB Obcodes
	opcodesCB[0x00] = std::bind(&Processor::RLC_B, this);
	opcodesCB[0x01] = std::bind(&Processor::RLC_C, this);
	opcodesCB[0x02] = std::bind(&Processor::RLC_D, this);
	opcodesCB[0x03] = std::bind(&Processor::RLC_E, this);
	opcodesCB[0x04] = std::bind(&Processor::RLC_H, this);
	opcodesCB[0x05] = std::bind(&Processor::RLC_L, this);
	opcodesCB[0x06] = std::bind(&Processor::RLC_MEM_HL, this);
	opcodesCB[0x07] = std::bind(&Processor::RLC_A, this);
	opcodesCB[0x08] = std::bind(&Processor::RRC_B, this);
	opcodesCB[0x09] = std::bind(&Processor::RRC_C, this);
	opcodesCB[0x0A] = std::bind(&Processor::RRC_D, this);
	opcodesCB[0x0B] = std::bind(&Processor::RRC_E, this);
	opcodesCB[0x0C] = std::bind(&Processor::RRC_H, this);
	opcodesCB[0x0D] = std::bind(&Processor::RRC_L, this);
	opcodesCB[0x0E] = std::bind(&Processor::RRC_MEM_HL, this);
	opcodesCB[0x0F] = std::bind(&Processor::RRC_A, this);
	opcodesCB[0x10] = std::bind(&Processor::RL_B, this);
	opcodesCB[0x11] = std::bind(&Processor::RL_C, this);
	opcodesCB[0x12] = std::bind(&Processor::RL_D, this);
	opcodesCB[0x13] = std::bind(&Processor::RL_E, this);
	opcodesCB[0x14] = std::bind(&Processor::RL_H, this);
	opcodesCB[0x15] = std::bind(&Processor::RL_L, this);
	opcodesCB[0x16] = std::bind(&Processor::RL_MEM_HL, this);
	opcodesCB[0x17] = std::bind(&Processor::RL_A, this);
	opcodesCB[0x18] = std::bind(&Processor::RR_B, this);
	opcodesCB[0x19] = std::bind(&Processor::RR_C, this);
	opcodesCB[0x1A] = std::bind(&Processor::RR_D, this);
	opcodesCB[0x1B] = std::bind(&Processor::RR_E, this);
	opcodesCB[0x1C] = std::bind(&Processor::RR_H, this);
	opcodesCB[0x1D] = std::bind(&Processor::RR_L, this);
	opcodesCB[0x1E] = std::bind(&Processor::RR_MEM_HL, this);
	opcodesCB[0x1F] = std::bind(&Processor::RR_A, this);
	opcodesCB[0x20] = std::bind(&Processor::SLA_B, this);
	opcodesCB[0x21] = std::bind(&Processor::SLA_C, this);
	opcodesCB[0x22] = std::bind(&Processor::SLA_D, this);
	opcodesCB[0x23] = std::bind(&Processor::SLA_E, this);
	opcodesCB[0x24] = std::bind(&Processor::SLA_H, this);
	opcodesCB[0x25] = std::bind(&Processor::SLA_L, this);
	opcodesCB[0x26] = std::bind(&Processor::SLA_MEM_HL, this);
	opcodesCB[0x27] = std::bind(&Processor::SLA_A, this);
	opcodesCB[0x28] = std::bind(&Processor::SRA_B, this);
	opcodesCB[0x29] = std::bind(&Processor::SRA_C, this);
	opcodesCB[0x2A] = std::bind(&Processor::SRA_D, this);
	opcodesCB[0x2B] = std::bind(&Processor::SRA_E, this);
	opcodesCB[0x2C] = std::bind(&Processor::SRA_H, this);
	opcodesCB[0x2D] = std::bind(&Processor::SRA_L, this);
	opcodesCB[0x2E] = std::bind(&Processor::SRA_MEM_HL, this);
	opcodesCB[0x2F] = std::bind(&Processor::SRA_A, this);
	opcodesCB[0x30] = std::bind(&Processor::SWAP_B, this);
	opcodesCB[0x31] = std::bind(&Processor::SWAP_C, this);
	opcodesCB[0x32] = std::bind(&Processor::SWAP_D, this);
	opcodesCB[0x33] = std::bind(&Processor::SWAP_E, this);
	opcodesCB[0x34] = std::bind(&Processor::SWAP_H, this);
	opcodesCB[0x35] = std::bind(&Processor::SWAP_L, this);
	opcodesCB[0x36] = std::bind(&Processor::SWAP_MEM_HL, this);
	opcodesCB[0x37] = std::bind(&Processor::SWAP_A, this);
	opcodesCB[0x38] = std::bind(&Processor::SRL_B, this);
	opcodesCB[0x39] = std::bind(&Processor::SRL_C, this);
	opcodesCB[0x3A] = std::bind(&Processor::SRL_D, this);
	opcodesCB[0x3B] = std::bind(&Processor::SRL_E, this);
	opcodesCB[0x3C] = std::bind(&Processor::SRL_H, this);
	opcodesCB[0x3D] = std::bind(&Processor::SRL_L, this);
	opcodesCB[0x3E] = std::bind(&Processor::SRL_MEM_HL, this);
	opcodesCB[0x3F] = std::bind(&Processor::SRL_A, this);
	opcodesCB[0x40] = std::bind(&Processor::BIT_0_B, this);
	opcodesCB[0x41] = std::bind(&Processor::BIT_0_C, this);
	opcodesCB[0x42] = std::bind(&Processor::BIT_0_D, this);
	opcodesCB[0x43] = std::bind(&Processor::BIT_0_E, this);
	opcodesCB[0x44] = std::bind(&Processor::BIT_0_H, this);
	opcodesCB[0x45] = std::bind(&Processor::BIT_0_L, this);
	opcodesCB[0x46] = std::bind(&Processor::BIT_0_MEM_HL, this);
	opcodesCB[0x47] = std::bind(&Processor::BIT_0_A, this);
	opcodesCB[0x48] = std::bind(&Processor::BIT_1_B, this);
	opcodesCB[0x49] = std::bind(&Processor::BIT_1_C, this);
	opcodesCB[0x4A] = std::bind(&Processor::BIT_1_D, this);
	opcodesCB[0x4B] = std::bind(&Processor::BIT_1_E, this);
	opcodesCB[0x4C] = std::bind(&Processor::BIT_1_H, this);
	opcodesCB[0x4D] = std::bind(&Processor::BIT_1_L, this);
	opcodesCB[0x4E] = std::bind(&Processor::BIT_1_MEM_HL, this);
	opcodesCB[0x4F] = std::bind(&Processor::BIT_1_A, this);
	opcodesCB[0x50] = std::bind(&Processor::BIT_2_B, this);
	opcodesCB[0x51] = std::bind(&Processor::BIT_2_C, this);
	opcodesCB[0x52] = std::bind(&Processor::BIT_2_D, this);
	opcodesCB[0x53] = std::bind(&Processor::BIT_2_E, this);
	opcodesCB[0x54] = std::bind(&Processor::BIT_2_H, this);
	opcodesCB[0x55] = std::bind(&Processor::BIT_2_L, this);
	opcodesCB[0x56] = std::bind(&Processor::BIT_2_MEM_HL, this);
	opcodesCB[0x57] = std::bind(&Processor::BIT_2_A, this);
	opcodesCB[0x58] = std::bind(&Processor::BIT_3_B, this);
	opcodesCB[0x59] = std::bind(&Processor::BIT_3_C, this);
	opcodesCB[0x5A] = std::bind(&Processor::BIT_3_D, this);
	opcodesCB[0x5B] = std::bind(&Processor::BIT_3_E, this);
	opcodesCB[0x5C] = std::bind(&Processor::BIT_3_H, this);
	opcodesCB[0x5D] = std::bind(&Processor::BIT_3_L, this);
	opcodesCB[0x5E] = std::bind(&Processor::BIT_3_MEM_HL, this);
	opcodesCB[0x5F] = std::bind(&Processor::BIT_3_A, this);
	opcodesCB[0x60] = std::bind(&Processor::BIT_4_B, this);
	opcodesCB[0x61] = std::bind(&Processor::BIT_4_C, this);
	opcodesCB[0x62] = std::bind(&Processor::BIT_4_D, this);
	opcodesCB[0x63] = std::bind(&Processor::BIT_4_E, this);
	opcodesCB[0x64] = std::bind(&Processor::BIT_4_H, this);
	opcodesCB[0x65] = std::bind(&Processor::BIT_4_L, this);
	opcodesCB[0x66] = std::bind(&Processor::BIT_4_MEM_HL, this);
	opcodesCB[0x67] = std::bind(&Processor::BIT_4_A, this);
	opcodesCB[0x68] = std::bind(&Processor::BIT_5_B, this);
	opcodesCB[0x69] = std::bind(&Processor::BIT_5_C, this);
	opcodesCB[0x6A] = std::bind(&Processor::BIT_5_D, this);
	opcodesCB[0x6B] = std::bind(&Processor::BIT_5_E, this);
	opcodesCB[0x6C] = std::bind(&Processor::BIT_5_H, this);
	opcodesCB[0x6D] = std::bind(&Processor::BIT_5_L, this);
	opcodesCB[0x6E] = std::bind(&Processor::BIT_5_MEM_HL, this);
	opcodesCB[0x6F] = std::bind(&Processor::BIT_5_A, this);
	opcodesCB[0x70] = std::bind(&Processor::BIT_6_B, this);
	opcodesCB[0x71] = std::bind(&Processor::BIT_6_C, this);
	opcodesCB[0x72] = std::bind(&Processor::BIT_6_D, this);
	opcodesCB[0x73] = std::bind(&Processor::BIT_6_E, this);
	opcodesCB[0x74] = std::bind(&Processor::BIT_6_H, this);
	opcodesCB[0x75] = std::bind(&Processor::BIT_6_L, this);
	opcodesCB[0x76] = std::bind(&Processor::BIT_6_MEM_HL, this);
	opcodesCB[0x77] = std::bind(&Processor::BIT_6_A, this);
	opcodesCB[0x78] = std::bind(&Processor::BIT_7_B, this);
	opcodesCB[0x79] = std::bind(&Processor::BIT_7_C, this);
	opcodesCB[0x7A] = std::bind(&Processor::BIT_7_D, this);
	opcodesCB[0x7B] = std::bind(&Processor::BIT_7_E, this);
	opcodesCB[0x7C] = std::bind(&Processor::BIT_7_H, this);
	opcodesCB[0x7D] = std::bind(&Processor::BIT_7_L, this);
	opcodesCB[0x7E] = std::bind(&Processor::BIT_7_MEM_HL, this);
	opcodesCB[0x7F] = std::bind(&Processor::BIT_7_A, this);
	opcodesCB[0x80] = std::bind(&Processor::RES_0_B, this);
	opcodesCB[0x81] = std::bind(&Processor::RES_0_C, this);
	opcodesCB[0x82] = std::bind(&Processor::RES_0_D, this);
	opcodesCB[0x83] = std::bind(&Processor::RES_0_E, this);
	opcodesCB[0x84] = std::bind(&Processor::RES_0_H, this);
	opcodesCB[0x85] = std::bind(&Processor::RES_0_L, this);
	opcodesCB[0x86] = std::bind(&Processor::RES_0_MEM_HL, this);
	opcodesCB[0x87] = std::bind(&Processor::RES_0_A, this);
	opcodesCB[0x88] = std::bind(&Processor::RES_1_B, this);
	opcodesCB[0x89] = std::bind(&Processor::RES_1_C, this);
	opcodesCB[0x8A] = std::bind(&Processor::RES_1_D, this);
	opcodesCB[0x8B] = std::bind(&Processor::RES_1_E, this);
	opcodesCB[0x8C] = std::bind(&Processor::RES_1_H, this);
	opcodesCB[0x8D] = std::bind(&Processor::RES_1_L, this);
	opcodesCB[0x8E] = std::bind(&Processor::RES_1_MEM_HL, this);
	opcodesCB[0x8F] = std::bind(&Processor::RES_1_A, this);
	opcodesCB[0x90] = std::bind(&Processor::RES_2_B, this);
	opcodesCB[0x91] = std::bind(&Processor::RES_2_C, this);
	opcodesCB[0x92] = std::bind(&Processor::RES_2_D, this);
	opcodesCB[0x93] = std::bind(&Processor::RES_2_E, this);
	opcodesCB[0x94] = std::bind(&Processor::RES_2_H, this);
	opcodesCB[0x95] = std::bind(&Processor::RES_2_L, this);
	opcodesCB[0x96] = std::bind(&Processor::RES_2_MEM_HL, this);
	opcodesCB[0x97] = std::bind(&Processor::RES_2_A, this);
	opcodesCB[0x98] = std::bind(&Processor::RES_3_B, this);
	opcodesCB[0x99] = std::bind(&Processor::RES_3_C, this);
	opcodesCB[0x9A] = std::bind(&Processor::RES_3_D, this);
	opcodesCB[0x9B] = std::bind(&Processor::RES_3_E, this);
	opcodesCB[0x9C] = std::bind(&Processor::RES_3_H, this);
	opcodesCB[0x9D] = std::bind(&Processor::RES_3_L, this);
	opcodesCB[0x9E] = std::bind(&Processor::RES_3_MEM_HL, this);
	opcodesCB[0x9F] = std::bind(&Processor::RES_3_A, this);
	opcodesCB[0xA0] = std::bind(&Processor::RES_4_B, this);
	opcodesCB[0xA1] = std::bind(&Processor::RES_4_C, this);
	opcodesCB[0xA2] = std::bind(&Processor::RES_4_D, this);
	opcodesCB[0xA3] = std::bind(&Processor::RES_4_E, this);
	opcodesCB[0xA4] = std::bind(&Processor::RES_4_H, this);
	opcodesCB[0xA5] = std::bind(&Processor::RES_4_L, this);
	opcodesCB[0xA6] = std::bind(&Processor::RES_4_MEM_HL, this);
	opcodesCB[0xA7] = std::bind(&Processor::RES_4_A, this);
	opcodesCB[0xA8] = std::bind(&Processor::RES_5_B, this);
	opcodesCB[0xA9] = std::bind(&Processor::RES_5_C, this);
	opcodesCB[0xAA] = std::bind(&Processor::RES_5_D, this);
	opcodesCB[0xAB] = std::bind(&Processor::RES_5_E, this);
	opcodesCB[0xAC] = std::bind(&Processor::RES_5_H, this);
	opcodesCB[0xAD] = std::bind(&Processor::RES_5_L, this);
	opcodesCB[0xAE] = std::bind(&Processor::RES_5_MEM_HL, this);
	opcodesCB[0xAF] = std::bind(&Processor::RES_5_A, this);
	opcodesCB[0xB0] = std::bind(&Processor::RES_6_B, this);
	opcodesCB[0xB1] = std::bind(&Processor::RES_6_C, this);
	opcodesCB[0xB2] = std::bind(&Processor::RES_6_D, this);
	opcodesCB[0xB3] = std::bind(&Processor::RES_6_E, this);
	opcodesCB[0xB4] = std::bind(&Processor::RES_6_H, this);
	opcodesCB[0xB5] = std::bind(&Processor::RES_6_L, this);
	opcodesCB[0xB6] = std::bind(&Processor::RES_6_MEM_HL, this);
	opcodesCB[0xB7] = std::bind(&Processor::RES_6_A, this);
	opcodesCB[0xB8] = std::bind(&Processor::RES_7_B, this);
	opcodesCB[0xB9] = std::bind(&Processor::RES_7_C, this);
	opcodesCB[0xBA] = std::bind(&Processor::RES_7_D, this);
	opcodesCB[0xBB] = std::bind(&Processor::RES_7_E, this);
	opcodesCB[0xBC] = std::bind(&Processor::RES_7_H, this);
	opcodesCB[0xBD] = std::bind(&Processor::RES_7_L, this);
	opcodesCB[0xBE] = std::bind(&Processor::RES_7_MEM_HL, this);
	opcodesCB[0xBF] = std::bind(&Processor::RES_7_A, this);
	opcodesCB[0xC0] = std::bind(&Processor::SET_0_B, this);
	opcodesCB[0xC1] = std::bind(&Processor::SET_0_C, this);
	opcodesCB[0xC2] = std::bind(&Processor::SET_0_D, this);
	opcodesCB[0xC3] = std::bind(&Processor::SET_0_E, this);
	opcodesCB[0xC4] = std::bind(&Processor::SET_0_H, this);
	opcodesCB[0xC5] = std::bind(&Processor::SET_0_L, this);
	opcodesCB[0xC6] = std::bind(&Processor::SET_0_MEM_HL, this);
	opcodesCB[0xC7] = std::bind(&Processor::SET_0_A, this);
	opcodesCB[0xC8] = std::bind(&Processor::SET_1_B, this);
	opcodesCB[0xC9] = std::bind(&Processor::SET_1_C, this);
	opcodesCB[0xCA] = std::bind(&Processor::SET_1_D, this);
	opcodesCB[0xCB] = std::bind(&Processor::SET_1_E, this);
	opcodesCB[0xCC] = std::bind(&Processor::SET_1_H, this);
	opcodesCB[0xCD] = std::bind(&Processor::SET_1_L, this);
	opcodesCB[0xCE] = std::bind(&Processor::SET_1_MEM_HL, this);
	opcodesCB[0xCF] = std::bind(&Processor::SET_1_A, this);
	opcodesCB[0xD0] = std::bind(&Processor::SET_2_B, this);
	opcodesCB[0xD1] = std::bind(&Processor::SET_2_C, this);
	opcodesCB[0xD2] = std::bind(&Processor::SET_2_D, this);
	opcodesCB[0xD3] = std::bind(&Processor::SET_2_E, this);
	opcodesCB[0xD4] = std::bind(&Processor::SET_2_H, this);
	opcodesCB[0xD5] = std::bind(&Processor::SET_2_L, this);
	opcodesCB[0xD6] = std::bind(&Processor::SET_2_MEM_HL, this);
	opcodesCB[0xD7] = std::bind(&Processor::SET_2_A, this);
	opcodesCB[0xD8] = std::bind(&Processor::SET_3_B, this);
	opcodesCB[0xD9] = std::bind(&Processor::SET_3_C, this);
	opcodesCB[0xDA] = std::bind(&Processor::SET_3_D, this);
	opcodesCB[0xDB] = std::bind(&Processor::SET_3_E, this);
	opcodesCB[0xDC] = std::bind(&Processor::SET_3_H, this);
	opcodesCB[0xDD] = std::bind(&Processor::SET_3_L, this);
	opcodesCB[0xDE] = std::bind(&Processor::SET_3_MEM_HL, this);
	opcodesCB[0xDF] = std::bind(&Processor::SET_3_A, this);
	opcodesCB[0xE0] = std::bind(&Processor::SET_4_B, this);
	opcodesCB[0xE1] = std::bind(&Processor::SET_4_C, this);
	opcodesCB[0xE2] = std::bind(&Processor::SET_4_D, this);
	opcodesCB[0xE3] = std::bind(&Processor::SET_4_E, this);
	opcodesCB[0xE4] = std::bind(&Processor::SET_4_H, this);
	opcodesCB[0xE5] = std::bind(&Processor::SET_4_L, this);
	opcodesCB[0xE6] = std::bind(&Processor::SET_4_MEM_HL, this);
	opcodesCB[0xE7] = std::bind(&Processor::SET_4_A, this);
	opcodesCB[0xE8] = std::bind(&Processor::SET_5_B, this);
	opcodesCB[0xE9] = std::bind(&Processor::SET_5_C, this);
	opcodesCB[0xEA] = std::bind(&Processor::SET_5_D, this);
	opcodesCB[0xEB] = std::bind(&Processor::SET_5_E, this);
	opcodesCB[0xEC] = std::bind(&Processor::SET_5_H, this);
	opcodesCB[0xED] = std::bind(&Processor::SET_5_L, this);
	opcodesCB[0xEE] = std::bind(&Processor::SET_5_MEM_HL, this);
	opcodesCB[0xEF] = std::bind(&Processor::SET_5_A, this);
	opcodesCB[0xF0] = std::bind(&Processor::SET_6_B, this);
	opcodesCB[0xF1] = std::bind(&Processor::SET_6_C, this);
	opcodesCB[0xF2] = std::bind(&Processor::SET_6_D, this);
	opcodesCB[0xF3] = std::bind(&Processor::SET_6_E, this);
	opcodesCB[0xF4] = std::bind(&Processor::SET_6_H, this);
	opcodesCB[0xF5] = std::bind(&Processor::SET_6_L, this);
	opcodesCB[0xF6] = std::bind(&Processor::SET_6_MEM_HL, this);
	opcodesCB[0xF7] = std::bind(&Processor::SET_6_A, this);
	opcodesCB[0xF8] = std::bind(&Processor::SET_7_B, this);
	opcodesCB[0xF9] = std::bind(&Processor::SET_7_C, this);
	opcodesCB[0xFA] = std::bind(&Processor::SET_7_D, this);
	opcodesCB[0xFB] = std::bind(&Processor::SET_7_E, this);
	opcodesCB[0xFC] = std::bind(&Processor::SET_7_H, this);
	opcodesCB[0xFD] = std::bind(&Processor::SET_7_L, this);
	opcodesCB[0xFE] = std::bind(&Processor::SET_7_MEM_HL, this);
	opcodesCB[0xFF] = std::bind(&Processor::SET_7_A, this);
}

/* NOP */
void Processor::NOP()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD BC, nn */
void Processor::LD_BC_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (BC), A */
void Processor::LD_MEM_BC_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* INC BC */
void Processor::INC_BC()
{
	// Not implemented yet
	UnknownOpcode();
}

/* INC B */
void Processor::INC_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* DEC B */
void Processor::DEC_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD B, n */
void Processor::LD_B_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLCA */
void Processor::RLCA()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (nn), SP */
void Processor::LD_MEM_nn_SP()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADD HL, BC */
void Processor::ADD_HL_BC()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, (BC) */
void Processor::LD_A_MEM_BC()
{
	// Not implemented yet
	UnknownOpcode();
}

/* DEC BC */
void Processor::DEC_BC()
{
	// Not implemented yet
	UnknownOpcode();
}

/* INC C */
void Processor::INC_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* DEC C */
void Processor::DEC_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD C, n */
void Processor::LD_C_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRCA */
void Processor::RRCA()
{
	// Not implemented yet
	UnknownOpcode();
}

/* STOP */
void Processor::STOP()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD DE, nn */
void Processor::LD_DE_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (DE), A */
void Processor::LD_MEM_DE_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* INC DE */
void Processor::INC_DE()
{
	// Not implemented yet
	UnknownOpcode();
}

/* INC D */
void Processor::INC_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* DEC D */
void Processor::DEC_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD D, n */
void Processor::LD_D_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLA */
void Processor::RLA()
{
	// Not implemented yet
	UnknownOpcode();
}

/* JR n */
void Processor::JR_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADD HL, DE */
void Processor::ADD_HL_DE()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, (DE) */
void Processor::LD_A_MEM_DE()
{
	// Not implemented yet
	UnknownOpcode();
}

/* DEC DE */
void Processor::DEC_DE()
{
	// Not implemented yet
	UnknownOpcode();
}

/* INC E */
void Processor::INC_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* DEC E */
void Processor::DEC_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD E, n */
void Processor::LD_E_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRA */
void Processor::RRA()
{
	// Not implemented yet
	UnknownOpcode();
}

/* JR NZ, n */
void Processor::JR_NZ_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD HL, nn */
void Processor::LD_HL_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (HLI), A */
void Processor::LD_MEM_HLI_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* INC HL */
void Processor::INC_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* INC H */
void Processor::INC_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* DEC H */
void Processor::DEC_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD H, n */
void Processor::LD_H_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* DAA */
void Processor::DAA()
{
	// Not implemented yet
	UnknownOpcode();
}

/* JR Z, n */
void Processor::JR_Z_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADD HL, HL */
void Processor::ADD_HL_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, (HLI) */
void Processor::LD_A_MEM_HLI()
{
	// Not implemented yet
	UnknownOpcode();
}

/* DEC HL */
void Processor::DEC_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* INC L */
void Processor::INC_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* DEC L */
void Processor::DEC_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD L, n */
void Processor::LD_L_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CPL */
void Processor::CPL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* JR NC, n */
void Processor::JR_NC_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD SP, nn */
void Processor::LD_SP_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (HLD), A */
void Processor::LD_MEM_HLD_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* INC SP */
void Processor::INC_SP()
{
	// Not implemented yet
	UnknownOpcode();
}

/* INC (HL) */
void Processor::INC_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* DEC (HL) */
void Processor::DEC_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (HL), n */
void Processor::LD_MEM_HL_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SCF */
void Processor::SCF()
{
	// Not implemented yet
	UnknownOpcode();
}

/* JR C, n */
void Processor::JR_C_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADD HL, SP */
void Processor::ADD_HL_SP()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, (HLD) */
void Processor::LD_A_MEM_HLD()
{
	// Not implemented yet
	UnknownOpcode();
}

/* DEC SP */
void Processor::DEC_SP()
{
	// Not implemented yet
	UnknownOpcode();
}

/* INC A */
void Processor::INC_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* DEC A */
void Processor::DEC_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LDA, n */
void Processor::LDA_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CCF */
void Processor::CCF()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD B, B */
void Processor::LD_B_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD B, C */
void Processor::LD_B_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD B, D */
void Processor::LD_B_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD B, E */
void Processor::LD_B_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD B, H */
void Processor::LD_B_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD B, L */
void Processor::LD_B_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD B, (HL) */
void Processor::LD_B_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD B, A */
void Processor::LD_B_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD C, B */
void Processor::LD_C_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD C, C */
void Processor::LD_C_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD C, D */
void Processor::LD_C_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD C, E */
void Processor::LD_C_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD C, H */
void Processor::LD_C_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD C, L */
void Processor::LD_C_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD C, (HL) */
void Processor::LD_C_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD C, A */
void Processor::LD_C_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD D, B */
void Processor::LD_D_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD D, C */
void Processor::LD_D_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD D, D */
void Processor::LD_D_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD D, E */
void Processor::LD_D_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD D, H */
void Processor::LD_D_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD D, L */
void Processor::LD_D_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD D, (HL) */
void Processor::LD_D_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD D, A */
void Processor::LD_D_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD E, B */
void Processor::LD_E_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD E, C */
void Processor::LD_E_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD E, D */
void Processor::LD_E_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD E, E */
void Processor::LD_E_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD E, H */
void Processor::LD_E_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD E, L */
void Processor::LD_E_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD E, (HL) */
void Processor::LD_E_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD E, A */
void Processor::LD_E_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD H, B */
void Processor::LD_H_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD H, C */
void Processor::LD_H_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD H, D */
void Processor::LD_H_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD H, E */
void Processor::LD_H_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD H, H */
void Processor::LD_H_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD H, L */
void Processor::LD_H_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD H, (HL) */
void Processor::LD_H_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD H, A */
void Processor::LD_H_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD L, B */
void Processor::LD_L_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD L, C */
void Processor::LD_L_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD L, D */
void Processor::LD_L_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD L, E */
void Processor::LD_L_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD L, H */
void Processor::LD_L_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD L, L */
void Processor::LD_L_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD L, (HL) */
void Processor::LD_L_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD L, A */
void Processor::LD_L_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (HL), B */
void Processor::LD_MEM_HL_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (HL), C */
void Processor::LD_MEM_HL_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (HL), D */
void Processor::LD_MEM_HL_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (HL), E */
void Processor::LD_MEM_HL_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (HL), H */
void Processor::LD_MEM_HL_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (HL), L */
void Processor::LD_MEM_HL_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* HALT */
void Processor::HALT()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (HL), A */
void Processor::LD_MEM_HL_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, B */
void Processor::LD_A_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, C */
void Processor::LD_A_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, D */
void Processor::LD_A_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, E */
void Processor::LD_A_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, H */
void Processor::LD_A_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, L */
void Processor::LD_A_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, (HL) */
void Processor::LD_A_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, A */
void Processor::LD_A_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADD A, B */
void Processor::ADD_A_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADD A, C */
void Processor::ADD_A_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADD A, D */
void Processor::ADD_A_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADD A, E */
void Processor::ADD_A_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADD A, H */
void Processor::ADD_A_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADD A, L */
void Processor::ADD_A_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADD A, (HL) */
void Processor::ADD_A_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADD A, A */
void Processor::ADD_A_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADC A, B */
void Processor::ADC_A_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADC A, C */
void Processor::ADC_A_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADC A, D */
void Processor::ADC_A_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADC A, E */
void Processor::ADC_A_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADC A, H */
void Processor::ADC_A_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADC A, L */
void Processor::ADC_A_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADC A, (HL) */
void Processor::ADC_A_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADC A, A */
void Processor::ADC_A_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SUB B */
void Processor::SUB_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SUB C */
void Processor::SUB_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SUB D */
void Processor::SUB_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SUB E */
void Processor::SUB_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SUB H */
void Processor::SUB_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SUB L */
void Processor::SUB_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SUB (HL) */
void Processor::SUB_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SUB A */
void Processor::SUB_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SBC A, B */
void Processor::SBC_A_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SBC A, C */
void Processor::SBC_A_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SBC A, D */
void Processor::SBC_A_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SBC A, E */
void Processor::SBC_A_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SBC A, H */
void Processor::SBC_A_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SBC A, L */
void Processor::SBC_A_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SBC A, (HL) */
void Processor::SBC_A_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SBC A, A */
void Processor::SBC_A_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* AND B */
void Processor::AND_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* AND C */
void Processor::AND_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* AND D */
void Processor::AND_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* AND E */
void Processor::AND_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* AND H */
void Processor::AND_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* AND L */
void Processor::AND_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* AND (HL) */
void Processor::AND_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* AND A */
void Processor::AND_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* XOR B */
void Processor::XOR_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* XOR C */
void Processor::XOR_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* XOR D */
void Processor::XOR_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* XOR E */
void Processor::XOR_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* XOR H */
void Processor::XOR_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* XOR L */
void Processor::XOR_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* XOR (HL) */
void Processor::XOR_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* XOR A */
void Processor::XOR_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* OR B */
void Processor::OR_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* OR C */
void Processor::OR_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* OR D */
void Processor::OR_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* OR E */
void Processor::OR_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* OR H */
void Processor::OR_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* OR L */
void Processor::OR_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* OR (HL) */
void Processor::OR_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* OR A */
void Processor::OR_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CP B */
void Processor::CP_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CP C */
void Processor::CP_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CP D */
void Processor::CP_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CP E */
void Processor::CP_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CP H */
void Processor::CP_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CP L */
void Processor::CP_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CP (HL) */
void Processor::CP_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CP A */
void Processor::CP_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RET NZ */
void Processor::RET_NZ()
{
	// Not implemented yet
	UnknownOpcode();
}

/* POP BC */
void Processor::POP_BC()
{
	// Not implemented yet
	UnknownOpcode();
}

/* JP NZ, nn */
void Processor::JP_NZ_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* JP nn */
void Processor::JP_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CALL NZ, nn */
void Processor::CALL_NZ_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* PUSH BC */
void Processor::PUSH_BC()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADD A, n */
void Processor::ADD_A_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RST  */
void Processor::RST()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RET Z */
void Processor::RET_Z()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RET */
void Processor::RET()
{
	// Not implemented yet
	UnknownOpcode();
}

/* JP Z, nn */
void Processor::JP_Z_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CALL Z, nn */
void Processor::CALL_Z_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CALL nn */
void Processor::CALL_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADC A, n */
void Processor::ADC_A_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RST 0x08 */
void Processor::RST_0x08()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RET NC */
void Processor::RET_NC()
{
	// Not implemented yet
	UnknownOpcode();
}

/* POP DE */
void Processor::POP_DE()
{
	// Not implemented yet
	UnknownOpcode();
}

/* JP NC, nn */
void Processor::JP_NC_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CALL NC, nn */
void Processor::CALL_NC_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* PUSH DE */
void Processor::PUSH_DE()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SUB n */
void Processor::SUB_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RST 0x10 */
void Processor::RST_0x10()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RET C */
void Processor::RET_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RETI */
void Processor::RETI()
{
	// Not implemented yet
	UnknownOpcode();
}

/* JP C, nn */
void Processor::JP_C_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CALL C, nn */
void Processor::CALL_C_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SBC A, n */
void Processor::SBC_A_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RST 0x18 */
void Processor::RST_0x18()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (0xFF00+n), A */
void Processor::LD_MEM_0xFF00_n_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* POP HL */
void Processor::POP_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (0xFF00+C), A */
void Processor::LD_MEM_0xFF00_C_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* PUSH HL */
void Processor::PUSH_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* AND n */
void Processor::AND_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RST 0x20 */
void Processor::RST_0x20()
{
	// Not implemented yet
	UnknownOpcode();
}

/* ADD SP, n */
void Processor::ADD_SP_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* JP (HL) */
void Processor::JP_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (nn), A */
void Processor::LD_MEM_nn_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* XOR n */
void Processor::XOR_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RST 0x28 */
void Processor::RST_0x28()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, (0xFF00+n) */
void Processor::LD_A_MEM_0xFF00_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* POP AF */
void Processor::POP_AF()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, (0xFF00+C) */
void Processor::LD_A_MEM_0xFF00_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* DI */
void Processor::DI()
{
	// Not implemented yet
	UnknownOpcode();
}

/* PUSH AF */
void Processor::PUSH_AF()
{
	// Not implemented yet
	UnknownOpcode();
}

/* OR n */
void Processor::OR_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RST 0x30 */
void Processor::RST_0x30()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD HL, SP */
void Processor::LD_HL_SP()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD SP, HL */
void Processor::LD_SP_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD A, (nn) */
void Processor::LD_A_MEM_nn()
{
	// Not implemented yet
	UnknownOpcode();
}

/* EI */
void Processor::EI()
{
	// Not implemented yet
	UnknownOpcode();
}

/* CP n */
void Processor::CP_n()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RST 0x38 */
void Processor::RST_0x38()
{
	// Not implemented yet
	UnknownOpcode();
}

// CB Obcodes

/* RLC B */
void Processor::RLC_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLC C */
void Processor::RLC_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLC D */
void Processor::RLC_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLC E */
void Processor::RLC_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLC H */
void Processor::RLC_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLC L */
void Processor::RLC_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLC (HL) */
void Processor::RLC_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLC A */
void Processor::RLC_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC B */
void Processor::RRC_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC C */
void Processor::RRC_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC D */
void Processor::RRC_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC E */
void Processor::RRC_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC H */
void Processor::RRC_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC L */
void Processor::RRC_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC (HL) */
void Processor::RRC_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC A */
void Processor::RRC_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL B */
void Processor::RL_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL C */
void Processor::RL_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL D */
void Processor::RL_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL E */
void Processor::RL_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL H */
void Processor::RL_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL L  */
void Processor::RL_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL (HL) */
void Processor::RL_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL A */
void Processor::RL_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR B */
void Processor::RR_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR C */
void Processor::RR_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR D */
void Processor::RR_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR E */
void Processor::RR_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR H */
void Processor::RR_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR L */
void Processor::RR_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR (HL) */
void Processor::RR_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR A */
void Processor::RR_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA B */
void Processor::SLA_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA C */
void Processor::SLA_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA D */
void Processor::SLA_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA E */
void Processor::SLA_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA H */
void Processor::SLA_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA L */
void Processor::SLA_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA (HL) */
void Processor::SLA_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA A */
void Processor::SLA_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA B */
void Processor::SRA_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA C */
void Processor::SRA_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA D */
void Processor::SRA_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA E */
void Processor::SRA_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA H */
void Processor::SRA_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA L */
void Processor::SRA_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA (HL) */
void Processor::SRA_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA A */
void Processor::SRA_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP B */
void Processor::SWAP_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP C */
void Processor::SWAP_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP D */
void Processor::SWAP_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP E */
void Processor::SWAP_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP H */
void Processor::SWAP_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP L */
void Processor::SWAP_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP (HL) */
void Processor::SWAP_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP A */
void Processor::SWAP_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL B */
void Processor::SRL_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL C */
void Processor::SRL_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL D */
void Processor::SRL_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL E */
void Processor::SRL_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL H */
void Processor::SRL_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL L */
void Processor::SRL_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL (HL) */
void Processor::SRL_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL A */
void Processor::SRL_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 0 B */
void Processor::BIT_0_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 0 C */
void Processor::BIT_0_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 0 D */
void Processor::BIT_0_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 0 E */
void Processor::BIT_0_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 0 H */
void Processor::BIT_0_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 0 L */
void Processor::BIT_0_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 0 (HL) */
void Processor::BIT_0_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 0 A */
void Processor::BIT_0_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 1 B */
void Processor::BIT_1_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 1 C */
void Processor::BIT_1_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 1 D */
void Processor::BIT_1_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 1 E */
void Processor::BIT_1_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 1 H */
void Processor::BIT_1_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 1 L */
void Processor::BIT_1_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 1 (HL) */
void Processor::BIT_1_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 1 A */
void Processor::BIT_1_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 2 B */
void Processor::BIT_2_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 2 C */
void Processor::BIT_2_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 2 D */
void Processor::BIT_2_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 2 E */
void Processor::BIT_2_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 2 H */
void Processor::BIT_2_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 2 L */
void Processor::BIT_2_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 2 (HL) */
void Processor::BIT_2_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 2 A */
void Processor::BIT_2_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 3 B */
void Processor::BIT_3_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 3 C */
void Processor::BIT_3_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 3 D */
void Processor::BIT_3_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 3 E */
void Processor::BIT_3_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 3 H */
void Processor::BIT_3_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 3 L */
void Processor::BIT_3_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 3 (HL) */
void Processor::BIT_3_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 3 A */
void Processor::BIT_3_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 4 B */
void Processor::BIT_4_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 4 C */
void Processor::BIT_4_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 4 D */
void Processor::BIT_4_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 4 E */
void Processor::BIT_4_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 4 H */
void Processor::BIT_4_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 4 L */
void Processor::BIT_4_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 4 (HL) */
void Processor::BIT_4_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 4 A */
void Processor::BIT_4_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 5 B */
void Processor::BIT_5_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 5 C */
void Processor::BIT_5_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 5 D */
void Processor::BIT_5_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 5 E */
void Processor::BIT_5_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 5 H */
void Processor::BIT_5_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 5 L */
void Processor::BIT_5_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 5 (HL) */
void Processor::BIT_5_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 5 A */
void Processor::BIT_5_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 6 B */
void Processor::BIT_6_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 6 C */
void Processor::BIT_6_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 6 D */
void Processor::BIT_6_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 6 E */
void Processor::BIT_6_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 6 H */
void Processor::BIT_6_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 6 L */
void Processor::BIT_6_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 6 (HL) */
void Processor::BIT_6_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 6 A */
void Processor::BIT_6_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 7 B */
void Processor::BIT_7_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 7 C */
void Processor::BIT_7_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 7 D */
void Processor::BIT_7_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 7 E */
void Processor::BIT_7_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 7 H */
void Processor::BIT_7_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 7 L */
void Processor::BIT_7_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 7 (HL) */
void Processor::BIT_7_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 7 A */
void Processor::BIT_7_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 0 B */
void Processor::RES_0_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 0 C */
void Processor::RES_0_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 0 D */
void Processor::RES_0_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 0 E */
void Processor::RES_0_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 0 H */
void Processor::RES_0_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 0 L */
void Processor::RES_0_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 0 (HL) */
void Processor::RES_0_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 0 A */
void Processor::RES_0_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 1 B */
void Processor::RES_1_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 1 C */
void Processor::RES_1_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 1 D */
void Processor::RES_1_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 1 E */
void Processor::RES_1_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 1 H */
void Processor::RES_1_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 1 L */
void Processor::RES_1_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 1 (HL) */
void Processor::RES_1_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 1 A */
void Processor::RES_1_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 2 B */
void Processor::RES_2_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 2 C */
void Processor::RES_2_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 2 D */
void Processor::RES_2_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 2 E */
void Processor::RES_2_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 2 H */
void Processor::RES_2_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 2 L */
void Processor::RES_2_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 2 (HL) */
void Processor::RES_2_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 2 A */
void Processor::RES_2_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 3 B */
void Processor::RES_3_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 3 C */
void Processor::RES_3_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 3 D */
void Processor::RES_3_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 3 E */
void Processor::RES_3_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 3 H */
void Processor::RES_3_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 3 L */
void Processor::RES_3_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 3 (HL) */
void Processor::RES_3_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 3 A */
void Processor::RES_3_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 4 B */
void Processor::RES_4_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 4 C */
void Processor::RES_4_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 4 D */
void Processor::RES_4_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 4 E */
void Processor::RES_4_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 4 H */
void Processor::RES_4_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 4 L */
void Processor::RES_4_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 4 (HL) */
void Processor::RES_4_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 4 A */
void Processor::RES_4_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 5 B */
void Processor::RES_5_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 5 C */
void Processor::RES_5_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 5 D */
void Processor::RES_5_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 5 E */
void Processor::RES_5_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 5 H */
void Processor::RES_5_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 5 L */
void Processor::RES_5_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 5 (HL) */
void Processor::RES_5_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 5 A */
void Processor::RES_5_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 6 B */
void Processor::RES_6_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 6 C */
void Processor::RES_6_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 6 D */
void Processor::RES_6_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 6 E */
void Processor::RES_6_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 6 H */
void Processor::RES_6_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 6 L */
void Processor::RES_6_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 6 (HL) */
void Processor::RES_6_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 6 A */
void Processor::RES_6_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 7 B */
void Processor::RES_7_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 7 C */
void Processor::RES_7_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 7 D */
void Processor::RES_7_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 7 E */
void Processor::RES_7_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 7 H */
void Processor::RES_7_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 7 L */
void Processor::RES_7_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 7 (HL) */
void Processor::RES_7_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* RES 7 A */
void Processor::RES_7_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 0 B */
void Processor::SET_0_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 0 C */
void Processor::SET_0_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 0 D */
void Processor::SET_0_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 0 E */
void Processor::SET_0_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 0 H */
void Processor::SET_0_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 0 L */
void Processor::SET_0_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 0 (HL) */
void Processor::SET_0_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 0 A */
void Processor::SET_0_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 1 B */
void Processor::SET_1_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 1 C */
void Processor::SET_1_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 1 D */
void Processor::SET_1_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 1 E */
void Processor::SET_1_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 1 H */
void Processor::SET_1_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 1 L */
void Processor::SET_1_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 1 (HL) */
void Processor::SET_1_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 1 A */
void Processor::SET_1_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 2 B */
void Processor::SET_2_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 2 C */
void Processor::SET_2_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 2 D */
void Processor::SET_2_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 2 E */
void Processor::SET_2_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 2 H */
void Processor::SET_2_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 2 L */
void Processor::SET_2_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 2 (HL) */
void Processor::SET_2_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 2 A */
void Processor::SET_2_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 3 B */
void Processor::SET_3_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 3 C */
void Processor::SET_3_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 3 D */
void Processor::SET_3_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 3 E */
void Processor::SET_3_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 3 H */
void Processor::SET_3_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 3 L */
void Processor::SET_3_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 3 (HL) */
void Processor::SET_3_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 3 A */
void Processor::SET_3_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 4 B */
void Processor::SET_4_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 4 C */
void Processor::SET_4_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 4 D */
void Processor::SET_4_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 4 E */
void Processor::SET_4_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 4 H */
void Processor::SET_4_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 4 L */
void Processor::SET_4_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 4 (HL) */
void Processor::SET_4_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 4 A */
void Processor::SET_4_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 5 B */
void Processor::SET_5_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 5 C */
void Processor::SET_5_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 5 D */
void Processor::SET_5_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 5 E */
void Processor::SET_5_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 5 H */
void Processor::SET_5_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 5 L */
void Processor::SET_5_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 5 (HL) */
void Processor::SET_5_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 5 A */
void Processor::SET_5_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 6 B */
void Processor::SET_6_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 6 C */
void Processor::SET_6_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 6 D */
void Processor::SET_6_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 6 E */
void Processor::SET_6_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 6 H */
void Processor::SET_6_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 6 L */
void Processor::SET_6_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 6 (HL) */
void Processor::SET_6_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 6 A */
void Processor::SET_6_A()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 7 B */
void Processor::SET_7_B()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 7 C */
void Processor::SET_7_C()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 7 D */
void Processor::SET_7_D()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 7 E */
void Processor::SET_7_E()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 7 H */
void Processor::SET_7_H()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 7 L */
void Processor::SET_7_L()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 7 (HL) */
void Processor::SET_7_MEM_HL()
{
	// Not implemented yet
	UnknownOpcode();
}

/* SET 7 A */
void Processor::SET_7_A()
{
	// Not implemented yet
	UnknownOpcode();
}

