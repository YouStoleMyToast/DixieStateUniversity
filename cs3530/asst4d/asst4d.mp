%%% asst4d.mp -- do not edit, generated automatically by asst4d.tex
verbatimtex
\documentclass [10pt]{article}
\usepackage {amsmath}
\begin {document}
etex;
input boxes; input theory;
beginfig(1);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 3cm;
b := a*2;
c := a*3;
d := a*4;
e := a*5;
f := a*6;
t := 2.5cm;
u := t*2;
v := t*3;
w := t*4;
x := t*5;
y := t*6;
node.q0("q0"); q0.c = origin;
node.q1("q1"); q1.c = q0.c + (t,0);
node.q2("q2"); q2.c = q0.c + (u,0);
node.q3("q3"); q3.c = q0.c + (w,0);
node.q4("q4"); q4.c = q0.c + (y,0);
node.q5("q5"); q5.c = q0.c + (w+t,-t);

makestart(q0);
makefinal(q5);

whiteedges;
edge(q2,q3,35,btex $(1,0)\rightarrow \varepsilon $ etex);
edge(q3,q2,35,btex $(1,0)\rightarrow \varepsilon $ etex);
edge(q3,q4,35,btex $(1,0)\rightarrow \varepsilon $ etex);
edge(q4,q3,35,btex $(1,0)\rightarrow \varepsilon $ etex);

blackedges;

loopsizeextralarge; whiteedges;
loop(q1,up,btex $(1,\varepsilon)\rightarrow 1 $ etex);
loop(q2,up,btex $(1,1)\rightarrow \varepsilon $ etex);
loop(q3,up,btex $(1,1)\rightarrow \varepsilon $ etex);
loop(q4,up,btex $(1,1)\rightarrow \varepsilon $ etex);
bignodes; blackedges; loopsizebig;

loop(q1,up,btex $(0,\varepsilon)\rightarrow 0 $ etex);
loop(q2,up,btex $(0,0)\rightarrow \varepsilon $ etex);
loop(q3,up,btex $(0,0)\rightarrow \varepsilon $ etex);
loop(q4,up,btex $(0,0)\rightarrow \varepsilon $ etex);


edge(q0,q1,left,btex $(\varepsilon,\varepsilon)\rightarrow \$ $ etex);
edge(q1,q2,left,btex $(\varepsilon,\varepsilon)\rightarrow \varepsilon $ etex);

edge(q2,q3,20,btex $(0,1)\rightarrow \varepsilon $ etex);
edge(q3,q2,20,btex $(0,1)\rightarrow \varepsilon $ etex);
edge(q3,q4,20,btex $(0,1)\rightarrow \varepsilon $ etex);
edge(q4,q3,20,btex $(0,1)\rightarrow \varepsilon $ etex);

edge(q3,q5,right,btex $(\varepsilon,\$)\rightarrow \varepsilon $ etex);
edge(q4,q5,left,btex $(\varepsilon,\$)\rightarrow \varepsilon $ etex);

drawboxed(q0,q1,q2,q3,q4,q5);

endfig;
verbatimtex
\end{document}
etex;
%%% the end.
end.
endinput;
