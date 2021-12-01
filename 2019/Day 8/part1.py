image_data = input()
index = 0
pixels = ("0" * 25) * 6


while index < len(image_data):
	layer = ""
	for height in range(0, 6):
		pixel = image_data[index:index+25]

		layer += pixel
		index += 25

	pixels = layer if layer.count("0") < pixels.count("0") else pixels



print(pixels.count("1") * pixels.count("2"))