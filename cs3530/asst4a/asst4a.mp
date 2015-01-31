%%% asst4a.mp -- do not edit, generated automatically by asst4a.tex
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

node.q0("0"); q0.c = origin;
node.q1("1"); q1.c = q0.c + (a,0);
node.q2("2"); q2.c = q0.c + (b,0);
node.q3("3"); q3.c = q0.c + (a,-a);
node.q4("4"); q4.c = q0.c + (b,-a);
node.q5("5"); q5.c = q0.c + (c,-a);


makestart(q0);
makefinal(q2);makefinal(q3);makefinal(q5);

drawboxed(q0,q1,q2,q3,q4,q5);

edge(q0,q1,right,btex $(\varepsilon,\varepsilon)\rightarrow \$ $ etex);

edge(q1,q2,right,btex $(a,\varepsilon)\rightarrow a $ etex);
edge(q1,q3,right,btex $(b,\varepsilon)\rightarrow b $ etex);
edge(q2,q4,right,btex $(a,a)\rightarrow \varepsilon $ etex);
edge(q3,q4,right,btex $(b,b)\rightarrow \varepsilon $ etex);

edge(q4,q5,right,btex $(\varepsilon,\$)\rightarrow \varepsilon$ etex);

loop(q2,up,btex $(a,\varepsilon)\rightarrow \varepsilon $ etex);
loop(q2,right,btex $(b,\varepsilon)\rightarrow \varepsilon $ etex);
loop(q3,left,btex $(a,\varepsilon)\rightarrow \varepsilon $ etex);
loop(q3,down,btex $(b,\varepsilon)\rightarrow \varepsilon $ etex);

endfig;
beginfig(2);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
a := -3cm;
b := a*2;
c := a*3;
d := a*4;
x := a/2;
node.q0("0"); q0.c = origin;
node.q1("1"); q1.c = q0.c + (0,a);
node.q2("2"); q2.c = q0.c + (0,b);
node.q3("3"); q3.c = q0.c + (0,c);
node.q4("4"); q4.c = q0.c + (-b+x,a);
node.q5("5"); q5.c = q0.c + (-c,a);
node.q6("6"); q6.c = q0.c + (-b+x,c);
node.q7("7"); q7.c = q0.c + (-c,c);

tinynodes;
node.q8("8"); q8.c = q0.c + (a+x,b-x);
node.q9("9"); q9.c = q0.c + (b,b+2);
node.q10("10"); q10.c = q0.c + (a+x,c);
bignodes;

makestart(q0);
makefinal(q3);

drawboxed(q0,q1,q2,q3,q4,q5,q6,q7);

edge(q0,q1,right,btex $(\varepsilon,\varepsilon)\rightarrow \$ $ etex);
edge(q1,q2,right,btex $(\varepsilon,\varepsilon)\rightarrow S  $ etex);
edge(q2,q3,right,btex $(\varepsilon,\$)\rightarrow \varepsilon $ etex);

edge(q2,q4,20,btex $(\varepsilon,S)\rightarrow a$ etex);
edge(q4,q5,20,btex $(\varepsilon,\varepsilon)\rightarrow S$ etex);
edge(q5,q2,10,btex $(\varepsilon,\varepsilon)\rightarrow a$ etex);

edge(q2,q6,-20,btex $(\varepsilon,S)\rightarrow b$ etex);
edge(q6,q7,-20,btex $(\varepsilon,\varepsilon)\rightarrow S$ etex);
edge(q7,q2,-10,btex $(\varepsilon,\varepsilon)\rightarrow b$ etex);

undirectededges;
edge(q2,q8,-20,btex $\hspace*{-4cm}(\varepsilon,S)\rightarrow \varepsilon$ etex);
edge(q2,q9,-10,btex $\hspace*{-1cm}(\varepsilon,S)\rightarrow a$ etex);
edge(q2,q10,-20,btex $\hspace*{-1cm}(\varepsilon,S)\rightarrow b$ etex);

directededges;
edge(q8,q2,-5,"");
edge(q9,q2,-10,"");
edge(q10,q2,-10,"");

endfig;
verbatimtex
\end{document}
etex;
%%% the end.
end.
endinput;
