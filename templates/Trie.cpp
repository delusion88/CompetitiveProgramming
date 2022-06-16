inline int bit (int x, unsigned b) {
    return (x >> b) & 1;
}
 
template <
    int maxBit = 30
>
struct Trie {
    struct node {
        int count = 0, subt = 0;
        int nxt[2];
        node () {
            nxt[0] = nxt[1] = -1;
        }
    };
    vector<node> tr;
    Trie () {
        tr.emplace_back();
    }
    void remove (int x) {
        int v = 0;
        for (int i = maxBit; i >= 0; --i) {
            tr[v].subt--;
            v = tr[v].nxt[bit(x, i)];
        }
        tr[v].subt--;
        tr[v].count--;
    }
    void add (int x) {
        int v = 0;
        for (int i = maxBit; i >= 0; --i) {
            int T = bit(x, i);
            tr[v].subt++;
            if (tr[v].nxt[T] == -1) {
                tr[v].nxt[T] = tr.size();
                tr.emplace_back();
            }
            v = tr[v].nxt[T];
        }
        tr[v].subt++;
        tr[v].count++;
    }
    int min (int x) {
        int v = 0;
        int ans = 0;
        for (int i = maxBit; i >= 0; --i) {
            int T = bit(x, i);
            if (tr[v].nxt[T] == -1 || tr[tr[v].nxt[T]].subt == 0) {
                ans |= (1 << i);
                v = tr[v].nxt[T ^ 1];
            }
            else {
                v = tr[v].nxt[T];
            }
        }
        return ans;
    }
    int max (int x) {
        int v = 0;
        int ans = 0;
        for (int i = maxBit; i >= 0; --i) {
            int T = bit(x, i);
            if (tr[v].nxt[T ^ 1] == -1 || tr[tr[v].nxt[T ^ 1]].subt == 0) {
                v = tr[v].nxt[T];
            }
            else {
                ans |= (1 << i);
                v = tr[v].nxt[T ^ 1];
            }
        }
        return ans;
    }
};struct Node {
    int sz, y, val, chg, push;
    Node* l = 0;
    Node* r = 0;
    Node (int val): val(val), push(0), chg(-1), y(rand()), sz(1) { }
};
 
Node* root;
 
int sz (Node* t) {
    return t ? t->sz : 0;
}
 
void upd (Node* t) {
    t->sz = sz(t->l) + sz(t->r) + 1;
}
 
void push (Node* t) {
    if (t->l)
        t->l->push += t->push;
    if (t->r)
        t->r->push += t->push;
    t->chg += t->push;
    t->push = 0;
}
 
Node* merge (Node* l, Node* r) {
    if (!l)
        return r;
    if (!r)
        return l;
    if (l->y > r->y) {
        push(l);
        l->r = merge(l->r, r);
        upd(l);
        return l;
    }
    else {
        push(r);
        r->l = merge(l, r->l);
        upd(r);
        return r;
    }
}
 
pair<Node*, Node*> split(Node* t, int x) {
    if (!t)
        return {0, 0};
    push(t);
    if (sz(t->l) >= x) {
        auto [l, r] = split(t->l, x);
        t->l = r;
        upd(t);
        return {l, t};
    }
    else {
        auto [l, r] = split(t->r, x - sz(t->l) - 1);
        t->r = l;
        upd(t);
        return {t, r};
    }
}
 
Node* cut (int l, int r) {
    auto [t1, t2] = split(root, r);
    auto [t3, t4] = split(t1, l - 1);
    root = merge(t3, t2);
    return t4;
}
 
void ins (Node* t, int x) {
    auto [l, r] = split(root, x);
    t->push++;
    root = merge(l, merge(t, r));
}

