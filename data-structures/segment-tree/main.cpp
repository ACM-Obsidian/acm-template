struct Node {
	Node *ch[2]; int l, r, same, Max; long long sum;
	inline void Same(int u) {
		Max = u; same = u; sum = (r - l + 1ll) * u;
	}
	inline void Update(void) {
		Max = max(ch[0]->Max, ch[1]->Max);
		sum = ch[0]->sum + ch[1]->sum;
	}
	inline void Push(void) {
		if (ch[1] && same) {
			ch[0]->Same(same);
			ch[1]->Same(same);
			same = 0;
		}
	}
	// 区间整体赋值
	inline void set(int L, int R, int c) {
		if (L > R) return;
		if (L <= l && r <= R) {
			Same(c);
			return;
		}
		Push();
		register int mid = (l + r) >> 1;
		ch[0]->set(L, min(mid, R), c);
		ch[1]->set(max(mid + 1, L), R, c);
		Update();
	}
	// 查询区间和
	inline long long get(int L, int R) {
		if (L > R) return 0;
		if (L <= l && r <= R) return sum;
		Push();
		register int mid = (l + r) >> 1;
		return ch[0]->get(L, min(mid, R)) + ch[1]->get(max(mid + 1, L), R);
	}
	// 分割区间
	inline int split(int L, int R, int c) {
		if (l == r) {
			if (sum >= c) return l-1; else return l;
		}
		Push();
		int mid = (l + r) >> 1;
		if (R <= mid) return ch[0]->split(L, R, c);
		if (L > mid) return ch[1]->split(L, R, c);
		if (ch[0]->Max <= c) return ch[1]->split(mid + 1, R, c);
		else return ch[0]->split(L, mid, c);
	}
}*root, POOL[MAXN * 4], *data;

inline Node* Renew(void) {
	data->ch[0] = data->ch[1] = NULL; data->same = data->Max = data->sum = 0;
	return data++;
}

inline Node* Build(int L, int R) {
	int mid = (L + R) >> 1;
	Node *tmp = Renew();
	tmp->l = L, tmp->r = R;
	if (L == R) {
		tmp->Max = tmp->sum = L - 1;
		return tmp;
	}
	tmp->ch[0] = Build(L, mid);
	tmp->ch[1] = Build(mid + 1, R);
	tmp->Update();
	return tmp;
}

