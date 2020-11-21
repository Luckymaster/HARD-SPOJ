//package com.solutions.spoj;

import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.AbstractMap.SimpleEntry;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.Iterator;



class FatysWarda {

	
	
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
	public static ArrayList<ArrayList<Integer>> Idx = new ArrayList<ArrayList<Integer>>(
			100005);

	public static void lookup(int N) {
		int c = 0, prev = Integer.MAX_VALUE;
		PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
		for (int i = 0; i < N; i++) {
			if (Idx.get(i).get(0) != -1) {
				out.println((Idx.get(i).get(0) + 1) + " "
						+ (Idx.get(i).get(2) + 1));
			} else {
				out.println("-1 -1");
			}
		}
		out.flush();

	}

	@SuppressWarnings("unchecked")
	public static void Solver(ArrayList<SimpleEntry<Integer, Integer>> Q, int N) {

		SimpleEntry<Integer, Integer> Tmp = new SimpleEntry<Integer, Integer>(
				0, 0);
		Iterator<SimpleEntry<Integer, Integer>> T = Q.iterator();
		if (T.hasNext()) {
			Tmp = T.next();
		}

		Deque<SimpleEntry<Integer, Integer>> S = new ArrayDeque<SimpleEntry<Integer, Integer>>();
		S.add(Tmp);
		while (T.hasNext()) {
			SimpleEntry<Integer, Integer> Tmp1 = T.next();
			while (!S.isEmpty() && S.peek().getValue() < Tmp1.getValue()) {
				Idx.get(S.peek().getKey()).add(Tmp1.getKey());
				S.pop();
			}
			S.push(Tmp1);

		}

		while (!S.isEmpty()) {
			Idx.get(S.peek().getKey()).add(-1);
			S.pop();
		}
	}

	public static void main(String[] args) throws Exception {

		int T;
		Parser aa = new Parser(System.in);
		T = aa.nextInt();

		for (int cs = 1; cs <= T ; cs++) {

			for (int i = 0; i < 100004; i++) {
				Idx.add(new ArrayList<Integer>());
			}

			int N = aa.nextInt();
			int[] inputs = new int[N+1];
			for(int i=0;i<N;i++) inputs [i] =aa.nextInt();;

			ArrayList<SimpleEntry<Integer, Integer>> inpr = new ArrayList<SimpleEntry<Integer, Integer>>();
			ArrayList<SimpleEntry<Integer, Integer>> rinp = new ArrayList<SimpleEntry<Integer, Integer>>();

			for (int i = 0; i < N; i++) {
				inpr.add(new SimpleEntry<Integer, Integer>(N - i - 1,
						inputs[N - i - 1]));
			}
			for (int i = 0; i < N; i++) {
				inpr.add(new SimpleEntry<Integer, Integer>(N - i - 1,
						inputs[N - i - 1]));
			}

			for (int i = 0; i < N; i++) {
				rinp.add(new SimpleEntry<Integer, Integer>(i, inputs[i]));
			}
			for (int i = 0; i < N; i++) {
				rinp.add(new SimpleEntry<Integer, Integer>(i, inputs[i]));
			}
			Solver(inpr, N);
			Solver(rinp, N);
			lookup(N);
			for (int i = 0; i < N; i++) {
				Idx.get(i).clear();
			}
		}
	}
}


