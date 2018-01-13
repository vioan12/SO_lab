import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Created by ioan on 1/12/18.
 */
public class MyThread extends Thread
{
    private static Lock lock = new ReentrantLock();
    private int start,end;
    MyThread(int valueofstart, int valueofend)
    {
        start = valueofstart;
        end = valueofend;
    }
    public void run()
    {
                for(int i=start; i<end; i++)
                    if(Main.n_x==0){
                        lock.lock();
                        Main.x[0]=Main.v[i];
                        Main.n_x++;
                        lock.unlock();
            }else{

                int j=0;
                while((Main.v[i]>Main.x[j])&&(j<Main.n_x))
                    j++;
                lock.lock();
                int k;
                if(Main.n_x<Main.v.length-1) {
                    Main.n_x++;
                }
                for(k=Main.n_x;k>j;k--)
                    Main.x[k]=Main.x[k-1];
                Main.x[j]=Main.v[i];
                lock.unlock();
            }
    }
}
