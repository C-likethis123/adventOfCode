with open('input') as f:
    items = [int(line.strip()) for line in f]

def qn1():
    increased = 0
    for i in range(1, len(items)):
        if items[i - 1] < items[i]:
            increased += 1
    return increased


def qn2():
    increased_sums = 0
    for i in range(3, len(items)):
        if items[i] > items[i - 3]:
            increased_sums += 1
    return increased_sums
    
print(f"Part 1: {qn1()}")
print(f"Part 2: {qn2()}")

