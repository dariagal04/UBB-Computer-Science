public class ComplexNumber {
    private double real;
    private double imag;
    public ComplexNumber(double real, double imag) {
        this.real = real;
        this.imag = imag;
    }

    public ComplexNumber add(ComplexNumber other) {
        return new ComplexNumber(real + other.real, imag + other.imag);
    }
    public ComplexNumber subtract(ComplexNumber other) {
        return new ComplexNumber(real - other.real, imag - other.imag);
    }
    public ComplexNumber multiply(ComplexNumber other) {
        double re = this.real * other.real - this.imag * other.imag;
        double im = this.real * other.imag + this.imag * other.real;
        return new ComplexNumber(re, im);
    }
    public ComplexNumber divide(ComplexNumber other) {
        double re = (this.real * other.real + this.imag * other.imag) / (other.real * other.real + other.imag * other.imag);
        double im = (other.real * this.imag - this.real * other.real / (other.real * other.real + other.imag * other.imag));
        return new ComplexNumber(re, im);
    }

    public String toString() {
        return real + " + " + imag + "i";
    }
}
