using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CpuGenerator
{
    class HeaderGenerator
    {
        public void Generate(TextWriter writer)
        {
            List<string> opcodes = Properties.Resources.Opcodes.Split(new[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries).ToList();
            List<string> opcodesCB = Properties.Resources.OpcodesCB.Split(new[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries).ToList();

            if (opcodes.Count != 256 && opcodesCB.Count != 256)
                return;

            for (int i = 0; i < 256; i++)
            {
                string line = opcodes.ElementAt(i);

                if ((line != "UNDEFINED") && (line != "CB_OPCODE"))
                    GenerateMethod(writer, i, line);
            }

            writer.WriteLine();
            writer.WriteLine("// CB Obcodes");

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

            writer.WriteLine("void {0}();", opcode.ToFunctionName());
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
    }
}
