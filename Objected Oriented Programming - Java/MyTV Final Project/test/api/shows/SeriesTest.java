package api.shows;

import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;

/**
 * JUnit tests for the Series class.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class SeriesTest {

    private Series series;

    /**
     * Sets up a sample Series object for testing.
     */
    @Before
    public void setUp() {
        // Initialize a sample Series object for testing
        String title = "Sample Series";
        String description = "This is a sample series for testing.";
        Boolean isRestricted = true;
        Category category = Category.DRAMA;
        ArrayList<String> stars = new ArrayList<>(List.of("Actor1", "Actress2", "Actor3"));
        ArrayList<Show> similarShows = new ArrayList<>();
        ArrayList<Rating> ratings = new ArrayList<>();
        ArrayList<Season> seasons = new ArrayList<>();
        Season season1 = new Season(1, 2022, new ArrayList<>(List.of(30, 25)));
        Season season2 = new Season(2, 2023, new ArrayList<>(List.of(35, 28)));
        seasons.add(season1);
        seasons.add(season2);
        series = new Series(title, description, isRestricted, category, stars, similarShows, ratings, seasons);
    }

    /**
     * Test the constructor of the Series class.
     */
    @Test
    public void testConstructor() {
        // Test constructor values
        assertNotNull(series.getId());
        assertEquals("Sample Series", series.getTitle());
        assertEquals("This is a sample series for testing.", series.getDescription());
        assertTrue(series.getIsRestricted());
        assertEquals(Category.DRAMA, series.getCategory());
        assertEquals("Actor1<br>Actress2<br>Actor3", series.getStarsAsString());
        assertEquals("", series.getSimilarShowsAsString());
        assertEquals(2, series.getSeasons().size());
        assertEquals("Season: 1, Year: 2022, Episodes: 30, 25<br>\nSeason: 2, Year: 2023, Episodes: 35, 28<br>\n", series.getSeasonsAsString());
    }

    /**
     * Test the setters of the Series class.
     */
    @Test
    public void testSetters() {
        // Test setting new values
        series.setTitle("Updated Series Title");
        series.setDescription("Updated Series Description");
        series.setIsRestricted(false);
        series.setCategory(Category.COMEDY);
        series.setStars(new ArrayList<>(List.of("NewActor1", "NewActor2")));

        // Test getters after setting new values
        assertEquals("Updated Series Title", series.getTitle());
        assertEquals("Updated Series Description", series.getDescription());
        assertFalse(series.getIsRestricted());
        assertEquals(Category.COMEDY, series.getCategory());
        assertEquals("NewActor1<br>NewActor2", series.getStarsAsString());
    }

    /**
     * Test the getSeasonsAsString method of the Series class.
     */
    @Test
    public void testGetSeasonsAsString() {
        // Test getSeasonsAsString method
        assertEquals("Season: 1, Year: 2022, Episodes: 30, 25<br>\nSeason: 2, Year: 2023, Episodes: 35, 28<br>\n", series.getSeasonsAsString());
    }
}