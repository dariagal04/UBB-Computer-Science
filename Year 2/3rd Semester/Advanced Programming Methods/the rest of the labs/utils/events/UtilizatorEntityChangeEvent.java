package src.ubb.javafxlab.utils.events;


import src.ubb.javafxlab.domain.Utilizator;

public class UtilizatorEntityChangeEvent implements Event {
    private ChangeEventType type;
    private Utilizator data, oldData;

    public UtilizatorEntityChangeEvent(ChangeEventType type, Utilizator data) {
        this.type = type;
        this.data = data;
    }
    public UtilizatorEntityChangeEvent(ChangeEventType type, Utilizator data, Utilizator oldData) {
        this.type = type;
        this.data = data;
        this.oldData=oldData;
    }

    public ChangeEventType getType() {
        return type;
    }

    public Utilizator getData() {
        return data;
    }

    public Utilizator getOldData() {
        return oldData;
    }
}