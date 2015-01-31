// Learn more about F# at http://fsharp.net
// See the 'F# Tutorial' project for more help.

open System
open System.Drawing
open System.Threading
open System.Windows.Forms
(*
type Tree =
| Leaf of char*int // = (char, int)
| Branch of Tree*Tree*char list*int // (Tree, Tree, char list, int)

static member Weigh =
let rec f tree =
match tree with
| Leaf(_, w) -> w
| Branch(l,r,_,_) -> f l + f r
f

static member MakeLeaves =
let rec f acc cs =
match cs with
| [] -> acc
| c::cs -> f (Leaf(c,1)::acc) cs
f []

static member CombineLeaves (leaves: Tree list) =
let rec f (m: Map<char, int>) ls =
match ls with
| [] -> m
| Leaf(c,x)::ls ->
if m.ContainsKey(c)
then f (m.Add(c, m.[c]+x)) ls
else f (m.Add(c, x)) ls
let m = f (Map<char,int>([]) ) leaves
let ls = Set.toList (set leaves)
let rec g acc ls =
match ls with
| [] -> acc
| Leaf(c,_)::ls -> g (Leaf(c, m.[c])::acc) ls
g [] ls

let screenWidth = 800
let screenHeight = 600

let mainButton = new Button(
Top = 150,
Left = 150,
Width = 50,
Height = 50,
BackColor = Color.CornflowerBlue,
ForeColor = Color.Black,
Text = "F#"

)

let mainForm = new Form(
Width = screenWidth,
Height = screenHeight
)
mainForm.Controls.Add(mainButton)
*)
let Calculation x =
    sqrt (pown x 2)

let dones = 0

let CalcPart (array: float[]) start stop id =
    printfn "%A starting" id
    let rec f (i: int) =
        match i < stop with
            | false -> true
            | true -> (array.SetValue(value=Calculation (float i), index=i)=()) && f (i+1)
    f start |> ignore
    dones = dones + 1 |> ignore
    printfn "%A done" id

let CalcAsync array start stop id = async {
    do CalcPart array start stop id
}
        

let Split (array: float[]) n = async {
    let inc = array.Length / n
    let clamp v =
        match v < array.Length with
            | true -> v
            | false -> array.Length
    
    let rec f acc i =
        match i < n with
            | false -> acc
            | true -> f (Async.StartAsTask(CalcAsync array (inc*i) (clamp(inc*(i+1))) i)::acc) (i+1)
    let rec g (ls: Tasks.Task<unit> list) =
        match ls with
            | [] -> true
            | l::ls -> l.Wait() |> ignore = () && g ls
    let childs = f [] 0

    g childs |> ignore


    (*for i in 0..n do
let start = i * inc
let tmp = inc * (i+1)
let stop =
match tmp < array.Length with
| true -> tmp
| false -> array.Length
let child = Async.StartAsTask(CalcAsync array start stop i)
()*)
}
        
        
[<EntryPoint>]
let main argv =
    (*let ti = DateTime.Now
let rec getChars acc i max =
match i < max with
| false -> acc
| true -> getChars ('a'::acc) (i+1) max
let leaves = Tree.CombineLeaves (Tree.MakeLeaves [ 'a'; 'a'; 'a';'b'; 'b';'c';'d';'e'; 'e'; 'e'; 'f';'f';'f';'f';'g';'g';'z';'z'])
let tf = DateTime.Now
let dt = (tf - ti).TotalMilliseconds*)

    let f (n: float) =
        sqrt (pown n 2)
    let n = 100000000
    let m = Array.zeroCreate 1

    //let bigArray: float[] = Array.zeroCreate 100000000
    let ti = DateTime.Now
    //let task = Async.StartAsTask(Split bigArray 4)
    //task.Wait()

    for i in 0..n do
        m.SetValue(
            value = f(float i),
            index = 0) |> ignore

    let tf = DateTime.Now
    let dt = (tf - ti).TotalMilliseconds

    printfn "%A" m
    printfn "%A" dt

    //printfn "%A" leaves |> ignore
    //printfn "%A" dt
    0 // return an integer exit code