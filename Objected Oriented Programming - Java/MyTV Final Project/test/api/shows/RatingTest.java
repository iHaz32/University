package api.shows;

import api.users.User;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 * JUnit tests for the Rating class.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class RatingTest {
    private User regularUser;

    /**
     * Sets up a sample {@code User} object for testing.
     */
    @Before
    public void setUp() {
        // Initialize a sample User object for testing
        regularUser = new User("John", "Doe", "john_doe", "password123", false);
    }
    /**
     * Test the creation of a valid rating.
     */
    @Test
    public void testValidRatingCreation() {
        // Valid rating creation
        Rating rating = new Rating(regularUser, "Great show!", 5);

        assertNotNull(rating.getId());
        assertEquals(regularUser, rating.getAuthor());
        assertEquals("Great show!", rating.getText());
        assertEquals(5, rating.getRating());
    }
    /**
     * Test rating creation with an empty text, should throw an IllegalArgumentException.
     */
    @Test
    public void testEmptyTextRatingCreation() {
        // Empty text should throw an exception
        assertThrows(IllegalArgumentException.class, () -> new Rating(regularUser, "", 4));
    }
    /**
     * Test rating creation with text exceeding 500 characters, should throw an IllegalArgumentException.
     */
    @Test
    public void testLongTextRatingCreation() {
        // Text exceeding 500 characters should throw an exception
        String longText = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. " +
                "Quisque id semper tortor. Nulla facilisi. Proin efficitur aliquet dolor, eget fringilla est. " +
                "Vestibulum vel neque vel justo sollicitudin gravida. Integer nec ante et orci dignissim malesuada." +
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit. " +
                "Quisque id semper tortor. Nulla facilisi. Proin efficitur aliquet dolor, eget fringilla est. " +
                "Vestibulum vel neque vel justo sollicitudin gravida. Integer nec ante et orci dignissim malesuada." +
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit. " +
                "Quisque id semper tortor. Nulla facilisi. Proin efficitur aliquet dolor, eget fringilla est. " +
                "Vestibulum vel neque vel justo sollicitudin gravida. Integer nec ante et orci dignissim malesuada.";
        assertThrows(IllegalArgumentException.class, () -> new Rating(regularUser, longText, 3));
    }
    /**
     * Test rating creation with an invalid rating value, should throw an IllegalArgumentException.
     */
    @Test
    public void testInvalidRatingValueCreation() {
        // Rating less than 1 should throw an exception
        assertThrows(IllegalArgumentException.class, () -> new Rating(regularUser, "Not good", 0));

        // Rating greater than 5 should throw an exception
        assertThrows(IllegalArgumentException.class, () -> new Rating(regularUser, "Amazing!", 6));
    }
    /**
     * Test rating creation by an admin user, should throw a SecurityException.
     */
    @Test
    public void testAdminAuthorRatingCreation() {
        User adminUser = new User("Admin", "User", "admin_user", "admin123", true);

        // Rating creation by an admin should throw an exception
        assertThrows(SecurityException.class, () -> new Rating(adminUser, "Awesome show", 5));
    }
    /**
     * Test the formatting of text with HTML line breaks.
     */
    @Test
    public void testSetTextFormatted() {
        // Test the formatting of text with HTML line breaks
        Rating rating = new Rating(regularUser, "This is a long comment that needs formatting to fit within the limit of characters.", 4);

        String expectedFormattedText = "This is a long comment that <br>needs formatting to fit within the limit <br>of characters.";
        assertEquals(expectedFormattedText, rating.getTextFormatted());
    }
}