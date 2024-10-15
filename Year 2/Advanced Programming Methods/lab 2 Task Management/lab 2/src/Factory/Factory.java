package Factory;

//import Model.Container;
import Enum.ContainerS;
import Container.Container;

public interface Factory {
    Container createContainer(ContainerS strategy);
}

