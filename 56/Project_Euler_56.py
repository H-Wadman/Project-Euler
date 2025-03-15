
def digit_sum(n):
    s = str(n)
    sum = 0
    for i in range(len(s)):
        sum += int(s[i])
    
    return sum


max = 0
for a in range(100):
    for b in range(100):
        dSum = digit_sum(pow(a, b))
        if  dSum > max:
            max = dSum

print(max)