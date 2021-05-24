import java.io.DataInputStream;
import java.io.InputStream;
import java.util.Arrays;

class PolyMul {

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

	static class Complex {

		public double real;
		public double imaginary;

		public Complex() {
			this.real = 0.0;
			this.imaginary = 0.0;
		}

		public Complex(double r, double i) {
			this.real = r;
			this.imaginary = i;
		}

		public Complex multiply(final Complex x) {
			final Complex copy = new Complex(this.real, this.imaginary);
			copy.real = this.real * x.real - this.imaginary * x.imaginary;
			copy.imaginary = this.imaginary * x.real + this.real * x.imaginary;
			return copy;
		}

		public Complex division(Complex temp) {
			final Complex result = new Complex();
			result.real = (((this.real * temp.real) + (this.imaginary * temp.imaginary))
					/ (Math.pow(temp.real, 2) + Math.pow(temp.imaginary, 2)));
			result.imaginary = (((this.real * temp.imaginary) - (this.imaginary * temp.real))
					/ (Math.pow(temp.real, 2) + Math.pow(temp.imaginary, 2)));
			return result;
		}

		public Complex add(final Complex x) {
			final Complex copy = new Complex(this.real, this.imaginary);
			copy.real += x.real;
			copy.imaginary += x.imaginary;
			return copy;
		}

		public Complex sub(final Complex x) {
			final Complex copy = new Complex(this.real, this.imaginary);
			copy.real -= x.real;
			copy.imaginary -= x.imaginary;
			return copy;
		}

		public double abs() {
			return Math.sqrt(this.real * this.real + this.imaginary * this.imaginary);
		}

		public String toString() {
			return "(" + this.real + "," + this.imaginary + ")";
		}

		public static Complex polar(final double rho, final double theta) {
			return (new Complex(rho * Math.cos(theta), rho * Math.sin(theta)));
		}

		public Complex conjugate() {
			final Complex copy = new Complex(this.real, this.imaginary);
			copy.imaginary = copy.imaginary * -1;
			return copy;

		}

		public void print() {
			final Complex copy = new Complex(this.real, this.imaginary);
			System.out.print("( " + copy.real + "," + copy.imaginary + ") ,");

		}

		public Complex scal(Double dFactor) {
			final Complex copy = new Complex(this.real, this.imaginary);

			copy.real = dFactor * copy.real;
			copy.imaginary = dFactor * copy.imaginary;

			return (copy);
		}

		public Complex Div(Complex cB) {
			Complex div = new Complex();
			double dR, dDen;

			if (Math.abs(cB.real) >= Math.abs(cB.imaginary)) {
				dR = cB.imaginary / cB.real;
				dDen = cB.real + dR * cB.imaginary;
				div.real = (this.real + dR * this.imaginary) / dDen;
				div.imaginary = (this.imaginary - dR * this.real) / dDen;
			} else {
				dR = cB.real / cB.imaginary;
				dDen = cB.imaginary + dR * cB.real;
				div.real = (dR * this.real + this.imaginary) / dDen;
				div.imaginary = (dR * this.imaginary - this.real) / dDen;
			}

			return (div);
		}
	}

	public static Complex[] cooleyTukeyFFT(Complex[] x, boolean invert) {
		int n = x.length;

		// base case
		if (n == 1)
			return new Complex[] { x[0] };

		// radix 2 Cooley-Tukey FFT
		if (n % 2 != 0) {
			throw new IllegalArgumentException("n is not a power of 2");
		}

		// compute FFT of even terms
		Complex[] even = new Complex[n / 2];
		for (int k = 0; k < n / 2; k++) {
			even[k] = x[2 * k];
		}
		Complex[] evenFFT = cooleyTukeyFFT(even, false);

		// compute FFT of odd terms
		Complex[] odd = even; // reuse the array (to avoid n log n space)
		for (int k = 0; k < n / 2; k++) {
			odd[k] = x[2 * k + 1];
		}
		Complex[] oddFFT = cooleyTukeyFFT(odd, false);

		// combine
		Complex[] y = new Complex[n];
		for (int k = 0; k < n / 2; k++) {
			double kth = -2 * k * Math.PI / n;
			Complex wk = new Complex(Math.cos(kth), Math.sin(kth));
			y[k] = evenFFT[k].add(wk.multiply(oddFFT[k]));
			y[k + n / 2] = evenFFT[k].sub(wk.multiply(oddFFT[k]));
		}

		// not required ifft is already in place
		if (invert) {
			for (Complex db : y) {
				db = db.scal(1.0 / n);
			}
		}
		return y;
	}

	public static long[] multiply(int[] a, int[] b) {

		int n = 1;
		while (n < a.length + b.length)
			n <<= 1;
		Complex[] fa = new Complex[n];
		Complex[] fb = new Complex[n];

		Arrays.fill(fa, new Complex());
		Arrays.fill(fb, new Complex());

		for (int i = 0; i < a.length; i++) {
			fa[i] = new Complex(a[i], 0.0);
		}

		for (int i = 0; i < b.length; i++) {
			fb[i] = new Complex(b[i], 0.0);
		}

		fa = cooleyTukeyFFT(fa, false);
		fb = cooleyTukeyFFT(fb, false);

		for (int i = 0; i < n; i++) {
			fa[i] = fa[i].multiply(fb[i]);
		}

		fa = ifft(fa);

		long[] res = new long[n];
		for (int i = 0; i < n; i++) {
			res[i] = (long) Math.round(fa[i].real);
		}

		return res;
	}

	// compute the inverse FFT of x[], assuming its length n is a power of 2
	public static Complex[] ifft(Complex[] x) {
		int n = x.length;
		Complex[] y = new Complex[n];

		// take conjugate
		for (int i = 0; i < n; i++) {
			y[i] = x[i].conjugate();
		}

		// compute forward FFT
		y = cooleyTukeyFFT(y, false);

		// take conjugate again
		for (int i = 0; i < n; i++) {
			y[i] = y[i].conjugate();
		}

		// divide by n
		for (int i = 0; i < n; i++) {
			y[i] = y[i].scal((1.0 / n));
		}

		return y;

	}

	public static void main(String[] args) throws Exception {

		Parser sc = new Parser(System.in);
		int T = sc.nextInt();

		for (int cs = 1; cs <= T; cs++) {

			StringBuilder sb = new StringBuilder();
			int n = sc.nextInt();
			int[] a = new int[n + 1];
			int[] b = new int[n + 1];

			for (int ai = 0; ai <= n; ai++) {
				a[ai] = sc.nextInt();
			}
			for (int bi = 0; bi <= n; bi++) {
				b[bi] = sc.nextInt();
			}

			long[] res = multiply(a, b);

			for (int i = 0; i <= 2 * n; i++) {
				sb.append(res[i] + " ");
			}
			System.out.println(sb);

		}

	}

}
