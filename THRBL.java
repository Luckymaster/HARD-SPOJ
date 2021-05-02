import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.InputStream;
import java.io.PrintWriter;

class CatapultThatBall {

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
		int N, M;
		Parser aa = new Parser(System.in);

		N = aa.nextInt();
		M = aa.nextInt();
		int K = (int) (Math.log(N) / Math.log(2));
		int[][] sptable = new int[N + 10][K + 1];
		int[] inputArray = new int[N + 1];

		for (int i = 0; i < N; i++) {
			inputArray[i] = aa.nextInt();
		}

		for (int i = 0; i < N; i++) {
			sptable[i][0] = inputArray[i];
		}

		int[] log = new int[N + 1];
		log[1] = 0;
		log[0] = 0;
		for (int i = 2; i <= N; i++)
			log[i] = log[i / 2] + 1;

		for (int i = 1; i <= K; i++) {
			for (int j = 0; j + (1 << i) <= N; j++) {
				sptable[j][i] = Math.max(sptable[j][i - 1], sptable[j + (1 << (i - 1))][i - 1]);
			}
		}

		int R, L, sum = 0;
		for (int cs = 0; cs < M; cs++) {
			L = aa.nextInt();
			R = aa.nextInt();
			L--;
			R--;
			int height = inputArray[L];
			int aux = 0;
			if ((R - L) < 2) {
				sum += 1;
				continue;
			}
			L++;
			R--;
			aux = log[R - L + 1];
			int maximum = Math.max(sptable[L][aux], sptable[R - (1 << aux) + 1][aux]);

			if (maximum <= height) {
				sum += 1;
			}
		}
		System.out.println(sum);
	}

}
