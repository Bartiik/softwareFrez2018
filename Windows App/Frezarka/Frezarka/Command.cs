using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace Frezarka
{
    public class Command
    {
        double[] values;
        String chars;
        public Command()
        {
            ParentFile = "";
            values = new double[10];
            chars = "GXYZIJMSFU";
            for (int i = 0; i < values.Length; i++)
                values[i] = 1234.56789;
        }
        public bool Fill(String code)
        {
            bool test = true;
            code.Replace(" ", String.Empty);
            code = code.ToUpper();
            var myRegex = new Regex(@"[A-Z][-]{0,1}\d{0,}[\.\,]{0,1}\d{0,}");
            List<String> lines = myRegex.Matches(code).Cast<Match>().Select(m => m.Value).ToList();
            foreach ( String line in lines)
            {
                char c = line[0];
                int value;
                if(Int32.TryParse(line.Substring(1), out value) && chars.Contains(c))
                {
                    values[chars.IndexOf(c)] = value;
                }
                else test = false;
            }
            return test;
        }
        public double returnValue(char c)
        {
            return values[chars.IndexOf(c)];
        }
        public String ParentFile { get; set; }
        public override String ToString()
        {
            StringBuilder value = new StringBuilder();
            for(int i = 0; i<values.Length;i++)
            {
                if (values[i] != 1234.56789)
                {
                    value.Append(chars[i]);
                    value.Append(values[i]);
                    value.Append(" ");
                }
            }
            return value.ToString();
        }
        public String ToSend()
        {
            StringBuilder value = new StringBuilder();
            for (int i = 0; i < values.Length; i++)
            {
                if (values[i] != 1234.56789)
                {
                    value.Append(chars[i]);
                    value.Append(values[i]);
                }
            }
            return value.ToString();
        }

    }
}
