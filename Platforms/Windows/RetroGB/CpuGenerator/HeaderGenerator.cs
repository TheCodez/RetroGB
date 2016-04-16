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

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

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
