package src.mpp2024.lab5.services;

import src.mpp2024.lab5.model.ComputerRepairRequest;
import src.mpp2024.lab5.model.ComputerRepairedForm;
import src.mpp2024.lab5.model.RequestStatus;
import src.mpp2024.lab5.repository.ComputerRepairRequestRepository;
import src.mpp2024.lab5.repository.ComputerRepairedFormRepository;
import src.mpp2024.lab5.repository.RepositoryException;

import java.util.List;

public class ComputerRepairServices {

    private ComputerRepairRequestRepository requestRepository;

    private ComputerRepairedFormRepository repairedRepository;

    public ComputerRepairServices(ComputerRepairRequestRepository requestRepository, ComputerRepairedFormRepository repairedRepository) {
        this.requestRepository = requestRepository;
        this.repairedRepository = repairedRepository;
    }

    public int addComputerRepairRequest(String ownerName, String ownerAddress, String phone, String model, String date, String problem) throws ServicesException{
       try {
           ComputerRepairRequest crr = new ComputerRepairRequest(ownerName, ownerAddress, phone, model, date, problem);
           ComputerRepairRequest newRequest = requestRepository.add(crr);
           return newRequest.getID();
       }catch (RepositoryException ex){
           throw new ServicesException("Error adding request"+ex);
       }
    }


    public List<ComputerRepairRequest> getUnfinishedRequestsByModel(String model){
        return requestRepository.filterByModelAndStatus(model, RequestStatus.New);

    }

    public void addRepairedForm(ComputerRepairRequest request,String services, double price,String repairedDate, String employeeN) throws ServicesException{
        try {
            request.setStatus(RequestStatus.Finished);
            ComputerRepairedForm repairedForm = new ComputerRepairedForm(request, services, price, repairedDate, employeeN);
            requestRepository.update(request, request.getID());
            repairedRepository.add(repairedForm);
        }catch (RepositoryException er){
            throw  new ServicesException("Error adding form"+er);
        }

    }

    public  List<ComputerRepairRequest> getRequestByStatus(RequestStatus status){
        return requestRepository.filterByStatus(status);
    }


}
