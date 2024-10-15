package Decorator;

public class DelayTaskRunner extends AbstractTaskRunner {
    public DelayTaskRunner(TaskRunner taskRunner) {
        super(taskRunner);
    }

    public void executeOneTask(){
        super.executeOneTask();
        try {
            Thread.sleep(3000);

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
