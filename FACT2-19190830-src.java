//package com.spoj.my.solution;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.Vector;
import java.math.BigInteger;

class MathsUtils {

	static long mx = -1L;
	static int idx = 0;
	static boolean[] isPrime = new boolean[100005];
	static long[] prime = new long[20000];

	public static void genPrimes() {
		Arrays.fill(isPrime, true);
		isPrime[0] = isPrime[1] = false;
		for (int i = 2; i * i <= 100000; i++) {
			if (isPrime[i]) {
				for (int j = i; j * i <= 100000; j++)
					isPrime[i * j] = false;
			}
		}
		prime[0] = 2;
		for (int i = 3; i < 100000; i += 2) {
			if (isPrime[i])
				prime[idx++] = i;
		}
	}

	public static boolean isPrimeInt(long j) {
		// return isPrime[(int)j];

		long k = sqrtLong(j);
		if (j < 100000)
			return isPrime[(int) j];
		
		  if ((j & 1) == 0) return false; for (int p = 1; prime[p] <= k; p++)
		  if (j % prime[p] == 0) return false;
		 
		//BigInteger m = new BigInteger(j + "");
		return true;//m.isProbablePrime(10);
	}

	public static long legendreSymbol1(long n, long p) {
		long count, temp;
		long legendre = 1;
		if (n == 0)
			return 0;
		if (n < 0) {
			n = -n;
			if ((p & 3) == 3)
				legendre = -1;
		}
		do {
			count = 0;
			while ((n & 1) == 0) {
				n >>=1;
				count = 1 - count;
			}
			if (((count * (p * p - 1)) & 15) == 8)
				legendre = -legendre;
			if ((((n - 1) * (p - 1)) & 7) == 4)
				legendre = -legendre;
			temp = n;
			n = p % n;
			p = temp;
		} while (n > 1);
		return legendre;
	}

	public static long legendreSymbol(long a, long p) {
		if (a == 1)
			return 1;
		if (a == 0) {
			if (p == 1)
				return 1;
			else
				return 0;
		} else if (a % p == 0)
			return 0;
		else {
			long r = modPowLong(a, (p - 1) >> 1, p);
			return r == 1 ? 1 : -1;
		}
	}

	public static long modPowLong(long n, long p, long m) {

		long x = 1, y = n;
		while (p > 0) {
			if ((p & 1) == 1)
				x = x * y % m;
			y = y * y % m;
			p >>= 1;
		}
		return x;
	}

	public static long sqrtLong(long n) {
		long low = 1;
		long high = n;
		long medium, square;
		do {
			medium = (high + low) >> 1;
			square = medium * medium;
			if (square < n)
				low = medium;
			if (square > n)
				high = medium;
			if (square == n)
				return medium;
		} while (high > low + 1);
		if (high * high == n)
			return high;
		else
			return low;
	}

	public static BigInteger sqrtBigInt(BigInteger i) {
		long c;
		BigInteger medium;
		BigInteger high = new BigInteger(i.toString());
		BigInteger low = BigInteger.ONE;
		while (high.subtract(low).compareTo(BigInteger.ONE) > 0) {
			medium = high.add(low).shiftRight(1);// divide(BigInteger.ONE.add(BigInteger.ONE));
			c = medium.multiply(medium).compareTo(i);
			if (c > 0)
				high = medium;
			if (c < 0)
				low = medium;
			if (c == 0)
				return medium;
		}
		if (high.multiply(high).compareTo(i) == 0)
			return high;
		else
			return low;
	}

	public static long v(long i, long h, long n, long p) {
		if (i == 1)
			return h;
		if (i == 2)
			return (h * h - (n << 1)) % p;
		long vi = v((i >> 1), h, n, p);
		long vi_1 = v((i >> 1) + 1, h, n, p);
		if (i % 2 == 1) {
			vi = (vi * vi_1 - h * modPowLong(n, (i >> 1), p)) % p;
			if (vi < 0)
				vi += p;
			return vi;
		} else
			return (vi * vi - 2 * modPowLong(n, (i >> 1), p)) % p;
	}

	public static long v_(long j, long h, long n, long p) {
		long b[] = new long[64];
		long m = n;
		long v = h;
		long w = (h * h - (m << 1)) % p;
		long x;
		int k, t;
		t = 0;
		while (j > 0) {
			b[++t] = (j & 1);
			j >>= 1;
		}
		for (k = t - 1; k >= 1; k--) {
			x = (v * w - h * m) % p;
			v = (v * v - (m << 1)) % p;
			w = (w * w - ((n * m) << 1)) % p;
			m = m * m % p;
			if (b[k] == 0)
				w = x;
			else {
				v = x;
				m = n * m % p;
			}
		}
		return v;
	}

}

class QuadraticSieve {

	private static BigInteger n;
	private long percentage;

	private final static InputStreamReader istream = new InputStreamReader(
			System.in);
	private final static BufferedReader stdin = new BufferedReader(istream);

	static BigInteger[] factors = new BigInteger[64];
	static int prlen = 0;
	private final BigInteger ZERO = BigInteger.ZERO;
	private final static BigInteger ONE = BigInteger.ONE;
	private final BigInteger TWO = ONE.add(ONE);
	private final int bitChunkSize = 15;

	private final int PRIME_BASE = 600;
	private final int ADDITIONAL = bitChunkSize;

	private int primes[];
	private BigInteger primesBig[];
	private double primeLog;
	private double primeLogs[];
	private int maxPrime;
	private BigInteger largePrimeBound;

	private BigInteger remaining;

	private BigInteger s[], fs[];
	private double logs[];
	private ArrayList decomposedNumbers;// private Vector decomposedNumbers;
	private int decomposed = 0;
	private int checked = 0;

	private long zeitmessung;

	public QuadraticSieve(BigInteger aNumber) {
		n = aNumber;
		percentage = -1;
		buildFactorBase();
		fs = null;
		logs = null;
		decomposedNumbers = null;
	}

	private void buildFactorBase() {
		int j, k, nModP;
		primes = new int[PRIME_BASE];
		primes[0] = -1;
		k = 1;
		primes[1] = 2;
		k = 2;
		j = 3;
		while (k < PRIME_BASE) {
			if (MathsUtils.isPrimeInt(j)) {
				nModP = n.mod(BigInteger.valueOf(j)).intValue();
				if (MathsUtils.legendreSymbol(nModP, j) == 1)
					primes[k++] = j;
			}
			j += 2;
		}
		primesBig = new BigInteger[PRIME_BASE];
		primeLogs = new double[PRIME_BASE];
		for (k = 1; k < PRIME_BASE; k++) {
			primesBig[k] = BigInteger.valueOf(primes[k]);
			primeLogs[k] = (double) Math.log(primes[k]);
		}
		maxPrime = primes[PRIME_BASE - 1];
		primeLog = primeLogs[PRIME_BASE - 1];
		largePrimeBound = BigInteger.valueOf(maxPrime);
		largePrimeBound = largePrimeBound.multiply(largePrimeBound);
	}

	/*
	 * public static void main(String[] args) {
	 * 
	 * // QuadraticSieve qs = new QuadraticSieve(); BigInteger num = new
	 * BigInteger("36270238006959067675891295930053"); QuadraticSieve qs = new
	 * QuadraticSieve(num); // n = num; BigInteger nn =
	 * qs.quadraticSieve(2000000); System.out.println(nn + " " + n.divide(nn));
	 * 
	 * }
	 */
	static BigInteger mr_min(BigInteger a, BigInteger b) {
		return a.min(b);
	}

	private static BigInteger generateRandom(BigInteger n) {
		Random random = new Random();
		BigInteger randomBigInteger = new BigInteger(n.bitLength(), random)
				.mod(n);

		// Repeat if the generated value is larger than or equal to n.
		while (randomBigInteger.compareTo(n) >= 0) {
			randomBigInteger = new BigInteger(n.bitLength(), random).mod(n);
		}
		return randomBigInteger;
	}

	public BigInteger fermat(long upperBound) {
		long cnt = 0;
		BigInteger x = MathsUtils.sqrtBigInt(n).add(ONE);
		BigInteger y = ZERO;
		BigInteger u = x.multiply(TWO).add(ONE);
		BigInteger v = ONE;
		BigInteger r = x.multiply(x).subtract(n);

		update(-1);

		while (r.compareTo(ZERO) != 0) {
			update((cnt * 100) / upperBound);
			cnt++;
			if (cnt > upperBound) {
				update(1234);
				return ZERO;
			}
			while (r.compareTo(ZERO) > 0) {
				r = r.subtract(v);
				v = v.add(TWO);
			}
			if (r.compareTo(ZERO) < 0) {
				r = r.add(u);
				u = u.add(TWO);
			}
		}
		update(1234);
		return u.subtract(v).divide(TWO);
	}

	/****************************************************************************************************/
	/*****
	 * PSEUDOFERMAT is nothing special. Works similar to FERMAT, it has just got
	 * a linear
	 *****/
	/***** progress bar, which I liked more some night. *****/
	/****************************************************************************************************/
	private void update(long percent) {
		if (percent < 0) {
			percentage = percent;
			return;
		}
		if (percent == 1234) {
			// writeln(". Done");
			return;
		}
		if (percent > 100)
			return;
		if (percentage != percent) {
			if (percent % 10 == 0)
				;
			// write("" + percent);
			else if (percent % 2 == 0)
				// write(".");
				percentage = percent;
		}
	}

	public BigInteger pseudoFermat(int upperBound) {
		BigInteger factor = MathsUtils.sqrtBigInt(n);
		if (factor.mod(TWO).compareTo(ZERO) == 0)
			factor = factor.subtract(ONE);

		long cnt = upperBound - 1;

		// writeln("Pseudo Fermat running. Searching for factors close to Sqrt(n).\n");

		update(-1);

		while (cnt > 0) {
			if (n.mod(factor).compareTo(ZERO) == 0) {
				update(1234);
				return factor;
			}
			factor = factor.subtract(TWO);
			cnt -= 2;
			update(((upperBound - cnt) * 100) / upperBound);
		}

		update(100);
		update(1234);
		return ZERO;
	}

	public static BigInteger factorizebrent(BigInteger n) {
		final BigInteger TWO = new BigInteger("2");
		BigInteger k = new BigInteger("1");
		BigInteger TEN = new BigInteger("10");
		BigInteger THREE = generateRandom(n);
		BigInteger r = new BigInteger("1");
		BigInteger i = new BigInteger("1");
		BigInteger m = new BigInteger("1");
		BigInteger iter = new BigInteger("1");
		BigInteger z = new BigInteger("1");
		BigInteger x = new BigInteger("1");
		BigInteger y = new BigInteger("1");
		BigInteger q = new BigInteger("1");
		BigInteger ys = new BigInteger("1");
		BigInteger TENTHOUSAND = new BigInteger("100000");
		m = TEN;
		r = ONE;
		iter = BigInteger.ZERO;
		z = BigInteger.ZERO;
		y = z;
		q = ONE;
		do {
			x = y;
			for (i = ONE; i.compareTo(r) <= 0; i = i.add(ONE))
				y = ((y.multiply(y)).add(THREE)).mod(n);
			k = BigInteger.ZERO;
			do {
				iter = iter.add(ONE);
				ys = y;
				for (i = ONE; i.compareTo(mr_min(m, r.subtract(k))) <= 0; i = i
						.add(ONE)) {
					y = ((y.multiply(y)).add(THREE)).mod(n);
					q = ((y.subtract(x).abs()).multiply(q)).mod(n);
				}
				z = n.gcd(q);
				k = k.add(m);
			} while (k.compareTo(r) < 0 && z.compareTo(ONE) == 0);
			r = r.shiftLeft(1);
		} while (z.compareTo(ONE) == 0 && iter.compareTo(TENTHOUSAND) < 0);
		if (z.compareTo(n) == 0)
			do {
				ys = ((ys.multiply(ys)).add(THREE)).mod(n);
				z = n.gcd((ys.subtract(x)).abs());
			} while (z.compareTo(ONE) == 0);
		return z;
	}

	private static int getPollardLimit(BigInteger n) {
		if (n.compareTo(new BigInteger("10")) < 0) {
			return n.intValue();
		} else if (n.compareTo(new BigInteger("100")) < 0) {
			return n.intValue() / 2;
		}
		return 100;
	}

	public static BigInteger trialDivision(BigInteger N) {
		for (int i = 0; i < 195; i++) {
			BigInteger p = BigInteger.valueOf(MathsUtils.prime[i]);
			if (N.mod(p).compareTo(BigInteger.ZERO) == 0) {
				while (N.mod(p).compareTo(BigInteger.ZERO) == 0) {
					factors[prlen++] = p;
					N = N.divide(p);
				}
			}
		}
		return N;
	}

	public static void init(BigInteger N) {

		/*
		 * if (N.isProbablePrime(10)) { factors[prlen++] = N; return; }
		 */
		QuadraticSieve qs = new QuadraticSieve(N);
		BigInteger tp = qs.pseudoFermat(20000);
		if (!(tp.compareTo(BigInteger.ZERO) == 0)) {
			factor(tp);
			factor(N.divide(tp));
		} else {
			BigInteger divisor = qs.quadraticSieve(200000);
			factor(divisor);
			factor(N.divide(divisor));
		}

	}

	public static void factor(BigInteger N) {

		if (N.compareTo(ONE) == 0)
			return;

		if (N.isProbablePrime(10)) {
			factors[prlen++] = N;
			return;
		}
		BigInteger divisor = factorizebrent(N);
		factor(divisor);
		factor(N.divide(divisor));
	}

	public static void main(String[] args) throws Exception {
		String s;
		BigInteger n;
		int i, j;
		boolean first;
		MathsUtils.genPrimes();
		long st = System.currentTimeMillis();
		while ((s = stdin.readLine()) != null) {
			if (s.equals("0"))
				break;
			prlen = 0;
			//System.out.println(s.length());
			BigInteger mm = trialDivision(new BigInteger(s));
			if (!(mm.compareTo(BigInteger.ONE) == 0)) {
				init(mm);
				// factor(mm);
			}
			// factor(new BigInteger(s));
			Arrays.sort(factors, 0, prlen);
			for (i = 0, first = true; i < prlen; i++) {
				n = factors[i];
				j = i;
				while (j < prlen && factors[j].equals(n))
					j++;
				if (first)
					first = false;
				else
					System.out.print(" ");
				System.out.print(n + "^" + (j - i));
				i = j - 1;
			}
			System.out.println("");
		}
		//System.out.println(System.currentTimeMillis() - st);
	}

	private void removeHighestPower(int index, BigInteger p) {
		if (fs[index].mod(p).compareTo(ZERO) == 0) {
			do
				fs[index] = fs[index].divide(p);
			while (fs[index].mod(p).compareTo(ZERO) == 0);
			if (fs[index].compareTo(ONE) == 0) {
				logs[index] = 0;
				decomposedNumbers.add(s[index]);
				decomposed++;
			}
		} else {

			try {
				Thread.sleep(1);
			} catch (InterruptedException ie) {
			}
		}
	}

	public long[] findFlats1(long p, long n) {
		long[] result = new long[2];
		if (p == 2) {
			result[0] = n;
			result[1] = n;
			return result;
		}

		long S = 0;
		long Q = p - 1;

		while ((Q & 1) == 0) {
			Q >>= 1;
			++S;
		}

		long z = 2;

		while (MathsUtils.legendreSymbol(z, p) != -1)
			++z;

		long c = MathsUtils.modPowLong(z, Q, p);
		long R = MathsUtils.modPowLong(n, (Q + 1) / 2, p);
		long t = MathsUtils.modPowLong(n, Q, p);
		long M = S;

		while (t % p != 1) {
			long i = 1;
			while (MathsUtils.modPowLong(t, (long) Math.pow(2, i), p) != 1)
				++i;

			long b = MathsUtils.modPowLong(c, (long) Math.pow(2, M - i - 1), p);
			R = R * b % p;
			t = t * b * b % p;
			c = b * b % p;
			M = i;
		}

		result[0] = R;
		result[1] = p - R;

		return result;
	}

	private long[] findFlats(long p, long n) {
		long j, k, x;
		BigInteger test;
		BigInteger prim = BigInteger.valueOf(p);

		long result[] = new long[2];
		result[0] = -1;
		result[1] = -1;

		if (p == 2) {
			result[0] = (n & 1);
			result[1] = -1;
			return result;
		}

		if (p % 4 == 3) {
			k = (p >> 2);
			x = MathsUtils.modPowLong(n, k + 1, p) % p;
			result[0] = x;
			result[1] = (p - x);
			return result;
		}

		if (p % 8 == 5) {
			k = (p >> 3);// changed p/8
			x = MathsUtils.modPowLong(n, (k << 1) + 1, p);
			if (x == 1) {
				x = MathsUtils.modPowLong(n, k + 1, p);
				result[0] = x;
				result[1] = (p - x);
				return result;
			}
			if (x == p - 1) {
				x = MathsUtils.modPowLong((n << 2), k + 1, p);
				x = (x * (p + 1) >> 1) % p;
				result[0] = x;
				result[1] = (p - x);
				return result;
			}
		}

		long h = 13;
		do
			h += 2;
		while (MathsUtils.legendreSymbol(h * h - (n << 2), p) != -1);

		k = (p + 1) >> 1;
		x = MathsUtils.v_(k, h, n, p);
		if (x < 0)
			x += p;
		x = (x * k) % p;
		result[0] = x;
		result[1] = (p - x);

		return result;
	}

	private BigInteger quadraticF(BigInteger x, BigInteger n) {
		return x.multiply(x).subtract(n);
	}

	private byte[] extractLine(int right[][], int index) {
		int j, k;
		int line[] = right[index];
		byte result[] = new byte[PRIME_BASE + ADDITIONAL];
		int comparation = 1;
		for (j = 0; j < PRIME_BASE + ADDITIONAL; j++) {
			if ((line[j / bitChunkSize] & comparation) > 0)
				result[j] = 1;
			else
				result[j] = 0;

			if (j % bitChunkSize == (bitChunkSize - 1))
				comparation = 1;
			else
				comparation <<= 1;
		}
		return result;
	}

	private void solveMatrix(int matrix[][], int right[][]) {
		int j, k;
		k = matrix.length;
		for (j = 0; j < k - 1; j++)
			gaussElim(matrix, right, j, k);
	}

	private void gaussElim(int matrix[][], int right[][], int j, int k) {
		int c1, c2;
		int temp;
		int comparation = 1;
		for (c1 = 1; c1 <= (j % bitChunkSize); c1++)
			comparation <<= 1;
		if ((matrix[j][j / bitChunkSize] & comparation) == 0)
			for (c1 = j + 1; c1 < k; c1++)
				if ((matrix[c1][j / bitChunkSize] & comparation) > 0) {
					for (c2 = j / bitChunkSize; c2 < k / bitChunkSize; c2++) {
						temp = matrix[j][c2];
						matrix[j][c2] = matrix[c1][c2];
						matrix[c1][c2] = temp;
					}
					for (c2 = 0; c2 < k / bitChunkSize; c2++) {
						temp = right[j][c2];
						right[j][c2] = right[c1][c2];
						right[c1][c2] = temp;
					}
					break;
				}

		if ((matrix[j][j / bitChunkSize] & comparation) > 0)
			for (c1 = j + 1; c1 < k; c1++)
				if ((matrix[c1][j / bitChunkSize] & comparation) > 0) {
					for (c2 = j / bitChunkSize; c2 < k / bitChunkSize; c2++)
						matrix[c1][c2] = (int) (matrix[c1][c2] ^ matrix[j][c2]);
					for (c2 = 0; c2 < k / bitChunkSize; c2++)
						right[c1][c2] = (int) (right[c1][c2] ^ right[j][c2]);
				}
	}

	private byte[][] buildMatrix(BigInteger numbers[], int size) {
		byte matrix[][] = new byte[size][size];
		BigInteger temp, prim;
		int j, k;
		for (j = 0; j < size; j++) {
			temp = numbers[j];
			if (temp.signum() < 0) {
				temp = temp.negate();
				matrix[j][0] = 1;
			} else
				matrix[j][0] = 0;
			for (k = 1; k < PRIME_BASE; k++) {
				matrix[j][k] = 0;
				prim = primesBig[k];
				while (temp.mod(prim).compareTo(ZERO) == 0) {
					matrix[j][k]++; // = 1 - matrix[j][k];
					temp = temp.divide(prim);
				}
			}
			for (k = PRIME_BASE; k < size; k++)
				matrix[j][k] = 0;
		}
		return matrix;
	}

	private int[][] buildIdentity(int size) {
		int matrix[][] = new int[size][size / bitChunkSize];
		int j, k;
		for (j = 0; j < size; j++)
			for (k = 0; k < size / bitChunkSize; k++)
				matrix[j][k] = 0;
		k = -1;
		int comparation = 0;
		for (j = 0; j < size; j++) {
			if (j % bitChunkSize == 0) {
				k++;
				comparation = 1;
			} else
				comparation <<= 1;
			matrix[j][k] = comparation;
		}
		return matrix;
	}

	private int[][] flattenMatrix(byte matrix[][]) {
		int m[][] = new int[matrix.length][matrix.length / bitChunkSize];
		int j, k, n;
		int comparation;
		for (j = 0; j < matrix.length; j++)
			for (k = 0; k < matrix.length / bitChunkSize; k++) {
				comparation = 1;
				m[j][k] = 0;
				for (n = 0; n < bitChunkSize; n++) {
					if ((matrix[j][k * bitChunkSize + n] & 1) > 0)
						m[j][k] += comparation;
					comparation <<= 1;
				}
			}
		return m;
	}

	public BigInteger quadraticSieve(int upperBound) {
		BigInteger m, x, y, test, prim;
		BigInteger quadraticN = n;
		int i, j, k, loop, mInt, remainder, p;
		int flats[][] = new int[PRIME_BASE][2];
		double logp;
		long tempflat[];

		decomposedNumbers = new ArrayList();// new Vector();

		// startTime("Solving congruences...");
		for (i = 1; i < PRIME_BASE; i++) {
			tempflat = findFlats(primes[i], quadraticN.mod(primesBig[i])
					.intValue());
			flats[i][0] = (int) tempflat[0];
			flats[i][1] = (int) tempflat[1];
		}
		// endTime();

		int offset = 0;
		int direction = 0;
		int multiplier = 0;
		m = MathsUtils.sqrtBigInt(n).add(ONE);

		// startTime("Starting sieving process...");

		s = new BigInteger[upperBound + 2];
		fs = new BigInteger[upperBound + 2];
		logs = new double[upperBound + 2];
		do {
			switch (direction) {
			case 0:
				direction = 1;
				offset = 0;
				break;
			case 1:
				direction = -1;
				offset = -offset + upperBound;
				break;
			case -1:
				direction = 1;
				offset = -offset;
				break;
			}

			checked += upperBound / 1000;

			for (i = 0; i < upperBound; i++) {
				s[i] = null;
				fs[i] = null;
				logs[i] = 0;
			}

			for (i = 1; i < PRIME_BASE; i++) {
				p = primes[i];
				logp = primeLogs[i];
				mInt = m.mod(primesBig[i]).intValue() + offset;

				if (flats[i][0] >= 0) {
					loop = (int) ((flats[i][0] - mInt) % p);
					if (loop < 0)
						loop += p;
					while (loop < upperBound) {
						logs[loop] += logp;
						loop += p;
					}
					;
				}
				if (flats[i][1] >= 0) {
					loop = (int) ((flats[i][1] - mInt) % p);
					if (loop < 0)
						loop += p;
					while (loop < upperBound) {
						logs[loop] += logp;
						loop += p;
					}
					;
				}
			}

			double TARGET = (double) (Math.log(m.doubleValue())
					+ Math.log(upperBound) - primeLog);

			for (i = 0; i < upperBound; i++) {
				if (logs[i] > TARGET) {
					s[i] = BigInteger.valueOf(i + offset).add(m);
					fs[i] = quadraticF(s[i], quadraticN).abs();
				}
			}

			for (i = 1; i < PRIME_BASE; i++) {
				p = primes[i];
				mInt = m.mod(primesBig[i]).intValue() + offset;

				if (flats[i][0] >= 0) {
					loop = (int) ((flats[i][0] - mInt) % p);
					if (loop < 0)
						loop += p;
					while (loop < upperBound) {
						if (logs[loop] > TARGET) {
							removeHighestPower(loop, primesBig[i]);
							if (decomposed >= PRIME_BASE + ADDITIONAL)
								break;
						}
						loop += p;
					}
				}
				if (flats[i][1] >= 0) {
					loop = (int) ((flats[i][1] - mInt) % p);
					if (loop < 0)
						loop += p;
					while (loop < upperBound) {
						if (logs[loop] > TARGET) {
							removeHighestPower(loop, primesBig[i]);
							if (decomposed >= PRIME_BASE + ADDITIONAL)
								break;
						}
						loop += p;
					}
				}
				if (decomposed >= PRIME_BASE + ADDITIONAL)
					break;
			}

			// writeln("" + checked + "K congruences checked, " + decomposed+
			// " decomposed.");
		} while (decomposed < PRIME_BASE + ADDITIONAL);

		// endTime();

		if (decomposed > PRIME_BASE + ADDITIONAL)
			decomposed = PRIME_BASE + ADDITIONAL;

		// startTime("Recalculating the necessary f(s) values...");

		s = new BigInteger[decomposed + 1];
		fs = new BigInteger[decomposed + 1];
		for (i = 0; i < decomposed; i++) {
			s[i] = ((BigInteger) decomposedNumbers.get(i));
			fs[i] = quadraticF(s[i], quadraticN);
		}
		decomposedNumbers = null;

		byte factors[][] = buildMatrix(fs, decomposed);
		int identity[][] = buildIdentity(decomposed);
		int matrix[][] = flattenMatrix(factors);

		solveMatrix(matrix, identity);

		loop = decomposed - 1;
		do {

			int primefacs[] = new int[PRIME_BASE];
			byte factorLine[] = extractLine(identity, loop);

			test = ONE;
			for (i = 0; i < PRIME_BASE; i++)
				primefacs[i] = 0;
			for (i = 0; i < decomposed; i++) {
				if (factorLine[i] == 1) {
					for (j = 0; j < PRIME_BASE; j++)
						primefacs[j] += (int) factors[i][j];
					test = test.multiply(s[i]).mod(n);
				}
			}

			prim = ONE;
			for (i = 0; i < PRIME_BASE; i++) {
				y = BigInteger.valueOf(primes[i]).modPow(
						BigInteger.valueOf((primefacs[i] >> 1)), n);
				prim = prim.multiply(y).mod(n);
			}

			test = test.mod(n);
			prim = prim.mod(n);

			x = test.add(prim);
			y = test.subtract(prim);

			test = n.gcd(x);
			if ((test.compareTo(ONE) != 0) && (test.compareTo(n) != 0))
				break;
		} while (--loop > PRIME_BASE);

		return test;
	}

}











