import java.io.DataInputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

class AdaAndGCD {

	private static final int MOD = 1000000007;

	private static long ans = 1;

	static class Parser {
		final private int BUFFER_SIZE = 1 << 16;
		private DataInputStream din;
		private byte[] buffer;
		private int bufferPointer, bytesRead;

		public Parser(InputStream in) {
			din = new DataInputStream(in);
			buffer = new byte[BUFFER_SIZE];
			bufferPointer = bytesRead = 0;
		}

		public int nextInt() throws Exception {
			int ret = 0;
			byte c = read();
			while (c <= ' ')
				c = read();
			boolean neg = c == '-';
			if (neg)
				c = read();
			do {
				ret = ret * 10 + c - '0';
				c = read();
			} while (c > ' ');
			if (neg)
				return -ret;
			return ret;
		}

		private void fillBuffer() throws Exception {
			bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
			if (bytesRead == -1)
				buffer[0] = -1;
		}

		private byte read() throws Exception {
			if (bufferPointer == bytesRead)
				fillBuffer();
			return buffer[bufferPointer++];
		}
	}

	private static final int MAXN = 10000001;
	static boolean[] v = new boolean[MAXN + 1];
	static int[] sp = new int[MAXN + 1];

	static void Sieve() {
		for (int i = 2; i < MAXN; i += 2)
			sp[i] = 2;
		for (int i = 3; i < MAXN; i += 2) {
			if (!v[i]) {
				sp[i] = i;
				for (long j = i; (j * i) < MAXN; j += 2) {
					if (!v[(int) (j * i)]) {
						v[(int) (j * i)] = true;
						sp[(int) (j * i)] = i;
					}
				}
			}
		}
	}

	static void genFactor(int n, Map<Integer, Integer> primeAndPow) {
		if (n < 2)
			return;
		do {
			if (primeAndPow.get(sp[n]) != null) {
				primeAndPow.put(sp[n], primeAndPow.get(sp[n]) + 1);
			} else{
				primeAndPow.put(sp[n], 1);
			}
			n /= sp[n];
			if (sp[n] == 0)
				break;
		} while (sp[n] >= 1 && n % sp[n] == 0);
	}

	static Map<Integer, Integer> updateGCD(Map<Integer, Integer> primeAndPowcurrent,
			Map<Integer, Integer> primeAndPowNew) {

		Map<Integer, Integer> aux = new HashMap<>();

		primeAndPowcurrent.forEach((k, v) -> {
			if (primeAndPowNew.get(k) != null) {
				aux.put(k, Math.min(v, primeAndPowNew.get(k)));
			}
		});
		return aux;

	}

	public static long modPow(long a, long b) {
		long res = 1;
		do {
			if (b % 2 == 1) {

				res = res * a % MOD;

			}
			a = a * a % MOD;

			b >>= 1;

		} while (b > 0);
		return res;
	}

	public static void main(String[] args) throws Exception {

		Sieve();
		Parser sc = new Parser(System.in);
		Map<Integer, Integer> primeAndPowcurrent = new HashMap<>();

		int N = sc.nextInt();

		int L = sc.nextInt();

		for (int i = 0; i < L; i++) {
			int number = sc.nextInt();
			genFactor(number, primeAndPowcurrent);
		}

		for (int cs = 1; cs <= N - 1; cs++) {
			Map<Integer, Integer> primeAndPowNew = new HashMap<>();
			L = sc.nextInt();
			for (int i = 0; i < L; i++) {
				int number = sc.nextInt();
				genFactor(number, primeAndPowNew);
			}
			primeAndPowcurrent = updateGCD(primeAndPowcurrent, primeAndPowNew);
		}

		primeAndPowcurrent.forEach((k, v) -> {
			ans = ans * modPow(k, v) % MOD;
		});

		System.out.println(ans);
	}

}
