import java.io.DataInputStream;
import java.io.InputStream;

class AdaAndPlants {

	private static final int MAXN = 100001;
	private static final int MAXK = 29;

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
		T = sc.nextInt();
		StringBuilder output = new StringBuilder();

		for (int cs = 0; cs < T; cs++) {

			N = sc.nextInt();
			K = sc.nextInt();

			int[] heights = new int[N + 1];

			int maxHeight = -1;

			for (int i = 0; i < N; i++) {
				heights[i] = sc.nextInt();
				maxHeight = Math.max(maxHeight, heights[i]);
			}

			int[] log = new int[100002];
			log[1] = 0;
			for (int i = 2; i <= 100001; i++)
				log[i] = log[i / 2] + 1;

			//int MAXK = getLogN(maxHeight);
			int[][] sptableMin = new int[N+1][MAXK + 1];
			int[][] sptableMax = new int[N+1][MAXK + 1];

			for (int i = 0; i < N; i++) {
				sptableMin[i][0] = heights[i];
				sptableMax[i][0] = heights[i];
			}

			for (int i = 1; i <= MAXK; i++) {
				for (int j = 0; j + (1 << i) <= N; j++) {
					sptableMin[j][i] = Math.min(sptableMin[j][i - 1], sptableMin[j + (1 << (i - 1))][i - 1]);
					sptableMax[j][i] = Math.max(sptableMax[j][i - 1], sptableMax[j + (1 << (i - 1))][i - 1]);
				}
			}

			int maxAns = Integer.MIN_VALUE;

			if (K > N - 2) {

				int R = N - 1;
				int L = 0;
				int aux = log[Math.abs(R - L + 1)];
				int minimum = Math.min(sptableMin[L][aux], sptableMin[R - (1 << aux) + 1][aux]);
				int maximum = Math.max(sptableMax[L][aux], sptableMax[R - (1 << aux) + 1][aux]);
				maxAns = Math.max(maxAns, maximum - minimum);
				output.append(maxAns + "\n");
			} else {

				for (int i = 0; i < N - K - 1; i++) {
					int R = i + K + 1;
					int L = i;
					int aux = log[Math.abs(R - L + 1)];
					int minimum = Math.min(sptableMin[L][aux], sptableMin[R - (1 << aux) + 1][aux]);
					int maximum = Math.max(sptableMax[L][aux], sptableMax[R - (1 << aux) + 1][aux]);

					maxAns = Math.max(maxAns, maximum - minimum);
				}

				output.append(maxAns + "\n");
			}

		}
		System.out.println(output);

	}

}
