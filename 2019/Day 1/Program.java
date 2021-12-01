import java.util.*;

class Program {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		HashMap<Integer, Integer> massToFuel = new HashMap<>();
		Integer sum = 0;
		for (int i = 0; i < 100; i++) {
			Integer mass = sc.nextInt();
			if (massToFuel.containsKey(mass)) {
				sum += massToFuel.get(mass);
			} else {
				Integer fuel = (mass / 3) - 2;
				sum += fuel;
				massToFuel.put(mass, fuel);
			}

		}

		System.out.println(sum);
	}
}