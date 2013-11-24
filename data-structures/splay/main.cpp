// 最大可能的节点数
const int MAXN = 100010;

// 每个打标记的操作就是更新这个节点的信息，然后对子节点打标记

struct Node {
	Node *ch[2], *p; int size, value;
	bool rev;
	inline bool dir(void) {return p->ch[1] == this;}
	inline void SetC(Node *x, bool d) {
		ch[d] = x; x->p = this;
	}
	inline void Rev(void) {
		swap(ch[0], ch[1]); rev ^= 1;
	}
	// null永远不会push
	inline void Push(void) { 
		if (rev) {
			ch[0]->Rev();
			ch[1]->Rev();
			rev = 0;
		}
	}
	// null永远不会update
	inline void Update(void) { 
		size = ch[0]->size + ch[1]->size + 1;
	}
	inline void initInfo(void) {
		rev = 0;
	}
}Tnull, *null = &Tnull, *data, POOL[MAXN];

class Splay {public:
	Node *root;
	inline void rotate(Node *x) {
		Node *p = x->p; bool d = x->dir();
		p->Push(); x->Push();
		p->p->SetC(x, p->dir());
		p->SetC(x->ch[!d], d);
		x->SetC(p, !d);
		p->Update();
	}

	inline void splay(Node *x, Node *G) {
		if (G == null) root = x;
		while (x->p != G) {
			if (x->p->p == G) rotate(x); else {
				if (x->dir() == x->p->dir()) {rotate(x->p); rotate(x);}
				else {rotate(x); rotate(x);}
			}
		}
		x->Push();
		x->Update();
	}

	inline Node* Renew(int value) {
		Node *ret = data++;
		ret->ch[0] = ret->ch[1] =ret->p = null;
		ret->size = 1; ret->value = value;
		ret->initInfo();
		return ret;
	}

	inline Node* getMin(Node *x) {Node *tmp = x; while (tmp->ch[0] != null) tmp = tmp->ch[0]; return tmp;}
	inline Node* getMax(Node *x) {Node *tmp = x; while (tmp->ch[1] != null) tmp = tmp->ch[1]; return tmp;}

	// 查询第k大
	inline Node* getKth(int k) {
		Node *tmp = root; 
		assert(k > 0 && k <= root->size);
		while (true) {
			tmp->Push();
			if (tmp->ch[0]->size + 1 == k) return tmp;
			if (tmp->ch[0]->size >= k) tmp = tmp->ch[0]; 
			else k -= tmp->ch[0]->size + 1, tmp = tmp->ch[1];
		}
	}

	// 以下为splay当作平衡树使用

	// 查找树中value = v的元素, 返回之后splay
	inline Node* find(int v) {
		Node *tmp = root;
		while (tmp != null) {
			tmp->Push();
			if (tmp->value == v) return tmp;
			if (v < tmp->value) tmp = tmp->ch[0]; else tmp = tmp->ch[1];
		}
		return null;
	}

	// 统计有多少元素小于等于v, 当flag = 1时，统计多少元素严格小于v, 一定要记得splay最后的那个tmp
	inline int Count(int v, bool flag = 0) {
		Node *tmp = root, *last = null; int ret = 0;
		while (tmp != null) {
			tmp->Push();
			last = tmp;
			if ((!flag && tmp->value > v) || (flag && tmp->value >= v)) {
				tmp = tmp->ch[0];
			} else ret += tmp->ch[0]->size + 1, tmp = tmp->ch[1];
		}
		if (last != null) splay(last, null);
		return ret;
	}

	// 删除x这个结点
	inline void erase(Node* x) {
		splay(x, null);
		if (x->ch[0] == null || x->ch[1] == null) {
			int d = x->ch[1] != null;
			root = x->ch[d]; root->p = null;
			return;
		}
		Node *L = getMax(x->ch[0]), *R = getMax(x->ch[1]);
		splay(L, x); splay(R, x);
		L->SetC(R, 1); L->p = null; root = L;
		L->Update();
	}

	// 插入一个值为value的节点，初始要以Insert(root, null, value)来调用, 返回之后splay
	inline Node* Insert(Node *&now, Node* father, int value) {
		if (now == null) {
			now = Renew(value); now->p = father;
			return now;
		}
		Node *ret;
		now->Push();
		if (value <= now->value) ret = Insert(now->ch[0], now, value);
		else ret = Insert(now->ch[1], now, value);
		now->Update();
		return ret;
	}

	// 以下为splay维护序列, 初始要在原序列中放入一个-inf和inf来防止边界条件

	// 得到原数列中[l,r]区间对应的结点，如果l == r + 1则表示是一个空区间
	inline Node* getInterval(int l, int r) {
		assert(l <= r + 1);
		Node *L = getKth(l), *R = getKth(r + 2);
		splay(L, null); splay(R, L);
		return R->ch[0];
	}

	// 删除一段区间[l,r]
	inline void eraseInterval(int l, int r) {
		getInterval(l, r);
		root->ch[1]->ch[0] = null;
		root->ch[1]->Update();
		root->Update();
	}

	// 在位置l的后面插入一段区间x (0 <= l <= n)
	inline void insertInterval(int l, Node *x) {
		Node *L = getKth(l + 1), *R = getKth(l + 2);
		splay(L, null); splay(R, L);
		R->SetC(x, 0);
		R->Update(); L->Update();
	}

	// 把数列a的[l,r]构建为一个splay
	inline Node* Build(int l, int r, int a[]) {
		if (l > r) return null;
		int mid = (l + r) >> 1;
		Node *ret = Renew(a[mid]);
		if (l == r) return ret;
		ret->SetC(Build(l, mid - 1, a), 0);
		ret->SetC(Build(mid + 1, r, a), 1);
		ret->Update();
		return ret;
	}
}T;

void clear(void) {
	data = POOL;
	T.root = null;
}

