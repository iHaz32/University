package api;

import api.shows.*;
import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

/**
 * JUnit tests for the SearchEngine class.
 *
 * These tests cover the functionality of the search method and matchesCriteria method
 * in the SearchEngine class, ensuring that shows are correctly filtered based on the specified criteria.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class SearchEngineTest {

    private SearchEngine searchEngine;

    /**
     * Sets up a sample SearchEngine for testing.
     */
    @Before
    public void setUp() {
        // Initialize a sample SearchEngine for testing
        searchEngine = new SearchEngine();
    }

    /**
     * Test the search method of the SearchEngine class with various criteria.
     *
     * Ensures that the search method correctly filters shows based on the specified criteria.
     */
    @Test
    public void testSearch() {
        // Create some sample shows for testing
        Movie movie1 = new Movie("Movie1", "Description1", true, Category.ACTION, new ArrayList<>(List.of("Leonardo DiCaprio", "Joseph Gordon-Levitt")), new ArrayList<>(), new ArrayList<>(), 2022, 120);
        Movie movie2 = new Movie("Movie2", "Description2", false, Category.COMEDY, new ArrayList<>(List.of("Leonardo DiCaprio", "Joseph Gordon-Levitt")), new ArrayList<>(), new ArrayList<>(), 2023, 90);
        Series series1 = new Series("Series1", "Description1", true, Category.DRAMA, new ArrayList<>(List.of("Leonardo DiCaprio", "Joseph Gordon-Levitt")), new ArrayList<>(), new ArrayList<>(), new ArrayList<>());

        // Test search with title, type, actor, and minRating criteria
        ArrayList<Show> results = searchEngine.search("Movie1", "Movie", "Leonardo DiCaprio", true, Category.ACTION, 0, createTestData(movie1, movie2, series1));
        assertEquals(1, results.size());
        assertEquals("Movie1", results.get(0).getTitle());
    }

    /**
     * Test the matchesCriteria method of the SearchEngine class with various criteria.
     *
     * Ensures that the matchesCriteria method correctly evaluates whether a show matches the specified criteria.
     */
    @Test
    public void testMatchesCriteria() {
        // Create some sample shows for testing
        Movie movie1 = new Movie("Movie1", "Description1", true, Category.ACTION, new ArrayList<>(List.of("Leonardo DiCaprio", "Joseph Gordon-Levitt")), new ArrayList<>(), new ArrayList<>(), 2022, 120);
        Movie movie2 = new Movie("Movie2", "Description2", false, Category.COMEDY, new ArrayList<>(List.of("Leonardo DiCaprio", "Joseph Gordon-Levitt")), new ArrayList<>(), new ArrayList<>(), 2023, 90);
        Series series1 = new Series("Series1", "Description1", true, Category.DRAMA, new ArrayList<>(List.of("Leonardo DiCaprio", "Joseph Gordon-Levitt")), new ArrayList<>(), new ArrayList<>(), new ArrayList<>());

        // Test matchesCriteria with various criteria
        assertTrue(searchEngine.matchesCriteria(movie1, "Movie1", "Movie", "Joseph Gordon-Levitt", true, Category.ACTION, 0));
        assertFalse(searchEngine.matchesCriteria(movie2, "Movie1", "Movie", "Joseph Gordon-Levitt", true, Category.ACTION, 0));
    }

    /**
     * Helper method to create test data with shows.
     *
     * @param shows The shows to include in the test data.
     * @return The test data containing the specified shows.
     */
    private Data createTestData(Show... shows) {
        Data testData = new Data();
        for (Show show : shows) {
            if (show instanceof Movie) {
                testData.movieAdd((Movie) show);
            } else if (show instanceof Series) {
                testData.seriesAdd((Series) show);
            }
        }
        return testData;
    }
}