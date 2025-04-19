package src.mpp2024.lab5;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import src.mpp2024.lab5.repository.ComputerRepairRequestRepository;
import src.mpp2024.lab5.repository.ComputerRepairedFormRepository;
import src.mpp2024.lab5.repository.jdbc.ComputerRepairRequestJdbcRepository;
import src.mpp2024.lab5.repository.jdbc.ComputerRepairedFormJdbcRepository;
import src.mpp2024.lab5.services.ComputerRepairServices;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

@Configuration
public class RepairShopConfig {
    @Bean
    Properties getProps() {

        Properties props = new Properties();
        try{
            System.out.println("Searching bd.config in directory"+((new File(".")).getAbsolutePath()));
            props.load(new FileReader("bd.config"));

        }catch(IOException e){
            System.out.println("Error reading bd.config"+e);
        }
        return props;
     
    }

    @Bean
    ComputerRepairRequestRepository requestsRepo(){
        return new ComputerRepairRequestJdbcRepository(getProps());
       

    }

    @Bean
    ComputerRepairedFormRepository formsRepo(){
       return new ComputerRepairedFormJdbcRepository(getProps());

    }

    @Bean
    ComputerRepairServices services(){
       

        return new ComputerRepairServices(requestsRepo(),formsRepo());
    }

}
