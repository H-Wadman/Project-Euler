from itertools import permutations


def isCube(n):
    i = 1
    while(pow(i, 3) < n):
        i += 1
    
    return n == pow(i, 3)


k = 345
found = False
while(not found):
    cube = pow(k, 3)
    counter = 1
    
    perms = [''.join(p) for p in permutations(str(cube))]

    for i in range(1, len(perms)):
        if(perms[i][0] != 0):
            if isCube(int(perms[i])):
                counter += 1
    
    if(counter == 5):
        print(k)
        found = True

    print("Number of cubes: " + str(counter))

    k += 1


    