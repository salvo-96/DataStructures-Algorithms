import org.junit.Test;
import static org.junit.Assert.*;

public class MyEditDistanceTest {

    @Test
    public void testEdit_dist() {
        EditDistance myUnit = new EditDistance();
        int result = myUnit.edit_dist("one", "one", 3, 3);
        assertEquals(0, result);
    }

    @Test
    public void testMin_distance() {
        EditDistance myUnit = new EditDistance();
        int result = myUnit.min_distance(0, 1, 2);
        assertEquals(0, result);
        result = myUnit.min_distance(1, 0, 2);
        assertEquals(0, result);
        result = myUnit.min_distance(1, 1, 0);
        assertEquals(0, result);
    }

    @Test
    public void testEdit_dist_dyn() {
        EditDistance myUnit = new EditDistance();
        int[][] matrix = new int[4][4];
        int result = myUnit.edit_dist_dyn("one", "one", 3, 3, matrix);
        assertEquals(0, result);
    }
}
