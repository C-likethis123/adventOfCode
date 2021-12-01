with open('input') as f:
    items = [int(line.strip()) for line in f]

increased = 0
for i in range(1, len(items)):
    if items[i - 1] < items[i]:
        increased += 1

print(increased)

