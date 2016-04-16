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
                    return "!IsFlagSet(FLAG_ZERO)";
                case "Z":
                    return "IsFlagSet(FLAG_ZERO)";
                case "NC":
                    return "!IsFlagSet(FLAG_CARRY)";
                case "C":
                    return "IsFlagSet(FLAG_CARRY)";
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
                    return "memory->ReadByte(" + op + ")";
                }
                case "(HLD)":
                {
                    string op = operand.Replace("(", "").Replace(")", "").Replace("D", "");
                    return "memory->ReadByte(" + op + "--)";
                }
                case "(HLI)":
                {
                    string op = operand.Replace("(", "").Replace(")", "").Replace("I", "");
                    return "memory->ReadByte(" + op + "++)";
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
            writer.WriteLine("\tSetFlag(FLAG_HALFCARRY);");
            writer.WriteLine("\tif (A == 0) EnableFlag(FLAG_ZERO);");
        }

        public void WriteOr(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tA |= {0};", GetLoadStub(opcode.FirstOperand));
            writer.WriteLine("\tClearFlags();");
            writer.WriteLine("\tif (A == 0) EnableFlag(FLAG_ZERO);");
        }

        public void WriteXor(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tA ^= {0};", GetLoadStub(opcode.FirstOperand));
            writer.WriteLine("\tClearFlags();");
            writer.WriteLine("\tif (A == 0) EnableFlag(FLAG_ZERO);");
        }

        public void WriteAddWord(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tAdd{0}({1});", opcode.FirstOperand, GetLoadStub(opcode.SecondOperand));
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
            writer.WriteLine("\tuint8 reg = A;\n");
            writer.WriteLine("\tif (IsFlagSet(FLAG_SUB))\n\t{");
            writer.WriteLine("\t\tif ((reg & 0x0F) > 9 || IsFlagSet(FLAG_HALFCARRY))");
            writer.WriteLine("\t\t{");
            writer.WriteLine("\t\t\treg -= 0x06;");
            writer.WriteLine("\t\t}");
            writer.WriteLine("\t\telse if ((reg & 0x9F) > 9 || IsFlagSet(FLAG_CARRY))");
            writer.WriteLine("\t\t{");
            writer.WriteLine("\t\t\treg -= 0x60;");
            writer.WriteLine("\t\t}");
            writer.WriteLine("\t}");
            writer.WriteLine("\telse\n\t{");
            writer.WriteLine("\t\tif ((reg & 0x0F) > 9 || IsFlagSet(FLAG_HALFCARRY))");
            writer.WriteLine("\t\t{");
            writer.WriteLine("\t\t\treg += 0x06;");
            writer.WriteLine("\t\t}");
            writer.WriteLine("\t\telse if ((reg & 0x9F) > 9 || IsFlagSet(FLAG_CARRY))");
            writer.WriteLine("\t\t{");
            writer.WriteLine("\t\t\treg += 0x60;");
            writer.WriteLine("\t\t}\n");
            writer.WriteLine("\t}");
            writer.WriteLine("\tDisableFlag(FLAG_HALFCARRY);");
            writer.WriteLine("\tif (reg == 0) EnableFlag(FLAG_ZERO);\n");
            writer.WriteLine("\tA = reg;");
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
            writer.WriteLine("\tif ((({0} >> {1}) & 0x01) == 0) EnableFlag(FLAG_ZERO);", GetLoadStub(opcode.SecondOperand), opcode.FirstOperand);
            writer.WriteLine("\telse DisableFlag(FLAG_ZERO);");
            writer.WriteLine("\tDisableFlag(FLAG_SUB);");
            writer.WriteLine("\tEnableFlag(FLAG_HALFCARRY);");
        }

        public void WriteSet(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tSetBit({0}, {1});", opcode.SecondOperand, opcode.FirstOperand);
        }

        public void WriteRes(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tResetBit({0}, {1});", opcode.SecondOperand, opcode.FirstOperand);
        }

        public void WriteHLSet(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tuint8 result = memory->ReadByte(HL);");
            writer.WriteLine("\tSetBit(result, {0});", opcode.FirstOperand);
            writer.WriteLine("\tmemory->WriteByte(HL, result);");
        }

        public void WriteHLRes(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tuint8 result = memory->ReadByte(HL);");
            writer.WriteLine("\tResetBit(result, {0});", opcode.FirstOperand);
            writer.WriteLine("\tmemory->WriteByte(HL, result);");
        }

        public void WriteCall(TextWriter writer, Opcode opcode)
        {
            string cond = GetCondition(opcode.FirstOperand);
            string tabs = "\t";
            if (!string.IsNullOrEmpty(cond))
            {
                tabs += "\t";
                writer.WriteLine("\tif (" + cond + ")\n\t{");
                writer.WriteLine(tabs + "condition = true;");
            }
            writer.WriteLine(tabs + "uint16 address = memory->ReadWord(PC);");
            writer.WriteLine(tabs + "PC += 2;");
            writer.WriteLine(tabs + "StackPush(PC);");
            writer.WriteLine(tabs + "PC = address;");
            if (cond != string.Empty)
            {
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
                writer.WriteLine("\tif (" + cond + ")\n\t{");
                writer.WriteLine(tabs + "condition = true;");
            }
            writer.WriteLine(tabs + "StackPop(PC);");
            if (cond != string.Empty)
            {
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
            writer.WriteLine("\tStackPush({0});", opcode.FirstOperand);
        }

        public void WritePop(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tStackPop({0});", opcode.FirstOperand);

            if (opcode.FirstOperand == "AF")
                writer.WriteLine("\tF &= 0xF0;");
        }

        public void WriteJr(TextWriter writer, Opcode opcode)
        {
            string cond = GetCondition(opcode.FirstOperand);
            string tabs = "\t";
            if (!string.IsNullOrEmpty(cond))
            {
                tabs += "\t";
                writer.WriteLine("\tif (" + cond + ")\n\t{");
                writer.WriteLine(tabs + "condition = true;");
            }

            writer.WriteLine(tabs + "PC += 1 + static_cast<int8>(memory->ReadByte(PC));");
            if (cond != string.Empty)
            {
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
                writer.WriteLine("\tif (" + cond + ")\n\t{");
                writer.WriteLine(tabs + "condition = true;");
            }

            writer.WriteLine(tabs + "PC = memory->ReadWord(PC);");
            if (cond != string.Empty)
            {
                writer.WriteLine("\t}\n\telse\n\t{\n\t\tPC += 2;\n\t}");
            }
        }

        public void WriteCpl(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tA = ~A;");
            writer.WriteLine("\tEnableFlag(FLAG_HALFCARRY);");
            writer.WriteLine("\tEnableFlag(FLAG_SUB);");
        }

        public void WriteCcf(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tInvertFlag(FLAG_CARRY);");
            writer.WriteLine("\tDisableFlag(FLAG_HALFCARRY);");
            writer.WriteLine("\tDisableFlag(FLAG_SUB);");
        }

        public void WriteScf(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tEnableFlag(FLAG_CARRY);");
            writer.WriteLine("\tDisableFlag(FLAG_HALFCARRY);");
            writer.WriteLine("\tDisableFlag(FLAG_SUB);");
        }

        public void WriteCp(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tuint8 value = {0};", GetLoadStub(opcode.FirstOperand));
            writer.WriteLine("\tuint8 result = A - value;");
            writer.WriteLine("\tSetFlag(FLAG_SUB);");
            writer.WriteLine("\tif (A < value) EnableFlag(FLAG_CARRY);");
            writer.WriteLine("\tif (result == 0) EnableFlag(FLAG_ZERO);");
            writer.WriteLine("\tif (((A ^ value ^ result) & 0x10) != 0) EnableFlag(FLAG_HALFCARRY);");
        }

        public void WriteHalt(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\thalted = true;");
        }

        public void WriteRst(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tStackPush(PC);");
            writer.WriteLine("\tPC = {0};", string.IsNullOrEmpty(opcode.FirstOperand) ? "0x0000" : opcode.FirstOperand);
        }

        public void WriteSwap(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\t{0} = (({0} >> 4) & 0x0F) | (({0} << 4) & 0xF0);", opcode.FirstOperand);
            writer.WriteLine("\tClearFlags();");
            writer.WriteLine("\tif ({0} == 0) EnableFlag(FLAG_ZERO);", opcode.FirstOperand);
        }

        public void WriteSwapHL(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tuint8 val = memory->ReadByte(HL);");
            writer.WriteLine("\tmemory->WriteByte(HL, ((val >> 4) & 0x0F) | ((val << 4) & 0xF0));");
            writer.WriteLine("\tClearFlags();");
            writer.WriteLine("\tif (memory->ReadByte(HL) == 0) EnableFlag(FLAG_ZERO);");
        }

        public void WriteHLSPN(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tint8 n = static_cast<int8>(memory->ReadByte(PC++));");
            writer.WriteLine("\tHL = SP + n;");
            writer.WriteLine("\tClearFlags();");
            writer.WriteLine("\tif (((SP ^ n ^ HL) & 0x100) == 0x100)");
            writer.WriteLine("\t\tEnableFlag(FLAG_CARRY);");
            writer.WriteLine("\tif (((SP ^ n ^ HL) & 0x10) == 0x10)");
            writer.WriteLine("\t\tEnableFlag(FLAG_HALFCARRY);");
        }

        public void WriteRl(TextWriter writer, Opcode opcode, bool a = false)
        {
            string operand = a ? "A" : opcode.FirstOperand;
            writer.WriteLine("\t" + GetStoreStub(operand), string.Format("Rl({0})", GetLoadStub(operand)));
        }

        public void WriteRlc(TextWriter writer, Opcode opcode, bool a = false)
        {
            string operand = a ? "A" : opcode.FirstOperand;
            writer.WriteLine("\t" + GetStoreStub(operand), string.Format("Rlc({0})", GetLoadStub(operand)));
        }

        public void WriteRr(TextWriter writer, Opcode opcode, bool a = false)
        {
            string operand = a ? "A" : opcode.FirstOperand;
            writer.WriteLine("\t" + GetStoreStub(operand), string.Format("Rr({0})", GetLoadStub(operand)));
        }

        public void WriteRrc(TextWriter writer, Opcode opcode, bool a = false)
        {
            string operand = a ? "A" : opcode.FirstOperand;
            writer.WriteLine("\t" + GetStoreStub(operand), string.Format("Rrc({0})", GetLoadStub(operand)));
        }

        public void WriteSla(TextWriter writer, Opcode opcode, bool a = false)
        {
            writer.WriteLine("\t" + GetStoreStub(opcode.FirstOperand), string.Format("Sla({0})", GetLoadStub(opcode.FirstOperand)));
        }

        public void WriteSra(TextWriter writer, Opcode opcode, bool a = false)
        {
            writer.WriteLine("\t" + GetStoreStub(opcode.FirstOperand), string.Format("Sra({0})", GetLoadStub(opcode.FirstOperand)));
        }

        public void WriteSrl(TextWriter writer, Opcode opcode, bool a = false)
        {
            writer.WriteLine("\t" + GetStoreStub(opcode.FirstOperand), string.Format("Srl({0})", GetLoadStub(opcode.FirstOperand)));
        }

        #endregion
    }
}
