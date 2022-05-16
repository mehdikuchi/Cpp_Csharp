using System;
using System.Linq;
/*
namespace delegatesample
{
    class Program
{
    static void Main(string[] args)
    {        
        Console.WriteLine("Hello World!");
    }
}
}
*/
Console.WriteLine("Hello World!");
Mehdi.Model M = new Mehdi.Model();
var v1 = new Mehdi.View1(ref M);
var v2 = new Mehdi.View2(ref M);
M.Change();

/*a = new Mehdi.test();
a.Data = 3;
a.changesth(5);*/
// Declaration only:
/*float temperature;
string name;
MyClass myClass;*/

// Declaration with initializers (four examples):
char firstLetter = 'C';
var limit = 3;
int[] source = { 0, 1, 2, 3, 4, 5 };
var query = from item in source
            where item <= limit
            select item;
foreach (var qu in query) {
    System.Console.WriteLine(qu);
}


query.Where(a=> { System.Console.WriteLine(limit);return true; });

