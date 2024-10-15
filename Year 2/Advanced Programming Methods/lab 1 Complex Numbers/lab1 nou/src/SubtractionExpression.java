public class SubtractionExpression extends ComplexExpression{
    public SubtractionExpression(ComplexNumber[] args) {
        super(Operation.SUBTRACT, args);
    }

    public ComplexNumber executeOneOperation(ComplexNumber nr1, ComplexNumber nr2) {
        return nr1.subtract(nr2);
    }
}
