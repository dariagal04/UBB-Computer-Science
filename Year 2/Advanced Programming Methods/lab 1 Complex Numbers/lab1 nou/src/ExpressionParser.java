import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class ExpressionParser {

    private final String[] args;

    public ExpressionParser(String[] args) {
        this.args = args;
    }

    public ComplexExpression parse() {
        String op = args[1];
        ComplexNumber[] argss = new ComplexNumber[(args.length + 1) / 2];
        for (int i = 0; i < args.length; i++) {
            if (i % 2 == 0) {
                int negativ = 0;
                String[] el = args[i].split("[+]", 2);
                if (el.length != 2) {
                    el = args[i].split("-", 2);
                    negativ = 1;
                }
                double re = Double.parseDouble(el[0]);
                double im = 0;
                if (el[1].equals("i")) {
                    im = 1;
                } else if (el[1].equals("-i")) {
                    im = -1;
                } else {
                    String[] IM = el[1].split("[*]", 2);
                    im = Double.parseDouble((IM[0]));
                    if (negativ == 1) {
                        im = -im;
                    }
                }
                ComplexNumber nr = new ComplexNumber(re, im);
                argss[i / 2] = nr;
            } else {
                //op = args[i];
                if (!args[i].equals(op)) {
                    throw new IllegalArgumentException("pune acelasi operator");
                }
            }
        }

        return switch (op) {
            case "+" -> ExpressionFactory.getInstance().createComplexExpression(Operation.ADDITION, argss);
            case "-" -> ExpressionFactory.getInstance().createComplexExpression(Operation.SUBTRACT, argss);
            case "*" -> ExpressionFactory.getInstance().createComplexExpression(Operation.MULTIPLY, argss);
            case "/" -> ExpressionFactory.getInstance().createComplexExpression(Operation.DIVIDE, argss);
            default -> null;
        };
    }
}
