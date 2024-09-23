package api;

import api.shows.Show;
import api.users.Subscriber;
import api.users.User;

import java.util.ArrayList;

/**
 * Manages authentication processes for users.
 *
 * The Auth class provides methods for user login and registration. It ensures proper validation
 * and authentication processes while interacting with a list of users.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class Auth {

    /**
     * Default constructor for the Auth class.
     */
    public Auth() {}

    /**
     * Authenticates a user based on the provided credentials.
     *
     * Iterates through the given list of users to find a match for the provided username and password.
     * If a match is found, the corresponding user is returned; otherwise, an IllegalArgumentException is thrown.
     *
     * @param usersList The list of users to search for authentication.
     * @param username  The username for authentication.
     * @param password  The password for authentication.
     * @return The authenticated user.
     * @throws IllegalArgumentException If the provided login information is invalid.
     */
    public User login(ArrayList<User> usersList, String username, String password) {
        for (User user : usersList) {
            if (user.getUsername().equals(username) && user.getPassword().equals(password)) {
                return user;
            }
        }
        throw new IllegalArgumentException("Invalid login info");
    }

    /**
     * Registers a new user with the provided information.
     *
     * Iterates through the given list of users to check if the provided username already exists.
     * If the username is unique, a new Subscriber is created and added to the users list.
     * If successful, the new Subscriber is returned; otherwise, an IllegalArgumentException is thrown.
     *
     * @param usersList The list of users to check for existing usernames and add the new user.
     * @param firstName The first name of the new user.
     * @param lastName  The last name of the new user.
     * @param username  The username of the new user.
     * @param password  The password of the new user.
     * @return The newly registered user.
     * @throws IllegalArgumentException If the provided username already exists or if any validation rules are violated.
     */
    public User register(ArrayList<User> usersList, String firstName, String lastName, String username, String password) {
        for (User user : usersList) {
            if (user.getUsername().equals(username)) {
                throw new IllegalArgumentException("Username already exists");
            }
        }
        try {
            Subscriber newSubscriber = new Subscriber(firstName, lastName, username, password, new ArrayList<Show>());
            usersList.add(newSubscriber);
            return newSubscriber;
        } catch (IllegalArgumentException e) {
            throw new IllegalArgumentException(e.getMessage());
        }
    }
}