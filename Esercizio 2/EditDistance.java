import java.io.BufferedReader;
import java.io.FileReader;

public class EditDistance {

    public void EditDistance() {
    }

    //Funzione ricorsiva per il calcolo dell'Edit Distance
    public static int edit_dist(String word2, String word1, int str2_length, int str1_length) {
        if (str1_length == 0) {
            return str2_length;
        }
        if (str2_length == 0) {
            return str1_length;
        }
        if (word1.charAt(str1_length - 1) == word2.charAt(str2_length - 1)) {
            return edit_dist(word2, word1, str2_length - 1, str1_length - 1);
        }
        return 1 + min_distance(edit_dist(word2, word1, str2_length, str1_length - 1),//Inserimento
                edit_dist(word2, word1, str2_length - 1, str1_length),//Cancellazione
                edit_dist(word2, word1, str2_length - 1, str1_length - 1)//Sostituzione
        );
    }

    //Funzione per il calcolo del minimo tra le tre operazioni: Inserimento, Cancellazione, Sostituzione
    public static int min_distance(int insert, int remove, int replace) {
        if (insert <= remove && insert <= replace) {
            return insert;
        } else {
            if (remove <= insert && remove <= replace) {
                return remove;
            } else {
                return replace;
            }
        }
    }

    //Funzione per il calcolo dell'Edit Distance (Versione Programmazione Dinamica)
    public static int edit_dist_dyn(String str1, String str2, int str1_length, int str2_length, int matrix[][]) {
        if (str1_length == 0) {
            return str2_length;
        }
        if (str2_length == 0) {
            return str1_length;
        }
        if (matrix[str1_length - 1][str2_length - 1] != -1) {
            return matrix[str1_length - 1][str2_length - 1];
        }
        if (str1.charAt(str1_length - 1) == str2.charAt(str2_length - 1)) {
            return matrix[str1_length - 1][str2_length - 1] = edit_dist_dyn(str1, str2, str1_length - 1, str2_length - 1, matrix);
        }
        return matrix[str1_length - 1][str2_length - 1] = 1 + min_distance(edit_dist_dyn(str1, str2, str1_length, str2_length - 1, matrix), // Insert 
                edit_dist_dyn(str1, str2, str1_length - 1, str2_length, matrix), // Remove 
                edit_dist_dyn(str1, str2, str1_length - 1, str2_length - 1, matrix) // Replace 
        );
    }

    //Main per l'utilizzo della funzione edit_distance_dyn
    public static void main(String args[]) {
        int matrix[][];
        try {
            BufferedReader b1 = new BufferedReader(new FileReader("correctme.txt"));
            BufferedReader b2 = new BufferedReader(new FileReader("dictionary.txt"));
            String s1, s2;
            s1 = b1.readLine();
            s2 = b2.readLine();
            while (s1 != null) {
                int n;
                matrix = new int[s1.length() + 1][s2.length() + 1];
                for (int i = 0; i < s1.length() + 1; i++) {
                    for (int j = 0; j < s2.length() + 1; j++) {
                        matrix[i][j] = -1;
                    }
                }
                int distance = edit_dist_dyn(s1, s2, s1.length(), s2.length(), matrix);
                String list = "";
                boolean fine = false;
                while (s2 != null && fine == false) {
                    matrix = new int[s1.length() + 1][s2.length() + 1];
                    for (int i = 0; i < s1.length() + 1; i++) {
                        for (int j = 0; j < s2.length() + 1; j++) {
                            matrix[i][j] = -1;
                        }
                    }
                    n = edit_dist_dyn(s1, s2, s1.length(), s2.length(), matrix);
                    if (n == 0) {
                        System.out.println(s1 + " is correct.\n");
                        s1 = b1.readLine();
                        while (s1.equals(".") || s1.equals(",") || s1.equals(":") || s1.equals(";") || s1.equals("'")) {
                            s1 = b1.readLine();
                        }
                        b2.close();
                        b2 = new BufferedReader(new FileReader("dictionary.txt"));
                        s2 = b2.readLine();
                        fine = true;
                    } else {
                        if (n < distance) {
                            distance = n;
                            list = s2 + "\n";
                            s2 = b2.readLine();
                        } else {
                            if (n == distance) {
                                list = list + s2 + "\n";
                                s2 = b2.readLine();
                            } else {
                                s2 = b2.readLine();
                            }
                        }
                    }
                }
                if (fine == false) {
                    System.out.println("Parola di john: " + s1 + "\nLista parola edit distance: \n" + list);
                    s1 = b1.readLine();
                    while (s1.equals(".") || s1.equals(",") || s1.equals(":") || s1.equals(";") || s1.equals("'")) {
                        s1 = b1.readLine();
                    }
                    b2.close();
                    b2 = new BufferedReader(new FileReader("dictionary.txt"));
                    s2 = b2.readLine();
                }
            }
        } catch (Exception ex) {
            System.out.println(ex.getMessage());
            System.exit(1);
        }
    }
}
