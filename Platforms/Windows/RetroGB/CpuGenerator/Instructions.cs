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

using System.IO;

namespace CpuGenerator
{
    // TODO Cleanup and finish generator
    partial class Generator
    {
        private string GetCondition(string operand)
        {
            switch (operand)
            {
                case "NZ":
                    return "!IsFlagSet(Flag::Zero)";
                case "Z":
                    return "IsFlagSet(Flag::Zero)";
                case "NC":
                    return "!IsFlagSet(Flag::Carry)";
                case "C":
                    return "IsFlagSet(Flag::Carry)";
                default:
                    return "";
            }
        }

        private string GetStoreStub(string operand)
        {
            switch (operand)
            {
                case "(0xFF00+n)":
                    return "memory->WriteByte(0xFF00 + memory->ReadByte(PC++), {0});";
                case "(0xFF00+C)":
                    return "memory->WriteByte(0xFF00 + C, {0});";
                case "(nn)":
                    return "memory->WriteWord(memory->ReadWord(PC), {0});";
                case "(BC)":
                case "(DE)":
                case "(HL)":
                {
                    string op = operand.Replace("(", "").Replace(")", "");
                    return "memory->WriteByte(" + op + ", {0});";
                }
                case "(HLD)":
                {
                    string op = operand.Replace("(", "").Replace(")", "").Replace("D", "");
                    return "memory->WriteByte(" + op + "--, {0});";
                }
                case "(HLI)":
                {
                    string op = operand.Replace("(", "").Replace(")", "").Replace("I", "");
                    return "memory->WriteByte(" + op + "++, {0});";
                }
                default:
                    return operand + " = {0};";
            }
        }

        private string GetLoadStub(string operand)
        {
            switch (operand)
            {
                case "(0xFF00+n)":
                    return "memory->ReadByte(0xFF00 + memory->ReadByte(PC++))";
                case "(0xFF00+C)":
                    return "memory->ReadByte(0xFF00 + C)";
                case "n":
                    return "memory->ReadByte(PC++)";
                case "nn":
                    return "memory->ReadWord(PC)";
                case "(nn)":
                    return "memory->ReadByte(memory->ReadWord(PC))";
                case "(BC)":
                case "(DE)":
                case "(HL)":
                {
                    string op = operand.Replace("(", "").Replace(")", "");
                    return $"memory->ReadByte({op})";
                }
                case "(HLD)":
                {
                    string op = operand.Replace("(", "").Replace(")", "").Replace("D", "");
                    return $"memory->ReadByte({op}--)";
                }
                case "(HLI)":
                {
                    string op = operand.Replace("(", "").Replace(")", "").Replace("I", "");
                    return $"memory->ReadByte({op}++)";
                }
                default:
                    return operand;
            }
        }

        #region Opcode Templates

        public void WriteIncByte(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\t" + GetStoreStub(opcode.FirstOperand), string.Format("Inc({0})", GetLoadStub(opcode.FirstOperand)));
        }

        public void WriteIncWord(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\t{0}++;", opcode.FirstOperand);
        }

        public void WriteDecByte(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\t" + GetStoreStub(opcode.FirstOperand), string.Format("Dec({0})", GetLoadStub(opcode.FirstOperand)));
        }

        public void WriteDecWord(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\t{0}--;", opcode.FirstOperand);
        }

        public void WriteAnd(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tA &= {0};", GetLoadStub(opcode.FirstOperand));
            writer.WriteLine("\tSetFlags(Flag::Half_Carry);");
            writer.WriteLine("\tToggleFlag(Flag::Zero, A == 0);");
        }

        public void WriteOr(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tA |= {0};", GetLoadStub(opcode.FirstOperand));
            writer.WriteLine("\tClearFlags();");
            writer.WriteLine("\tToggleFlag(Flag::Zero, A == 0);");
        }

        public void WriteXor(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tA ^= {0};", GetLoadStub(opcode.FirstOperand));
            writer.WriteLine("\tClearFlags();");
            writer.WriteLine("\tToggleFlag(Flag::Zero, A == 0);");
        }

        public void WriteAddWord(TextWriter writer, Opcode opcode)
        {
            if (opcode.FirstOperand == "SP")
            {
                writer.WriteLine("\tAddSP(static_cast<int8>({0}));", GetLoadStub(opcode.SecondOperand));
            }
            else
            {
                writer.WriteLine("\tAdd{0}({1});", opcode.FirstOperand, GetLoadStub(opcode.SecondOperand));
            }
        }

        public void WriteAdd(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tAdd({0});", GetLoadStub(opcode.SecondOperand));
        }

        public void WriteAdc(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tAdc({0});", GetLoadStub(opcode.SecondOperand));
        }

        public void WriteSub(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tSub({0});", GetLoadStub(opcode.FirstOperand));
        }

        public void WriteSbc(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tSbc({0});", GetLoadStub(opcode.SecondOperand));
        }

        public void WriteDaa(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tint reg = A;\n");
            writer.WriteLine("\tif (!IsFlagSet(Flag::Sub))\n\t{");
            writer.WriteLine("\t\tif (IsFlagSet(Flag::Half_Carry) || (reg & 0xF) > 9)");
            writer.WriteLine("\t\t{");
            writer.WriteLine("\t\t\treg += 0x06;");
            writer.WriteLine("\t\t}\n");
            writer.WriteLine("\t\tif (IsFlagSet(Flag::Carry) || (reg > 0x9F))");
            writer.WriteLine("\t\t{");
            writer.WriteLine("\t\t\treg += 0x60;");
            writer.WriteLine("\t\t}");
            writer.WriteLine("\t}");
            writer.WriteLine("\telse\n\t{");
            writer.WriteLine("\t\tif (IsFlagSet(Flag::Half_Carry))");
            writer.WriteLine("\t\t{");
            writer.WriteLine("\t\t\treg = (reg - 6) & 0xFF;");
            writer.WriteLine("\t\t}\n");
            writer.WriteLine("\t\tif (IsFlagSet(Flag::Carry))");
            writer.WriteLine("\t\t{");
            writer.WriteLine("\t\t\treg -= 0x60;");
            writer.WriteLine("\t\t}");
            writer.WriteLine("\t}\n");
            writer.WriteLine("\tDisableFlag(Flag::Half_Carry);");
            writer.WriteLine("\tToggleFlag(Flag::Carry, (reg & 0x100) == 0x100);\n");
            writer.WriteLine("\treg &= 0xFF;");
            writer.WriteLine("\tToggleFlag(Flag::Zero, reg == 0);\n");
            writer.WriteLine("\tA = static_cast<uint8>(reg);");
        }

        public void WriteDi(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\time = false;");
        }

        public void WriteEi(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\time = true;");
        }

        public void WriteBit(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine($"\tBit({GetLoadStub(opcode.SecondOperand)}, {opcode.FirstOperand});");
        }

        public void WriteSet(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine($"\tSetBit({opcode.SecondOperand}, {opcode.FirstOperand});");
        }

        public void WriteRes(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine($"\tResetBit({opcode.SecondOperand}, {opcode.FirstOperand});");
        }

        public void WriteHLSet(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tuint8 result = memory->ReadByte(HL);");
            writer.WriteLine($"\tSetBit(result, {opcode.FirstOperand});");
            writer.WriteLine("\tmemory->WriteByte(HL, result);");
        }

        public void WriteHLRes(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tuint8 result = memory->ReadByte(HL);");
            writer.WriteLine($"\tResetBit(result, {opcode.FirstOperand});");
            writer.WriteLine("\tmemory->WriteByte(HL, result);");
        }

        public void WriteCall(TextWriter writer, Opcode opcode)
        {
            string cond = GetCondition(opcode.FirstOperand);
            string tabs = "\t";
            if (!string.IsNullOrEmpty(cond))
            {
                tabs += "\t";
                writer.WriteLine($"\tif ({cond})");
                writer.WriteLine("\t{");
            }
            writer.WriteLine(tabs + "uint16 address = memory->ReadWord(PC);");
            writer.WriteLine(tabs + "PC += 2;");
            writer.WriteLine(tabs + "PushToStack(PC);");
            writer.WriteLine(tabs + "PC = address;");
            if (cond != string.Empty)
            {
                writer.WriteLine();
                writer.WriteLine(tabs + $"return {opcode.ConditionalCycles};");
                writer.WriteLine("\t}\n\telse\n\t{\n\t\tPC += 2;\n\t}");
            }
        }

        public void WriteRet(TextWriter writer, Opcode opcode)
        {
            string cond = GetCondition(opcode.FirstOperand);
            string tabs = "\t";
            if (!string.IsNullOrEmpty(cond))
            {
                tabs += "\t";
                writer.WriteLine($"\tif ({cond})");
                writer.WriteLine("\t{");
            }
            writer.WriteLine(tabs + "PopFromStack(PC);");
            if (cond != string.Empty)
            {
                writer.WriteLine();
                writer.WriteLine(tabs + $"return {opcode.ConditionalCycles};");
                writer.WriteLine("\t}");
            }
        }

        public void WriteReti(TextWriter writer, Opcode opcode)
        {
            WriteRet(writer, opcode);
            writer.WriteLine("\time = true;");
        }

        public void WritePush(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine($"\tPushToStack({opcode.FirstOperand});");
        }

        public void WritePop(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine($"\tPopFromStack({opcode.FirstOperand});");

            if (opcode.FirstOperand == "AF")
            {
                writer.WriteLine("\tF &= 0xF0;");
            }
        }

        public void WriteJr(TextWriter writer, Opcode opcode)
        {
            string cond = GetCondition(opcode.FirstOperand);
            string tabs = "\t";
            if (!string.IsNullOrEmpty(cond))
            {
                tabs += "\t";
                writer.WriteLine($"\tif ({cond})");
                writer.WriteLine("\t{");
            }

            writer.WriteLine(tabs + "PC += 1 + static_cast<int8>(memory->ReadByte(PC));");
            if (cond != string.Empty)
            {
                writer.WriteLine();
                writer.WriteLine(tabs + "return " + opcode.ConditionalCycles + ";");
                writer.WriteLine("\t}\n\telse\n\t{\n\t\tPC++;\n\t}");
            }
        }

        public void WriteJp(TextWriter writer, Opcode opcode)
        {
            string cond = GetCondition(opcode.FirstOperand);
            string tabs = "\t";
            if (!string.IsNullOrEmpty(cond))
            {
                tabs += "\t";
                writer.WriteLine($"\tif ({cond})");
                writer.WriteLine("\t{");
            }

            writer.WriteLine(tabs + "PC = memory->ReadWord(PC);");
            if (cond != string.Empty)
            {
                writer.WriteLine();
                writer.WriteLine(tabs + "return " + opcode.ConditionalCycles + ";");
                writer.WriteLine("\t}\n\telse\n\t{\n\t\tPC += 2;\n\t}");
            }
        }

        public void WriteCpl(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tA = ~A;");
            writer.WriteLine("\tEnableFlag(Flag::Half_Carry);");
            writer.WriteLine("\tEnableFlag(Flag::Sub);");
        }

        public void WriteCcf(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tInvertFlag(Flag::Carry);");
            writer.WriteLine("\tDisableFlag(Flag::Half_Carry);");
            writer.WriteLine("\tDisableFlag(Flag::Sub);");
        }

        public void WriteScf(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tEnableFlag(Flag::Carry);");
            writer.WriteLine("\tDisableFlag(Flag::Half_Carry);");
            writer.WriteLine("\tDisableFlag(Flag::Sub);");
        }

        public void WriteCp(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tuint8 value = {0};", GetLoadStub(opcode.FirstOperand));
            writer.WriteLine("\tSetFlags(Flag::Sub);");
            writer.WriteLine("\tToggleFlag(Flag::Carry, A < value);");
            writer.WriteLine("\tToggleFlag(Flag::Zero, A == value);");
            writer.WriteLine("\tToggleFlag(Flag::Half_Carry, ((A - value) & 0xF) > (A & 0xF));");
            /*
            writer.WriteLine($"\tuint8 value = {GetLoadStub(opcode.FirstOperand)};");
            writer.WriteLine("\tuint8 result = A - value;");
            writer.WriteLine("\tSetFlags(Flag::Sub);");
            writer.WriteLine("\tToggleFlag(Flag::Carry, A < value);");
            writer.WriteLine("\tToggleFlag(Flag::Zero, result == 0);");
            writer.WriteLine("\tToggleFlag(Flag::Half_Carry, ((A ^ value ^ result) & 0x10) != 0);");
            */
        }

        public void WriteHalt(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\thalted = true;");
        }

        public void WriteRst(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tPushToStack(PC);");
            writer.WriteLine("\tPC = {0};", string.IsNullOrEmpty(opcode.FirstOperand) ? "0x0000" : opcode.FirstOperand);
        }

        public void WriteSwap(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\t{0} = (({0} >> 4) & 0x0F) | (({0} << 4) & 0xF0);", opcode.FirstOperand);
            writer.WriteLine("\tClearFlags();");
            writer.WriteLine($"\tToggleFlag(Flag::Zero, {opcode.FirstOperand} == 0);");
        }

        public void WriteSwapHL(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tuint8 val = memory->ReadByte(HL);");
            writer.WriteLine("\tmemory->WriteByte(HL, ((val >> 4) & 0x0F) | ((val << 4) & 0xF0));");
            writer.WriteLine("\tClearFlags();");
            writer.WriteLine("\tToggleFlag(Flag::Zero, memory->ReadByte(HL) == 0);");
        }

        public void WriteHLSPN(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tint8 n = static_cast<int8>(memory->ReadByte(PC++));");
            writer.WriteLine("\tHL = SP + n;");
            writer.WriteLine("\tClearFlags();");
            writer.WriteLine("\tToggleFlag(Flag::Carry, ((SP ^ n ^ HL) & 0x100) == 0x100);");
            writer.WriteLine("\tToggleFlag(Flag::Half_Carry, ((SP ^ n ^ HL) & 0x10) == 0x10);");
        }

        public void WriteRl(TextWriter writer, Opcode opcode, bool a = false)
        {
            string operand = a ? "A" : opcode.FirstOperand;
            string registerA = a ? "true" : "false";
            writer.WriteLine("\t" + GetStoreStub(operand), $"Rl({GetLoadStub(operand)}, {registerA})");
        }

        public void WriteRlc(TextWriter writer, Opcode opcode, bool a = false)
        {
            string operand = a ? "A" : opcode.FirstOperand;
            string registerA = a ? "true" : "false";
            writer.WriteLine("\t" + GetStoreStub(operand), $"Rlc({GetLoadStub(operand)}, {registerA})");
        }

        public void WriteRr(TextWriter writer, Opcode opcode, bool a = false)
        {
            string operand = a ? "A" : opcode.FirstOperand;
            string registerA = a ? "true" : "false";
            writer.WriteLine("\t" + GetStoreStub(operand), $"Rr({GetLoadStub(operand)}, {registerA})");
        }

        public void WriteRrc(TextWriter writer, Opcode opcode, bool a = false)
        {
            string operand = a ? "A" : opcode.FirstOperand;
            string registerA = a ? "true" : "false";
            writer.WriteLine("\t" + GetStoreStub(operand), $"Rrc({GetLoadStub(operand)}, {registerA})");
        }

        public void WriteSla(TextWriter writer, Opcode opcode, bool a = false)
        {
            writer.WriteLine("\t" + GetStoreStub(opcode.FirstOperand), $"Sla({GetLoadStub(opcode.FirstOperand)})");
        }

        public void WriteSra(TextWriter writer, Opcode opcode, bool a = false)
        {
            writer.WriteLine("\t" + GetStoreStub(opcode.FirstOperand), $"Sra({GetLoadStub(opcode.FirstOperand)})");
        }

        public void WriteSrl(TextWriter writer, Opcode opcode, bool a = false)
        {
            writer.WriteLine("\t" + GetStoreStub(opcode.FirstOperand), $"Srl({GetLoadStub(opcode.FirstOperand)})");
        }

        #endregion
    }
}
