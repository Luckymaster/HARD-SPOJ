import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class AdaAndCarrot {

	private static final int MAXN = 200001;
	private static final int MOD = 1000000007;
	private static int[] permutation = new int[MAXN + 1];

	public static long modPow(int a, int b) {
		long res = 1;
		long aa  = a;
		do {
			if (b % 2 == 1) {

				res = res * aa % MOD;

			}
			aa = aa * aa  % MOD;

			b >>= 1;

		} while (b > 0);
		return res;
	}

	public static void main(String[] args) throws IOException {

		Scanner sc = new Scanner(System.in);

		permutation[0] = 1;
		
		for (int i = 1; i < MAXN; i++) {

			permutation[i] = (int)(1L * permutation[i - 1] * i % MOD);

		}

		while (sc.hasNext()) {

			long ans = 0;

			int N = sc.nextInt();

			for (int i = 1; i < N; i++) {

				int x = i;
				int y = (N - i);
				ans += (1L * modPow(x, y - 1) * modPow(y, x - 1) )% MOD;
				ans = (ans >= MOD)?ans-MOD:ans;
			}

			ans = ans * permutation[(int) N] % MOD;

			System.out.println(ans);

		}

	}

}
