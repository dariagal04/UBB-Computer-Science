//import jdk.incubator.vector.VectorOperators;

import java.util.Arrays;
public abstract class ComplexExpression {
    protected Operation operation;
    protected ComplexNumber[] args;

    public ComplexExpression(Operation operation, ComplexNumber[] args) {
        this.operation = operation;
        this.args = args;
    }


    public ComplexNumber execute(){
        ComplexNumber result = args[0];

        for(int i = 1; i < args.length; i++) {
            result = executeOneOperation(result,args[i]);
        }
        return result;
    }
    protected abstract ComplexNumber executeOneOperation(ComplexNumber arg1, ComplexNumber arg2);


    @Override
    public String toString() {
        return "operation=" + operation + ", args=" + Arrays.toString(args) ;
    }
}
