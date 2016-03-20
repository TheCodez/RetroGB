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

            writer.WriteLine("\t// Not implemented yet");
            writer.WriteLine("\tUnknownOpcode();");
        }

        public void MapOpcodes(TextWriter writer, int op, string line)
        {
            Opcode opcode;
            ParseOpcode(line, out opcode);

            var funcName = opcode.ToFunctionName();

            writer.WriteLine("\topcodes[0x{0:X2}] = std::bind(&Processor::{1}, this);", op, funcName);
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
