import model.ComputerRepairRequest;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;


public class ComputerRepairRequestTest {
    @Test
    @DisplayName("First Test")
    public void testFirst() {
        ComputerRepairRequest test = new ComputerRepairRequest();
        assertEquals("",test.getOwnerName());
        assertEquals("",test.getOwnerAddress());
    }


    @Test
    @DisplayName("Test Exemplu")
    public void testExemplu() {
        assertEquals(2,2,"Numele ar trebui sa fie egale");
    }
}
