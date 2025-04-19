package src.mpp2024.lab5.repository;

public class RepositoryException extends RuntimeException {
    public RepositoryException(){}

    public RepositoryException(String message){
        super(message);
    }
    public RepositoryException(Exception ex){
        super(ex);
    }
}
