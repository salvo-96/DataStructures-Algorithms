import org.junit.Test;
import static org.junit.Assert.*;

public class MyUnionFindTest<V> {

    @Test
    public void test_makeSet() {
        UnionFind<Integer> myUnit = new UnionFind<>(1);
        myUnit.parent = myUnit;
        myUnit.rank = 0;
        assertEquals(0, myUnit.rank);
        assertEquals(myUnit.parent, myUnit);
    }

    @Test
    public void test_union() {
        UnionFind<Integer> myUnit = new UnionFind<>(1);
        UnionFind<Integer> myUnit2 = new UnionFind<>(1);
        myUnit.rank = 0;
        myUnit2.rank = 1;
        myUnit.parent = myUnit;
        myUnit2.parent = myUnit2;
        myUnit.link(myUnit.find_set(), myUnit2.find_set());
        assertEquals(myUnit, myUnit);
    }

    @Test
    public void test_link() {
        UnionFind<Integer> myUnit = new UnionFind<>(1);
        UnionFind<Integer> myUnit2 = new UnionFind<>(2);
        myUnit.rank = 1;
        myUnit2.rank = 2;
        myUnit.link(myUnit, myUnit2);
        assertEquals(myUnit.parent, myUnit2);
        myUnit.rank = 2;
        myUnit2.rank = 1;
        myUnit.link(myUnit, myUnit2);
        assertEquals(myUnit2.parent, myUnit);
    }

    @Test
    public void test_find_set() {
        UnionFind<Integer> myUnit = new UnionFind<>(1);
        myUnit.parent = myUnit;
        assertEquals(myUnit.find_set(), myUnit);
        UnionFind<Integer> myUnit2 = new UnionFind<>(2);
        myUnit2.parent = myUnit;
        assertEquals(myUnit2.find_set(), myUnit);
    }
}
