package api.users;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Test class for the User class.
 *
 * This class contains test cases for the User class, covering various scenarios
 * for validation rules in the User class methods.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class UserTest {
    private User user;

    /**
     * Set up a new User instance before each test.
     */
    @Before
    public void setUp() {
        user = new User("Alice", "Smith", "alice_smith", "SecurePwd123", true);
    }

    /**
     * Test the constructor with valid parameters.
     */
    @Test
    public void testConstructorWithValidParameters() {
        assertNotNull(user.getId());
        assertEquals("Alice", user.getFirstName());
        assertEquals("Smith", user.getLastName());
        assertEquals("alice_smith", user.getUsername());
        assertEquals("SecurePwd123", user.getPassword());
        assertTrue(user.getIsAdmin());
    }

    /**
     * Test the generation of a non-null UUID for the user's ID.
     */
    @Test
    public void testId() {
        assertNotNull(user.getId());
    }

    /**
     * Test setting a different isAdmin property.
     */
    @Test
    public void testIsAdmin() {
        user.setIsAdmin(false);
        assertFalse(user.getIsAdmin());
    }

    /**
     * Test setting a valid first name for the user.
     */
    @Test
    public void testFirstName() {
        user.setFirstName("John");
        assertEquals("John", user.getFirstName());
    }

    /**
     * Test attempting to set a blank first name, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testFirstNameWithBlank() {
        user.setFirstName("");
    }

    /**
     * Test attempting to set a first name with space, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testFirstNameWithSpace() {
        user.setFirstName("John Doe");
    }

    /**
     * Test attempting to set a first name with symbols, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testFirstNameWithSymbol() {
        user.setFirstName("John$");
    }

    /**
     * Test setting a valid last name for the user.
     */
    @Test
    public void testLastName() {
        user.setLastName("Doe");
        assertEquals("Doe", user.getLastName());
    }

    /**
     * Test attempting to set a blank last name, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testLastNameWithBlank() {
        user.setLastName("");
    }

    /**
     * Test attempting to set a last name with space, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testLastNameWithSpace() {
        user.setLastName("Doe Smith");
    }

    /**
     * Test attempting to set a last name with symbols, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testLastNameWithSymbol() {
        user.setLastName("Doe$");
    }

    /**
     * Test setting a valid username for the user.
     */
    @Test
    public void testUsername() {
        user.setUsername("john_doe");
        assertEquals("john_doe", user.getUsername());
    }

    /**
     * Test attempting to set a blank username, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testUsernameWithBlank() {
        user.setUsername("");
    }

    /**
     * Test attempting to set a username with a length less than the required, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testUsernameWithShortLength() {
        user.setUsername("abc");
    }

    /**
     * Test attempting to set a username with a length more than the required, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testUsernameWithLongLength() {
        user.setUsername("abcdefghijklmnopqrstuvwxyz");
    }

    /**
     * Test attempting to set a username with space, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testUsernameWithSpace() {
        user.setUsername("john doe");
    }

    /**
     * Test attempting to set a username starting with an invalid character, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testUsernameWithInvalidStart() {
        user.setUsername("1john_doe");
    }

    /**
     * Test attempting to set a username with symbols, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testUsernameWithSymbol() {
        user.setUsername("john@doe");
    }

    /**
     * Test setting a valid password for the user.
     */
    @Test
    public void testPassword() {
        user.setPassword("Password123");
        assertEquals("Password123", user.getPassword());
    }

    /**
     * Test attempting to set a blank password, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testPasswordWithBlank() {
        user.setPassword("");
    }

    /**
     * Test attempting to set a password with length less than the required, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testPasswordWithShortLength() {
        user.setPassword("abc");
    }

    /**
     * Test attempting to set a password without a letter, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testPasswordWithoutLetter() {
        user.setPassword("123456");
    }

    /**
     * Test attempting to set a password without a number, expecting an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testPasswordWithoutNumber() {
        user.setPassword("Password");
    }
}