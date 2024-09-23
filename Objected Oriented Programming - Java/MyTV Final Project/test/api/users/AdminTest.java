package api.users;

import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;;

/**
 * JUnit tests for the Admin class.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class AdminTest {

    private Admin admin;

    /**
     * Sets up a fresh instance of the Admin class before each test method.
     */
    @Before
    public void setUp() {
        admin = new Admin("John", "Doe", "adminUser123", "adminPassword123");
    }

    /**
     * Test the successful initialization of the Admin class.
     */
    @Test
    public void adminInitializationSucceeds() {
        assertNotNull(admin);
    }

    /**
     * Test if the admin has the correct first name.
     */
    @Test
    public void adminHasCorrectFirstName() {
        assertEquals("John", admin.getFirstName());
    }

    /**
     * Test if the admin has the correct last name.
     */
    @Test
    public void adminHasCorrectLastName() {
        assertEquals("Doe", admin.getLastName());
    }

    /**
     * Test if the admin has the correct username.
     */
    @Test
    public void adminHasCorrectUsername() {
        assertEquals("adminUser123", admin.getUsername());
    }

    /**
     * Test if the admin has the correct password.
     */
    @Test
    public void adminHasCorrectPassword() {
        assertEquals("adminPassword123", admin.getPassword());
    }

    /**
     * Test if the initialization of the admin fails with invalid parameters.
     */
    @Test
    public void adminInitializationFailsWithInvalidParameters() {
        assertThrows(IllegalArgumentException.class, () -> {
            Admin invalidAdmin = new Admin("John", "Doe", "admin", "pass"); // Invalid username
        });
    }
}
