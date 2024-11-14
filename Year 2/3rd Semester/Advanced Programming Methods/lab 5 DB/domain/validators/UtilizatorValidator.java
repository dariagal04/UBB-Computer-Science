package src.ubb.domain.validators;


import src.ubb.domain.Utilizator;

public class UtilizatorValidator implements Validator<Utilizator> {
    @Override
    public void validate(Utilizator entity) throws ValidationException {
        //TODO: implement method validate
        if(entity.getFirstName().equals(""))
            throw new ValidationException("Utilizatorul nu este valid");

        if(entity.getLastName().equals(""))
            throw new ValidationException("Utilizatorul nu este valid");
    }
}
