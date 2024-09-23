package api.shows;

import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;

/**
 * JUnit tests for the Movie class.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class MovieTest {

    private Movie movie;

    /**
     * Sets up a sample Movie object for testing.
     */
    @Before
    public void setUp() {
        // Initialize a sample Movie object for testing
        String title = "Sample Movie";
        String description = "This is a sample movie for testing.";
        Boolean isRestricted = true;
        Category category = Category.DRAMA;
        ArrayList<String> stars = new ArrayList<>(List.of("Actor1", "Actress2", "Actor3"));
        ArrayList<Show> similarShows = new ArrayList<>();
        ArrayList<Rating> ratings = new ArrayList<>();
        int year = 2022;
        int duration = 120;
        movie = new Movie(title, description, isRestricted, category, stars, similarShows, ratings, year, duration);
    }

    /**
     * Test the constructor of the Movie class.
     */
    @Test
    public void testConstructor() {
        // Test constructor values
        assertEquals("Sample Movie", movie.getTitle());
        assertEquals("This is a sample movie for testing.", movie.getDescription());
        assertTrue(movie.getIsRestricted());
        assertEquals(Category.DRAMA, movie.getCategory());
        assertEquals("Actor1<br>Actress2<br>Actor3", movie.getStarsAsString());
        assertEquals("", movie.getSimilarShowsAsString()); // No similar shows in this case
        assertEquals(2022, movie.getYear());
        assertEquals(120, movie.getDuration());
        assertEquals("120 minutes", movie.getDurationAsString());
    }

    /**
     * Test the setters of the Movie class.
     */
    @Test
    public void testSetters() {
        // Test setting new values
        movie.setTitle("Updated Movie Title");
        movie.setDescription("Updated Movie Description");
        movie.setIsRestricted(false);
        movie.setCategory(Category.COMEDY);
        movie.setStars(new ArrayList<>(List.of("NewActor1", "NewActor2")));
        movie.setYear(2023);
        movie.setDuration(150);

        // Test getters after setting new values
        assertEquals("Updated Movie Title", movie.getTitle());
        assertEquals("Updated Movie Description", movie.getDescription());
        assertFalse(movie.getIsRestricted());
        assertEquals(Category.COMEDY, movie.getCategory());
        assertEquals("NewActor1<br>NewActor2", movie.getStarsAsString());
        assertEquals(2023, movie.getYear());
        assertEquals(150, movie.getDuration());
        assertEquals("150 minutes", movie.getDurationAsString());
    }

    /**
     * Test setting an invalid year (less than or equal to 0), should throw an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testSetInvalidYear() {
        movie.setYear(0);
    }

    /**
     * Test setting an invalid duration (less than or equal to 0), should throw an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testSetInvalidDuration() {
        movie.setDuration(-5);
    }
}
