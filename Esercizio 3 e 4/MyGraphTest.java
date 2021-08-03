import org.junit.Test;
import static org.junit.Assert.*;

public class MyGraphTest<V,T>{

//    @Test
//    public void testcreate_empty_graph() {
//        Graph<Integer, String> g = new Graph<>(true);
//        g = g.create_empty_graph(true);
//        assertEquals(g, g.create_empty_graph(true));
//    }

    @Test
    public void test_add_node() {
        Graph<Integer, String> g = new Graph<>(true);
        g = g.create_empty_graph(true);
        g.add_node(10);
        assertTrue(g.has_node(10));
    }
    
    @Test
    public void test_add_edge() {
        Graph<Integer, String> g = new Graph<>(true);
        g = g.create_empty_graph(true);
        g.add_node(1);
        g.add_node(2);
        g.add_edge(1, 2, "adisabeba");
        assertTrue(g.has_edge(1, 2));
    }
    @Test
    public void test_delete_node() {
        Graph<Integer, String> g = new Graph<>(true);
        g = g.create_empty_graph(true);
        g.add_node(1);
        assertTrue(g.has_node(1));
    }
    
    @Test
    public void test_delete_edge() {
        Graph<Integer, String> g = new Graph<>(true);
        g = g.create_empty_graph(true);
        g.add_node(1);
        g.add_node(2);
        g.add_edge(1, 2, "adisabeba");
        g.delete_edge(1, 2);
        assertFalse(g.has_edge(1, 2));
    }

    @Test
    public void test_size_node() {
        Graph<Integer, String> g = new Graph<>(true);
        g = g.create_empty_graph(true);
        g.add_node(1);
        assertEquals(1, g.size_node());
    }

    @Test
    public void test_size_edge() {
        Graph<Integer, String> g = new Graph<>(true);
        g = g.create_empty_graph(true);
        g.add_node(1);
        g.add_node(2);
        g.add_edge(1, 2, "adisabeba");
        assertEquals(1, g.size_edge());
    }

    @Test
    public void test_get_label() {
        Graph<Integer, String> g = new Graph<>(true);
        g = g.create_empty_graph(true);
        g.add_node(1);
        g.add_node(2);
        g.add_edge(1, 2, "adisabeba");
        assertEquals("adisabeba", g.get_label(1, 2));
    }
}
