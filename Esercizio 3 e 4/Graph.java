import java.util.*;
import java.io.*;

public class Graph<V, T> {

    private ArrayList<V> vertex;
    private Hashtable<V, Hashtable<V, T>> adj;
    private boolean oriented;

    public Graph(boolean oriented) {
        this.oriented = oriented;
        this.vertex = new ArrayList<V>();
        this.adj = new Hashtable<V, Hashtable<V, T>>();
    }

    public static <V, T> Graph<V, T> create_empty_graph(boolean oriented) {
        return new Graph<V, T>(oriented);
    }

    //Il metodo inserisce il nodo se e solo se esso non è presente all'interno del grafo
    public void add_node(V node) {
        if (!this.has_node(node)) {
            this.vertex.add(node);
            this.adj.put(node, new Hashtable<V, T>());
        }
    }

    //Il metodo inserisce l'arco se e solo se i due nodi start/end esistono
    public void add_edge(V start, V end, T weight) {
        if (this.has_node(start) && this.has_node(end)) {
            if (!this.has_edge(start, end)) {
                if (this.direct_graph()) {
                    this.adj.get(start).put(end, weight);
                } else {
                    this.adj.get(start).put(end, weight);
                    this.adj.get(end).put(start, weight);
                }
            }
        }
    }

    public boolean direct_graph() {
        return this.oriented;
    }

    public boolean has_node(V node) {
        return this.vertex.contains(node);
    }

    public boolean has_edge(V start, V end) {
        if (this.has_node(start) && this.has_node(end)) {
            if (this.direct_graph()) {
                return this.adj.get(start).containsKey(end);
            } else {
                return this.adj.get(start).containsKey(end) && this.adj.get(end).containsKey(start);
            }
        }
        return false;
    }

//  Se il nodo esiste all'interno del grafo, 
//  prima venogno rimossi tutti gli archi 
//  che partono dal nodo stesso e che arrivano 
//  ad esso, poi viene rimosso il nodo
    public void delete_node(V node) {
        if (this.has_node(node)) {
            Object[] temp = this.vertex.toArray();
            for (int i = 0; i < temp.length; i++) {
                if (this.has_edge((V) temp[i], node)) {
                    if (this.direct_graph()) {
                        this.delete_edge((V) temp[i], node);
                    } else {
                        this.delete_edge((V) temp[i], node);
                        this.delete_edge(node, (V) temp[i]);
                    }
                }
            }
            this.adj.get(node).clear();
            this.adj.remove(node);
            this.vertex.remove(node);
        }
    }

    public void delete_edge(V start, V end) {
        if (this.has_edge(start, end)) {
            if (this.direct_graph()) {
                this.adj.get(start).remove(end);
            } else {
                this.adj.get(end).remove(start);
                this.adj.get(start).remove(end);
            }
        }
    }

    public int size_node() {
        return this.vertex.size();
    }

    public int size_edge() {
        int sum = 0;
        Object[] temp = this.vertex.toArray();
        for (int i = 0; i < temp.length; i++) {
            sum += this.adj.get((V) temp[i]).size();
        }
        if (!this.direct_graph()) {
            return sum / 2;
        } else {
            return sum;
        }
    }

    public Set<V> get_all_node() {
        Set<V> s = new HashSet<V>();
        s = this.adj.keySet();
        return s;
    }

//  Il metodo ritorna un'ArrayList di tipo Edge
//  contenente tutti gli archi del grafo
    public ArrayList<Edge> get_all_edge() {
        ArrayList<Edge> array = new ArrayList<Edge>(this.size_edge());
        Iterator<V> iterator1 = this.vertex.iterator();
        for (int i = 0; i < this.size_node(); i++) {
            V node1 = iterator1.next();
            Iterator<V> iterator2 = this.adj.get(node1).keySet().iterator();
            while (iterator2.hasNext()) {
                V node2 = iterator2.next();
                array.add(new Edge(node1, node2, (Comparable<T>) this.get_label(node1, node2)));
            }
        }
        return array;
    }

//  Ritorna un set contenente tutti i nodi adiacenti di node
    public Set<V> adjacent(V node) {
        Set<V> s = new HashSet<V>();
        s = this.adj.get(node).keySet();
        return s;
    }

    public T get_label(V start, V end) {
        return this.adj.get(start).get(end);
    }

    public static void main(String[] args) {
        String path = "italian_dist_graph.csv";
        Graph<String, Float> grafo;
        grafo = create_empty_graph(false);
        try {
            BufferedReader br = new BufferedReader(new FileReader(path));
            String[] linea = br.readLine().split(",");
            while (linea != null) {
                grafo.add_node(linea[0]);
                grafo.add_node(linea[1]);
                grafo.add_edge(linea[0], linea[1], Float.parseFloat(linea[2]));
                String temp = "";
                temp = br.readLine();
                if (temp != null) {
                    linea = temp.split(",");
                } else {
                    linea = null;
                }
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        };
        ArrayList<Edge> edges = new ArrayList<>();
        for (int i = 0; i < edges.size(); i++) {
            System.out.println(i);
        }
        Kruskal k = new Kruskal();
        edges = k.Kruskal(grafo);
        float MAX = 0;
        for (int i = 0; i < edges.size(); i++) {
            MAX += (float) edges.get(i).get_weight();
        }
        System.out.println("Km = " + MAX / 1000 + " Edges.size() = " + edges.size() + " numero nodi: " + grafo.size_node());
    }
}
