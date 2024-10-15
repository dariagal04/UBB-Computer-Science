package Model;

public class QuickSort extends AbstractSorter {
    @Override
    public void sort(int[] array) {

    }

    public void QuickSort(int[] array, int left, int right) {
        if (left < right) {
            int pivot = partition(array, left, right);
            QuickSort(array, left, pivot - 1);
            QuickSort(array, pivot + 1, right);

        }
    }

    private int partition(int[] array, int left, int right) {
        int pivot = array[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (array[j] < pivot) {
                i++;
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        int temp = array[right];
        array[right] = array[i];
        array[i] = temp;
        return i;
    }
}

