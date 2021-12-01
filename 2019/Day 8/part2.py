import numpy as np
image_data = input()
index = 0
pixels = []


while index < len(image_data):
	layer = ""
	for height in range(0, 6):
		layer += image_data[index:index+25]
		index += 25

	pixels.append(layer)


final_image = ""
for pixel in range(0, len(pixels[0])):
	assigned_pixel = False
	for layer in pixels:
		if layer[pixel] < "2":
			final_image += layer[pixel]
			assigned_pixel = True
			break


	if not assigned_pixel:
		final_image += "2"





final_image = final_image.replace("0", ".").replace("1", "*")
index = 0
for i in range(0, 6):
	print(final_image[index:index+25])
	index += 25