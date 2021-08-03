import java.util.*;

public class Edge<V, T extends Comparable> implements Comparable<Edge> {

    private V start;
    private V end;
    private T weight;

    public Edge(V start, V end, T weight) {
        this.start = start;
        this.end = end;
        this.weight = weight;
    }

    public V get_start() {
        return this.start;
    }

    public V get_end() {
        return this.end;
    }

    public T get_weight() {
        return this.weight;
    }

    //Implementazione del metodo compareTo(): ciò permette l'utilizzo del metodo .sort() di ArrayList per il proprio ordinamento
    @Override
    public int compareTo(Edge e) {
        return this.get_weight().compareTo(e.get_weight());
    }
}
