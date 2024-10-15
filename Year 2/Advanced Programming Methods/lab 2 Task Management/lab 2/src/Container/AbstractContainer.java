package Container;
import Model.Task;
public abstract class AbstractContainer implements Container {

    protected Task[] tasks;
    protected int size;

    public void add(Task task) {
        if (size == tasks.length) {
            Task[] newTasks = new Task[size * 2];
            System.arraycopy(tasks, 0, newTasks, 0, size);
            tasks = newTasks;
        }
        tasks[size++] = task;
    }

    public int size(){
        return size;
    }
    public boolean isEmpty(){
        return size == 0;
    }
}
