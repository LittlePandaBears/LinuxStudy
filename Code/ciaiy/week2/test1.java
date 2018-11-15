import java.util.*;

public class test1 {
    public static int main(String args[]) {
        int[][] arr1 = new int[3][2];
        int[][] arr2 = new int[3][2];
        Scanner sc = new Scanner(System.in);

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 2; j++) {
                arr1[i][j] = sc.nextInt();
            }
        }
    
    
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 2; j++) {
                arr2[i][j] = sc.nextInt();
            }
        }

        for(int i = 0; i < 3; i++) {
            if(arr1[i].equals(arr2[i]) != false) {
                System.out.println("不匹配");
            }
        }

        return 0;
    }
}