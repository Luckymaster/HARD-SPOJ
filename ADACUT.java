import java.io.DataInputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

class AdaAndTreeCutting {
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

	public static int upperBound(List<Integer> array, int value) {
		int low = 0;
		int high = array.size() - 1;
		while (low < high) {
			final int mid = (low + high) / 2;
			if (value >= array.get(mid)) {
				low = mid + 1;
			} else {
				high = mid;
			}
		}
		return low;
	}

	public static void main(String[] args) throws Exception {
		Parser sc = new Parser(System.in);
		int n;
		n = sc.nextInt();

		List<Integer> heightOfTrees = new ArrayList<>();
		long[] sumOfHeightOfTrees = new long[n + 1];

		for (int i = 0; i < n; i++) {
			heightOfTrees.add(sc.nextInt());
		}
		long z = 1;
		Arrays.fill(sumOfHeightOfTrees, 0);
		Collections.sort(heightOfTrees);
		sumOfHeightOfTrees[0] = heightOfTrees.get(0);
		for (int i = 1; i < n; i++) {
			sumOfHeightOfTrees[i] = heightOfTrees.get(i) + sumOfHeightOfTrees[i - 1];
		}
		long minAns = Long.MAX_VALUE;
		
		for (int i = 0; i < n; i++) {

			long totalCost = sumOfHeightOfTrees[n - 1]  - z * (n - i) * heightOfTrees.get(i);
			minAns = Math.min(minAns, totalCost);

		}

		System.out.println(minAns);

	}

}
