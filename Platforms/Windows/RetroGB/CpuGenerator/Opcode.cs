using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CpuGenerator
{
    class Opcode
    {
        public string Operation { get; set; }
        public string FirstOperand { get; set; }
        public string SecondOperand { get; set; }

        public int NumberOfOperands { get; set; }

        public Opcode()
        {
            Operation = string.Empty;
            FirstOperand = string.Empty;
            SecondOperand = string.Empty;
        }

        public override string ToString()
        {
            string ret = Operation;

            if (FirstOperand != string.Empty)
            {
                ret += "_" + FirstOperand;

                if (SecondOperand != string.Empty)
                {
                    ret += "_" + SecondOperand;
                }
            }

            return ret;
        }

        public string ToFunctionName()
        {
            string ret = Operation;

            if (FirstOperand != string.Empty)
            {
                ret += "_" + FirstOperand.Replace("(", "MEM_").Replace(")", "").Replace("+", "_");

                if (SecondOperand != string.Empty)
                {
                    ret += "_" + SecondOperand.Replace("(", "MEM_").Replace(")", "").Replace("+", "_");
                }
            }

            return ret;
        }
    }
}
