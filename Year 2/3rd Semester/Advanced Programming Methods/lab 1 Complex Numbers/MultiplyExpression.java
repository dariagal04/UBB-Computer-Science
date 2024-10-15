public class MultiplyExpression extends ComplexExpression {
    public MultiplyExpression(ComplexNumber[] args) {
        super(Operation.MULTIPLY, args);
    }

    public ComplexNumber executeOneOperation(ComplexNumber nr1, ComplexNumber nr2) {
        return nr1.multiply(nr2);
    }
}