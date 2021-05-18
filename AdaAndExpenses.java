import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

class AdaAndExpenses {

	private static final int MOD = 1000000007;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		String readline = br.readLine();
		char[] numberString = readline.toCharArray();

		long sum = 0;
		long endMultiplier = 0;
		for (int i = numberString.length - 1; i >= 0; i--) {
			endMultiplier = 10 * endMultiplier + 1;
			sum += (numberString[i] - '0') * (i + 1) * endMultiplier;
			sum %= MOD;
		}
		System.out.println(sum);
	}

}
