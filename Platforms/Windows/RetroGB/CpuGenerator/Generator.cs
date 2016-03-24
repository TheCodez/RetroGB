using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CpuGenerator
{
    class Generator
    {
        public Generator()
        {
        }

        public void Generate(TextWriter writer)
        {
            writer.WriteLine("#include \"Processor.h\"");
            writer.WriteLine();

            List<string> opcodes = Properties.Resources.Opcodes.Split(new[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries).ToList();
            List<string> opcodesCB = Properties.Resources.OpcodesCB.Split(new[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries).ToList();

            if (opcodes.Count != 256 && opcodesCB.Count != 256)
                return;

            writer.WriteLine("void Processor::InitOpcodes()");
            writer.WriteLine("{");

            for (int i = 0; i < 256; i++)
            {
                string line = opcodes.ElementAt(i);

                if ((line != "UNDEFINED") && (line != "CB_OPCODE"))
                    MapOpcodes(writer, i, line);
                else
                    MapInvalid(writer, i, line);
            }

            writer.WriteLine();
            writer.WriteLine("\t// CB Obcodes");

            for (int i = 0; i < 256; i++)
            {
                string line = opcodesCB.ElementAt(i);

                MapCBOpcodes(writer, i, line);
            }

            writer.WriteLine("}");
            writer.WriteLine();

            for (int i = 0; i < 256; i++)
            {
                string line = opcodes.ElementAt(i);

                if ((line != "UNDEFINED") && (line != "CB_OPCODE"))
                    GenerateMethod(writer, i, line);
            }

            writer.WriteLine("// CB Obcodes");
            writer.WriteLine();

            for (int i = 0; i < 256; i++)
            {
                string line = opcodesCB.ElementAt(i);

                GenerateMethod(writer, i, line);
            }
        }

        public void GenerateMethod(TextWriter writer, int op, string line)
        {
            Opcode opcode;
            ParseOpcode(line, out opcode);

            writer.WriteLine("/* {0} */", line.Replace(",", ", "));
            writer.WriteLine("void Processor::{0}() // 0x{1:X2}", opcode.ToFunctionName(), op);
            writer.WriteLine("{");

            WriteOpcodeStub(writer, opcode);

            writer.WriteLine("}");
            writer.WriteLine();
        }

        public void ParseOpcode(string opString, out Opcode opcode)
        {
            var instr = opString.Split(' ', ',');
            var instrLength = instr.Length;

            opcode = new Opcode();
            opcode.Operation = instr[0];
            opcode.NumberOfOperands = instrLength - 1;

            if (opcode.NumberOfOperands == 1)
            {
                opcode.FirstOperand = instr[1];
                opcode.SecondOperand = string.Empty;
            }
            else if (opcode.NumberOfOperands == 2)
            {
                opcode.FirstOperand = instr[1];
                opcode.SecondOperand = instr[2];
            }
        }

        private void WriteOpcodeStub(TextWriter writer, Opcode opcode)
        {
            string operation = opcode.Operation;
            string firstOperand = opcode.FirstOperand;
            string secondOperand = opcode.SecondOperand;

            string first = GetStoreStub(firstOperand);
            string second = GetLoadStub(secondOperand);

            switch (operation)
            {
                case "NOP":
                    break;
                case "LD":
                    if (firstOperand != secondOperand)
                    {
                        writer.WriteLine("\t" + string.Format(first, second));
                    }
                    break;
                case "INC":
                    if (firstOperand == "BC" || firstOperand == "DE" || firstOperand == "HL" || firstOperand == "SP")
                        WriteIncWord(writer, opcode);
                    else
                        WriteIncByte(writer, opcode);
                    break;
                case "DEC":
                    if (firstOperand == "BC" || firstOperand == "DE" || firstOperand == "HL" || firstOperand == "SP")
                        WriteDecWord(writer, opcode);
                    else
                        WriteDecByte(writer, opcode);
                    break;
                case "AND":
                    WriteAnd(writer, opcode);
                    break;
                case "OR":
                    WriteOr(writer, opcode);
                    break;
                case "XOR":
                    WriteXor(writer, opcode);
                    break;
                case "ADD":
                    WriteAdd(writer, opcode);
                    break;
                case "ADC":
                    WriteAdc(writer, opcode);
                    break;
                case "SUB":
                    WriteSub(writer, opcode);
                    break;
                case "SBC":
                    WriteSbc(writer, opcode);
                    break;
                case "DI":
                    WriteDi(writer, opcode);
                    break;
                case "BIT":
                    WriteBit(writer, opcode);
                    break;
                case "SET":
                    if (secondOperand != "(HL)")
                        WriteSet(writer, opcode);
                    else
                        WriteHLSet(writer, opcode);
                    break;
                case "RES":
                    if (secondOperand != "(HL)")
                        WriteRes(writer, opcode);
                    else
                        WriteHLRes(writer, opcode);
                        break;
                case "CALL":
                        WriteCall(writer, opcode);
                        break;
                case "RET":
                        WriteRet(writer, opcode);
                        break;
                case "RETI":
                        WriteReti(writer, opcode);
                        break;
                case "PUSH":
                        WritePush(writer, opcode);
                        break;
                case "POP":
                        WritePop(writer, opcode);
                        break;
                case "JR":
                        WriteJr(writer, opcode);
                        break;
                case "JP":
                        WriteJp(writer, opcode);
                        break;
                case "DAA":
                        WriteDaa(writer, opcode);
                        break;
                case "CCF":
                        WriteCcf(writer, opcode);
                        break;
                case "SCF":
                        WriteScf(writer, opcode);
                        break;
                case "CP":
                        WriteCp(writer, opcode);
                        break;
                case "HALT":
                        WriteHalt(writer, opcode);
                        break;
                case "RST":
                        WriteRst(writer, opcode);
                        break;
                default:
                    writer.WriteLine("\t// Not implemented yet");
                    writer.WriteLine("\tUnknownOpcode();");
                    break;
            }
        }

        private string GetCondition(string operand)
        {
            switch (operand)
            {
                case "NZ":
                    return "!IsFlagSet(FLAG_ZERO)";
                    break;
                case "Z":
                    return "IsFlagSet(FLAG_ZERO)";
                    break;
                case "NC":
                    return "!IsFlagSet(FLAG_CARRY)";
                    break;
                case "C":
                    return "IsFlagSet(FLAG_CARRY)";
                    break;
                default:
                    return "";
                    break;
            }
        }

        private string GetStoreStub(string operand)
        {
            switch (operand)
            {
                case "(0xFF00+n)":
                    return "memory->WriteWord(0xFF00 + memory->ReadWord(PC++), {0});";
                case "(0xFF00+C)":
                    return "memory->WriteByte(0xFF00 + C, {0});";
                case "(nn)":
                    return "memory->WriteWord(memory->ReadWord(PC++), {0});";
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
                    return "memory->ReadByte(0xFF00 + PC++)";
                case "(0xFF00+C)":
                    return "memory->ReadByte(0xFF00 + C)";
                case "n":
                    return "memory->ReadByte(PC++)";
                case "nn":
                    return "memory->ReadWord(PC++)";
                case "(nn)":
                    return "memory->ReadByte(memory->ReadWord(PC++))";
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

        public void MapOpcodes(TextWriter writer, int op, string line)
        {
            Opcode opcode;
            ParseOpcode(line, out opcode);

            var funcName = opcode.ToFunctionName();

            writer.WriteLine("\topcodes[0x{0:X2}] = std::bind(&Processor::{1}, this);", op, funcName);
        }

        public void MapInvalid(TextWriter writer, int op, string line)
        {
            writer.WriteLine("\topcodes[0x{0:X2}] = std::bind(&Processor::InvalidOpcode, this);", op);
        }

        public void MapCBOpcodes(TextWriter writer, int op, string line)
        {
            Opcode opcode;
            ParseOpcode(line, out opcode);

            var funcName = opcode.ToFunctionName();

            writer.WriteLine("\topcodesCB[0x{0:X2}] = std::bind(&Processor::{1}, this);", op, funcName);
        }

        #region Opcode Templates

        #region Inc, Dec
        public void WriteIncByte(TextWriter writer, Opcode opcode)
        {
            if (opcode.FirstOperand == "(HL)")
                writer.WriteLine("\tmemory->WriteByte(HL, memory->ReadByte(HL++));");
            else
                writer.WriteLine("\t{0}++;", opcode.FirstOperand);
            writer.WriteLine("\t//TODO flags");
            writer.WriteLine("\tDisableFlag(FLAG_SUB);");
            writer.WriteLine("\tif (A == 0) EnableFlag(FLAG_ZERO);");
        }

        public void WriteIncWord(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\t{0}++;", opcode.FirstOperand);
        }

        public void WriteDecByte(TextWriter writer, Opcode opcode)
        {
            if (opcode.FirstOperand == "(HL)")
                writer.WriteLine("\tmemory->WriteByte(HL, memory->ReadByte(HL--));");
            else
                writer.WriteLine("\t{0}++;", opcode.FirstOperand);
            writer.WriteLine("\t//TODO flags");
            writer.WriteLine("\tEnableFlag(FLAG_SUB);");
            writer.WriteLine("\tif (A == 0) EnableFlag(FLAG_ZERO);");
        }

        public void WriteDecWord(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\t{0}--;", opcode.FirstOperand);
        }
        #endregion

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

        public void WriteAdd(TextWriter writer, Opcode opcode)
        {
            string secOperand = !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.SecondOperand : opcode.FirstOperand;
            writer.WriteLine("\t{0} += {1};", !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.FirstOperand : "A", GetLoadStub(secOperand));
            writer.WriteLine("\tDisableFlag(FLAG_SUB);");
            writer.WriteLine("\tif ({0} == 0) EnableFlag(FLAG_ZERO);", !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.FirstOperand : "A");
            writer.WriteLine("\tif ({0} > 0xFF) EnableFlag(FLAG_CARRY);", !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.FirstOperand : "A");
        }

        public void WriteAdc(TextWriter writer, Opcode opcode)
        {
            string secOperand = !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.SecondOperand : opcode.FirstOperand; 
            writer.WriteLine("\tuint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;");
            writer.WriteLine("\tA += ({1} + carry);", !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.FirstOperand : "A", GetLoadStub(secOperand));
            writer.WriteLine("\tDisableFlag(FLAG_SUB);");
            writer.WriteLine("\tif ({0} == 0) EnableFlag(FLAG_ZERO);", !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.FirstOperand : "A");
            writer.WriteLine("\tif ({0} > 0xFF) EnableFlag(FLAG_CARRY);", !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.FirstOperand : "A");
        }

        public void WriteSub(TextWriter writer, Opcode opcode)
        {
            string secOperand = !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.SecondOperand : opcode.FirstOperand;
            writer.WriteLine("\t{0} -= {1};", !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.FirstOperand : "A", GetLoadStub(secOperand));
            writer.WriteLine("\tEnableFlag(FLAG_SUB);");
            writer.WriteLine("\tif ({0} == 0) EnableFlag(FLAG_ZERO);", !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.FirstOperand : "A");
            writer.WriteLine("\tif ({0} < 0) EnableFlag(FLAG_CARRY);", !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.FirstOperand : "A");
        }

        public void WriteSbc(TextWriter writer, Opcode opcode)
        {
            string secOperand = !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.SecondOperand : opcode.FirstOperand;
            writer.WriteLine("\tuint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;");
            writer.WriteLine("\t{0} -= ({1} + carry);", !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.FirstOperand : "A", GetLoadStub(secOperand));
            writer.WriteLine("\tEnableFlag(FLAG_SUB);");
            writer.WriteLine("\tif ({0} == 0) EnableFlag(FLAG_ZERO);", !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.FirstOperand : "A");
            writer.WriteLine("\tif ({0} < 0) EnableFlag(FLAG_CARRY);", !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.FirstOperand : "A");
        }

        public void WriteAnd(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tA &= {0};", GetLoadStub(opcode.FirstOperand));
            writer.WriteLine("\tClearFlags();");
            writer.WriteLine("\tif (A == 0) EnableFlag(FLAG_ZERO);");
        }

        public void WriteDaa(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tuint8 reg = A;\n");
            writer.WriteLine("\tif ((reg & 0x0F) > 9 || IsFlagSet(FLAG_HALFCARRY))");
            writer.WriteLine("\t{");
            writer.WriteLine("\t\treg += 0x06;");
            writer.WriteLine("\t}");
            writer.WriteLine("\telse if ((reg & 0x9F) > 9 || IsFlagSet(FLAG_CARRY))");
            writer.WriteLine("\t{");
            writer.WriteLine("\t\treg += 0x60;");
            writer.WriteLine("\t}\n");
            writer.WriteLine("\tDisableFlag(FLAG_HALFCARRY);");
            writer.WriteLine("\tif (reg == 0) EnableFlag(FLAG_ZERO);\n");
            writer.WriteLine("\tA = reg;");
        }

        public void WriteDi(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\time = false;");
        }

        public void WriteBit(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tif ((({0} >> {1}) & 0x01) == 0) EnableFlag(FLAG_ZERO);", GetLoadStub(opcode.SecondOperand), opcode.FirstOperand);
            writer.WriteLine("\tDisableFlag(FLAG_SUB);");
            writer.WriteLine("\tEnableFlag(FLAG_HALFCARRY);");
        }

        public void WriteSet(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\t{0} = SetBit({1}, {2});", opcode.SecondOperand, opcode.SecondOperand, opcode.FirstOperand);
        }

        public void WriteRes(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\t{0} = ClearBit({1}, {2});", opcode.SecondOperand, opcode.SecondOperand, opcode.FirstOperand);
        }

        public void WriteHLSet(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tuint8 result = SetBit(memory->ReadByte(HL), {0});", opcode.FirstOperand);
            writer.WriteLine("\tmemory->WriteByte(HL, result);");
        }

        public void WriteHLRes(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tuint8 result = ClearBit(memory->ReadByte(HL), {0});", opcode.FirstOperand);
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
            }
            writer.WriteLine(tabs + "SP -= 2;");
            writer.WriteLine(tabs + "memory->WriteWord(SP, PC + 2);");
            writer.WriteLine(tabs + "PC = memory->ReadWord(PC);");
            if (cond != string.Empty)
            {
                writer.WriteLine("\t}");
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
        }

        public void WriteJr(TextWriter writer, Opcode opcode)
        {
            string cond = GetCondition(opcode.FirstOperand);
            string tabs = "\t";
            if (!string.IsNullOrEmpty(cond))
            {
                tabs += "\t";
                writer.WriteLine("\tif (" + cond + ")\n\t{");
            }

            writer.WriteLine(tabs + "PC += memory->ReadWord(PC++);", opcode.FirstOperand);
            if (cond != string.Empty)
            {
                writer.WriteLine("\t}");
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
            }

            writer.WriteLine(tabs + "PC = memory->ReadWord(PC++);", opcode.FirstOperand);
            if (cond != string.Empty)
            {
                writer.WriteLine("\t}");
            }
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
            writer.WriteLine("\tuint8 reg = A;");
            writer.WriteLine("\treg -= {0};", GetLoadStub(opcode.FirstOperand));
            writer.WriteLine("\tEnableFlag(FLAG_SUB);");
            writer.WriteLine("\tif (reg == 0) EnableFlag(FLAG_ZERO);");
            writer.WriteLine("\tif (reg < 0) EnableFlag(FLAG_CARRY);");
        }

        public void WriteHalt(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\thalted = true;");
        }

        public void WriteRst(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tStackPush(PC);");
            writer.WriteLine("\tPC = {0};", string.IsNullOrEmpty(opcode.FirstOperand) ? "0x00" : opcode.FirstOperand);
        }

        #endregion
    }
}
