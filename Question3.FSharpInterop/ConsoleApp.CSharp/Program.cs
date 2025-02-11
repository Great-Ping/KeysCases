//ConsoleApp.CSharp Program.cs
using ClassLibrary.FSharp;

var result = StringNumberType.create("12344");

if (result.IsOk)
    Console.WriteLine(result.ResultValue);
else
    Console.WriteLine(result.ErrorValue);

