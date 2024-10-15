public class AdditionExpression extends ComplexExpression {
    public AdditionExpression(ComplexNumber[] args) {
        super(Operation.ADDITION, args);
    }

    public ComplexNumber executeOneOperation(ComplexNumber nr1, ComplexNumber nr2) {
        return nr1.add(nr2);
    }
}