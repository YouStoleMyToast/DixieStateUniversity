%%% asst2a.mp -- do not edit, generated automatically by asst2a.tex
verbatimtex
\documentclass [10pt]{article}
\begin {document}
etex;
input boxes; input theory;
beginfig(1);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 2cm;
b := a*2;

node.q0(); q0.c = origin;
node.q1(); q1.c = q0.c + (a,0);
node.q2(); q2.c = q0.c + (0,-a);
node.q3(); q3.c = q0.c + (a,-a);
node.q4(); q4.c = q0.c + (b,-a);


makestart(q0);
makefinal(q2);makefinal(q4);
drawboxed(q0,q1,q2,q3,q4);

edge(q0,q1,right,A);
edge(q0,q2,curve,B);
edge(q2,q0,curve,B);
edge(q2,q3,right,A);
edge(q3,q1,right,B);
edge(q4,q1,right,B);
edge(q3,q4,curve,A);
edge(q4,q3,curve,A);

loop(q1,right,"a,b");


endfig;
verbatimtex
\end{document}
etex;
%%% the end.
end.
endinput;
