import java.io.DataInputStream;
import java.io.InputStream;
import java.util.Arrays;

class AdaAndRain {

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

	public static void main(String[] args) throws Exception {

		Parser sc = new Parser(System.in);
		StringBuilder output = new StringBuilder();

		int N, Q, size = 0;
		N = sc.nextInt();
		Q = sc.nextInt();
		size = sc.nextInt();

		int[] furrow = new int[size + 2];
		int[] furrowWithSumAllrain = new int[size + 2];
		Arrays.fill(furrow, 0);

		for (int i = 0; i < N; i++) {
			int L, H;
			L = sc.nextInt();
			H = sc.nextInt();
			furrow[L] += 1;
			furrow[H + 1] -= 1;
		}
		int sm = 0;
		for (int i = 0; i < size; i++) {
			sm += furrow[i];
			furrowWithSumAllrain[i] = sm;
		}
		for (int i = 0; i < Q; i++) {
			int p = sc.nextInt();
			output.append(furrowWithSumAllrain[p] + "\n");

		}
		System.out.println(output);

	}

}
