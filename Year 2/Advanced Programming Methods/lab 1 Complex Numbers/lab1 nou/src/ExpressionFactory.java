public class ExpressionFactory {

    private static ExpressionFactory instance;

    private ExpressionFactory() {}
    public static ExpressionFactory getInstance() {
        if (instance == null) {
            instance = new ExpressionFactory();
        }
        return instance;
    }

    public ComplexExpression createComplexExpression(Operation operation, ComplexNumber[] args){
        switch(operation){
            case ADDITION -> {
                return new AdditionExpression(args);
            }
            case SUBTRACT -> {
                return new SubtractionExpression(args);
            }
            case MULTIPLY -> {
                return new MultiplyExpression(args);
            }
            case DIVIDE -> {
                return new DivisionExpression(args);
            }
            default -> {
                return null;
            }
        }
    }
}
