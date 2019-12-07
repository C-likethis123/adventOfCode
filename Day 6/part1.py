'''
Some observations:
A)B
B)C
C)D
number of indirect orbits for p+1 is 
number of direct orbits of planet p + number of indirect orbits of planet p

number of direct orbits can be calculated when input is read. 
'''
class Planet:
	def __init__(self, name):
		self.name = name
		self.planets_orbiting = []
		self.orbits = None

	def add_planet(self, planet):
		self.planets_orbiting.append(planet)

	def getOrbits(self):
		if self.orbits == None:
			self.orbits = len(self.planets_orbiting)
			for planet in self.planets_orbiting:
				self.orbits += planet.getOrbits()



		return self.orbits


		
import sys
import resource
import time
start_time = time.time()
dict_of_orbits = {}

for line in sys.stdin:
	planets = line.rstrip().split(")")
	first_planet, second_planet = planets[0], planets[1]

	if first_planet not in dict_of_orbits:
		dict_of_orbits[first_planet] = Planet(first_planet)
	
	
	if second_planet not in dict_of_orbits:
		dict_of_orbits[second_planet] = Planet(second_planet)


	dict_of_orbits[second_planet].add_planet(dict_of_orbits[first_planet])




#start graph traversal
total_orbits = 0
for planets in dict_of_orbits:
	total_orbits += dict_of_orbits[planets].getOrbits()


print(time.time() - start_time)
print(total_orbits)


