import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;

class Pop1 {

	static boolean isprime(BigInteger n) {
		return n.isProbablePrime(20);
	}

	static boolean isPop(BigInteger n) {
		String buff = n.toString();
		int L = buff.length();
		int[] pop = new int[L];
		for (int i = 0; i < L; i++) {
			pop[i] = -1;
		}
		for (int i = 0; i < L; i++) {
			if (isprime(new BigInteger(buff.substring(0, i + 1)))) {
				pop[i] = 1;
			}
		}
		for (int i = 0; i < L; i++) {
			for (int j = 1; j < i + 1; j++) {
				if (pop[j - 1] != -1 && buff.charAt(j) != '0' && pop[j - 1] + 1 > pop[i]) {
					if (isprime(new BigInteger(buff.substring(j, i + 1)))) {
						pop[i] = pop[j - 1] + 1;
					}
				}

			}
		}
		if (pop[L - 1] > 1)
			return true;
		return false;
	}

	public static void main(String[] args) throws NumberFormatException, IOException {
		int T;
		String N;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(br.readLine());
		while (T-- > 0) {
			N = br.readLine();
			BigInteger num = new BigInteger(N);

			boolean isPr = isprime(num);

			while (!isPop(num) || !isPr) {
				isPr = true;
				num = num.nextProbablePrime();
			}
			System.out.println(num);

		}
	}

}
