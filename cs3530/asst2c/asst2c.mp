%%% asst2c.mp -- do not edit, generated automatically by asst2c.tex
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
node.q2(); q2.c = q0.c + (b,0);


makestart(q0);
makefinal(q2);

drawboxed(q0,q1,q2);

edge(q0,q1,right,"1");
edge(q1,q2,right,"1");


loop(q0,down,"0");
loop(q1,down,"0");
loop(q2,down,"0,1");

endfig;
beginfig(2);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 2cm;
b := a*2;

node.q0(); q0.c = origin;
node.q1(); q1.c = q0.c + (a,0);
node.q2(); q2.c = q0.c + (b,0);


makestart(q0);
makefinal(q2);

drawboxed(q0,q1,q2);

edge(q0,q1,right,"1");
edge(q1,q2,right,"1");


loop(q2,down,"0");
loop(q1,down,"0");
loop(q0,down,"0,1");

endfig;
beginfig(3);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 2cm;
b := a*2;

node.q0("0"); q0.c = origin;
node.q1("1"); q1.c = q0.c + (a,0);
node.q2("n"); q2.c = q0.c + (b,0);


makestart(q0);
makefinal(q2);

drawboxed(q0,q1,q2);

edge(q0,q1,right,"1");
edge(q1,q2,right,"1");

edge(q0,q1,45, E );
edge(q1,q2,45, E );

loop(q0,down,"0");
loop(q1,down,"0");
loop(q2,down,"0,1");

endfig;
verbatimtex
\end{document}
etex;
%%% the end.
end.
endinput;
