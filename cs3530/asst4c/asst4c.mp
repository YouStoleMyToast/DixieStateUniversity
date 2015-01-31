%%% asst4c.mp -- do not edit, generated automatically by asst4c.tex
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
x := a/2;
y := 2cm;
k := 3.5cm;
node.q0("q0"); q0.c = origin;
node.q1("q1"); q1.c = q0.c + (a,0);
node.q2("q2"); q2.c = q0.c + (b,0);

node.q3("q3"); q3.c = q0.c + (c,x);
node.q4("q4"); q4.c = q0.c + (d,x);

node.q6("q6"); q6.c = q0.c + (c,-x);
node.q7("q7"); q7.c = q0.c + (d,-x);

node.q10("q10"); q10.c = q0.c + (e,0);

smallnodes; node.q100(); q100.c = q0.c + (b,y); bignodes;
smallnodes; node.q300(); q300.c = q0.c + (d,a); bignodes;
smallnodes; node.q600(); q600.c = q0.c + (c,-a); bignodes;

makestart(q1);
makefinal(q10);

drawboxed(q1,q2,q3,q4,q6,q7,q10,q100,q300,q600);


edge(q1,q2,right,btex $(\varepsilon,\varepsilon)\rightarrow \$ $ etex);
edge(q2,q100,40,btex $(a,\varepsilon)\rightarrow a $ etex);
edge(q100,q2,40,btex $(a,\varepsilon)\rightarrow \varepsilon $ etex);

edge(q2,q3,right,btex $(\varepsilon,\varepsilon)\rightarrow \varepsilon $ etex);
edge(q3,q4,right,btex $(a,\varepsilon)\rightarrow \varepsilon $ etex);
loop(q2,down,btex $(a,\varepsilon)\rightarrow a $ etex);

loop(q3,up,btex $(a,\varepsilon)\rightarrow \varepsilon $ etex);
loop(q4,down,btex $(b,a) \rightarrow \varepsilon $ etex);
edge(q4,q300,40,btex $(b,a)\rightarrow \varepsilon $ etex);
edge(q300,q4,40,btex $(b,\varepsilon)\rightarrow \varepsilon $ etex);

edge(q2,q6,left,btex $(\varepsilon,\varepsilon)\rightarrow \varepsilon $ etex);
edge(q6,q7,right,btex $(b,\varepsilon)\rightarrow \varepsilon $ etex);

loop(q6,up,btex $\hspace*{1cm}(b,a) \rightarrow \varepsilon $ etex);
loop(q7,down,btex $(b,\varepsilon) \rightarrow \varepsilon $ etex);

edge(q6,q600,-40,btex $(b,a)\rightarrow \varepsilon $ etex);
edge(q600,q6,-40,btex $(b,\varepsilon)\rightarrow \varepsilon $ etex);

edge(q4,q10,left,btex $(\varepsilon,\$)\rightarrow \$ $ etex);
edge(q7,q10,right,btex $(\varepsilon,\$)\rightarrow \$ $ etex);

endfig;
beginfig(2);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 3cm;
b := a*2;
x := 1.5cm;
node.q0("q0"); q0.c = origin;
node.q1("q1"); q1.c = q0.c + (a,0);
node.q2("q2"); q2.c = q0.c + (b,x);
node.q3("q3"); q3.c = q0.c + (b,-x);
node.q4("q4"); q4.c = q0.c + (a,-a-x);
node.q5("q5"); q5.c = q0.c + (0,-a-x);


makestart(q0);
makefinal(q5);

drawboxed(q0,q1,q2,q3,q4,q5);

edge(q0,q1,right,btex $(\varepsilon,\varepsilon)\rightarrow \$ $ etex);
edge(q1,q2,left,btex $(a,\varepsilon)\rightarrow a $ etex);
edge(q2,q3,left,btex $(a,\varepsilon)\rightarrow a $ etex);
edge(q3,q1,left,btex $(a,\varepsilon)\rightarrow a $ etex);
edge(q1,q4,right,btex $(\varepsilon,\varepsilon)\rightarrow \varepsilon $ etex);
edge(q4,q5,right,btex $(\varepsilon,\$)\rightarrow \varepsilon $ etex);

loop(q4,right,btex $(b,a)\rightarrow \varepsilon $ etex);

endfig;
verbatimtex
\end{document}
etex;
%%% the end.
end.
endinput;
