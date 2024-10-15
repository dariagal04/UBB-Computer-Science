package Decorator;

import Container.Container;
import Model.Task;
import Factory.TaskContainerFactory;
//import Factory.Strategy;
import Enum.ContainerS;

public class StrategyTaskRunner implements TaskRunner {

    private Container container;

    public StrategyTaskRunner(ContainerS strategy) {
        container = TaskContainerFactory.getInstance().createContainer(strategy);
    }


    @Override
    public void executeOneTask() {
        Task task = container.remove();
        task.execute();
    }

    @Override
    public void executeAll() {
        while (hasTask()) {
            executeOneTask();
        }
    }

    @Override
    public void addTask(Task t) {
        container.add(t);
    }

    @Override
    public boolean hasTask() {
        return !container.isEmpty();
    }
}
