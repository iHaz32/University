package api;

import api.users.Subscriber;
import api.users.User;
import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;

import static org.junit.Assert.*;

/**
 * JUnit tests for the Auth class.
 *
 * These tests cover the login and register functionality of the Auth class, ensuring proper validation
 * and authentication processes.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class AuthTest {

    private Auth auth;
    private ArrayList<User> usersList;

    /**
     * Sets up a sample Auth object and users list for testing.
     */
    @Before
    public void setUp() {
        // Initialize a sample Auth object for testing
        auth = new Auth();

        // Initialize a sample users list for testing
        usersList = new ArrayList<>();
        User user1 = new Subscriber("John", "Doe", "john_doe", "password1", new ArrayList<>());
        User user2 = new Subscriber("Jane", "Doe", "jane_doe", "secure123", new ArrayList<>());
        usersList.add(user1);
        usersList.add(user2);
    }

    /**
     * Test the login method of the Auth class with valid credentials.
     *
     * Ensures that the login method correctly authenticates a user with valid credentials.
     */
    @Test
    public void testLoginValidCredentials() {
        User loggedInUser = auth.login(usersList, "john_doe", "password1");
        assertEquals("john_doe", loggedInUser.getUsername());
    }

    /**
     * Test the login method of the Auth class with invalid credentials.
     *
     * Ensures that the login method throws an IllegalArgumentException for invalid credentials.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testLoginInvalidCredentials() {
        auth.login(usersList, "nonexistent_user", "invalid_password");
    }

    /**
     * Test the register method of the Auth class with a new user.
     *
     * Ensures that the register method correctly creates a new user with valid information.
     */
    @Test
    public void testRegisterNewUser() {
        User newUser = auth.register(usersList, "Alice", "Wonderland", "alice_w", "new_password1");
        // Assert
        assertEquals("Alice", newUser.getFirstName());
        assertEquals("new_password1", newUser.getPassword());
    }

    /**
     * Test the register method of the Auth class with an existing username.
     *
     * Ensures that the register method throws an IllegalArgumentException for an existing username.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testRegisterExistingUsername() {
        auth.register(usersList, "Bob", "Builder", "john_doe", "password123");
    }
}