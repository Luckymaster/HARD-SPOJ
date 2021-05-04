//refrernce https://codeforces.com/blog/entry/10912
//Sum of GCD of all contiguous subsequence
import java.io.DataInputStream;
import java.io.InputStream;

class AdaAndGreenflies {

	private static final int MAXN = 300001;
	private static final int MAXK = 19;

	private static int[][] sptableGCD = new int[MAXN + 1][MAXK];
	private static int[] log = new int[MAXN + 1];

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

	static int gcdBySteinsAlgorithm(int n1, int n2) {
		if (n1 == 0) {
			return n2;
		}

		if (n2 == 0) {
			return n1;
		}

		int n;
		for (n = 0; ((n1 | n2) & 1) == 0; n++) {
			n1 >>= 1;
			n2 >>= 1;
		}

		while ((n1 & 1) == 0) {
			n1 >>= 1;
		}

		do {
			while ((n2 & 1) == 0) {
				n2 >>= 1;
			}

			if (n1 > n2) {
				int temp = n1;
				n1 = n2;
				n2 = temp;
			}
			n2 = (n2 - n1);
		} while (n2 != 0);
		return n1 << n;
	}

	static int getGCDQuery(int L, int R) {
		int aux = log[R - L + 1];
		return gcdBySteinsAlgorithm(sptableGCD[L][aux], sptableGCD[R - (1 << aux) + 1][aux]);
	}

	static int nextPosition(int currentGCD, int startIdxPointer, int prevEndPointer, int n) {
		int high = n - 1;
		int low = prevEndPointer;
		int mid = prevEndPointer;
		int nextPos = prevEndPointer;

		// BinarySearch for Next Position
		// for lastPointer
		while (high >= low) {

			mid = ((high + low) >> 1);

			if (getGCDQuery(startIdxPointer, mid) == currentGCD) {
				nextPos = mid;
				low = mid + 1;
			} else {
				high = mid - 1;
			}
		}

		return nextPos + 1;
	}

	static int getLogN(int N) {

		int idx = 1;
		while (N > 0) {
			N /= 2;
			idx += 1;
		}

		return idx;

	}

	public static void main(String[] args) throws Exception {

		Parser sc = new Parser(System.in);

		int N, K, T;

		N = sc.nextInt();

		int[] greenflies = new int[N + 1];

		for (int i = 0; i < N; i++) {
			greenflies[i] = sc.nextInt();
		}

		log[1] = 0;
		for (int i = 2; i <= MAXN; i++)
			log[i] = log[i / 2] + 1;

		for (int i = 0; i < N; i++) {
			sptableGCD[i][0] = greenflies[i];
		}

		int sum = 0;

		for (int i = 1; i <= MAXK; i++) {
			for (int j = 0; j + (1 << i) <= N; j++) {
				sptableGCD[j][i] = gcdBySteinsAlgorithm(sptableGCD[j][i - 1], sptableGCD[j + (1 << (i - 1))][i - 1]);
			}
		}

		long tempAns = 0;

		for (int i = 0; i < N; i++) {

			int currentGCD = greenflies[i];
			int startIdxPointer = i;
			int lastIdxPointer = i;
			int prevEndPointer = i;

			while (lastIdxPointer < N) {

				// Finding the next position for lastIdxPointer
				lastIdxPointer = nextPosition(currentGCD, startIdxPointer, prevEndPointer, N);

				// Adding the suitable sum to our answer
				tempAns += ((lastIdxPointer - prevEndPointer) * 1L * currentGCD);

				// Changing prevEndPointer
				prevEndPointer = lastIdxPointer;

				if (lastIdxPointer < N) {
					// Recalculating currentGCD
					currentGCD = gcdBySteinsAlgorithm(currentGCD, greenflies[lastIdxPointer]);
				}
			}
		}

		System.out.println(tempAns);

	}

}
