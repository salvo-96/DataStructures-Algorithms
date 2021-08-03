import java.util.*;

public class Kruskal<V, T extends Comparable<T>> {

    //vertex: vertici del grafo g
    //edges: archi del grafo g
    //table: HashTable per associare a ogni vertice il proprio insieme disgiunto di tipo UnionFind
    //mst (Minimun Spanning Tree): insieme degli archi che compongono il cammino minomo del Grafo g
    //g : grafo in input
    public ArrayList<Edge> Kruskal(Graph<V, T> g) {

        Set<V> vertex = new HashSet<V>();
        ArrayList<Edge> edges = new ArrayList<>();
        Hashtable<V, UnionFind<V>> table = new Hashtable<>();
        ArrayList<Edge> mst = new ArrayList<>();

        vertex = g.get_all_node();
        edges = g.get_all_edge();
        Collections.sort(edges);
        Iterator<V> iter = vertex.iterator();

        for (int i = 0; i < vertex.size(); i++) {
            V nodo = iter.next();
            UnionFind<V> u = new UnionFind<V>(nodo);
            u.makeSet();
            table.put(nodo, u);
        }

        for (int j = 0; j < edges.size(); j++) {
            Edge temp = edges.get(j);
            if (table.get(temp.get_start()).find_set() != table.get(temp.get_end()).find_set()) {
                mst.add(temp);
                table.get(temp.get_start()).union(table.get(temp.get_end()));
            }
        }

        return mst;
    }
}
