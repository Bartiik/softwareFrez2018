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
        int[] valuesToSend;
        int _Z;
        int _XY;
        public Command(int StepsPerValXY, int StepsPerValZ)
        {
            _XY = StepsPerValXY;
            _Z = StepsPerValZ;
            valuesToSend = new int[13];
            values = new double[13];
            chars = "GXYZIJMSFUEWP";
            for (int i = 0; i < values.Length; i++)
                values[i] = 1234.56789;
        }
        public bool Fill(String code)
        {
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
                    if("XYIJ".Contains(c))
                        valuesToSend[chars.IndexOf(c)] = (int)(value * _XY);
                    else if(c == 'Z')
                        valuesToSend[chars.IndexOf(c)] = (int)(value * _Z);
                    else if(c== 'P')
                        valuesToSend[chars.IndexOf(c)] = (int)(value * 1000);
                    else valuesToSend[chars.IndexOf(c)] = (int)(value);
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
                    value.Append(valuesToSend[i]);
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
                    value.Append(valuesToSend[i]);
                }
            }
            return value.ToString();
        }
    }
}
