import java.util.*;

class Program1 {
	public static HashMap<Integer, Integer> massToFuel = new HashMap<>();
	public static Integer sum = 0;

	public static int fuelHelper(Integer mass, Integer sum) {
		int fuel;
		if (massToFuel.containsKey(mass)) {
			fuel = massToFuel.get(mass);
		} else {
			fuel = (mass / 3) - 2;
		}
	
		if (fuel <= 0) {
			return sum;
		} else {
			return fuelHelper(fuel, sum + fuel);
		}
	}

	public static int fuel(Integer mass) {
		return fuelHelper(mass, 0);
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextInt()) {
			Integer mass = sc.nextInt();
			if (massToFuel.containsKey(mass)) {
				sum += massToFuel.get(mass);
			} else {
				Integer fuel = fuel(mass);
				sum += fuel;
				massToFuel.put(mass, fuel);
			}

		}
		System.out.println(sum);
	}
}