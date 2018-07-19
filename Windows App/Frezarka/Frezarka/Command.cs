using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace Frezarka
{
    public class Command
    {
        public bool isAbsolute { get; private set; }
        double[] values;
        String chars;
        public Command()
        {
            values = new double[13];
            chars = "GXYZIJMFSUEWP";
            for (int i = 0; i < values.Length; i++)
                values[i] = 1234.56789;
        }
        public bool Fill(String code, bool abs)
        {
            isAbsolute = abs;
            bool test = true;
            code = code.Replace(" ", String.Empty);
            code = code.Replace(".", ",");
            code = code.ToUpper();
            var myRegex = new Regex(@"[A-Z][-]{0,1}\d{0,}[\.\,]{0,1}\d{0,}");
            List<String> lines = myRegex.Matches(code).Cast<Match>().Select(m => m.Value).ToList();
            foreach ( String line in lines)
            {
                char c = line[0];
                float value;
                if(float.TryParse(line.Substring(1), out value) && chars.Contains(c))
                {
                    values[chars.IndexOf(c)] = value;
                    if (c == 'P')
                        values[chars.IndexOf(c)] = (value * 1000);
                    values[chars.IndexOf(c)] = Math.Round(values[chars.IndexOf(c)], 6);
                }
                else test = false;
            }
            return test;
        }
        public double returnValue(char c)
        {
            return values[chars.IndexOf(c)];
        }
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
                if (values[chars.IndexOf('F')] != 1234.56789 || values[0] == 94)
                    return "U5";
                else if (values[i] != 1234.56789)
                {
                    value.Append(chars[i]);
                    value.Append(values[i]);
                }
            }
            return value.ToString();
        }
    }
}