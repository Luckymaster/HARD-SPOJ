import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

class RangeMinimumQuries {

	private static final int K = 17;
	private static final int MAXN = 100001;

	private static int[][] sptable = new int[MAXN][K];

	public static void main(String[] args) throws NumberFormatException, IOException {
		int N, Q;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		List<Integer> inputArray = Stream.of(br.readLine().split(" ")).map(Integer::parseInt)
				.collect(Collectors.toList());

		for (int i = 0; i < N; i++) {
			sptable[i][0] = inputArray.get(i);
		}

		int[] log = new int[MAXN + 1];
		log[1] = 0;
		for (int i = 2; i <= MAXN; i++)
			log[i] = log[i / 2] + 1;

		for (int i = 1; i <= K; i++) {
			for (int j = 0; j + (1 << i) <= N; j++) {
				sptable[j][i] = Math.min(sptable[j][i - 1], sptable[j + (1 << (i - 1))][i - 1]);
			}
		}

		int R, L;
		Q = Integer.parseInt(br.readLine());
		StringBuilder sb = new StringBuilder();
		for (int cs = 0; cs < Q; cs++) {
			String[] ranges = br.readLine().split(" ");
			L = Integer.parseInt(ranges[0]);
			R = Integer.parseInt(ranges[1]);
			int aux = log[R - L + 1];
			int minimum = Math.min(sptable[L][aux], sptable[R - (1 << aux) + 1][aux]);
			sb.append(minimum + "\n");
		}
		System.out.println(sb);

	}

}
