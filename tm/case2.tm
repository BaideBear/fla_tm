#Q = {start,init,patch,add1,add2,return,accept,reject,final,t1,t2,t3,f1,f2,f3,f4}

#q0 = start

#S = {1}

#G = {1,_,t,r,u,e,f,a,l,s}

#B = _

#F = {final}

#N = 2

start __ __ ** accept
start 1_ 11 ** init
init 11 _1 rr patch
patch 11 _1 rr patch
patch _1 _1 ** reject
patch __ __ ** accept
patch 1_ 1_ ** add1
add1 1_ 11 *r add2
add2 1_ 11 ** return
return 11 11 *l return
return 1_ 1_ *r init

accept __ t_ r* t1
t1 __ r_ r* t2
t2 __ u_ r* t3
t3 __ e_ ** final

accept _1 t_ r* t1
t1 _1 r_ r* t2
t2 _1 u_ r* t3
t3 _1 e_ ** final

reject __ f_ r* f1
f1 __ a_ r* f2
f2 __ l_ r* f3
f3 __ s_ r* f4
f4 __ e_ ** final

reject _1 f_ r* f1
f1 _1 a_ r* f2
f2 _1 l_ r* f3
f3 _1 s_ r* f4
f4 _1 e_ ** final


