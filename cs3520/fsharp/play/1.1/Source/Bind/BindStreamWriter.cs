﻿#region License
//
// The Open Toolkit Library License
//
// Copyright (c) 2006 - 2013 Stefanos Apostolopoulos for the Open Toolkit Library
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights to 
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//


#endregion

using System;
using System.IO;
using System.Text.RegularExpressions;
using Bind.Structures;
using Enum=Bind.Structures.Enum;

namespace Bind
{
    class BindStreamWriter : StreamWriter
    {
        int indent_level = 0;
        Regex splitLines = new Regex(Environment.NewLine, RegexOptions.Compiled);
        //Regex splitLines = new Regex("(\r\n|\n\r|\n|\r)", RegexOptions.Compiled);

        public readonly string File;

        public BindStreamWriter(string file)
            : base(file)
        {
            File = file;
        }

        public void Indent()
        {
            ++indent_level;
        }

        public void Unindent()
        {
            if (indent_level > 0)
                --indent_level;
        }

        public override void Write(string value)
        {
            var lines = splitLines.Split(value);
            bool is_multiline = lines.Length > 1;
            if (is_multiline)
            {
                // Write all internal lines
                for (int i = 0; i < lines.Length - 1; i++)
                {
                    var line = lines[i];
                    WriteIndentations();
                    base.Write(line);
                    base.Write(System.Environment.NewLine);
                }
                // Write the last line without appending a newline
                WriteIndentations();
                base.Write(lines[lines.Length - 1]);
            }
            else
            {
                WriteIndentations();
                base.Write(value);
            }
        }

        public override void WriteLine(string value)
        {
            // The Mono implementation of WriteLine calls Write internally.
            // The .Net implementation does not.
            // If running on Mono, we must avoid indenting in WriteLine
            // because then we'll indent twice (once in WriteLine and once in Write).
            // If running on .Net we must indent in both WriteLine and Write.
            // Neat, no?
            if (System.Type.GetType("Mono.Runtime") == null)
            {
                WriteIndentations();
            }
            base.WriteLine(value);
        }

        void WriteIndentations()
        {
            for (int i = indent_level; i > 0; i--)
                base.Write("    ");
        }
    }
}
