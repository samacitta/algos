# basic dynamic programming version of knapsack problem.
# (bottom-up solution)

import sys

def knapsack(W, items):
    # determine optimal solution (i.e. max vaslue)
    N = len(items)
    A = [[0 for _ in xrange(W+1)] for _ in xrange(N+1)]
    #printArray(A)
    for i in range(1, N+1):
        v, w = items[i-1]
        for j in xrange(W+1):
            if j-w < 0:
                A[i][j] = A[i-1][j]
            else:
                A[i][j] = max(A[i-1][j], A[i-1][j-w] + v)
                
    # print value array after building it
    printArray(A)
    
    # now, create a list of selected items
    select_items = []
    j = W
    for i in range(N, 0, -1):
        temp = items[i-1][1]
        if (j - temp) >= 0 and A[i-1][j-temp]+temp >= A[i-1][j]:
            select_items.append(i-1)
            j -= temp
        
    return A[N][W], select_items
    
#####

def printArray(A):
    for i in xrange(len(A)):
        print A[i]
    
#####

W = 19
items = [ (3,3), (4,4), (1,1), (8,8), (9,9) ]

result = knapsack(W, items)
print "result =", result