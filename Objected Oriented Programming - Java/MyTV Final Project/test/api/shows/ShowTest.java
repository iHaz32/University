package api.shows;

import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;

/**
 * JUnit tests for the Show class.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class ShowTest {

    private Show show;

    /**
     * Sets up a sample Show object for testing.
     */
    @Before
    public void setUp() {
        // Initialize a sample Show object for testing
        String title = "Sample Show";
        String description = "This is a sample show for testing.";
        Boolean isRestricted = true;
        Category category = Category.DRAMA;
        ArrayList<String> stars = new ArrayList<>(List.of("Actor1", "Actress2", "Actor3"));
        ArrayList<Show> similarShows = new ArrayList<>();
        ArrayList<Rating> ratings = new ArrayList<>();
        show = new Show(title, description, isRestricted, category, stars, similarShows, ratings);
    }

    /**
     * Test the constructor of the Show class.
     */
    @Test
    public void testConstructor() {
        // Test constructor values
        assertEquals("Sample Show", show.getTitle());
        assertEquals("This is a sample show for testing.", show.getDescription());
        assertTrue(show.getIsRestricted());
        assertEquals(Category.DRAMA, show.getCategory());
        assertEquals("Actor1<br>Actress2<br>Actor3", show.getStarsAsString());
        assertEquals("", show.getSimilarShowsAsString()); // No similar shows in this case
    }

    /**
     * Test the getters of the Show class.
     */
    @Test
    public void testGetters() {
        assertEquals("Sample Show", show.getTitle());
        assertEquals("This is a sample show for testing.", show.getDescription());
        assertTrue(show.getIsRestricted());
        assertEquals(Category.DRAMA, show.getCategory());
        assertEquals("Actor1<br>Actress2<br>Actor3", show.getStarsAsString());
        assertEquals("", show.getSimilarShowsAsString()); // No similar shows in this case
    }

    /**
     * Test the setters of the Show class.
     */
    @Test
    public void testSetters() {
        // Test setting new values
        show.setTitle("Updated Title");
        show.setDescription("Updated Description");
        show.setIsRestricted(false);
        show.setCategory(Category.COMEDY);
        show.setStars(new ArrayList<>(List.of("NewActor1", "NewActor2")));

        // Test getters after setting new values
        assertEquals("Updated Title", show.getTitle());
        assertEquals("Updated Description", show.getDescription());
        assertFalse(show.getIsRestricted());
        assertEquals(Category.COMEDY, show.getCategory());
        assertEquals("NewActor1<br>NewActor2", show.getStarsAsString());
    }

    /**
     * Test setting an empty stars list, should throw an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testSetEmptyStars() {
        show.setStars(new ArrayList<>());
    }

    /**
     * Test that each show has a unique ID.
     */
    @Test
    public void testIdGeneration() {
        Show anotherShow = new Show("Another Show", "Another description", false, Category.COMEDY, new ArrayList<>(List.of("Actor1", "Actress2", "Actor3")), new ArrayList<>(), new ArrayList<>());
        assertNotEquals(show.getId(), anotherShow.getId());
    }

    /**
     * Test the getSimilarShowsAsString method of the Show class.
     */
    @Test
    public void testGetSimilarShowsAsString() {
        // Test when there are similar shows
        ArrayList<Show> similarShows = new ArrayList<>(List.of(new Show("SimilarShow1", "abc", false, Category.ACTION, new ArrayList<>(List.of("Actor1", "Actress2", "Actor3")), new ArrayList<>(), new ArrayList<>()),
                new Show("SimilarShow2", "abc", false, Category.COMEDY, new ArrayList<>(List.of("Actor1", "Actress2", "Actor3")), new ArrayList<>(), new ArrayList<>())));
        show.setSimilarShows(similarShows);
        assertEquals("SimilarShow1<br>SimilarShow2", show.getSimilarShowsAsString());
    }
}