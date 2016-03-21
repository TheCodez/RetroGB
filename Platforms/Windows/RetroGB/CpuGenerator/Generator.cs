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

            if (operation != "NOP")
            {
                if (operation == "LD")
                {
                    if (firstOperand != secondOperand)
                    {
                        string first = GetStoreStub(firstOperand);
                        string second = GetLoadStub(secondOperand);

                        writer.WriteLine("\t" + string.Format(first, second));
                    }
                }
                else
                {
                    writer.WriteLine("\t// Not implemented yet");
                    writer.WriteLine("\tUnknownOpcode();");
                }
            }
        }

        private string GetStoreStub(string operand)
        {
            switch (operand)
            {
                case "(0xFF00+n)":
                    return "memory->WriteByte(0xFF00 + memory->ReadWord(PC++), {0});";
                case "(0xFF00+C)":
                    return "memory->WriteByte(0xFF00 + C, {0});";
                case "(nn)":
                    return "memory->WriteByte(memory->ReadWord(PC++), {0});";
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
                    break;
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
                    break;
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
        
        public void GenerateDAAMethod(TextWriter writer)
        {
            writer.WriteLine("\t//Not implememented yet");
        }
#endregion
    }
}
