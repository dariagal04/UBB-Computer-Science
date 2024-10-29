package org.example.domain;

import java.util.Objects;

public class Pereche<u1, u2> {
    private u1 _1;
    private u2 _2;
    public Pereche(u1 _1, u2 _2) {
        this._1 = _1;
        this._2 = _2;
    }
    public u1 get_1() {
        return _1;
    }
    public void set_1(u1 _1) {
        this._1 = _1;
    }
    public u2 get_2() {
        return _2;
    }
    public void set_2(u2 _2) {
        this._2 = _2;
    }

    @Override
    public String toString() {
        return ""+_1+""+_2;
    }

    @Override
    public boolean equals(Object obj) {
        return this._1.equals(((Pereche)obj)._1) && this._2.equals(((Pereche)obj)._2);
    }

    @Override
    public int hashCode() {
        return Objects.hash(_1, _2);
    }
}
