#!/bin/python3

import math
import os
import random
import re
import sys
import itertools

#
# Complete the 'diagonalDifference' function below.
#
# The function is expected to return an INTEGER.
# The function accepts 2D_INTEGER_ARRAY arr as parameter.
#

def diagonalDifference(arr, n):
    # Write your code here
    rtol_diag = ltor_diag = 0
    for x in range(n):
        rtol_diag += arr[x][x]
    
    for x in range(n):
        ltor_diag += arr[x][n-x-1]
    
    return abs(rtol_diag - ltor_diag)


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    arr = []

    for _ in range(n):
        arr.append(list(map(int, input().rstrip().split())))

    result = diagonalDifference(arr, n)

    fptr.write(str(result) + '\n')

    fptr.close()
