package Model;

public class BubbleSort extends AbstractSorter {
    @Override
    public void sort(int[] array) {
        int nr = array.length;
        for (int i = 0; i < nr - 1; i++) {
            for (int j = 0; j < nr - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }
}
