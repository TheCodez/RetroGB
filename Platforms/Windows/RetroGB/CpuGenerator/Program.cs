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
    class Program
    {
        static void Main(string[] args)
        {
            GenerateJson.Generate("opcodes.json", Properties.Resources.Opcodes);
            GenerateJson.Generate("opcodesCB.json", Properties.Resources.OpcodesCB, true);

            using (var Output = new StreamWriter("Processor.Generated.cpp"))
            {
                var generator = new Generator();
                generator.Generate(Output);
            }

            using (var Output = new StreamWriter("Processor.Generated.h"))
            {
                var generator = new HeaderGenerator();
                generator.Generate(Output);
            }

            using (var Output = new StreamWriter("OpcodeNames.h"))
            {
                var generator = new OpcodesNamesGenerator();
                generator.Generate(Output);
            }

            File.Copy("Processor.Generated.cpp", @"..\..\..\..\..\..\RetroGB\Processor.Generated.cpp", true);
            File.Copy("OpcodeNames.h", @"..\..\..\..\..\..\RetroGB\OpcodeNames.h", true);
        }
    }
}
