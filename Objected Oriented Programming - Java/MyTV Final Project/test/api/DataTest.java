package api;

import api.shows.Category;
import api.shows.Movie;
import api.shows.Series;
import api.users.Admin;
import api.users.Subscriber;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;
import java.nio.file.*;
import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;

/**
 * Test class for the Data class.
 *
 * This class contains test cases for the Data class, covering various scenarios
 * for validating the functionality of the Data class methods.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class DataTest {
    private Data testData;
    private Path tempDir;

    /**
     * Set up a temporary directory for test data and copy original data files.
     *
     * @throws IOException if an I/O error occurs during setup.
     */
    @Before
    public void setUp() throws IOException {
        tempDir = Files.createTempDirectory("testData");

        copyDataFiles(Paths.get("users.dat"), tempDir.resolve("users.dat"));
        copyDataFiles(Paths.get("movies.dat"), tempDir.resolve("movies.dat"));
        copyDataFiles(Paths.get("series.dat"), tempDir.resolve("series.dat"));

        testData = new Data();
    }

    /**
     * Test creating a new Data instance.
     */
    @Test
    public void testCreateNewData() {
        assertNotNull(testData.getUsers());
        assertNotNull(testData.getMovies());
        assertNotNull(testData.getSeries());
    }

    /**
     * Test adding a new user to the data.
     */
    @Test
    public void testAddUser() {
        int initialUserCount = testData.getUsers().size();
        testData.userAdd(new Subscriber("New", "User", "newuser", "newpassword1", new ArrayList<>()));
        assertEquals(initialUserCount + 1, testData.getUsers().size());
    }

    /**
     * Test adding a new movie to the data.
     */
    @Test
    public void testAddMovie() {
        int initialMovieCount = testData.getMovies().size();
        Movie newMovie = new Movie("New Movie", "Description", false, Category.ACTION,
                new ArrayList<>(List.of("Actor1", "Actor2")), new ArrayList<>(), new ArrayList<>(), 2022, 120);
        testData.movieAdd(newMovie);
        assertEquals(initialMovieCount + 1, testData.getMovies().size());
    }

    /**
     * Test adding a new series to the data.
     */
    @Test
    public void testAddSeries() {
        int initialSeriesCount = testData.getSeries().size();
        Series newSeries = new Series("New Series", "Description", false, Category.DRAMA,
                new ArrayList<>(List.of("Actor1", "Actor2")), new ArrayList<>(), new ArrayList<>(), new ArrayList<>());
        testData.seriesAdd(newSeries);
        assertEquals(initialSeriesCount + 1, testData.getSeries().size());
    }

    /**
     * Test saving and loading data.
     */
    @Test
    public void testSaveAndLoad() {
        testData.userAdd(new Admin("Admin", "New", "admin_new", "newpass1"));
        testData.save();

        Data loadedData = new Data();
        loadedData.load();

        assertEquals(testData.getUsers().size(), loadedData.getUsers().size());
        assertEquals(testData.getMovies().size(), loadedData.getMovies().size());
        assertEquals(testData.getSeries().size(), loadedData.getSeries().size());
    }

    /**
     * Test deleting a movie from the data.
     */
    @Test
    public void testDeleteMovie() {
        int initialMovieCount = testData.getMovies().size();
        Movie movieToDelete = testData.getMovies().get(0);
        testData.movieDelete(movieToDelete);
        assertEquals(initialMovieCount - 1, testData.getMovies().size());
        assertFalse(testData.getMovies().contains(movieToDelete));
    }

    /**
     * Test deleting a series from the data.
     */
    @Test
    public void testDeleteSeries() {
        int initialSeriesCount = testData.getSeries().size();
        Series seriesToDelete = testData.getSeries().get(0);
        testData.seriesDelete(seriesToDelete);
        assertEquals(initialSeriesCount - 1, testData.getSeries().size());
        assertFalse(testData.getSeries().contains(seriesToDelete));
    }

    /**
     * Copy data files from source to destination.
     *
     * @param source      the source file or directory.
     * @param destination the destination file or directory.
     * @throws IOException if an I/O error occurs during the copy operation.
     */
    private void copyDataFiles(Path source, Path destination) throws IOException {
        Files.copy(source, destination, StandardCopyOption.REPLACE_EXISTING);
    }
}