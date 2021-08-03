public class UnionFind<V> {

    private UnionFind<V> parent;
    private V value;
    private int rank;

    public UnionFind(V value) {
        this.value = value;
    }

    public void makeSet() {
        this.parent = this;
        this.rank = 0;
    }

    public void union(UnionFind<V> y) {
        link(this.find_set(), y.find_set());
    }

    public void link(UnionFind x, UnionFind y) {
        if (x.rank > y.rank) {
            y.parent = x;
        } else {
            x.parent = y;
            if (x.rank == y.rank) {
                y.rank = y.rank + 1;
            }
        }
    }

    public UnionFind<V> find_set() {
        if (this != this.parent) {
            return this.parent.find_set();
        } else {
            return this;
        }
    }
}
