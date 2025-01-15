#Q = {start,read_a,read_b,get,solve_illegal,copy_m,find_a,copy_a,find_c,copy_c,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,solve_loss,final}

#S = {a,b}

#G = {a,b,c,_,,i,l,e,g,n,p,u,t}

#q0 = start

#B = _

#F = {final}

#N = 3

;将所有a搬运到tape 1 上， 每在tape 0读到一个b, 根据tape 1上a的数量将c拷贝到tape 2上 
start a__ _a_ rr* read_a
start b__ ___ r** read_b
read_a a__ _a_ rr* read_a
read_a b__ ___ r** copy_m
copy_m *__ *__ *l* find_a
copy_m ___ ___ *l* find_a
find_a *a_ *a_ *l* find_a
find_a _a_ _a_ *l* find_a
find_a *__ *__ *r* copy_a
find_a ___ ___ *r* copy_a
copy_a *a_ *ac *rr copy_a
copy_a _a_ _ac *rr copy_a
copy_a *__ *__ *** read_b
copy_a ___ ___ *** read_b
read_b b__ ___ r** copy_m
read_b a__ ___ *** solve_illegal
read_b ___ ___ *** get

;将tape 2的c拷贝到tape 0上
get ___ ___ **l find_c
find_c __c __c **l find_c
find_c ___ ___ **r copy_c
copy_c *_c c__ r*r copy_c
copy_c __c c__ r*r copy_c
copy_c *__ ___ *** final
copy_c ___ ___ *** final

;失败，打印illegal input
solve_illegal *__ i__ r** s1
s1 *__ l__ r** s2
s2 *__ l__ r** s3
s3 *__ e__ r** s4
s4 *__ g__ r** s5
s5 *__ a__ r** s6
s6 *__ l__ r** s7
s7 *__ ___ r** s8
s8 *__ i__ r** s9
s9 *__ n__ r** s10
s10 *__ p__ r** s11
s11 *__ u__ r** s12
s12 *__ t__ r** solve_loss

solve_illegal ___ i__ r** s1
s1 ___ l__ r** s2
s2 ___ l__ r** s3
s3 ___ e__ r** s4
s4 ___ g__ r** s5
s5 ___ a__ r** s6
s6 ___ l__ r** s7
s7 ___ ___ r** s8
s8 ___ i__ r** s9
s9 ___ n__ r** s10
s10 ___ p__ r** s11
s11 ___ u__ r** s12
s12 ___ t__ r** solve_loss

solve_loss *__ ___ r** solve_loss
solve_loss ___ ___ *** final

