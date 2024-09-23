package api.users;

import api.shows.Category;
import api.shows.Show;
import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;;

/**
 * JUnit tests for the Subscriber class.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class SubscriberTest {

    private Subscriber subscriber;

    /**
     * Sets up a fresh instance of the Subscriber class before each test method.
     */
    @Before
    public void setUp() {
        // Set up a subscriber with a list of favorite shows for each test
        ArrayList<Show> favoriteShows = new ArrayList<>();
        favoriteShows.add(new Show("Inception", "A mind-bending thriller", false, Category.SCIFI, new ArrayList<>(List.of("Leonardo DiCaprio", "Joseph Gordon-Levitt")), new ArrayList<>(), new ArrayList<>()));
        favoriteShows.add(new Show("The Shawshank Redemption", "A tale of hope and redemption", false, Category.DRAMA, new ArrayList<>(List.of("Tim Robbins", "Morgan Freeman")), new ArrayList<>(), new ArrayList<>()));
        subscriber = new Subscriber("John", "Doe", "subscriberUser", "subscriberPassword123", favoriteShows);
    }

    /**
     * Test the successful initialization of the Subscriber class.
     */
    @Test
    public void subscriberInitializationSucceeds() {
        assertNotNull(subscriber);
    }

    /**
     * Test if the subscriber has the correct first name.
     */
    @Test
    public void subscriberHasCorrectFirstName() {
        assertEquals("John", subscriber.getFirstName());
    }

    /**
     * Test if the subscriber has the correct last name.
     */
    @Test
    public void subscriberHasCorrectLastName() {
        assertEquals("Doe", subscriber.getLastName());
    }

    /**
     * Test if the subscriber has the correct username.
     */
    @Test
    public void subscriberHasCorrectUsername() {
        assertEquals("subscriberUser", subscriber.getUsername());
    }

    /**
     * Test if the subscriber has the correct password.
     */
    @Test
    public void subscriberHasCorrectPassword() {
        assertEquals("subscriberPassword123", subscriber.getPassword());
    }

    /**
     * Test if the subscriber has favorite shows.
     */
    @Test
    public void subscriberHasFavoriteShows() {
        assertEquals(2, subscriber.getFavoriteShows().size());
    }

    /**
     * Test if the subscriber can add a favorite show.
     */
    @Test
    public void subscriberCanAddFavoriteShow() {
        Show newShow = new Show("The Dark Knight", "A superhero masterpiece", false, Category.ACTION, new ArrayList<>(List.of("Christian Bale", "Heath Ledger")), new ArrayList<>(), new ArrayList<>());
        subscriber.addFavoriteShow(newShow);
        assertTrue(subscriber.getFavoriteShows().contains(newShow));
    }

    /**
     * Test if the subscriber can remove a favorite show.
     */
    @Test
    public void subscriberCanRemoveFavoriteShow() {
        Show showToRemove = subscriber.getFavoriteShows().get(0);
        subscriber.removeFavoriteShow(showToRemove);
        assertFalse(subscriber.getFavoriteShows().contains(showToRemove));
    }
}
