const int MAXN = 100010;
struct Node {
	Node *ch[2], *p; int size, value;
	bool rev;
	Node(int t = 0);
	inline bool dir(void) {return p->ch[1] == this;}
	inline void SetC(Node *x, bool d) {
		ch[d] = x; x->p = this;
	}
	inline void Rev(void) {
		swap(ch[0], ch[1]); rev ^= 1;
	}
	inline void Push(void) { 
		if (rev) {
			ch[0]->Rev();
			ch[1]->Rev();
			rev = 0;
		}
	}
	inline void Update(void) { 
		size = ch[0]->size + ch[1]->size + 1;
	}
}Tnull, *null = &Tnull, *fim[MAXN];
// 要记得额外更新null的信息
Node::Node(int _value){ch[0] = ch[1] = p = null; rev = 0;}
inline bool isRoot(Node *x) {return x->p == null || (x != x->p->ch[0] && x != x->p->ch[1]);}
inline void rotate(Node *x) {
	Node *p = x->p; bool d = x->dir();
	p->Push(); x->Push();
	if (!isRoot(p)) p->p->SetC(x, p->dir()); else x->p = p->p;
	p->SetC(x->ch[!d], d);
	x->SetC(p, !d);
	p->Update();
}
inline void splay(Node *x) {
	x->Push();
	while (!isRoot(x)) {
		if (isRoot(x->p)) rotate(x);
		else {
			if (x->dir() == x->p->dir()) {rotate(x->p); rotate(x);} 
			else {rotate(x); rotate(x);}
		}
	}
	x->Update();
}
inline Node* Access(Node *x) {
	Node *t = x, *q = null;
	for (; x != null; x = x->p) {
		splay(x); x->ch[1] = q; q = x;
	}
	splay(t); //info will be updated in the splay;
	return q;
}
inline void Evert(Node *x) {
	Access(x); x->Rev();
}
inline void link(Node *x, Node *y) {
	Evert(x); x->p = y;
}
inline Node* getRoot(Node *x) {
	Node *tmp = x;
	Access(x);
	while (tmp->Push(), tmp->ch[0] != null) tmp = tmp->ch[0];
	splay(tmp);
	return tmp;
}
// 一定要确定x和y之间有边
inline void cut(Node *x, Node *y) { 	
	Access(x); splay(y);
	if (y->p != x) swap(x, y);
	Access(x); splay(y);
	y->p = null;
}
inline Node* getPath(Node *x, Node *y) {
	Evert(x); Access(y);
	return y;
}
inline void clear(void) {
	null->rev = 0; null->sie = 0; null->value = 0;
}
