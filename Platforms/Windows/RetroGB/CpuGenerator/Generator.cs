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
            writer.WriteLine("void Processor::{0}()", opcode.ToFunctionName());
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
                default:
                    writer.WriteLine("\t// Not implemented yet");
                    writer.WriteLine("\tUnknownOpcode();");
                    break;
            }
        }

        private string GetStoreStub(string operand)
        {
            switch (operand)
            {
                case "(0xFF00+n)":
                    return "memory->WriteWord(static_cast<uint16>(0xFF00 + memory->ReadWord(PC++)), {0});";
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
            writer.WriteLine("\t{0}++;", opcode.FirstOperand);
            writer.WriteLine("\t//TODO flags");
        }

        public void WriteIncWord(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\t{0}++;", opcode.FirstOperand);
        }

        public void WriteDecByte(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\t{0}--;", opcode.FirstOperand);
            writer.WriteLine("\t//TODO flags");
        }

        public void WriteDecWord(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\t{0}--;", opcode.FirstOperand);
        }
        #endregion

        public void WriteOr(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tA |= {0};", GetLoadStub(opcode.FirstOperand));
            writer.WriteLine("\t//TODO flags");
        }

        public void WriteXor(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tA ^= {0};", GetLoadStub(opcode.FirstOperand));
            writer.WriteLine("\t//TODO flags");
        }

        public void WriteAdd(TextWriter writer, Opcode opcode)
        {
            string operand = !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.SecondOperand : opcode.FirstOperand;
            writer.WriteLine("\tA += {0};", GetLoadStub(operand));
            writer.WriteLine("\t//TODO flags");
        }

        public void WriteAdc(TextWriter writer, Opcode opcode)
        {
            string operand = !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.SecondOperand : opcode.FirstOperand;
            writer.WriteLine("\tuint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;");
            writer.WriteLine("\tA += ({0} + carry);", GetLoadStub(operand));
            writer.WriteLine("\t//TODO flags");
        }

        public void WriteSub(TextWriter writer, Opcode opcode)
        {
            string operand = !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.SecondOperand : opcode.FirstOperand;
            writer.WriteLine("\tA -= {0};", GetLoadStub(operand));
            writer.WriteLine("\t//TODO flags");
        }

        public void WriteSbc(TextWriter writer, Opcode opcode)
        {
            string operand = !string.IsNullOrEmpty(opcode.SecondOperand) ? opcode.SecondOperand : opcode.FirstOperand;
            writer.WriteLine("\tuint8 carry = IsFlagSet(FLAG_CARRY) ? 1 : 0;");
            writer.WriteLine("\tA -= ({0} + carry);", GetLoadStub(operand));
            writer.WriteLine("\t//TODO flags");
        }

        public void WriteAnd(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\tA &= {0};", GetLoadStub(opcode.FirstOperand));
            writer.WriteLine("\t//TODO flags");
        }

        public void WriteDAA(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("\t//Not implememented yet");
        }
        
        #endregion
    }
}
