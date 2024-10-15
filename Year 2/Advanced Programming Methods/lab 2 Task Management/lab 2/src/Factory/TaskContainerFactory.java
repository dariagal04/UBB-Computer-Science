package Factory;


import Container.*;
import Enum.ContainerS;


public class TaskContainerFactory implements Factory {

    static TaskContainerFactory factory = null;
    private TaskContainerFactory(){}

    static public TaskContainerFactory getInstance() {
        if (factory == null) {
            factory = new TaskContainerFactory();
        }
        return factory;
    }

    @Override
    public Container createContainer(ContainerS strategy) {
        if (strategy == ContainerS.FIFO) {
            return new QueueContainer();
           // return null;
        } else {
            return new StackContainer();
        }
        //return null;
    }
}
