package api.users;

import api.shows.Show;

import java.util.ArrayList;

/**
 * The Subscriber class represents a subscriber user in the system,
 * inheriting from the User class.
 *
 * A subscriber is a regular user with the ability to manage a list of favorite shows.
 *
 * This class provides a constructor to create a new subscriber with the specified
 * parameters such as first name, last name, username, password, and a list of favorite shows.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class Subscriber extends User {

    private ArrayList<Show> favoriteShows;

    /**
     * Constructs a new Subscriber with the specified parameters.
     *
     * @param firstName      the first name of the subscriber.
     * @param lastName       the last name of the subscriber.
     * @param username       the username of the subscriber.
     * @param password       the password of the subscriber.
     * @param favoriteShows  the list of favorite shows for the subscriber.
     * @throws IllegalArgumentException if any of the parameters violate validation rules.
     */
    public Subscriber(String firstName, String lastName, String username, String password, ArrayList<Show> favoriteShows) {
        super(firstName, lastName, username, password, false);
        setFavoriteShows(favoriteShows);
    }

    /**
     * Sets the list of favorite shows for the subscriber.
     *
     * @param favoriteShows the list of favorite shows to be set.
     */
    public void setFavoriteShows(ArrayList<Show> favoriteShows) {
        this.favoriteShows = favoriteShows;
    }

    /**
     * Gets the list of favorite shows for the subscriber.
     *
     * @return the list of favorite shows.
     */
    public ArrayList<Show> getFavoriteShows() {
        return favoriteShows;
    }

    /**
     * Adds a show to the list of favorite shows for the subscriber.
     *
     * @param show the show to be added to the list of favorite shows.
     */
    public void addFavoriteShow(Show show) {
        favoriteShows.add(show);
    }

    /**
     * Removes a show from the list of favorite shows for the subscriber.
     *
     * @param show the show to be removed from the list of favorite shows.
     */
    public void removeFavoriteShow(Show show) {
        favoriteShows.remove(show);
    }
}
