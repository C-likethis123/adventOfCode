string_input = list(input())
string_input = list(map(int, string_input))

for i in range(0, len(string_input), 4):
	numberToStore = 0
	if string_input[i] == 99:
		print(string_input[0])
		break
	elif string_input[i] == 1:
		index1 = string_input[i+1]
		index2 = string_input[i+2]
		numberToStore = string_input[index1] + string_input[index2]
	elif string_input[i] == 2:
		index1 = string_input[i+1]
		index2 = string_input[i+2]
		numberToStore = string_input[index1] * string_input[index2]
	else:
		continue

	index = string_input[i+3]
	string_input[index] = numberToStore