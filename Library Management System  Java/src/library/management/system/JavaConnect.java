package library.management.system;
import java.sql.Connection;
import java.sql.DriverManager;
import javax.swing.JOptionPane;

public class JavaConnect {
    
    public static Connection ConnectDB() {
        try {
            // Load the MySQL JDBC driver (consider using the newer driver class)
            Class.forName("com.mysql.cj.jdbc.Driver");
            
            // Enable SSL and provide truststore (adjust the trustCertificateKeyStoreUrl accordingly)
            String jdbcUrl = "jdbc:mysql://localhost/lms";
            
            Connection conn = DriverManager.getConnection(jdbcUrl, "root", "iyi@123789");
            
            return conn;
        } catch (Exception e) {
            JOptionPane.showMessageDialog(null, e.getMessage());
            return null;
        }
    }
}
