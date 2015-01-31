%%% asst3a.mp -- do not edit, generated automatically by asst3a.tex
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
a := 2cm;
b := a*2;
c := a*3;
d := a*4;
e := a*5;
node.q0(); q0.c = origin;
node.q1(); q1.c = q0.c + (a,0);
node.q2(); q2.c = q0.c + (b,0);
node.q3(); q3.c = q0.c + (c,0);
node.q4(); q4.c = q0.c + (d,0);
node.q5(); q5.c = q0.c + (e,0);


makestart(q0);
makefinal(q0); makefinal(q5);
drawboxed(q0,q1,q2,q3,q4);

edge(q0,q1,curve,"[0 1]");
edge(q1,q2,curve,"[0 0]");
edge(q2,q1,curve,"[1 0]");
edge(q1,q0,curve,"[1 1]");

edge(q2,q3,right,"[1 1]");
edge(q3,q4,right,"[1 0]");
edge(q4,q5,right,"[1 1]");

loop(q0,up,"[0 0]");
loop(q5,up,"[0 0]");

endfig;
verbatimtex
\end{document}
etex;
%%% the end.
end.
endinput;
