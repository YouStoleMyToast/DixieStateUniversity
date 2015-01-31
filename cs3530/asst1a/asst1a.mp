%%% asst1a.mp -- do not edit, generated automatically by asst1a.tex
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
node.q0(); q0.c = origin;
node.q1(); q1.c = q0.c + (a,0);
node.q2(); q2.c = q0.c + (b,0);
node.q3(); q3.c = q0.c + (c,0);

makestart(q0);
makefinal(q3);

drawboxed(q0,q1,q2,q3);

edge(q0,q1,right,"1");
edge(q1,q2,right,"1");
edge(q2,q3,right,"1");


loop(q0,down,"0");
loop(q1,down,"0");
loop(q2,down,"0");
loop(q3,down,"0,1");

endfig;
beginfig(2);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 2cm;
b := a*2;
c := a*3;
d := a*4;
node.q0(); q0.c = origin;
node.q1(); q1.c = q0.c + (a,0);
node.q2(); q2.c = q0.c + (b,0);
node.q3(); q3.c = q0.c + (c,0);
node.q4(); q4.c = q0.c + (d,0);

makestart(q0);
makefinal(q4);

drawboxed(q0,q1,q2,q3,q4);

edge(q0,q1,right,"0");
edge(q1,q2,right,"1");
edge(q2,q3,right,"0");
edge(q3,q4,right,"1");

edge(q2,q0,-curve,"1");
edge(q3,q1,-curve,"0");

loop(q0,down,"1");
loop(q1,down,"0");
loop(q4,down,"0,1");

endfig;
beginfig(3);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 2cm;
b := a/2;
node.q0(); q0.c = origin;
node.q1(); q1.c = q0.c + (a,b);
node.q2(); q2.c = q0.c + (a,-b);

makestart(q0);
makefinal(q1);
drawboxed(q0,q1,q2);

edge(q0,q1,right,"0");
edge(q0,q2,right,"1");
edge(q1,q2,right,"0,1");
edge(q2,q1,right,"");

endfig;
beginfig(4);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 2cm;
b := a*2;
c := a*3;
d := a*4;
node.q0(); q0.c = origin;
node.q1(); q1.c = q0.c + (a,0);
node.q2(); q2.c = q0.c + (b,0);
node.q3(); q3.c = q0.c + (c,0);

makestart(q0);
makefinal(q0);makefinal(q1);makefinal(q2);

drawboxed(q0,q1,q2,q3);

edge(q0,q1,curve,"1");
edge(q1,q0,curve,"0");
edge(q1,q2,right,"1");
edge(q2,q3,right,"0");


loop(q0,down,"0");
loop(q2,down,"1");
loop(q3,down,"0,1");

endfig;
beginfig(5);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 2cm;

node.q0(); q0.c = origin;
node.q1(); q1.c = q0.c + (a,0);
node.q2(); q2.c = q0.c + (a,-a);

makestart(q0);
makefinal(q1);

edge(q0,q1,right,EMPTYSET);
edge(q0,q2,right,SIGMA);

drawboxed(q0,q1,q2);



endfig;
verbatimtex
\end{document}
etex;
%%% the end.
end.
endinput;
