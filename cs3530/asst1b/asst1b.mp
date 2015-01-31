%%% asst1b.mp -- do not edit, generated automatically by asst1b.tex
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
makefinal(q1); makefinal(q2);

drawboxed(q0,q1,q2,q3);

edge(q0,q1,right,"b");
edge(q1,q2,right,"b");
edge(q2,q3,right,"b");

loop(q3,right,"b");

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



makestart(q0);
makefinal(q0);

drawboxed(q0,q1);

edge(q0,q1,right,"a");
edge(q1,q0,right,"");



endfig;
beginfig(3);
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
node.q4(); q4.c = q0.c + (0,-a);
node.q5(); q5.c = q0.c + (a,-a);
node.q6(); q6.c = q0.c + (b,-a);
node.q7(); q7.c = q0.c + (c,-a);

makestart(q0);
makefinal(q1); makefinal(q2);

drawboxed(q0,q1,q2,q3,q4,q5,q6,q7);

edge(q0,q1,right,"b");
edge(q1,q2,right,"b");
edge(q2,q3,right,"b");

edge(q0,q4,right,"a");
edge(q1,q5,right,"a");
edge(q2,q6,right,"a");
edge(q3,q7,right,"a");
edge(q4,q0,right,"");
edge(q5,q1,right,"");
edge(q6,q2,right,"");
edge(q7,q3,right,"");

edge(q4,q5,right,"b");
edge(q5,q6,right,"b");
edge(q6,q7,right,"b");

loop(q3,right,"b");
loop(q7,right,"b");
endfig;
beginfig(4);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 2cm;
b := a/2;
c := a*2;
node.q0(); q0.c = origin;
node.q1(); q1.c = q0.c + (a,b);
node.q2(); q2.c = q0.c + (c,b);
node.q3(); q3.c = q0.c + (a,-b);
node.q4(); q4.c = q0.c + (c,-b);


makestart(q0);
makefinal(q0); makefinal(q1); makefinal(q3);
drawboxed(q0,q1,q2,q3,q4);

edge(q0,q1,right,"a");
edge(q1,q2,right,"b");
edge(q0,q3,right,"b");
edge(q3,q4,right,"a");

loop(q1,up,"a");
loop(q3,down,"b");
loop(q2,right,"a,b");
loop(q4,right,"a,b");

endfig;
beginfig(5);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 2cm;
b := a*2;
c := a*3;

node.q0(); q0.c = origin;
node.q1(); q1.c = q0.c + (a,0);
node.q2(); q2.c = q0.c + (b,0);
node.q3(); q3.c = q0.c + (0,-a);
node.q4(); q4.c = q0.c + (a,-a);
node.q5(); q5.c = q0.c + (b,-a);

makestart(q0);
makefinal(q0); makefinal(q1); makefinal(q2); makefinal(q5);
drawboxed(q0,q1,q2,q3,q4,q5);

edge(q0,q1,right,"1");
edge(q1,q2,right,"1");

edge(q0,q3,right,"0");
edge(q3,q0,left,"");
edge(q1,q4,right,"0");
edge(q4,q1,left,"");
edge(q2,q5,right,"0");
edge(q5,q2,left,"");

edge(q3,q4,right,"1");
edge(q4,q5,right,"1");

endfig;
verbatimtex
\end{document}
etex;
%%% the end.
end.
endinput;
