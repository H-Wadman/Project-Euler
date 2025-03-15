def next_iteration(bråk):
    result = (bråk[1], bråk[0] + 2 * bråk[1])
    return result


def störreTäljare(bråk):
    return (len(str(bråk[0])) > len(str(bråk[1])))

bråk = (1, 2)
counter = 0



for i in range (999):
    bråk = next_iteration(bråk)
    if störreTäljare((bråk[0] + bråk[1], bråk[1])):
        counter += 1

print(counter)