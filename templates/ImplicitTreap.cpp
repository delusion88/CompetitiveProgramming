struct Node {
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
