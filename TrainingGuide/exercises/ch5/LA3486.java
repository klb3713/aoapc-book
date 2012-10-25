// LA3486 陈锋
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Stack;
import java.util.StringTokenizer;

public class Main {
	static Reader stdin = new Reader(System.in);
	static PrintWriter stdout = new PrintWriter(new BufferedOutputStream(
			System.out, 1024));

	private static final int MAX_TOT = 20000000 + 1, MAXN = 300000 + 1;
	private static final int MAXM = 1000000 + 1;

	public static void main(String[] args) throws IOException {
		final int T = stdin.nextInt();
		Main p = new Main();
		for (int t = 0; t < T; t++)
			p.runTestCase(t);
		stdout.flush();
	}

	private final int[] pre = new int[MAX_TOT], post = new int[MAX_TOT],
			child_start = new int[MAXN], child_end = new int[MAXN];
	private final boolean[] ans = new boolean[MAXM];
	private final StringBuilder buf = new StringBuilder();

	private void runTestCase(int t) throws IOException {
		if (t > 0)
			stdout.println();
		stdout.println(String.format("Case %d:", t + 1));

		final int N = stdin.nextInt();

		int child = 1;
		for (int i = 0; i < N; i++) {
			int num = stdin.nextInt();
			child_start[i] = child_end[i] = 0;
			if (num > 0) {
				child_start[i] = child;
				child += num;
				child_end[i] = child;
			}
		}

		int dfsClock = 1, root = 0;
		Stack<Integer> stack = new Stack<Integer>();
		stack.push(root);
		pre[root] = 0;

		while (!stack.isEmpty()) {
			Integer cur = stack.peek();
			if (pre[cur] != 0) {
				post[cur] = dfsClock++;
				stack.pop();
				continue;
			}

			pre[cur] = dfsClock++;
			for (int i = child_start[cur]; i < child_end[cur]; i++) {
				if (i >= N) { // 叶子结点
					pre[i] = dfsClock++;
					post[i] = dfsClock++;
				} else {
					pre[i] = 0;
					stack.push(i);
				}
			}
		}

		final int M = stdin.nextInt();
		buf.delete(0, buf.length());
		for (int q = 0; q < M; q++) {
			int a = stdin.nextInt();
			int b = stdin.nextInt();
			ans[q] = (pre[a] < pre[b] && post[a] > post[b]);
			buf.append(ans[q] ? "Yes\n" : "No\n");
			// TODO 这里如果直接输出就得TLE了，因为Java默认的System.out输出巨慢，大概光输出时间就得6s
		}

		stdout.print(buf.toString());
	}
}

class Reader {
	final BufferedReader reader;

	StringTokenizer tokenizer;

	public Reader(InputStream input) {
		reader = new BufferedReader(new InputStreamReader(input));
		tokenizer = new StringTokenizer("");
	}

	public String next() throws IOException {
		while (!tokenizer.hasMoreTokens())
			tokenizer = new StringTokenizer(reader.readLine());
		return tokenizer.nextToken();
	}

	public int nextInt() throws IOException {
		return Integer.parseInt(next());
	}

	public double nextDouble() throws IOException {
		return Double.parseDouble(next());
	}
}
