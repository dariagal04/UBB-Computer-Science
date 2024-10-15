package Model;
import java.util.Arrays;
import Enum.SortStrategy;

public class SortingTask extends Task {

    private AbstractSorter abstractSorter;
    private final int[] array;
    private final SortStrategy sortStrategy;

    public SortingTask(String taskID, String description,int[] array, SortStrategy sortStrategy) {
        super(taskID, description);
        this.array = array;
        this.sortStrategy = sortStrategy;

        switch (sortStrategy) {
            case BUBBLESORT -> abstractSorter = new BubbleSort();
            case QUICKSORT -> abstractSorter = new QuickSort();
            default -> {

            }
        }
    }
    public void execute(){
        abstractSorter.sort(array);
        System.out.println(Arrays.toString(array));
    }
}


