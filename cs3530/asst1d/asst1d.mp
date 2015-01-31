%%% asst1d.mp -- do not edit, generated automatically by asst1d.tex
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
c := a*3;
d := a*4;
node.q0("0"); q0.c = origin;
node.q1("1"); q1.c = q0.c + (a,0);
node.q2("2"); q2.c = q0.c + (b,0);
node.q3("3"); q3.c = q0.c + (c,0);
node.q4("4"); q4.c = q0.c + (d,0);


makestart(q0);
makefinal(q4);

drawboxed(q0,q1,q2,q3,q4);

loop(q0,up,"a,b");
edge(q0,q1,right,A);

edge(q1,q2,curve,A);
edge(q1,q2,-curve,B);
edge(q2,q3,curve,A);
edge(q2,q3,-curve,B);
edge(q3,q4,curve,A);
edge(q3,q4,-curve,B);

edge(q4,q0,-curve,B);
edge(q4,q1,curve,A);

endfig;
beginfig(2);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 2cm;
b := a*2;
c := a*3;
d := a*4;
node.q0("0"); q0.c = origin;
node.q1("1"); q1.c = q0.c + (a,0);
node.q2("2"); q2.c = q0.c + (b,0);
node.q3("3"); q3.c = q0.c + (c,0);
node.q4("4"); q4.c = q0.c + (d,0);


makestart(q0);
makefinal(q1);makefinal(q2);makefinal(q3);makefinal(q4);

drawboxed(q0,q1,q2,q3,q4);

loop(q0,up,B);
edge(q0,q1,right,A);

edge(q1,q2,curve,A);
edge(q1,q2,-curve,B);
edge(q2,q3,curve,A);
edge(q2,q3,-curve,B);
edge(q3,q4,curve,A);
edge(q3,q4,-curve,B);

loop(q4,up,A);
edge(q4,q0,-curve,B);

endfig;
verbatimtex
\end{document}
etex;
%%% the end.
end.
endinput;
