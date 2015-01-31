%%% asst1c.mp -- do not edit, generated automatically by asst1c.tex
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
e := a/2;
node.q0(); q0.c = origin;
node.q1(); q1.c = q0.c + (a,0);
node.q2(); q2.c = q0.c + (b,0);
node.q3(); q3.c = q0.c + (c,0);
node.q4(); q4.c = q0.c + (d,0);
node.q5(); q5.c = q0.c + (0,-a);
node.q6(); q6.c = q0.c + (a,-a);
node.q7(); q7.c = q0.c + (b,-a);
node.q8(); q8.c = q0.c + (c,-a);

node.q9(); q9.c = q0.c + (-a,-e);

makestart(q9);
makefinal(q4);makefinal(q5);makefinal(q6);makefinal(q7);

drawboxed(q0,q1,q2,q3,q4,q5,q6,q7,q8,q9);
edge(q9,q0,right,EMPTYSTRING);
edge(q9,q5,right,EMPTYSTRING);

edge(q0,q1,right,"0");
edge(q1,q2,right,"1");
edge(q2,q3,right,"0");
edge(q3,q4,right,"1");
edge(q2,q0,-curve,"1");
edge(q3,q1,-curve,"0");
loop(q0,down,"1");
loop(q1,down,"0");
loop(q4,down,"0,1");

edge(q5,q6,curve,"1");
edge(q6,q5,curve,"0");
edge(q6,q7,right,"1");
edge(q7,q8,right,"0");
loop(q5,down,"0");
loop(q6,down,"1");
loop(q7,down,"0,1");

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
makefinal(q3);

drawboxed(q0,q1,q2,q3,q4);

edge(q0,q1,right,"1");
edge(q1,q2,right,"1");
edge(q2,q3,right,"1");
edge(q3,q4,right,EMPTYSTRING);

loop(q0,down,"0");
loop(q1,down,"0");
loop(q2,down,"0");
loop(q3,down,"0,1");
loop(q4,down,"0,1");




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
makefinal(q0);makefinal(q3);

drawboxed(q0,q1,q2,q3);

edge(q0,q1,right,"1");
edge(q1,q2,right,"1");
edge(q2,q3,right,"1");


loop(q0,down,"0");
loop(q1,down,"0");
loop(q2,down,"0");
loop(q3,down,"0,1");

endfig;
beginfig(5);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
  bignodes;
  u := 1.5cm;
  node.a1("1"); a1.c=(0,0);
  node.a2("2"); a2.c=(0,-u);
  makestart(a1); makefinal(a1);
  drawboxed(a1,a2);
  edge(a1,a2,curve,AB);
  edge(a2,a1,curve,B);
  loop(a1,right,A);
endfig;
beginfig(6);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
  bignodes;
  u := 1.5cm;
  s := u*sqrt(2);
  node.b1("1"); b1.c=(0,0);
  node.b2("2"); b2.c=(s,0);
  node.b3("3"); b3.c=(.5s,-u);
  makestart(b1); makefinal(b2);
  drawboxed(b1,b2,b3);
  edge(b1,b2,curve,E);
  edge(b2,b1,curve,A);
  edge(b1,b3,right,A);
  edge(b3,b2,right,AB);
  loop(b3,right,B);
endfig;
beginfig(7);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;

  a := 2cm;
  node.a1("1"); a1.c=(0,0);
  node.a2("2"); a2.c=(0,-a);

  makestart(a1); makefinal(a1);
  drawboxed(a1,a2);

  edge(a1,a2,curve,B);
  edge(a2,a1,curve,B);
  loop(a1,right,A);
  loop(a2,right,A);

endfig;
beginfig(8);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;

  a := 2cm;
  b := 2*a;
  c := 3*a;
  d := 4*a;

  node.b0("0");       b0.c=(a,b);
  %node.b1("1");       b1.c=(c,b);
  node.b2("2");       b2.c=(a,a);
  node.b3("3");       b3.c=(c,a);
  node.b12("1,2");    b12.c=(a,0);
  node.b13("1,3");    b13.c=(c,-a);
  node.b23("2,3");    b23.c=(c,0);
  node.b123("1,2,3"); b123.c=(a,-a);


  makestart(b12);
  makefinal(b2);makefinal(b12);makefinal(b23);makefinal(b123);
  drawboxed(b0,b2,b3,b12,b13,b23,b123);

  loop(b0,up,"a,b");
  %edge(b1,b3,right,A);    edge(b1,b0,right,B);
  edge(b2,b12,right,A);   edge(b2,b0,right,B);
  edge(b3,b2,right,A);    edge(b3,b23,right,B);
  edge(b12,b23,right,A);  edge(b12,b3,right,B);
  edge(b13,b23,curve,A);  edge(b13,b23,-curve,B);
  edge(b23,b123,right,A); edge(b23,b2,right,B);
  edge(b123,b12,right,A); loop(b123,right,B);


endfig;
verbatimtex
\end{document}
etex;
%%% the end.
end.
endinput;
