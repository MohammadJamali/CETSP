input - 2 problems

```
2
5 3
2 -4 2
5 1 1
0 0 0
1 5 1
7 0 1
5 1
4 0 0
5 5 1
2 -5 2
-4 3 1
2 2 1
```
### Algorithm :
1) found the relax solution ( at first find three nodes that they had farthest distance from each other ) for tree node
2) if sum of distance in relax solution is less than lower bound goto 3 else return
3) define V as set of uncoverd vertixes
    I)      for each remainded city do step II
    II)     for all edges in the partial solution
    III)    define θ and compute − ( p2 − p1 )⊤( p1 − c ) / || p2 − p1 || for witch p1p2 is an edge and c is vertix
    IV)   find minimum d defined as distance between c and all p1p2 s in partial solution
    V)    if d is less then or equal to radius of c then c is covered
    VI)   if goto II if any edge reminded else goto VII
    VII)  if goto I if any vertix reminded else goto 4
4) compute gamma for all k in V and select a vertex which has greater gamma for next loop


result
```
 Reading from input file, Please wait ...

 Problem Number 1


 Number Of cities : 5
 Start Point : 3
 Close enught traveling saleman problem is ready to solve ...


 Solving ...
 Generating first three nodes ...
 Generating solving tree ...


Result :

[0.000000 , 0.000000] [2.000000 , -2.000000]     (2 - 0 )
[2.000000 , -2.000000] [6.000000 , 0.000000]     (0 - 4 )
[6.000000 , 0.000000] [1.707107 , 4.292893]      (4 - 3 )
[1.707107 , 4.292893] [0.000000 , 0.000000]      (3 - 2 )

Done ! going for next problem ...



 Problem Number 2


 Number Of cities : 5
 Start Point : 1
 Close enught traveling saleman problem is ready to solve ...


 Solving ...
 Generating first three nodes ...
 Generating solving tree ...


Result :

[4.000000 , 0.000000] [2.702247 , -3.000000]     (0 - 2 )
[2.702247 , -3.000000] [-3.063671 , 2.648877]    (2 - 3 )
[-3.063671 , 2.648877] [4.039975 , 4.720086]     (3 - 1 )
[4.039975 , 4.720086] [2.999964 , 1.000000]      (1 - 4 )
[2.999964 , 1.000000] [4.000000 , 0.000000]      (4 - 0 )

Done ! going for next problem ...


```
