%%% figure-examples.mp -- do not edit, generated automatically by figure-examples.tex
verbatimtex
\documentclass [11pt]{article}
\begin {document}
etex;
input boxes; input theory;
beginfig(1);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
  % it's good practice to pick a basic size unit and make all your
  % distances relative to that unit
  u := 2cm;

  % create a node, and position its center at the origin
  node.q0(); q0.c = origin;

  % create 3 more nodes, and position their respective centers
  % relative to the center of the first node.
  node.q1(); q1.c = q0.c + (u,0);
  node.q2(); q2.c = q0.c + (0,-u);
  node.q3(); q3.c = q0.c + (u,-u);

  % mark q0 as a start node
  makestart(q0);

  % mark q3 as an accept node
  makefinal(q3);

  % draw the nodes
  drawboxed(q0,q1,q2,q3);

  % an edge from q0 to q1, curved 25 degrees, with label $a$
  edge(q0,q1,25,A);

  % additional edges with default curve and $a$ label
  edge(q1,q0,curve,A);
  edge(q2,q3,curve,A);
  edge(q3,q2,curve,A);

  % additional edges with default curve and $b$ label
  edge(q0,q2,curve,B);
  edge(q2,q0,curve,B);
  edge(q1,q3,curve,B);
  edge(q3,q1,curve,B);
endfig;
beginfig(2);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
  % Pick a size of nodes other than the default (bignodes). This
  % also resets the edge color, solid/dashed, etc.
  mediumnodes;
  u := 1cm;

  % create a node with a zero inside it, centered at the origin
  node.a("0"); a.c = (0,0);

  % position additional nodes using absolute coordinates
  node.b("1"); b.c = (u,0);
  node.c("2"); c.c = (2u,0);
  node.d("03"); d.c = (3u,0);
  node.e("01"); e.c = (4u,0);
  node.f("12"); f.c = (5u,0);
  node.g("02"); g.c = (6u,0);

  % labels can use LaTeX format with btex ... etex
  node.h(btex $\emptyset$ etex); h.c = (0,-u);
  makestart(a); makefinal(a,d,e,g);

  edge(a,b,right,A);
  edge(b,c,right,A);
  edge(c,d,right,B);
  edge(d,e,right,A);
  edge(e,f,right,A);
  edge(f,g,right,A);
  edge(a,h,right,B);

  % negative angles emerge curved to the left instead of right
  edge(c,a,-45,A);
  edge(g,e,-45,A);
  edge(g,d,-60,B);
  edge(f,d,60,B);

  loop(h,down,A);
  loop(h,left,B);

  drawboxed(a,b,c,d,e,f,g,h);
endfig;
beginfig(3);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
  smallnodes;
  node.a(); a.c = (0,0);
  makestart(a); makefinal(a);

  % this time we didn't define a scaling unit, so we use standard
  % units instead
  node.b(); b.c = (1.5cm,1cm);
  node.c(); c.c = (2cm,0);
  node.d(); d.c = (1.5cm,-1cm);

  % switch to drawing red edges
  rededges;
  edge(a,b,left,A);

  % back to black edges
  blackedges;
  edge(b,c,left,A);
  edge(c,d,left,B);
  edge(d,a,left,A);

  node.e(); e.c = (-1cm,1cm);

  % metapost is capable of quite a bit of math, so you can compute
  % positions instead of specifying literal coordinates
  node.f(); f.c = (0cm, sqrt(2)*1cm);
  rededges;
  edge(a,e,left,A);
  blackedges;
  edge(e,f,left,A);
  edge(f,a,left,B);

  node.g(); g.c = (-1cm,-1cm);
  node.h(); h.c = (0cm, -sqrt(2)*1cm);
  rededges;
  edge(a,h,left,A);
  blackedges;
  edge(h,g,left,A);
  edge(g,a,left,A);

  drawboxed(a,b,c,d,e,f,g,h);
endfig;
beginfig(4);
LaTeX_unitlength := 1.0pt;
w := 0*LaTeX_unitlength;
h := 0*LaTeX_unitlength;
  mediumnodes;
  picture x;
  u := 1cm;

  % turn off arrow heads on the edges
  undirectededges;
  node.x(X); x.c=(0,0);

  % up is a unit vector, scaling it gives it the desired length
  node.a(A); a.c=up scaled u;

  % here we scale and rotate a vector to specify the position
  node.b(B); b.c=up rotated 120 scaled u;
  node.c(C); c.c=up rotated -120 scaled u;
  drawboxed(x,a,b,c);

  % straight edges can use this shortcut
  sedge(x,a);
  sedge(x,b);
  sedge(x,c);
  dashededges;
  sedge(a,b);
  sedge(b,c);
  sedge(a,c);
  solidedges; directededges;
endfig;
verbatimtex
\end{document}
etex;
%%% the end.
end.
endinput;
