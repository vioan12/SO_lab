import java.util.*;

public class Main {

    private static final int NR_THREADURI=2;
    public static int []v={8,7,6,5,4,3,2,1};
    public static int x[];
    public static int n_x=0;
    private static Thread[] threads;
    public static Comparator<Integer> comparator = new VectComp();

    public static void main(String[] args) {
        x = new int[v.length];
        threads = new Thread[3];
        for(int i=0; i<threads.length; i++) {
            if (i != threads.length - 1) {
                threads[i] = new MyThread(i * (v.length / NR_THREADURI), (i + 1) * (v.length / NR_THREADURI));
            }else {
                threads[i] = new MyThread(i * (v.length / NR_THREADURI), v.length);
            }
        }
        for(int i=0; i<threads.length; i++){
            threads[i].start();
        }
        for(int i=0; i<threads.length; i++){
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        for(int i=0; i<x.length; i++){
            System.out.print(x[i]+" ");
        }
    }
}
