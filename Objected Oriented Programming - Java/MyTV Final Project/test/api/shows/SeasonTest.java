package api.shows;

import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;

/**
 * JUnit tests for the Season class.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class SeasonTest {

    private Season season;

    /**
     * Sets up a sample Season object for testing.
     */
    @Before
    public void setUp() {
        // Initialize a sample Season object for testing
        int number = 1;
        int year = 2022;
        ArrayList<Integer> episodes = new ArrayList<>(List.of(30, 25));
        season = new Season(number, year, episodes);
    }

    /**
     * Test the constructor of the Season class.
     */
    @Test
    public void testConstructor() {
        // Test constructor values
        assertNotNull(season.getId());
        assertEquals(1, season.getNumber());
        assertEquals(2022, season.getYear());
        assertEquals(2, season.getEpisodes().size());
        assertEquals("30, 25", season.getEpisodesAsString());
    }

    /**
     * Test the setters of the Season class.
     */
    @Test
    public void testSetters() {
        // Test setting new values
        season.setNumber(2);
        season.setYear(2023);
        season.setEpisodes(new ArrayList<>(List.of(35, 28)));

        // Test getters after setting new values
        assertEquals(2, season.getNumber());
        assertEquals(2023, season.getYear());
        assertEquals(2, season.getEpisodes().size());
        assertEquals("35, 28", season.getEpisodesAsString());
    }

    /**
     * Test setting an invalid season number, should throw an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testSetInvalidNumber() {
        season.setNumber(0);
    }

    /**
     * Test setting an invalid year, should throw an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testSetInvalidYear() {
        season.setYear(0);
    }

    /**
     * Test setting an empty episodes list, should throw an IllegalArgumentException.
     */
    @Test(expected = IllegalArgumentException.class)
    public void testSetEmptyEpisodes() {
        season.setEpisodes(new ArrayList<>());
    }
}