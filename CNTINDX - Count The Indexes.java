//package com.spoj.my.solution;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.ArrayList;


class CountingIndex {

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

	public static int BinarySearch_Left(ArrayList<Integer> index, int n2) {
		int low = 0;
		int high = index.size() - 1;
		while (low <= high) {
			int mid = (low + high) / 2;
			if (index.get(mid) >= n2)
				high = mid - 1;
			else
				low = mid + 1;
		}
		return low;
	}

	public static int BinarySearch_Right(ArrayList<Integer> index, int n2) {
		int low = 0;
		int high = index.size() - 1;
		while (low <= high) {

			int mid = (low + high) / 2;
			if (index.get(mid) > n2)
				high = mid - 1;
			else
				low = mid + 1;
		}
		return low;
	}

	public static void main(String[] args) throws Exception {

		int T;
		@SuppressWarnings("unchecked")
		ArrayList<Integer>[] index = (ArrayList<Integer>[]) new ArrayList[200002];
		int Q, op, num, l, r, rem = 0, val, idx;
		ArrayList<Integer> lastnum = new ArrayList<Integer>();
		
		Parser input = new Parser(System.in);
		PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
		T = input.nextInt();
		for (int i = 0; i < 200002; i++)
			index[i] = new ArrayList<Integer>();
		
		StringBuilder sb = new StringBuilder();
		while (T-- > 0) {

			op = input.nextInt();
			if (op == 1) {
				num = input.nextInt();
				index[num].add(rem);
				lastnum.add(num);
				rem += 1;
			} else if (op == 0) {
				if (rem <= 0) {
					sb.append("invalid\n");
				} else if (!lastnum.isEmpty()) {
					int tmp = lastnum.get(lastnum.size()-1);
					lastnum.remove(lastnum.size()-1);
					index[tmp].remove(index[tmp].size()-1);
					rem -= 1;
				}
			} else if (op == 2) {
				val = input.nextInt();
				l = input.nextInt();
				r = input.nextInt();
				
				int lo = BinarySearch_Left(index[val], l-1);
				int hi = BinarySearch_Left(index[val], r);
				
				sb.append((hi-lo)+"\n");
			}

		}
		out.print(sb);
		out.flush();

	}

}
