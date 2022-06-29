std::mt19937_64 rnd64(
    std::chrono::high_resolution_clock::now().time_since_epoch().count());
 
const int Inf       = 0x4f4f4f4f;
const long long inf = 1100000000000000000;
 
struct Node {
    int x, sz, y;
    Node* l = 0;
    Node* r = 0;
    Node(int val): x(val), y(rand()), sz(1) { }
};
 
Node* root;
 
int sz(Node* t) {
    return t ? t->sz : 0;
}
 
void upd(Node* t) {
    t->sz = sz(t->l) + sz(t->r) + 1;
}
 
Node* merge(Node* l, Node* r) {
    if(!l)
        return r;
    if(!r)
        return l;
    if(l->y > r->y) {
        l->r = merge(l->r, r);
        upd(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        upd(r);
        return r;
    }
}
 
pair<Node*, Node*> split(Node* t, int x) {
    if(!t)
        return {0, 0};
    if(t->x <= x) {
        auto [l, r] = split(t->r, x);
        t->r = l;
        upd(t);
        return {t, r};
    } else {
        auto [l, r] = split(t->l, x);
        t->l = r;
        upd(t);
        return {l, t};
    }
}
 
Node* insert(Node* t, int x) {
    auto [L, R] = split(t, x);
    return merge(merge(L, new Node(x)), R);
}
 
Node* remove(Node* t, int x) {
    auto [L, R] = split(t, x);
    auto [l, r] = split(L, x - 1);
    return merge(l, R);
}
 
int kth(Node* t, int x) {
    if(x < sz(t->l))
        return kth(t->l, x);
    else if(x > sz(t->l))
        return kth(t->r, x - sz(t->l) - 1);
    return t->x;
}
