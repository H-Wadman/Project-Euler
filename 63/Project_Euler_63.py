done = False
k = 0
counter = 0
while(not done):
    k += 1
    current = 1
    done = True
    while pow(current, k) < pow(10, k):
        if len(str(pow(current, k))) == k:
            counter += 1
            done = False
        current += 1

print(counter)