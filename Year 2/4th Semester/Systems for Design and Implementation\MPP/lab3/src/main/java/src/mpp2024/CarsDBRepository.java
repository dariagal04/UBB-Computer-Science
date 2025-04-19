package src.mpp2024;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class CarsDBRepository implements CarRepository{

    private JdbcUtils dbUtils;



    private static final Logger logger= LogManager.getLogger();

    public CarsDBRepository(Properties props) {
        logger.info("Initializing CarsDBRepository with properties: {} ",props);
        dbUtils=new JdbcUtils(props);
    }


@Override
public List<Car> findByManufacturer(String manufacturerN) {
    logger.traceEntry("Finding cars by manufacturer: {}", manufacturerN);
    List<Car> cars = new ArrayList<>();
    String sql = "SELECT * FROM cars WHERE manufacturer = ?";

    try (Connection con = dbUtils.getConnection();
         PreparedStatement preStmt = con.prepareStatement(sql)) {

        preStmt.setString(1, manufacturerN); // Set the manufacturer parameter

        try (ResultSet result = preStmt.executeQuery()) {
            while (result.next()) {
                int id = result.getInt("id");
                String manufacturer = result.getString("manufacturer"); // Fixed typo
                String model = result.getString("model");
                int year = result.getInt("year");

                Car car = new Car(manufacturer, model, year);
                car.setId(id);
                cars.add(car);
            }
        }
    } catch (SQLException e) {
        logger.error("Error finding cars by manufacturer: {}", e.getMessage(), e);
    }

    logger.traceExit("Found {} cars", cars.size());
    return cars;
}


    @Override
    public List<Car> findBetweenYears(int min, int max) {
        //to do
        return null;
    }

    @Override
    public void add(Car elem) {
        logger.traceEntry("saving task {}", elem);
        Connection con = dbUtils.getConnection();
        try(PreparedStatement preStmt = con.prepareStatement("insert into cars(manufacturer, model, year) values (?,?,?)")) {
            preStmt.setString(1, elem.getManufacturer());
            preStmt.setString(2, elem.getModel());
            preStmt.setInt(3, elem.getYear());
            int result = preStmt.executeUpdate();

        }catch (SQLException ex){
            logger.error(ex);
            System.out.println(ex);
        }
        logger.traceExit();
    }

    @Override
    public void update(Integer integer, Car elem) {
        //to do
    }

    @Override
    public Iterable<Car> findAll() {
        logger.traceEntry();
        Connection con = dbUtils.getConnection();
        List<Car> cars = new ArrayList<>();
        try(PreparedStatement preStmt = con.prepareStatement("select * from cars")){
            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){
                    int id  = result.getInt("id");
                    String manufacturer = result.getString("manufacturer");
                    String model = result.getString("model");
                    int year = result.getInt("year");
                    Car car = new Car(manufacturer, model, year);
                    car.setId(id);
                    cars.add(car);
                }
            }
        }catch (SQLException e){
            logger.error(e);
            System.out.println(e);
        }
        logger.traceExit();
        return cars;

    }
}
