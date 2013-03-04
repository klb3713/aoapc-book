// UVa11294 Wedding
// 陈锋
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Stack;
import java.util.StringTokenizer;

public class Main {
	private static Reader stdin = new Reader(System.in);

	public static void main(String[] args) throws IOException {
		while (true) {
			int n = stdin.getInt();
			int a = stdin.getInt();

			if (n == 0)
				break;

			TwoSAT runner = new TwoSAT(n);
			// 对于第i对夫妻(i = 0 to n - 1)来说，xi = (i的wife坐在bride的同一侧)
			// 所以一开始就要限定，x0 = true
			runner.init(0, true);

			for (int i = 0; i < a; i++) {
				String str1 = stdin.next();
				String str2 = stdin.next();

				// 3h 7h
				// 3h 或者 7h必须有一个坐在bride同一侧 3 = false || 7 == false
				// 5w 3w 5w 或者 3w必须有一个坐在bride同一侧
				// 5 = true || 3 == true 7h 3w
				// 7h 或者 3w必须有一个坐在bride同一侧 7 = false || 3 == true

				int len = str1.length();
				int x = Integer.parseInt(str1.substring(0, len - 1));
				boolean xval = (str1.charAt(len - 1) == 'w');

				len = str2.length();
				int y = Integer.parseInt(str2.substring(0, len - 1));
				boolean yval = (str2.charAt(len - 1) == 'w');

				runner.add_clause(x, xval, y, yval);
			}

			boolean result = runner.solve();
			StringBuilder buf = new StringBuilder();
			if (result) {
				buf.delete(0, buf.length());
				boolean[] marks = runner.Marks;
				for (int i = 1; i < n; i++) {
					if (i > 1)
						buf.append(' ');
					buf.append(i);
					buf.append(marks[i * 2] ? 'w' : 'h');
				}
			} else
				buf.append("bad luck");

			System.out.println(buf.toString());
		}
	}
}

class TwoSAT {
	public final int n;
	private final List<List<Integer>> G;
	public final boolean[] Marks;
	private final Stack<Integer> stack = new Stack<Integer>();

	public TwoSAT(int n) {
		this.n = n;
		G = new ArrayList<List<Integer>>();
		for (int i = 0; i < 2 * n; i++)
			G.add(new ArrayList<Integer>());
		Marks = new boolean[2 * n];
		Arrays.fill(Marks, false);
	}

	void init(int x, boolean xval) {
		x = x * 2 + (xval ? 0 : 1);
		dfs(x);
		stack.clear();
	}

	boolean dfs(int x) {
		if (Marks[x ^ 1])
			return false;
		if (Marks[x])
			return true;
		Marks[x] = true;
		stack.push(x);

		List<Integer> children = G.get(x);
		for (Integer next : children)
			if (!dfs(next))
				return false;
		return true;
	}

	// x = xval or y = yval
	void add_clause(int x, boolean xval, int y, boolean yval) {
		x = x * 2 + (xval ? 0 : 1);
		y = y * 2 + (yval ? 0 : 1);
		G.get(x ^ 1).add(y);
		G.get(y ^ 1).add(x);
	}

	boolean solve() {
		for (int i = 0; i < 2 * n; i += 2) {
			if (!Marks[i] && !Marks[i + 1]) {
				stack.clear();
				if (!dfs(i)) {
					while (!stack.isEmpty())
						Marks[stack.pop()] = false;
					if (!dfs(i + 1))
						return false;
				}
			}
		}

		return true;
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

	public int getInt() throws IOException {
		return Integer.parseInt(next());
	}

	public double nextDouble() throws IOException {
		return Double.parseDouble(next());
	}
}
