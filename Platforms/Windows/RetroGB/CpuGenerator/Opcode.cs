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
