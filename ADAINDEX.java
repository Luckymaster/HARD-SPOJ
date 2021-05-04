

import java.util.*;
import java.io.*;  



class TrieNode {
	public Map<Character, TrieNode> children = new HashMap<>();
	char c;
	boolean isleaf;
	int size=0;

	public TrieNode() {
	}

	public TrieNode(char c) {
		this.c = c;
	}
}

class Solution {

	private TrieNode trieroot;

	public Solution() {
		trieroot = new TrieNode();
	}

	/**
	 * insert aa word in tries
	 * 
	 * @param word
	 */
	public void insert(String word) {
		Map<Character, TrieNode> childern = trieroot.children;

		for (int i = 0; i < word.length(); i++) {
			char c = word.charAt(i);
			TrieNode t;
			if (childern.containsKey(c)) {
				t = childern.get(c);
			} else {
				t = new TrieNode(c);
				childern.put(c, t);
			}
			childern = t.children;
			t.size++;
			if (i == word.length() - 1) {
				t.isleaf = true;
			}

		}
	}

	/**
	 * Seatch word in tries;
	 * 
	 * @param word
	 * @return
	 */
	public TrieNode searchNode(String word) {
		TrieNode t = null;
		Map<Character, TrieNode> childern = trieroot.children;
		for (int i = 0; i < word.length(); i++) {
			if (childern.containsKey(word.charAt(i))) {
				t = childern.get(word.charAt(i));
				childern = t.children;
			} else {
				return new TrieNode();
			}
		}
		return t;

	}

	public boolean search(String word) {
		TrieNode t = searchNode(word);
		return null != t && t.isleaf;
	}

	public boolean starWith(String word) {
		return searchNode(word) == null ? false : true;

	}


	public static void main(String[] args) throws Exception{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String [] wd = br.readLine().split(" ");
		int T = Integer.parseInt(wd[0]);
		int Q = Integer.parseInt(wd[1]);
		Solution tries = new Solution();
		StringBuilder sb = new StringBuilder();
		for (int cs = 1; cs <= T; cs++) {
			String word = br.readLine();
			tries.insert(word);
		}
		for(int i=1;i<=Q;i++){
			String word = br.readLine();
			sb.append(tries.searchNode(word).size + "\n");
		}
		System.out.println(sb);
	}

}
