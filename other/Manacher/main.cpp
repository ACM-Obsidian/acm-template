inline int Manacher(int a[], int n, int ret[]) {
	int MaxR = -1, where = 0, Ans = 0;
	for (int i = 1; i <= n; i++) {
		int &it = ret[i]; it = 0;
		if (i <= MaxR) it = min(ret[where * 2 - i], MaxR - i);
		while (i - it - 1 >= 1 && i + it + 1 <= n && a[i - it - 1] == a[i + it + 1]) it++;
		if (it + i > MaxR) MaxR = it + i, where = i;
		int tmp = (it << 1) + 1; tmp >>= 1; 
		if (a[i - it] != '$') tmp++; //如果a[i - it]不是分割符
		Ans = max(Ans, tmp);
	}
	return Ans;
}
