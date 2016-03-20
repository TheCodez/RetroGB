using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CpuGenerator
{
    class Program
    {
        static void Main(string[] args)
        {
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

            File.Copy("Processor.Generated.cpp", @"..\..\..\..\..\..\RetroGB\Processor.Generated.cpp", true);
        }
    }
}
