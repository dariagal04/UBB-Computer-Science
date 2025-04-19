package src.ubb.javafxlab.utils;

import src.ubb.javafxlab.utils.events.Event;

public interface Observer<E extends Event> {
    void update(E e);
}