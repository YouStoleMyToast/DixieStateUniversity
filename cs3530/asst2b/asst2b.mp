%%% asst2b.mp -- do not edit, generated automatically by asst2b.tex
verbatimtex
\documentclass [10pt]{article}
\begin {document}
etex;
input boxes; input theory;
beginfig(1);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
  mediumnodes;
  u := 1.5cm;
  udiag := 2u/sqrt(3);

  node.q1("1"); q1.c = (0,0);
  node.q2("2"); q2.c = (0,-u);
  makestart(q1);
  makefinal(q2);
  drawboxed(q1,q2);
  loop(q1,right,A);
  edge(q1,q2,curve,B);
  edge(q2,q1,curve,B);
  loop(q2,right,A);
  label.bot("(a)", q2.s+(0,-12pt));

  node.r1("1"); r1.c = (2u, 0);
  node.r2("2"); r2.c = (2u + udiag, 0);
  node.r3("3"); r3.c = (2u + 0.5udiag, -u);
  makestart(r1);
  makefinal(r1,r3);
  drawboxed(r1,r2,r3);
  edge(r1,r2,left,AB);
  edge(r2,r3,curve,B);
  edge(r3,r2,curve,B);
  edge(r3,r1,left,A);
  loop(r2,right,A);
  label.bot("(b)", r3.s+(0,-12pt));
endfig;
beginfig(2);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := 1.5cm;
b := a*2;
c := a*3;
d := a*4;
e := a*5;
f := a*6;
g := a*7;
h := a*8;
i := a*9;
j := a*10;
k := a*11;
l := a*12;

x :=a/2;
node.q0("0"); q0.c = origin;
node.q1("1"); q1.c = q0.c + (a,0);

node.q2("2"); q2.c = q0.c + (b,x);
node.q3("3"); q3.c = q0.c + (c,x);
node.q4("4"); q4.c = q0.c + (b,-x);
node.q5("5"); q5.c = q0.c + (c,-x);

node.q6("6"); q6.c = q0.c + (d,0);
node.q7("7"); q7.c = q0.c + (e,0);
node.q8("8"); q8.c = q0.c + (f,0);
node.q9("9"); q9.c = q0.c + (g,0);
node.q10("10"); q10.c = q0.c + (h,0);
node.q11("11"); q11.c = q0.c + (i,0);
node.q12("12"); q12.c = q0.c + (j,0);
node.q13("13"); q13.c = q0.c + (k,0);
node.q14("14"); q14.c = q0.c + (l,0);

makestart(q1);
makefinal(q14);

drawboxed(q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,q11,q12,q13,q14);


%edge(q0,q1,right, btex $\varepsilon$ etex);

edge(q1,q2,right,btex $\varepsilon$ etex);
edge(q2,q3,right,A);
edge(q3,q6,right,btex $\varepsilon$ etex);

edge(q1,q4,right,btex $\varepsilon$ etex);
edge(q4,q5,right,B);
edge(q5,q6,right,btex $\varepsilon$ etex);

edge(q6,q7,right,A);
edge(q7,q8,right,btex $\varepsilon$ etex);
edge(q8,q9,right,A);
edge(q9,q10,right,btex $\varepsilon$ etex);
edge(q10,q11,right,B);
edge(q11,q12,right,btex $\varepsilon$ etex);
edge(q12,q13,right,B);
edge(q13,q14,right,btex $\varepsilon$ etex);

edge(q5,q4,60,btex $\varepsilon$ etex);
edge(q9,q8,60,btex $\varepsilon$ etex);
edge(q13,q12,60,btex $\varepsilon$ etex);

edge(q7,q10,45,btex $\varepsilon$ etex);
edge(q11,q14,45,btex $\varepsilon$ etex);


endfig;
verbatimtex
\end{document}
etex;
%%% the end.
end.
endinput;
