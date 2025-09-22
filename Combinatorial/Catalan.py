catalan = [0] * 105
catalan[0], catalan[1] = 1, 1
for i in range(2, n + 1):
    catalan[i] = 0
    for j in range(i):
        catalan[i] = catalan[i] + catalan[j] * catalan[i - j - 1]