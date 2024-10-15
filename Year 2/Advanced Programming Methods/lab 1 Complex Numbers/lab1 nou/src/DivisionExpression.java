public class DivisionExpression extends ComplexExpression {
    public DivisionExpression(ComplexNumber[] args) {
        super(Operation.DIVIDE, args);
    }

    public ComplexNumber executeOneOperation(ComplexNumber nr1, ComplexNumber nr2) {
        return nr1.divide(nr2);
    }
}
