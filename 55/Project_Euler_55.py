def reverseString(s):
    return s[::-1]

def flipSum(x):
    rX = reverseString(str(x))
    return x + int(rX)

def isPalindrome(n):
    s = str(n)
    for i in range(0, len(s)//2):
        if s[i] != s[len(s)-1 - i]:
            return False
    return True

def isLyc(n):
    counter = 0
    while counter < 49:
        n = flipSum(n)
        counter += 1
        if isPalindrome(n):
            return False
    
    return True


lycCounter = 0
for i in range (1, 10000):
    if isLyc(i):
        lycCounter += 1

print(lycCounter)