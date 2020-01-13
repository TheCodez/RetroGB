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

using Newtonsoft.Json;
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
            StreamReader opReader = new StreamReader("opcodes.json");
            List<Opcode> opCodes = JsonConvert.DeserializeObject<List<Opcode>>(opReader.ReadToEnd());

            StreamReader cbReader = new StreamReader("opcodesCB.json");
            List<Opcode> opCodesCB = JsonConvert.DeserializeObject<List<Opcode>>(cbReader.ReadToEnd());

            // Should already be sorted
            opCodes.Sort((x, y) => x.Address.CompareTo(y.Address));
            opCodesCB.Sort((x, y) => x.Address.CompareTo(y.Address));

            foreach (Opcode opcode in opCodes)
            {
                string operation = opcode.Operation;

                if (operation != "UNDEFINED")
                {
                    GenerateMethod(writer, opcode);
                }
            }

            writer.WriteLine();
            writer.WriteLine("// CB Obcodes");

            foreach (Opcode opcode in opCodesCB)
            {
                GenerateMethod(writer, opcode);
            }

            opReader.Close();
            cbReader.Close();
        }

        public void GenerateMethod(TextWriter writer, Opcode opcode)
        {
            writer.WriteLine("unsigned int {0}();", opcode.ToFunctionName());
        }
    }
}
