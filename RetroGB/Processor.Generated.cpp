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
	opcodes[0xCB] = std::bind(&Processor::InvalidOpcode, this);
	opcodes[0xCC] = std::bind(&Processor::CALL_Z_nn, this);
	opcodes[0xCD] = std::bind(&Processor::CALL_nn, this);
	opcodes[0xCE] = std::bind(&Processor::ADC_A_n, this);
	opcodes[0xCF] = std::bind(&Processor::RST_0x08, this);
	opcodes[0xD0] = std::bind(&Processor::RET_NC, this);
	opcodes[0xD1] = std::bind(&Processor::POP_DE, this);
	opcodes[0xD2] = std::bind(&Processor::JP_NC_nn, this);
	opcodes[0xD3] = std::bind(&Processor::InvalidOpcode, this);
	opcodes[0xD4] = std::bind(&Processor::CALL_NC_nn, this);
	opcodes[0xD5] = std::bind(&Processor::PUSH_DE, this);
	opcodes[0xD6] = std::bind(&Processor::SUB_n, this);
	opcodes[0xD7] = std::bind(&Processor::RST_0x10, this);
	opcodes[0xD8] = std::bind(&Processor::RET_C, this);
	opcodes[0xD9] = std::bind(&Processor::RETI, this);
	opcodes[0xDA] = std::bind(&Processor::JP_C_nn, this);
	opcodes[0xDB] = std::bind(&Processor::InvalidOpcode, this);
	opcodes[0xDC] = std::bind(&Processor::CALL_C_nn, this);
	opcodes[0xDD] = std::bind(&Processor::InvalidOpcode, this);
	opcodes[0xDE] = std::bind(&Processor::SBC_A_n, this);
	opcodes[0xDF] = std::bind(&Processor::RST_0x18, this);
	opcodes[0xE0] = std::bind(&Processor::LD_MEM_0xFF00_n_A, this);
	opcodes[0xE1] = std::bind(&Processor::POP_HL, this);
	opcodes[0xE2] = std::bind(&Processor::LD_MEM_0xFF00_C_A, this);
	opcodes[0xE3] = std::bind(&Processor::InvalidOpcode, this);
	opcodes[0xE4] = std::bind(&Processor::InvalidOpcode, this);
	opcodes[0xE5] = std::bind(&Processor::PUSH_HL, this);
	opcodes[0xE6] = std::bind(&Processor::AND_n, this);
	opcodes[0xE7] = std::bind(&Processor::RST_0x20, this);
	opcodes[0xE8] = std::bind(&Processor::ADD_SP_n, this);
	opcodes[0xE9] = std::bind(&Processor::JP_MEM_HL, this);
	opcodes[0xEA] = std::bind(&Processor::LD_MEM_nn_A, this);
	opcodes[0xEB] = std::bind(&Processor::InvalidOpcode, this);
	opcodes[0xEC] = std::bind(&Processor::InvalidOpcode, this);
	opcodes[0xED] = std::bind(&Processor::InvalidOpcode, this);
	opcodes[0xEE] = std::bind(&Processor::XOR_n, this);
	opcodes[0xEF] = std::bind(&Processor::RST_0x28, this);
	opcodes[0xF0] = std::bind(&Processor::LD_A_MEM_0xFF00_n, this);
	opcodes[0xF1] = std::bind(&Processor::POP_AF, this);
	opcodes[0xF2] = std::bind(&Processor::LD_A_MEM_0xFF00_C, this);
	opcodes[0xF3] = std::bind(&Processor::DI, this);
	opcodes[0xF4] = std::bind(&Processor::InvalidOpcode, this);
	opcodes[0xF5] = std::bind(&Processor::PUSH_AF, this);
	opcodes[0xF6] = std::bind(&Processor::OR_n, this);
	opcodes[0xF7] = std::bind(&Processor::RST_0x30, this);
	opcodes[0xF8] = std::bind(&Processor::LD_HL_SP, this);
	opcodes[0xF9] = std::bind(&Processor::LD_SP_HL, this);
	opcodes[0xFA] = std::bind(&Processor::LD_A_MEM_nn, this);
	opcodes[0xFB] = std::bind(&Processor::EI, this);
	opcodes[0xFC] = std::bind(&Processor::InvalidOpcode, this);
	opcodes[0xFD] = std::bind(&Processor::InvalidOpcode, this);
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
void Processor::NOP() // 0x00
{
}

/* LD BC, nn */
void Processor::LD_BC_nn() // 0x01
{
	BC = memory->ReadWord(PC++);
}

/* LD (BC), A */
void Processor::LD_MEM_BC_A() // 0x02
{
	memory->WriteByte(BC, A);
}

/* INC BC */
void Processor::INC_BC() // 0x03
{
	BC++;
}

/* INC B */
void Processor::INC_B() // 0x04
{
	B++;
	//TODO flags
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* DEC B */
void Processor::DEC_B() // 0x05
{
	B++;
	//TODO flags
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* LD B, n */
void Processor::LD_B_n() // 0x06
{
	B = memory->ReadByte(PC++);
}

/* RLCA */
void Processor::RLCA() // 0x07
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD (nn), SP */
void Processor::LD_MEM_nn_SP() // 0x08
{
	memory->WriteWord(memory->ReadWord(PC++), SP);
}

/* ADD HL, BC */
void Processor::ADD_HL_BC() // 0x09
{
	HL += BC;
	DisableFlag(FLAG_SUB);
	if (HL == 0) EnableFlag(FLAG_ZERO);
	if (HL > 0xFF) EnableFlag(FLAG_CARRY);
}

/* LD A, (BC) */
void Processor::LD_A_MEM_BC() // 0x0A
{
	A = memory->ReadByte(BC);
}

/* DEC BC */
void Processor::DEC_BC() // 0x0B
{
	BC--;
}

/* INC C */
void Processor::INC_C() // 0x0C
{
	C++;
	//TODO flags
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* DEC C */
void Processor::DEC_C() // 0x0D
{
	C++;
	//TODO flags
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* LD C, n */
void Processor::LD_C_n() // 0x0E
{
	C = memory->ReadByte(PC++);
}

/* RRCA */
void Processor::RRCA() // 0x0F
{
	// Not implemented yet
	UnknownOpcode();
}

/* STOP */
void Processor::STOP() // 0x10
{
	// Not implemented yet
	UnknownOpcode();
}

/* LD DE, nn */
void Processor::LD_DE_nn() // 0x11
{
	DE = memory->ReadWord(PC++);
}

/* LD (DE), A */
void Processor::LD_MEM_DE_A() // 0x12
{
	memory->WriteByte(DE, A);
}

/* INC DE */
void Processor::INC_DE() // 0x13
{
	DE++;
}

/* INC D */
void Processor::INC_D() // 0x14
{
	D++;
	//TODO flags
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* DEC D */
void Processor::DEC_D() // 0x15
{
	D++;
	//TODO flags
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* LD D, n */
void Processor::LD_D_n() // 0x16
{
	D = memory->ReadByte(PC++);
}

/* RLA */
void Processor::RLA() // 0x17
{
	// Not implemented yet
	UnknownOpcode();
}

/* JR n */
void Processor::JR_n() // 0x18
{
	PC += memory->ReadWord(PC++);
}

/* ADD HL, DE */
void Processor::ADD_HL_DE() // 0x19
{
	HL += DE;
	DisableFlag(FLAG_SUB);
	if (HL == 0) EnableFlag(FLAG_ZERO);
	if (HL > 0xFF) EnableFlag(FLAG_CARRY);
}

/* LD A, (DE) */
void Processor::LD_A_MEM_DE() // 0x1A
{
	A = memory->ReadByte(DE);
}

/* DEC DE */
void Processor::DEC_DE() // 0x1B
{
	DE--;
}

/* INC E */
void Processor::INC_E() // 0x1C
{
	E++;
	//TODO flags
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* DEC E */
void Processor::DEC_E() // 0x1D
{
	E++;
	//TODO flags
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* LD E, n */
void Processor::LD_E_n() // 0x1E
{
	E = memory->ReadByte(PC++);
}

/* RRA */
void Processor::RRA() // 0x1F
{
	// Not implemented yet
	UnknownOpcode();
}

/* JR NZ, n */
void Processor::JR_NZ_n() // 0x20
{
	if (!IsFlagSet(FLAG_ZERO))
	{
		PC += memory->ReadWord(PC++);
	}
}

/* LD HL, nn */
void Processor::LD_HL_nn() // 0x21
{
	HL = memory->ReadWord(PC++);
}

/* LD (HLI), A */
void Processor::LD_MEM_HLI_A() // 0x22
{
	memory->WriteByte(HL++, A);
}

/* INC HL */
void Processor::INC_HL() // 0x23
{
	HL++;
}

/* INC H */
void Processor::INC_H() // 0x24
{
	H++;
	//TODO flags
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* DEC H */
void Processor::DEC_H() // 0x25
{
	H++;
	//TODO flags
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* LD H, n */
void Processor::LD_H_n() // 0x26
{
	H = memory->ReadByte(PC++);
}

/* DAA */
void Processor::DAA() // 0x27
{
	uint8 reg = A;

	if ((reg & 0x0F) > 9 || IsFlagSet(FLAG_HALFCARRY))
	{
		reg += 0x06;
	}
	else if ((reg & 0x9F) > 9 || IsFlagSet(FLAG_CARRY))
	{
		reg += 0x60;
	}

	DisableFlag(FLAG_HALFCARRY);
	if (reg == 0) EnableFlag(FLAG_ZERO);

	A = reg;
}

/* JR Z, n */
void Processor::JR_Z_n() // 0x28
{
	if (IsFlagSet(FLAG_ZERO))
	{
		PC += memory->ReadWord(PC++);
	}
}

/* ADD HL, HL */
void Processor::ADD_HL_HL() // 0x29
{
	HL += HL;
	DisableFlag(FLAG_SUB);
	if (HL == 0) EnableFlag(FLAG_ZERO);
	if (HL > 0xFF) EnableFlag(FLAG_CARRY);
}

/* LD A, (HLI) */
void Processor::LD_A_MEM_HLI() // 0x2A
{
	A = memory->ReadByte(HL++);
}

/* DEC HL */
void Processor::DEC_HL() // 0x2B
{
	HL--;
}

/* INC L */
void Processor::INC_L() // 0x2C
{
	L++;
	//TODO flags
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* DEC L */
void Processor::DEC_L() // 0x2D
{
	L++;
	//TODO flags
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* LD L, n */
void Processor::LD_L_n() // 0x2E
{
	L = memory->ReadByte(PC++);
}

/* CPL */
void Processor::CPL() // 0x2F
{
	// Not implemented yet
	UnknownOpcode();
}

/* JR NC, n */
void Processor::JR_NC_n() // 0x30
{
	if (!IsFlagSet(FLAG_CARRY))
	{
		PC += memory->ReadWord(PC++);
	}
}

/* LD SP, nn */
void Processor::LD_SP_nn() // 0x31
{
	SP = memory->ReadWord(PC++);
}

/* LD (HLD), A */
void Processor::LD_MEM_HLD_A() // 0x32
{
	memory->WriteByte(HL--, A);
}

/* INC SP */
void Processor::INC_SP() // 0x33
{
	SP++;
}

/* INC (HL) */
void Processor::INC_MEM_HL() // 0x34
{
	memory->WriteByte(HL, memory->ReadByte(HL++));
	//TODO flags
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* DEC (HL) */
void Processor::DEC_MEM_HL() // 0x35
{
	memory->WriteByte(HL, memory->ReadByte(HL--));
	//TODO flags
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* LD (HL), n */
void Processor::LD_MEM_HL_n() // 0x36
{
	memory->WriteByte(HL, memory->ReadByte(PC++));
}

/* SCF */
void Processor::SCF() // 0x37
{
	EnableFlag(FLAG_CARRY);
	DisableFlag(FLAG_HALFCARRY);
	DisableFlag(FLAG_SUB);
}

/* JR C, n */
void Processor::JR_C_n() // 0x38
{
	if (IsFlagSet(FLAG_CARRY))
	{
		PC += memory->ReadWord(PC++);
	}
}

/* ADD HL, SP */
void Processor::ADD_HL_SP() // 0x39
{
	HL += SP;
	DisableFlag(FLAG_SUB);
	if (HL == 0) EnableFlag(FLAG_ZERO);
	if (HL > 0xFF) EnableFlag(FLAG_CARRY);
}

/* LD A, (HLD) */
void Processor::LD_A_MEM_HLD() // 0x3A
{
	A = memory->ReadByte(HL--);
}

/* DEC SP */
void Processor::DEC_SP() // 0x3B
{
	SP--;
}

/* INC A */
void Processor::INC_A() // 0x3C
{
	A++;
	//TODO flags
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* DEC A */
void Processor::DEC_A() // 0x3D
{
	A++;
	//TODO flags
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* LDA, n */
void Processor::LDA_n() // 0x3E
{
	// Not implemented yet
	UnknownOpcode();
}

/* CCF */
void Processor::CCF() // 0x3F
{
	InvertFlag(FLAG_CARRY);
	DisableFlag(FLAG_HALFCARRY);
	DisableFlag(FLAG_SUB);
}

/* LD B, B */
void Processor::LD_B_B() // 0x40
{
}

/* LD B, C */
void Processor::LD_B_C() // 0x41
{
	B = C;
}

/* LD B, D */
void Processor::LD_B_D() // 0x42
{
	B = D;
}

/* LD B, E */
void Processor::LD_B_E() // 0x43
{
	B = E;
}

/* LD B, H */
void Processor::LD_B_H() // 0x44
{
	B = H;
}

/* LD B, L */
void Processor::LD_B_L() // 0x45
{
	B = L;
}

/* LD B, (HL) */
void Processor::LD_B_MEM_HL() // 0x46
{
	B = memory->ReadByte(HL);
}

/* LD B, A */
void Processor::LD_B_A() // 0x47
{
	B = A;
}

/* LD C, B */
void Processor::LD_C_B() // 0x48
{
	C = B;
}

/* LD C, C */
void Processor::LD_C_C() // 0x49
{
}

/* LD C, D */
void Processor::LD_C_D() // 0x4A
{
	C = D;
}

/* LD C, E */
void Processor::LD_C_E() // 0x4B
{
	C = E;
}

/* LD C, H */
void Processor::LD_C_H() // 0x4C
{
	C = H;
}

/* LD C, L */
void Processor::LD_C_L() // 0x4D
{
	C = L;
}

/* LD C, (HL) */
void Processor::LD_C_MEM_HL() // 0x4E
{
	C = memory->ReadByte(HL);
}

/* LD C, A */
void Processor::LD_C_A() // 0x4F
{
	C = A;
}

/* LD D, B */
void Processor::LD_D_B() // 0x50
{
	D = B;
}

/* LD D, C */
void Processor::LD_D_C() // 0x51
{
	D = C;
}

/* LD D, D */
void Processor::LD_D_D() // 0x52
{
}

/* LD D, E */
void Processor::LD_D_E() // 0x53
{
	D = E;
}

/* LD D, H */
void Processor::LD_D_H() // 0x54
{
	D = H;
}

/* LD D, L */
void Processor::LD_D_L() // 0x55
{
	D = L;
}

/* LD D, (HL) */
void Processor::LD_D_MEM_HL() // 0x56
{
	D = memory->ReadByte(HL);
}

/* LD D, A */
void Processor::LD_D_A() // 0x57
{
	D = A;
}

/* LD E, B */
void Processor::LD_E_B() // 0x58
{
	E = B;
}

/* LD E, C */
void Processor::LD_E_C() // 0x59
{
	E = C;
}

/* LD E, D */
void Processor::LD_E_D() // 0x5A
{
	E = D;
}

/* LD E, E */
void Processor::LD_E_E() // 0x5B
{
}

/* LD E, H */
void Processor::LD_E_H() // 0x5C
{
	E = H;
}

/* LD E, L */
void Processor::LD_E_L() // 0x5D
{
	E = L;
}

/* LD E, (HL) */
void Processor::LD_E_MEM_HL() // 0x5E
{
	E = memory->ReadByte(HL);
}

/* LD E, A */
void Processor::LD_E_A() // 0x5F
{
	E = A;
}

/* LD H, B */
void Processor::LD_H_B() // 0x60
{
	H = B;
}

/* LD H, C */
void Processor::LD_H_C() // 0x61
{
	H = C;
}

/* LD H, D */
void Processor::LD_H_D() // 0x62
{
	H = D;
}

/* LD H, E */
void Processor::LD_H_E() // 0x63
{
	H = E;
}

/* LD H, H */
void Processor::LD_H_H() // 0x64
{
}

/* LD H, L */
void Processor::LD_H_L() // 0x65
{
	H = L;
}

/* LD H, (HL) */
void Processor::LD_H_MEM_HL() // 0x66
{
	H = memory->ReadByte(HL);
}

/* LD H, A */
void Processor::LD_H_A() // 0x67
{
	H = A;
}

/* LD L, B */
void Processor::LD_L_B() // 0x68
{
	L = B;
}

/* LD L, C */
void Processor::LD_L_C() // 0x69
{
	L = C;
}

/* LD L, D */
void Processor::LD_L_D() // 0x6A
{
	L = D;
}

/* LD L, E */
void Processor::LD_L_E() // 0x6B
{
	L = E;
}

/* LD L, H */
void Processor::LD_L_H() // 0x6C
{
	L = H;
}

/* LD L, L */
void Processor::LD_L_L() // 0x6D
{
}

/* LD L, (HL) */
void Processor::LD_L_MEM_HL() // 0x6E
{
	L = memory->ReadByte(HL);
}

/* LD L, A */
void Processor::LD_L_A() // 0x6F
{
	L = A;
}

/* LD (HL), B */
void Processor::LD_MEM_HL_B() // 0x70
{
	memory->WriteByte(HL, B);
}

/* LD (HL), C */
void Processor::LD_MEM_HL_C() // 0x71
{
	memory->WriteByte(HL, C);
}

/* LD (HL), D */
void Processor::LD_MEM_HL_D() // 0x72
{
	memory->WriteByte(HL, D);
}

/* LD (HL), E */
void Processor::LD_MEM_HL_E() // 0x73
{
	memory->WriteByte(HL, E);
}

/* LD (HL), H */
void Processor::LD_MEM_HL_H() // 0x74
{
	memory->WriteByte(HL, H);
}

/* LD (HL), L */
void Processor::LD_MEM_HL_L() // 0x75
{
	memory->WriteByte(HL, L);
}

/* HALT */
void Processor::HALT() // 0x76
{
	halted = true;
}

/* LD (HL), A */
void Processor::LD_MEM_HL_A() // 0x77
{
	memory->WriteByte(HL, A);
}

/* LD A, B */
void Processor::LD_A_B() // 0x78
{
	A = B;
}

/* LD A, C */
void Processor::LD_A_C() // 0x79
{
	A = C;
}

/* LD A, D */
void Processor::LD_A_D() // 0x7A
{
	A = D;
}

/* LD A, E */
void Processor::LD_A_E() // 0x7B
{
	A = E;
}

/* LD A, H */
void Processor::LD_A_H() // 0x7C
{
	A = H;
}

/* LD A, L */
void Processor::LD_A_L() // 0x7D
{
	A = L;
}

/* LD A, (HL) */
void Processor::LD_A_MEM_HL() // 0x7E
{
	A = memory->ReadByte(HL);
}

/* LD A, A */
void Processor::LD_A_A() // 0x7F
{
}

/* ADD A, B */
void Processor::ADD_A_B() // 0x80
{
	A += B;
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADD A, C */
void Processor::ADD_A_C() // 0x81
{
	A += C;
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADD A, D */
void Processor::ADD_A_D() // 0x82
{
	A += D;
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADD A, E */
void Processor::ADD_A_E() // 0x83
{
	A += E;
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADD A, H */
void Processor::ADD_A_H() // 0x84
{
	A += H;
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADD A, L */
void Processor::ADD_A_L() // 0x85
{
	A += L;
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADD A, (HL) */
void Processor::ADD_A_MEM_HL() // 0x86
{
	A += memory->ReadByte(HL);
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADD A, A */
void Processor::ADD_A_A() // 0x87
{
	A += A;
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADC A, B */
void Processor::ADC_A_B() // 0x88
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A += (B + carry);
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADC A, C */
void Processor::ADC_A_C() // 0x89
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A += (C + carry);
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADC A, D */
void Processor::ADC_A_D() // 0x8A
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A += (D + carry);
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADC A, E */
void Processor::ADC_A_E() // 0x8B
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A += (E + carry);
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADC A, H */
void Processor::ADC_A_H() // 0x8C
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A += (H + carry);
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADC A, L */
void Processor::ADC_A_L() // 0x8D
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A += (L + carry);
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADC A, (HL) */
void Processor::ADC_A_MEM_HL() // 0x8E
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A += (memory->ReadByte(HL) + carry);
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* ADC A, A */
void Processor::ADC_A_A() // 0x8F
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A += (A + carry);
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* SUB B */
void Processor::SUB_B() // 0x90
{
	A -= B;
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SUB C */
void Processor::SUB_C() // 0x91
{
	A -= C;
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SUB D */
void Processor::SUB_D() // 0x92
{
	A -= D;
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SUB E */
void Processor::SUB_E() // 0x93
{
	A -= E;
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SUB H */
void Processor::SUB_H() // 0x94
{
	A -= H;
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SUB L */
void Processor::SUB_L() // 0x95
{
	A -= L;
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SUB (HL) */
void Processor::SUB_MEM_HL() // 0x96
{
	A -= memory->ReadByte(HL);
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SUB A */
void Processor::SUB_A() // 0x97
{
	A -= A;
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SBC A, B */
void Processor::SBC_A_B() // 0x98
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A -= (B + carry);
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SBC A, C */
void Processor::SBC_A_C() // 0x99
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A -= (C + carry);
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SBC A, D */
void Processor::SBC_A_D() // 0x9A
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A -= (D + carry);
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SBC A, E */
void Processor::SBC_A_E() // 0x9B
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A -= (E + carry);
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SBC A, H */
void Processor::SBC_A_H() // 0x9C
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A -= (H + carry);
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SBC A, L */
void Processor::SBC_A_L() // 0x9D
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A -= (L + carry);
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SBC A, (HL) */
void Processor::SBC_A_MEM_HL() // 0x9E
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A -= (memory->ReadByte(HL) + carry);
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* SBC A, A */
void Processor::SBC_A_A() // 0x9F
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A -= (A + carry);
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* AND B */
void Processor::AND_B() // 0xA0
{
	A &= B;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* AND C */
void Processor::AND_C() // 0xA1
{
	A &= C;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* AND D */
void Processor::AND_D() // 0xA2
{
	A &= D;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* AND E */
void Processor::AND_E() // 0xA3
{
	A &= E;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* AND H */
void Processor::AND_H() // 0xA4
{
	A &= H;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* AND L */
void Processor::AND_L() // 0xA5
{
	A &= L;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* AND (HL) */
void Processor::AND_MEM_HL() // 0xA6
{
	A &= memory->ReadByte(HL);
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* AND A */
void Processor::AND_A() // 0xA7
{
	A &= A;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* XOR B */
void Processor::XOR_B() // 0xA8
{
	A ^= B;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* XOR C */
void Processor::XOR_C() // 0xA9
{
	A ^= C;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* XOR D */
void Processor::XOR_D() // 0xAA
{
	A ^= D;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* XOR E */
void Processor::XOR_E() // 0xAB
{
	A ^= E;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* XOR H */
void Processor::XOR_H() // 0xAC
{
	A ^= H;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* XOR L */
void Processor::XOR_L() // 0xAD
{
	A ^= L;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* XOR (HL) */
void Processor::XOR_MEM_HL() // 0xAE
{
	A ^= memory->ReadByte(HL);
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* XOR A */
void Processor::XOR_A() // 0xAF
{
	A ^= A;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* OR B */
void Processor::OR_B() // 0xB0
{
	A |= B;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* OR C */
void Processor::OR_C() // 0xB1
{
	A |= C;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* OR D */
void Processor::OR_D() // 0xB2
{
	A |= D;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* OR E */
void Processor::OR_E() // 0xB3
{
	A |= E;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* OR H */
void Processor::OR_H() // 0xB4
{
	A |= H;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* OR L */
void Processor::OR_L() // 0xB5
{
	A |= L;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* OR (HL) */
void Processor::OR_MEM_HL() // 0xB6
{
	A |= memory->ReadByte(HL);
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* OR A */
void Processor::OR_A() // 0xB7
{
	A |= A;
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* CP B */
void Processor::CP_B() // 0xB8
{
	uint8 reg = A;
	reg -= B;
	EnableFlag(FLAG_SUB);
	if (reg == 0) EnableFlag(FLAG_ZERO);
	if (reg < 0) EnableFlag(FLAG_CARRY);
}

/* CP C */
void Processor::CP_C() // 0xB9
{
	uint8 reg = A;
	reg -= C;
	EnableFlag(FLAG_SUB);
	if (reg == 0) EnableFlag(FLAG_ZERO);
	if (reg < 0) EnableFlag(FLAG_CARRY);
}

/* CP D */
void Processor::CP_D() // 0xBA
{
	uint8 reg = A;
	reg -= D;
	EnableFlag(FLAG_SUB);
	if (reg == 0) EnableFlag(FLAG_ZERO);
	if (reg < 0) EnableFlag(FLAG_CARRY);
}

/* CP E */
void Processor::CP_E() // 0xBB
{
	uint8 reg = A;
	reg -= E;
	EnableFlag(FLAG_SUB);
	if (reg == 0) EnableFlag(FLAG_ZERO);
	if (reg < 0) EnableFlag(FLAG_CARRY);
}

/* CP H */
void Processor::CP_H() // 0xBC
{
	uint8 reg = A;
	reg -= H;
	EnableFlag(FLAG_SUB);
	if (reg == 0) EnableFlag(FLAG_ZERO);
	if (reg < 0) EnableFlag(FLAG_CARRY);
}

/* CP L */
void Processor::CP_L() // 0xBD
{
	uint8 reg = A;
	reg -= L;
	EnableFlag(FLAG_SUB);
	if (reg == 0) EnableFlag(FLAG_ZERO);
	if (reg < 0) EnableFlag(FLAG_CARRY);
}

/* CP (HL) */
void Processor::CP_MEM_HL() // 0xBE
{
	uint8 reg = A;
	reg -= memory->ReadByte(HL);
	EnableFlag(FLAG_SUB);
	if (reg == 0) EnableFlag(FLAG_ZERO);
	if (reg < 0) EnableFlag(FLAG_CARRY);
}

/* CP A */
void Processor::CP_A() // 0xBF
{
	uint8 reg = A;
	reg -= A;
	EnableFlag(FLAG_SUB);
	if (reg == 0) EnableFlag(FLAG_ZERO);
	if (reg < 0) EnableFlag(FLAG_CARRY);
}

/* RET NZ */
void Processor::RET_NZ() // 0xC0
{
	if (!IsFlagSet(FLAG_ZERO))
	{
		StackPop(PC);
	}
}

/* POP BC */
void Processor::POP_BC() // 0xC1
{
	StackPop(BC);
}

/* JP NZ, nn */
void Processor::JP_NZ_nn() // 0xC2
{
	if (!IsFlagSet(FLAG_ZERO))
	{
		PC = memory->ReadWord(PC++);
	}
}

/* JP nn */
void Processor::JP_nn() // 0xC3
{
	PC = memory->ReadWord(PC++);
}

/* CALL NZ, nn */
void Processor::CALL_NZ_nn() // 0xC4
{
	if (!IsFlagSet(FLAG_ZERO))
	{
		SP -= 2;
		memory->WriteWord(SP, PC + 2);
		PC = memory->ReadWord(PC);
	}
}

/* PUSH BC */
void Processor::PUSH_BC() // 0xC5
{
	StackPush(BC);
}

/* ADD A, n */
void Processor::ADD_A_n() // 0xC6
{
	A += memory->ReadByte(PC++);
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* RST  */
void Processor::RST() // 0xC7
{
	StackPush(PC);
	PC = 0x00;
}

/* RET Z */
void Processor::RET_Z() // 0xC8
{
	if (IsFlagSet(FLAG_ZERO))
	{
		StackPop(PC);
	}
}

/* RET */
void Processor::RET() // 0xC9
{
	StackPop(PC);
}

/* JP Z, nn */
void Processor::JP_Z_nn() // 0xCA
{
	if (IsFlagSet(FLAG_ZERO))
	{
		PC = memory->ReadWord(PC++);
	}
}

/* CALL Z, nn */
void Processor::CALL_Z_nn() // 0xCC
{
	if (IsFlagSet(FLAG_ZERO))
	{
		SP -= 2;
		memory->WriteWord(SP, PC + 2);
		PC = memory->ReadWord(PC);
	}
}

/* CALL nn */
void Processor::CALL_nn() // 0xCD
{
	SP -= 2;
	memory->WriteWord(SP, PC + 2);
	PC = memory->ReadWord(PC);
}

/* ADC A, n */
void Processor::ADC_A_n() // 0xCE
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A += (memory->ReadByte(PC++) + carry);
	DisableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A > 0xFF) EnableFlag(FLAG_CARRY);
}

/* RST 0x08 */
void Processor::RST_0x08() // 0xCF
{
	StackPush(PC);
	PC = 0x08;
}

/* RET NC */
void Processor::RET_NC() // 0xD0
{
	if (!IsFlagSet(FLAG_CARRY))
	{
		StackPop(PC);
	}
}

/* POP DE */
void Processor::POP_DE() // 0xD1
{
	StackPop(DE);
}

/* JP NC, nn */
void Processor::JP_NC_nn() // 0xD2
{
	if (!IsFlagSet(FLAG_CARRY))
	{
		PC = memory->ReadWord(PC++);
	}
}

/* CALL NC, nn */
void Processor::CALL_NC_nn() // 0xD4
{
	if (!IsFlagSet(FLAG_CARRY))
	{
		SP -= 2;
		memory->WriteWord(SP, PC + 2);
		PC = memory->ReadWord(PC);
	}
}

/* PUSH DE */
void Processor::PUSH_DE() // 0xD5
{
	StackPush(DE);
}

/* SUB n */
void Processor::SUB_n() // 0xD6
{
	A -= memory->ReadByte(PC++);
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* RST 0x10 */
void Processor::RST_0x10() // 0xD7
{
	StackPush(PC);
	PC = 0x10;
}

/* RET C */
void Processor::RET_C() // 0xD8
{
	if (IsFlagSet(FLAG_CARRY))
	{
		StackPop(PC);
	}
}

/* RETI */
void Processor::RETI() // 0xD9
{
	StackPop(PC);
	ime = true;
}

/* JP C, nn */
void Processor::JP_C_nn() // 0xDA
{
	if (IsFlagSet(FLAG_CARRY))
	{
		PC = memory->ReadWord(PC++);
	}
}

/* CALL C, nn */
void Processor::CALL_C_nn() // 0xDC
{
	if (IsFlagSet(FLAG_CARRY))
	{
		SP -= 2;
		memory->WriteWord(SP, PC + 2);
		PC = memory->ReadWord(PC);
	}
}

/* SBC A, n */
void Processor::SBC_A_n() // 0xDE
{
	uint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;
	A -= (memory->ReadByte(PC++) + carry);
	EnableFlag(FLAG_SUB);
	if (A == 0) EnableFlag(FLAG_ZERO);
	if (A < 0) EnableFlag(FLAG_CARRY);
}

/* RST 0x18 */
void Processor::RST_0x18() // 0xDF
{
	StackPush(PC);
	PC = 0x18;
}

/* LD (0xFF00+n), A */
void Processor::LD_MEM_0xFF00_n_A() // 0xE0
{
	memory->WriteWord(0xFF00 + memory->ReadWord(PC++), A);
}

/* POP HL */
void Processor::POP_HL() // 0xE1
{
	StackPop(HL);
}

/* LD (0xFF00+C), A */
void Processor::LD_MEM_0xFF00_C_A() // 0xE2
{
	memory->WriteByte(0xFF00 + C, A);
}

/* PUSH HL */
void Processor::PUSH_HL() // 0xE5
{
	StackPush(HL);
}

/* AND n */
void Processor::AND_n() // 0xE6
{
	A &= memory->ReadByte(PC++);
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* RST 0x20 */
void Processor::RST_0x20() // 0xE7
{
	StackPush(PC);
	PC = 0x20;
}

/* ADD SP, n */
void Processor::ADD_SP_n() // 0xE8
{
	SP += memory->ReadByte(PC++);
	DisableFlag(FLAG_SUB);
	if (SP == 0) EnableFlag(FLAG_ZERO);
	if (SP > 0xFF) EnableFlag(FLAG_CARRY);
}

/* JP (HL) */
void Processor::JP_MEM_HL() // 0xE9
{
	PC = memory->ReadWord(PC++);
}

/* LD (nn), A */
void Processor::LD_MEM_nn_A() // 0xEA
{
	memory->WriteWord(memory->ReadWord(PC++), A);
}

/* XOR n */
void Processor::XOR_n() // 0xEE
{
	A ^= memory->ReadByte(PC++);
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* RST 0x28 */
void Processor::RST_0x28() // 0xEF
{
	StackPush(PC);
	PC = 0x28;
}

/* LD A, (0xFF00+n) */
void Processor::LD_A_MEM_0xFF00_n() // 0xF0
{
	A = memory->ReadByte(0xFF00 + PC++);
}

/* POP AF */
void Processor::POP_AF() // 0xF1
{
	StackPop(AF);
}

/* LD A, (0xFF00+C) */
void Processor::LD_A_MEM_0xFF00_C() // 0xF2
{
	A = memory->ReadByte(0xFF00 + C);
}

/* DI */
void Processor::DI() // 0xF3
{
	ime = false;
}

/* PUSH AF */
void Processor::PUSH_AF() // 0xF5
{
	StackPush(AF);
}

/* OR n */
void Processor::OR_n() // 0xF6
{
	A |= memory->ReadByte(PC++);
	ClearFlags();
	if (A == 0) EnableFlag(FLAG_ZERO);
}

/* RST 0x30 */
void Processor::RST_0x30() // 0xF7
{
	StackPush(PC);
	PC = 0x30;
}

/* LD HL, SP */
void Processor::LD_HL_SP() // 0xF8
{
	HL = SP;
}

/* LD SP, HL */
void Processor::LD_SP_HL() // 0xF9
{
	SP = HL;
}

/* LD A, (nn) */
void Processor::LD_A_MEM_nn() // 0xFA
{
	A = memory->ReadByte(memory->ReadWord(PC++));
}

/* EI */
void Processor::EI() // 0xFB
{
	// Not implemented yet
	UnknownOpcode();
}

/* CP n */
void Processor::CP_n() // 0xFE
{
	uint8 reg = A;
	reg -= memory->ReadByte(PC++);
	EnableFlag(FLAG_SUB);
	if (reg == 0) EnableFlag(FLAG_ZERO);
	if (reg < 0) EnableFlag(FLAG_CARRY);
}

/* RST 0x38 */
void Processor::RST_0x38() // 0xFF
{
	StackPush(PC);
	PC = 0x38;
}

// CB Obcodes

/* RLC B */
void Processor::RLC_B() // 0x00
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLC C */
void Processor::RLC_C() // 0x01
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLC D */
void Processor::RLC_D() // 0x02
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLC E */
void Processor::RLC_E() // 0x03
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLC H */
void Processor::RLC_H() // 0x04
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLC L */
void Processor::RLC_L() // 0x05
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLC (HL) */
void Processor::RLC_MEM_HL() // 0x06
{
	// Not implemented yet
	UnknownOpcode();
}

/* RLC A */
void Processor::RLC_A() // 0x07
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC B */
void Processor::RRC_B() // 0x08
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC C */
void Processor::RRC_C() // 0x09
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC D */
void Processor::RRC_D() // 0x0A
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC E */
void Processor::RRC_E() // 0x0B
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC H */
void Processor::RRC_H() // 0x0C
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC L */
void Processor::RRC_L() // 0x0D
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC (HL) */
void Processor::RRC_MEM_HL() // 0x0E
{
	// Not implemented yet
	UnknownOpcode();
}

/* RRC A */
void Processor::RRC_A() // 0x0F
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL B */
void Processor::RL_B() // 0x10
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL C */
void Processor::RL_C() // 0x11
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL D */
void Processor::RL_D() // 0x12
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL E */
void Processor::RL_E() // 0x13
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL H */
void Processor::RL_H() // 0x14
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL L  */
void Processor::RL_L() // 0x15
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL (HL) */
void Processor::RL_MEM_HL() // 0x16
{
	// Not implemented yet
	UnknownOpcode();
}

/* RL A */
void Processor::RL_A() // 0x17
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR B */
void Processor::RR_B() // 0x18
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR C */
void Processor::RR_C() // 0x19
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR D */
void Processor::RR_D() // 0x1A
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR E */
void Processor::RR_E() // 0x1B
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR H */
void Processor::RR_H() // 0x1C
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR L */
void Processor::RR_L() // 0x1D
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR (HL) */
void Processor::RR_MEM_HL() // 0x1E
{
	// Not implemented yet
	UnknownOpcode();
}

/* RR A */
void Processor::RR_A() // 0x1F
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA B */
void Processor::SLA_B() // 0x20
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA C */
void Processor::SLA_C() // 0x21
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA D */
void Processor::SLA_D() // 0x22
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA E */
void Processor::SLA_E() // 0x23
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA H */
void Processor::SLA_H() // 0x24
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA L */
void Processor::SLA_L() // 0x25
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA (HL) */
void Processor::SLA_MEM_HL() // 0x26
{
	// Not implemented yet
	UnknownOpcode();
}

/* SLA A */
void Processor::SLA_A() // 0x27
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA B */
void Processor::SRA_B() // 0x28
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA C */
void Processor::SRA_C() // 0x29
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA D */
void Processor::SRA_D() // 0x2A
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA E */
void Processor::SRA_E() // 0x2B
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA H */
void Processor::SRA_H() // 0x2C
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA L */
void Processor::SRA_L() // 0x2D
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA (HL) */
void Processor::SRA_MEM_HL() // 0x2E
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRA A */
void Processor::SRA_A() // 0x2F
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP B */
void Processor::SWAP_B() // 0x30
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP C */
void Processor::SWAP_C() // 0x31
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP D */
void Processor::SWAP_D() // 0x32
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP E */
void Processor::SWAP_E() // 0x33
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP H */
void Processor::SWAP_H() // 0x34
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP L */
void Processor::SWAP_L() // 0x35
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP (HL) */
void Processor::SWAP_MEM_HL() // 0x36
{
	// Not implemented yet
	UnknownOpcode();
}

/* SWAP A */
void Processor::SWAP_A() // 0x37
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL B */
void Processor::SRL_B() // 0x38
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL C */
void Processor::SRL_C() // 0x39
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL D */
void Processor::SRL_D() // 0x3A
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL E */
void Processor::SRL_E() // 0x3B
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL H */
void Processor::SRL_H() // 0x3C
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL L */
void Processor::SRL_L() // 0x3D
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL (HL) */
void Processor::SRL_MEM_HL() // 0x3E
{
	// Not implemented yet
	UnknownOpcode();
}

/* SRL A */
void Processor::SRL_A() // 0x3F
{
	// Not implemented yet
	UnknownOpcode();
}

/* BIT 0 B */
void Processor::BIT_0_B() // 0x40
{
	if (((B >> 0) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 0 C */
void Processor::BIT_0_C() // 0x41
{
	if (((C >> 0) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 0 D */
void Processor::BIT_0_D() // 0x42
{
	if (((D >> 0) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 0 E */
void Processor::BIT_0_E() // 0x43
{
	if (((E >> 0) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 0 H */
void Processor::BIT_0_H() // 0x44
{
	if (((H >> 0) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 0 L */
void Processor::BIT_0_L() // 0x45
{
	if (((L >> 0) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 0 (HL) */
void Processor::BIT_0_MEM_HL() // 0x46
{
	if (((memory->ReadByte(HL) >> 0) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 0 A */
void Processor::BIT_0_A() // 0x47
{
	if (((A >> 0) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 1 B */
void Processor::BIT_1_B() // 0x48
{
	if (((B >> 1) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 1 C */
void Processor::BIT_1_C() // 0x49
{
	if (((C >> 1) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 1 D */
void Processor::BIT_1_D() // 0x4A
{
	if (((D >> 1) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 1 E */
void Processor::BIT_1_E() // 0x4B
{
	if (((E >> 1) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 1 H */
void Processor::BIT_1_H() // 0x4C
{
	if (((H >> 1) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 1 L */
void Processor::BIT_1_L() // 0x4D
{
	if (((L >> 1) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 1 (HL) */
void Processor::BIT_1_MEM_HL() // 0x4E
{
	if (((memory->ReadByte(HL) >> 1) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 1 A */
void Processor::BIT_1_A() // 0x4F
{
	if (((A >> 1) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 2 B */
void Processor::BIT_2_B() // 0x50
{
	if (((B >> 2) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 2 C */
void Processor::BIT_2_C() // 0x51
{
	if (((C >> 2) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 2 D */
void Processor::BIT_2_D() // 0x52
{
	if (((D >> 2) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 2 E */
void Processor::BIT_2_E() // 0x53
{
	if (((E >> 2) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 2 H */
void Processor::BIT_2_H() // 0x54
{
	if (((H >> 2) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 2 L */
void Processor::BIT_2_L() // 0x55
{
	if (((L >> 2) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 2 (HL) */
void Processor::BIT_2_MEM_HL() // 0x56
{
	if (((memory->ReadByte(HL) >> 2) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 2 A */
void Processor::BIT_2_A() // 0x57
{
	if (((A >> 2) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 3 B */
void Processor::BIT_3_B() // 0x58
{
	if (((B >> 3) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 3 C */
void Processor::BIT_3_C() // 0x59
{
	if (((C >> 3) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 3 D */
void Processor::BIT_3_D() // 0x5A
{
	if (((D >> 3) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 3 E */
void Processor::BIT_3_E() // 0x5B
{
	if (((E >> 3) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 3 H */
void Processor::BIT_3_H() // 0x5C
{
	if (((H >> 3) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 3 L */
void Processor::BIT_3_L() // 0x5D
{
	if (((L >> 3) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 3 (HL) */
void Processor::BIT_3_MEM_HL() // 0x5E
{
	if (((memory->ReadByte(HL) >> 3) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 3 A */
void Processor::BIT_3_A() // 0x5F
{
	if (((A >> 3) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 4 B */
void Processor::BIT_4_B() // 0x60
{
	if (((B >> 4) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 4 C */
void Processor::BIT_4_C() // 0x61
{
	if (((C >> 4) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 4 D */
void Processor::BIT_4_D() // 0x62
{
	if (((D >> 4) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 4 E */
void Processor::BIT_4_E() // 0x63
{
	if (((E >> 4) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 4 H */
void Processor::BIT_4_H() // 0x64
{
	if (((H >> 4) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 4 L */
void Processor::BIT_4_L() // 0x65
{
	if (((L >> 4) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 4 (HL) */
void Processor::BIT_4_MEM_HL() // 0x66
{
	if (((memory->ReadByte(HL) >> 4) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 4 A */
void Processor::BIT_4_A() // 0x67
{
	if (((A >> 4) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 5 B */
void Processor::BIT_5_B() // 0x68
{
	if (((B >> 5) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 5 C */
void Processor::BIT_5_C() // 0x69
{
	if (((C >> 5) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 5 D */
void Processor::BIT_5_D() // 0x6A
{
	if (((D >> 5) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 5 E */
void Processor::BIT_5_E() // 0x6B
{
	if (((E >> 5) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 5 H */
void Processor::BIT_5_H() // 0x6C
{
	if (((H >> 5) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 5 L */
void Processor::BIT_5_L() // 0x6D
{
	if (((L >> 5) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 5 (HL) */
void Processor::BIT_5_MEM_HL() // 0x6E
{
	if (((memory->ReadByte(HL) >> 5) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 5 A */
void Processor::BIT_5_A() // 0x6F
{
	if (((A >> 5) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 6 B */
void Processor::BIT_6_B() // 0x70
{
	if (((B >> 6) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 6 C */
void Processor::BIT_6_C() // 0x71
{
	if (((C >> 6) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 6 D */
void Processor::BIT_6_D() // 0x72
{
	if (((D >> 6) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 6 E */
void Processor::BIT_6_E() // 0x73
{
	if (((E >> 6) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 6 H */
void Processor::BIT_6_H() // 0x74
{
	if (((H >> 6) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 6 L */
void Processor::BIT_6_L() // 0x75
{
	if (((L >> 6) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 6 (HL) */
void Processor::BIT_6_MEM_HL() // 0x76
{
	if (((memory->ReadByte(HL) >> 6) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 6 A */
void Processor::BIT_6_A() // 0x77
{
	if (((A >> 6) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 7 B */
void Processor::BIT_7_B() // 0x78
{
	if (((B >> 7) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 7 C */
void Processor::BIT_7_C() // 0x79
{
	if (((C >> 7) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 7 D */
void Processor::BIT_7_D() // 0x7A
{
	if (((D >> 7) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 7 E */
void Processor::BIT_7_E() // 0x7B
{
	if (((E >> 7) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 7 H */
void Processor::BIT_7_H() // 0x7C
{
	if (((H >> 7) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 7 L */
void Processor::BIT_7_L() // 0x7D
{
	if (((L >> 7) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 7 (HL) */
void Processor::BIT_7_MEM_HL() // 0x7E
{
	if (((memory->ReadByte(HL) >> 7) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* BIT 7 A */
void Processor::BIT_7_A() // 0x7F
{
	if (((A >> 7) & 0x01) == 0) EnableFlag(FLAG_ZERO);
	DisableFlag(FLAG_SUB);
	EnableFlag(FLAG_HALFCARRY);
}

/* RES 0 B */
void Processor::RES_0_B() // 0x80
{
	B = ClearBit(B, 0);
}

/* RES 0 C */
void Processor::RES_0_C() // 0x81
{
	C = ClearBit(C, 0);
}

/* RES 0 D */
void Processor::RES_0_D() // 0x82
{
	D = ClearBit(D, 0);
}

/* RES 0 E */
void Processor::RES_0_E() // 0x83
{
	E = ClearBit(E, 0);
}

/* RES 0 H */
void Processor::RES_0_H() // 0x84
{
	H = ClearBit(H, 0);
}

/* RES 0 L */
void Processor::RES_0_L() // 0x85
{
	L = ClearBit(L, 0);
}

/* RES 0 (HL) */
void Processor::RES_0_MEM_HL() // 0x86
{
	uint8 result = ClearBit(memory->ReadByte(HL), 0);
	memory->WriteByte(HL, result);
}

/* RES 0 A */
void Processor::RES_0_A() // 0x87
{
	A = ClearBit(A, 0);
}

/* RES 1 B */
void Processor::RES_1_B() // 0x88
{
	B = ClearBit(B, 1);
}

/* RES 1 C */
void Processor::RES_1_C() // 0x89
{
	C = ClearBit(C, 1);
}

/* RES 1 D */
void Processor::RES_1_D() // 0x8A
{
	D = ClearBit(D, 1);
}

/* RES 1 E */
void Processor::RES_1_E() // 0x8B
{
	E = ClearBit(E, 1);
}

/* RES 1 H */
void Processor::RES_1_H() // 0x8C
{
	H = ClearBit(H, 1);
}

/* RES 1 L */
void Processor::RES_1_L() // 0x8D
{
	L = ClearBit(L, 1);
}

/* RES 1 (HL) */
void Processor::RES_1_MEM_HL() // 0x8E
{
	uint8 result = ClearBit(memory->ReadByte(HL), 1);
	memory->WriteByte(HL, result);
}

/* RES 1 A */
void Processor::RES_1_A() // 0x8F
{
	A = ClearBit(A, 1);
}

/* RES 2 B */
void Processor::RES_2_B() // 0x90
{
	B = ClearBit(B, 2);
}

/* RES 2 C */
void Processor::RES_2_C() // 0x91
{
	C = ClearBit(C, 2);
}

/* RES 2 D */
void Processor::RES_2_D() // 0x92
{
	D = ClearBit(D, 2);
}

/* RES 2 E */
void Processor::RES_2_E() // 0x93
{
	E = ClearBit(E, 2);
}

/* RES 2 H */
void Processor::RES_2_H() // 0x94
{
	H = ClearBit(H, 2);
}

/* RES 2 L */
void Processor::RES_2_L() // 0x95
{
	L = ClearBit(L, 2);
}

/* RES 2 (HL) */
void Processor::RES_2_MEM_HL() // 0x96
{
	uint8 result = ClearBit(memory->ReadByte(HL), 2);
	memory->WriteByte(HL, result);
}

/* RES 2 A */
void Processor::RES_2_A() // 0x97
{
	A = ClearBit(A, 2);
}

/* RES 3 B */
void Processor::RES_3_B() // 0x98
{
	B = ClearBit(B, 3);
}

/* RES 3 C */
void Processor::RES_3_C() // 0x99
{
	C = ClearBit(C, 3);
}

/* RES 3 D */
void Processor::RES_3_D() // 0x9A
{
	D = ClearBit(D, 3);
}

/* RES 3 E */
void Processor::RES_3_E() // 0x9B
{
	E = ClearBit(E, 3);
}

/* RES 3 H */
void Processor::RES_3_H() // 0x9C
{
	H = ClearBit(H, 3);
}

/* RES 3 L */
void Processor::RES_3_L() // 0x9D
{
	L = ClearBit(L, 3);
}

/* RES 3 (HL) */
void Processor::RES_3_MEM_HL() // 0x9E
{
	uint8 result = ClearBit(memory->ReadByte(HL), 3);
	memory->WriteByte(HL, result);
}

/* RES 3 A */
void Processor::RES_3_A() // 0x9F
{
	A = ClearBit(A, 3);
}

/* RES 4 B */
void Processor::RES_4_B() // 0xA0
{
	B = ClearBit(B, 4);
}

/* RES 4 C */
void Processor::RES_4_C() // 0xA1
{
	C = ClearBit(C, 4);
}

/* RES 4 D */
void Processor::RES_4_D() // 0xA2
{
	D = ClearBit(D, 4);
}

/* RES 4 E */
void Processor::RES_4_E() // 0xA3
{
	E = ClearBit(E, 4);
}

/* RES 4 H */
void Processor::RES_4_H() // 0xA4
{
	H = ClearBit(H, 4);
}

/* RES 4 L */
void Processor::RES_4_L() // 0xA5
{
	L = ClearBit(L, 4);
}

/* RES 4 (HL) */
void Processor::RES_4_MEM_HL() // 0xA6
{
	uint8 result = ClearBit(memory->ReadByte(HL), 4);
	memory->WriteByte(HL, result);
}

/* RES 4 A */
void Processor::RES_4_A() // 0xA7
{
	A = ClearBit(A, 4);
}

/* RES 5 B */
void Processor::RES_5_B() // 0xA8
{
	B = ClearBit(B, 5);
}

/* RES 5 C */
void Processor::RES_5_C() // 0xA9
{
	C = ClearBit(C, 5);
}

/* RES 5 D */
void Processor::RES_5_D() // 0xAA
{
	D = ClearBit(D, 5);
}

/* RES 5 E */
void Processor::RES_5_E() // 0xAB
{
	E = ClearBit(E, 5);
}

/* RES 5 H */
void Processor::RES_5_H() // 0xAC
{
	H = ClearBit(H, 5);
}

/* RES 5 L */
void Processor::RES_5_L() // 0xAD
{
	L = ClearBit(L, 5);
}

/* RES 5 (HL) */
void Processor::RES_5_MEM_HL() // 0xAE
{
	uint8 result = ClearBit(memory->ReadByte(HL), 5);
	memory->WriteByte(HL, result);
}

/* RES 5 A */
void Processor::RES_5_A() // 0xAF
{
	A = ClearBit(A, 5);
}

/* RES 6 B */
void Processor::RES_6_B() // 0xB0
{
	B = ClearBit(B, 6);
}

/* RES 6 C */
void Processor::RES_6_C() // 0xB1
{
	C = ClearBit(C, 6);
}

/* RES 6 D */
void Processor::RES_6_D() // 0xB2
{
	D = ClearBit(D, 6);
}

/* RES 6 E */
void Processor::RES_6_E() // 0xB3
{
	E = ClearBit(E, 6);
}

/* RES 6 H */
void Processor::RES_6_H() // 0xB4
{
	H = ClearBit(H, 6);
}

/* RES 6 L */
void Processor::RES_6_L() // 0xB5
{
	L = ClearBit(L, 6);
}

/* RES 6 (HL) */
void Processor::RES_6_MEM_HL() // 0xB6
{
	uint8 result = ClearBit(memory->ReadByte(HL), 6);
	memory->WriteByte(HL, result);
}

/* RES 6 A */
void Processor::RES_6_A() // 0xB7
{
	A = ClearBit(A, 6);
}

/* RES 7 B */
void Processor::RES_7_B() // 0xB8
{
	B = ClearBit(B, 7);
}

/* RES 7 C */
void Processor::RES_7_C() // 0xB9
{
	C = ClearBit(C, 7);
}

/* RES 7 D */
void Processor::RES_7_D() // 0xBA
{
	D = ClearBit(D, 7);
}

/* RES 7 E */
void Processor::RES_7_E() // 0xBB
{
	E = ClearBit(E, 7);
}

/* RES 7 H */
void Processor::RES_7_H() // 0xBC
{
	H = ClearBit(H, 7);
}

/* RES 7 L */
void Processor::RES_7_L() // 0xBD
{
	L = ClearBit(L, 7);
}

/* RES 7 (HL) */
void Processor::RES_7_MEM_HL() // 0xBE
{
	uint8 result = ClearBit(memory->ReadByte(HL), 7);
	memory->WriteByte(HL, result);
}

/* RES 7 A */
void Processor::RES_7_A() // 0xBF
{
	A = ClearBit(A, 7);
}

/* SET 0 B */
void Processor::SET_0_B() // 0xC0
{
	B = SetBit(B, 0);
}

/* SET 0 C */
void Processor::SET_0_C() // 0xC1
{
	C = SetBit(C, 0);
}

/* SET 0 D */
void Processor::SET_0_D() // 0xC2
{
	D = SetBit(D, 0);
}

/* SET 0 E */
void Processor::SET_0_E() // 0xC3
{
	E = SetBit(E, 0);
}

/* SET 0 H */
void Processor::SET_0_H() // 0xC4
{
	H = SetBit(H, 0);
}

/* SET 0 L */
void Processor::SET_0_L() // 0xC5
{
	L = SetBit(L, 0);
}

/* SET 0 (HL) */
void Processor::SET_0_MEM_HL() // 0xC6
{
	uint8 result = SetBit(memory->ReadByte(HL), 0);
	memory->WriteByte(HL, result);
}

/* SET 0 A */
void Processor::SET_0_A() // 0xC7
{
	A = SetBit(A, 0);
}

/* SET 1 B */
void Processor::SET_1_B() // 0xC8
{
	B = SetBit(B, 1);
}

/* SET 1 C */
void Processor::SET_1_C() // 0xC9
{
	C = SetBit(C, 1);
}

/* SET 1 D */
void Processor::SET_1_D() // 0xCA
{
	D = SetBit(D, 1);
}

/* SET 1 E */
void Processor::SET_1_E() // 0xCB
{
	E = SetBit(E, 1);
}

/* SET 1 H */
void Processor::SET_1_H() // 0xCC
{
	H = SetBit(H, 1);
}

/* SET 1 L */
void Processor::SET_1_L() // 0xCD
{
	L = SetBit(L, 1);
}

/* SET 1 (HL) */
void Processor::SET_1_MEM_HL() // 0xCE
{
	uint8 result = SetBit(memory->ReadByte(HL), 1);
	memory->WriteByte(HL, result);
}

/* SET 1 A */
void Processor::SET_1_A() // 0xCF
{
	A = SetBit(A, 1);
}

/* SET 2 B */
void Processor::SET_2_B() // 0xD0
{
	B = SetBit(B, 2);
}

/* SET 2 C */
void Processor::SET_2_C() // 0xD1
{
	C = SetBit(C, 2);
}

/* SET 2 D */
void Processor::SET_2_D() // 0xD2
{
	D = SetBit(D, 2);
}

/* SET 2 E */
void Processor::SET_2_E() // 0xD3
{
	E = SetBit(E, 2);
}

/* SET 2 H */
void Processor::SET_2_H() // 0xD4
{
	H = SetBit(H, 2);
}

/* SET 2 L */
void Processor::SET_2_L() // 0xD5
{
	L = SetBit(L, 2);
}

/* SET 2 (HL) */
void Processor::SET_2_MEM_HL() // 0xD6
{
	uint8 result = SetBit(memory->ReadByte(HL), 2);
	memory->WriteByte(HL, result);
}

/* SET 2 A */
void Processor::SET_2_A() // 0xD7
{
	A = SetBit(A, 2);
}

/* SET 3 B */
void Processor::SET_3_B() // 0xD8
{
	B = SetBit(B, 3);
}

/* SET 3 C */
void Processor::SET_3_C() // 0xD9
{
	C = SetBit(C, 3);
}

/* SET 3 D */
void Processor::SET_3_D() // 0xDA
{
	D = SetBit(D, 3);
}

/* SET 3 E */
void Processor::SET_3_E() // 0xDB
{
	E = SetBit(E, 3);
}

/* SET 3 H */
void Processor::SET_3_H() // 0xDC
{
	H = SetBit(H, 3);
}

/* SET 3 L */
void Processor::SET_3_L() // 0xDD
{
	L = SetBit(L, 3);
}

/* SET 3 (HL) */
void Processor::SET_3_MEM_HL() // 0xDE
{
	uint8 result = SetBit(memory->ReadByte(HL), 3);
	memory->WriteByte(HL, result);
}

/* SET 3 A */
void Processor::SET_3_A() // 0xDF
{
	A = SetBit(A, 3);
}

/* SET 4 B */
void Processor::SET_4_B() // 0xE0
{
	B = SetBit(B, 4);
}

/* SET 4 C */
void Processor::SET_4_C() // 0xE1
{
	C = SetBit(C, 4);
}

/* SET 4 D */
void Processor::SET_4_D() // 0xE2
{
	D = SetBit(D, 4);
}

/* SET 4 E */
void Processor::SET_4_E() // 0xE3
{
	E = SetBit(E, 4);
}

/* SET 4 H */
void Processor::SET_4_H() // 0xE4
{
	H = SetBit(H, 4);
}

/* SET 4 L */
void Processor::SET_4_L() // 0xE5
{
	L = SetBit(L, 4);
}

/* SET 4 (HL) */
void Processor::SET_4_MEM_HL() // 0xE6
{
	uint8 result = SetBit(memory->ReadByte(HL), 4);
	memory->WriteByte(HL, result);
}

/* SET 4 A */
void Processor::SET_4_A() // 0xE7
{
	A = SetBit(A, 4);
}

/* SET 5 B */
void Processor::SET_5_B() // 0xE8
{
	B = SetBit(B, 5);
}

/* SET 5 C */
void Processor::SET_5_C() // 0xE9
{
	C = SetBit(C, 5);
}

/* SET 5 D */
void Processor::SET_5_D() // 0xEA
{
	D = SetBit(D, 5);
}

/* SET 5 E */
void Processor::SET_5_E() // 0xEB
{
	E = SetBit(E, 5);
}

/* SET 5 H */
void Processor::SET_5_H() // 0xEC
{
	H = SetBit(H, 5);
}

/* SET 5 L */
void Processor::SET_5_L() // 0xED
{
	L = SetBit(L, 5);
}

/* SET 5 (HL) */
void Processor::SET_5_MEM_HL() // 0xEE
{
	uint8 result = SetBit(memory->ReadByte(HL), 5);
	memory->WriteByte(HL, result);
}

/* SET 5 A */
void Processor::SET_5_A() // 0xEF
{
	A = SetBit(A, 5);
}

/* SET 6 B */
void Processor::SET_6_B() // 0xF0
{
	B = SetBit(B, 6);
}

/* SET 6 C */
void Processor::SET_6_C() // 0xF1
{
	C = SetBit(C, 6);
}

/* SET 6 D */
void Processor::SET_6_D() // 0xF2
{
	D = SetBit(D, 6);
}

/* SET 6 E */
void Processor::SET_6_E() // 0xF3
{
	E = SetBit(E, 6);
}

/* SET 6 H */
void Processor::SET_6_H() // 0xF4
{
	H = SetBit(H, 6);
}

/* SET 6 L */
void Processor::SET_6_L() // 0xF5
{
	L = SetBit(L, 6);
}

/* SET 6 (HL) */
void Processor::SET_6_MEM_HL() // 0xF6
{
	uint8 result = SetBit(memory->ReadByte(HL), 6);
	memory->WriteByte(HL, result);
}

/* SET 6 A */
void Processor::SET_6_A() // 0xF7
{
	A = SetBit(A, 6);
}

/* SET 7 B */
void Processor::SET_7_B() // 0xF8
{
	B = SetBit(B, 7);
}

/* SET 7 C */
void Processor::SET_7_C() // 0xF9
{
	C = SetBit(C, 7);
}

/* SET 7 D */
void Processor::SET_7_D() // 0xFA
{
	D = SetBit(D, 7);
}

/* SET 7 E */
void Processor::SET_7_E() // 0xFB
{
	E = SetBit(E, 7);
}

/* SET 7 H */
void Processor::SET_7_H() // 0xFC
{
	H = SetBit(H, 7);
}

/* SET 7 L */
void Processor::SET_7_L() // 0xFD
{
	L = SetBit(L, 7);
}

/* SET 7 (HL) */
void Processor::SET_7_MEM_HL() // 0xFE
{
	uint8 result = SetBit(memory->ReadByte(HL), 7);
	memory->WriteByte(HL, result);
}

/* SET 7 A */
void Processor::SET_7_A() // 0xFF
{
	A = SetBit(A, 7);
}

