#enumerate a list of integers

#isValid:
'''
have a double (convert to string and find nums)
find if it's decreasing
'''
def hasDouble(stringValue):
	for number in stringValue:
		if stringValue.count(number) >= 2:
			return True



	return False


def isIncreasing(stringValue):
	for i in range(1, len(stringValue)):
		if int(stringValue[i]) < int(stringValue[i-1]):
			return False



	return True



inputValues = input().split("-")
list_of_values = range(int(inputValues[0]), int(inputValues[1]))
print(list_of_values)
res = 0

for value in list_of_values:
	stringValue = str(value)
	if hasDouble(stringValue) and isIncreasing(stringValue):
		res += 1




print(res)