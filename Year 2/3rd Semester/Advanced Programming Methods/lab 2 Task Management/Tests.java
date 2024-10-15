import Decorator.DelayTaskRunner;
import Decorator.PrinterTaskRunner;
import Decorator.StrategyTaskRunner;
import Decorator.TaskRunner;
import Enum.*;
import Model.*;
import java.time.LocalDateTime;

public class Tests {

    static private void testSort(){
        System.out.println("Sorting task BUBBLESORT:");
        Task task1 = new SortingTask("1", "bubblesort", new int[]{3,2,4,5,1}, SortStrategy.BUBBLESORT);
        task1.execute();

        System.out.println("Sorting task QUICKSORT:");
        Task task2 = new SortingTask("2", "quicksort", new int[]{3,2,4,5,1}, SortStrategy.QUICKSORT);
        task2.execute();
    }

    static private Task[] messages(){
        Task t1 = new MessageTask("1","mesaj1","nota test este 9", "Ana", "Maria",LocalDateTime.of(2024,10,14,8,51));
        Task t2 = new MessageTask("2","mesaj2","nota test este 10", "Ana", "Alexia",LocalDateTime.of(2024,10,14,8,52));
        Task t3 = new MessageTask("3","mesaj3","nota test este 8", "Ana", "George",LocalDateTime.of(2024,10,14,8,53));
        return new Task[]{t1,t2,t3};
    }

    static public void runStrategy(String[] args){
        testSort();
        if(args.length !=0){
            TaskRunner delayTaskRunner, printerTaskRunner,strategyTaskRunner;
            if(args[0].equals("FIFO")){
                delayTaskRunner = new StrategyTaskRunner(ContainerS.FIFO);
                printerTaskRunner = new StrategyTaskRunner(ContainerS.FIFO);
                strategyTaskRunner = new StrategyTaskRunner(ContainerS.FIFO);
            }
            else if(args[0].equals("LIFO")){
                delayTaskRunner = new StrategyTaskRunner(ContainerS.LIFO);
                printerTaskRunner = new StrategyTaskRunner(ContainerS.LIFO);
                strategyTaskRunner = new StrategyTaskRunner(ContainerS.LIFO);
            }
            else return;

            TaskRunner dtr = new DelayTaskRunner(delayTaskRunner);
            TaskRunner ptr = new PrinterTaskRunner(printerTaskRunner);

            for (Task t : messages()) {
                dtr.addTask(t);
                //System.out.println(t);
                ptr.addTask(t);
                strategyTaskRunner.addTask(t);
            }
          dtr.executeAll();
          ptr.executeAll();
          strategyTaskRunner.executeAll();
        }
    }
}
