inline int bit(int x, unsigned b) {
  return (x >> b) & 1;
}
 
template <
  int maxBit = 30
>
struct Trie {
  struct node {
    int count = 0, subt = 0;
    int nxt[2];
    node() {
      nxt[0] = nxt[1] = -1;
    }
  };
  vector<node> tr;
  Trie() {
    tr.emplace_back();
  }
  void remove(int x) {
    int v = 0;
    for(int i = maxBit; i >= 0; --i) {
      tr[v].subt--;
      v = tr[v].nxt[bit(x, i)];
    }
    tr[v].subt--;
    tr[v].count--;
  }
  void add(int x) {
    int v = 0;
    for(int i = maxBit; i >= 0; --i) {
      int T = bit(x, i);
      tr[v].subt++;
      if(tr[v].nxt[T] == -1) {
        tr[v].nxt[T] = tr.size();
        tr.emplace_back();
      }
      v = tr[v].nxt[T];
    }
    tr[v].subt++;
    tr[v].count++;
  }
  int min(int x) {
    int v = 0;
    int ans = 0;
    for(int i = maxBit; i >= 0; --i) {
      int T = bit(x, i);
      if(tr[v].nxt[T] == -1 || tr[tr[v].nxt[T]].subt == 0) {
        ans |= (1 << i);
        v = tr[v].nxt[T ^ 1];
      } else {
        v = tr[v].nxt[T];
      }
    }
    return ans;
  }
  int max(int x) {
    int v = 0;
    int ans = 0;
    for(int i = maxBit; i >= 0; --i) {
      int T = bit(x, i);
      if(tr[v].nxt[T ^ 1] == -1 || tr[tr[v].nxt[T ^ 1]].subt == 0) {
        v = tr[v].nxt[T];
      } else {
        ans |= (1 << i);
        v = tr[v].nxt[T ^ 1];
      }
    }
    return ans;
  }
};
