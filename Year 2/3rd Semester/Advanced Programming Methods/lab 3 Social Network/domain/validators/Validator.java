package org.example.domain.validators;

public interface Validator<T> {
    void validate(T entity) throws org.example.domain.validators.ValidationException;
}