//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    public static void main(String[] args) {

        ExpressionParser parser = new ExpressionParser(args);
        ComplexExpression expr = parser.parse();
        if(expr == null){
            System.out.println("Syntax Error");
        }else{
        ComplexNumber result = expr.execute();
        System.out.println(parser.parse().toString());
        System.out.println("Rezultatul expresiei este: " + result);}
    }
}