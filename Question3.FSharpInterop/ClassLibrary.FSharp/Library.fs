//Проект ClassLibrary.FSharp файл Library.fs
namespace ClassLibrary.FSharp

open System

//За счет модификатора доступа private нельзя создать тип в обход create
type public StringNumberType = private StringNumberType of string
    with 
        //Публичный метод для создания экземпляра с проверкой входных данных
        static member create (value: string) =
            let mutable parsedValue:int64 = 0
            if Int64.TryParse(value, &parsedValue) then
                Ok(StringNumberType value)
            else
                Error()
                
        static member create (value: int64) : Result<StringNumberType, unit>=
            Ok(StringNumberType (value.ToString()))
            
           