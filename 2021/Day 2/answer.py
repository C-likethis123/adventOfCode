with open("input") as file:
    lines = [line.strip() for line in file]

def qn1():
    vertical, horizontal = 0, 0
    for line in lines:
        direction, magnitude = line.split(" ")
        if direction == "forward":
            horizontal += int(magnitude)
        if direction == "backward":
            horizontal -= int(magnitude)
        if direction == "down":
            vertical += int(magnitude)
        if direction == "up":
            vertical -= int(magnitude)
    return vertical * horizontal


def qn2():
    vertical = horizontal = aim = 0
    for line in lines:
        direction, magnitude = line.split(" ")
        magnitude = int(magnitude)
        if direction == "forward":
            horizontal += magnitude
            vertical += aim * magnitude
        if direction == "down":
            aim += magnitude
        if direction == "up":
            aim -= magnitude
    return vertical * horizontal

print(f"Part 1: {qn1()}")
print(f"Part 2: {qn2()}")
