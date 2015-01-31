%%% asst4cPDAs.mp -- do not edit, generated automatically by asst4cPDAs.tex
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

node.q0("q0"); q0.c = origin;
node.q1("q1"); q1.c = q0.c + (a,0);
node.q2("q2"); q2.c = q0.c + (b,0);
node.q3("q3"); q3.c = q0.c + (c,0);

smallnodes;
node.q4(); q4.c = q0.c + (a,a/2);
bignodes;

makestart(q0);
makefinal(q3)

drawboxed(q0,q1,q2,q3,q4);

edge(q0,q1,right,btex $(\varepsilon,\varepsilon)\rightarrow \$ $ etex);
edge(q1,q2,right,btex $(\varepsilon,\varepsilon)\rightarrow \varepsilon $ etex);
edge(q2,q3,right,btex $(\varepsilon,\$)\rightarrow \varepsilon $ etex);

edge(q1,q4,60,btex $(a,\varepsilon)\rightarrow a $ etex);
edge(q4,q1,60,btex $(a,\varepsilon)\rightarrow a $ etex);

loop(q2,up,btex $(b,a)\rightarrow \varepsilon $ etex);

endfig;
beginfig(2);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 3cm;
b := a*2;
c := a*3;
d := a*4;

node.q0("q0"); q0.c = origin;
node.q1("q1"); q1.c = q0.c + (a,0);
node.q2("q2"); q2.c = q0.c + (b,0);
node.q3("q3"); q3.c = q0.c + (c,0);


makestart(q0);
makefinal(q3)

drawboxed(q0,q1,q2,q3);

edge(q0,q1,right,btex $(\varepsilon,\varepsilon)\rightarrow \$ $ etex);
edge(q1,q2,right,btex $(\varepsilon,\varepsilon)\rightarrow \varepsilon $ etex);
edge(q2,q3,right,btex $(\varepsilon,\$)\rightarrow \varepsilon $ etex);

loop(q1,up,btex $(a,\varepsilon)\rightarrow a $ etex);
loop(q2,up,btex $(b,a)\rightarrow \varepsilon $ etex);

endfig;
beginfig(3);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 3cm;
b := a*2;
c := a*3;
d := a*4;
e := a*5;
f := a*6;

node.q0("q0"); q0.c = origin;
node.q1("q1"); q1.c = q0.c + (a,0);
node.q2("q2"); q2.c = q0.c + (b,0);
node.q3("q3"); q3.c = q0.c + (c,0);
smallnodes; node.q4(); q4.c = q0.c + (a,a/2); bignodes;

node.q5("q5"); q5.c = q0.c + (b,-a);
node.q6("q6"); q6.c = q0.c + (c,-a);
node.q7("q7"); q7.c = q0.c + (d,-a);
node.q8("q8"); q8.c = q0.c + (e,-a);

makestart(q0); makefinal(q8)

drawboxed(q0,q1,q2,q3,q4,q5,q6,q7,q8);

edge(q0,q1,right,btex $(\varepsilon,\varepsilon)\rightarrow \$ $ etex);
edge(q1,q2,right,btex $(\varepsilon,\varepsilon)\rightarrow \varepsilon $ etex);
edge(q2,q3,right,btex $(\varepsilon,\$)\rightarrow \varepsilon $ etex);

edge(q1,q4,60,btex $(a,\varepsilon)\rightarrow a $ etex);
edge(q4,q1,60,btex $(a,\varepsilon)\rightarrow a $ etex);

loop(q2,up,btex $(b,a)\rightarrow \varepsilon $ etex);


edge(q3,q5,right,btex $(\varepsilon,\varepsilon)\rightarrow \varepsilon $ etex);


edge(q5,q6,right,btex $(\varepsilon,\varepsilon)\rightarrow \$ $ etex);
edge(q6,q7,right,btex $(\varepsilon,\varepsilon)\rightarrow \varepsilon $ etex);
edge(q7,q8,right,btex $(\varepsilon,\$)\rightarrow \varepsilon $ etex);

loop(q6,up,btex $(a,\varepsilon)\rightarrow a $ etex);
loop(q7,up,btex $(b,a)\rightarrow \varepsilon $ etex);

endfig;
verbatimtex
\end{document}
etex;
%%% the end.
end.
endinput;
