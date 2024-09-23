package api.users;

import java.io.Serializable;
import java.util.UUID;

/**
 * Represents a User in the system.
 *
 * A user has a unique identifier (UUID), first name, last name, username, and password.
 * This class provides methods to set and retrieve user information with validation rules.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class User implements Serializable {
    private UUID id;
    private String firstName;
    private String lastName;
    private String username;
    private String password;
    private Boolean isAdmin;

    /**
     * Constructs a new User with the specified parameters.
     *
     * @param firstName the first name of the user.
     * @param lastName  the last name of the user.
     * @param username  the username of the user.
     * @param password  the password of the user.
     * @param isAdmin  if the user is admin.
     * @throws IllegalArgumentException if any of the parameters violate validation rules.
     */
    public User(String firstName, String lastName, String username, String password, Boolean isAdmin) {
        setId();
        setFirstName(firstName);
        setLastName(lastName);
        setUsername(username);
        setPassword(password);
        setIsAdmin(isAdmin);
    }

    /**
     * Sets a unique identifier for the user.
     */
    public void setId() {
        id = UUID.randomUUID();
    }

    /**
     * Sets the first name of the user.
     *
     * @param firstName the first name to set.
     * @throws IllegalArgumentException if the first name violates validation rules.
     */
    public void setFirstName(String firstName) {
        if (firstName.isBlank()) throw new IllegalArgumentException("First name cannot be blank");
        if (firstName.contains(" ")) throw new IllegalArgumentException("First name cannot contain space");
        if (firstName.matches(".*[\\W\\d].*")) throw new IllegalArgumentException("First name cannot have symbols or numbers");
        this.firstName = firstName;
    }

    /**
     * Sets the last name of the user.
     *
     * @param lastName the last name to set.
     * @throws IllegalArgumentException if the last name violates validation rules.
     */
    public void setLastName(String lastName) {
        if (lastName.isBlank()) throw new IllegalArgumentException("Last name cannot be blank");
        if (lastName.contains(" ")) throw new IllegalArgumentException("Last name cannot contain space");
        if (lastName.matches(".*[\\W\\d].*")) throw new IllegalArgumentException("Last name cannot have symbols or numbers");
        this.lastName = lastName;
    }

    /**
     * Sets the username of the user.
     *
     * @param username the username to set.
     * @throws IllegalArgumentException if the username violates validation rules.
     */
    public void setUsername(String username) {
        if (username.isBlank()) throw new IllegalArgumentException("Username cannot be blank");
        if (username.length() < 5 || username.length() > 20)
            throw new IllegalArgumentException("Username length must be between 5 and 20 characters");
        if (username.contains(" ")) throw new IllegalArgumentException("Username cannot contain space");
        if (!username.matches("[a-zA-Z][a-zA-Z0-9_]*"))
            throw new IllegalArgumentException("Username must start with letter and not contain any symbols except underscore");
        this.username = username;
    }

    /**
     * Sets the password of the user.
     *
     * @param password the password to set.
     * @throws IllegalArgumentException if the password violates validation rules.
     */
    public void setPassword(String password) {
        if (password.isBlank()) throw new IllegalArgumentException("Password cannot be blank");
        if (password.length() < 5) throw new IllegalArgumentException("Password must contain at least 5 characters");
        if (!(password.matches(".*[a-zA-Z].*") && password.matches(".*\\d.*")))
            throw new IllegalArgumentException("Password must contain at least a letter and a number");
        this.password = password;
    }

    /**
     * Sets if the user is admin.
     *
     * @param isAdmin if user is admin
     */
    public void setIsAdmin(Boolean isAdmin) {
        this.isAdmin = isAdmin;
    }

    /**
     * Gets the unique identifier of the user.
     *
     * @return the UUID of the user.
     */
    public UUID getId() {
        return id;
    }

    /**
     * Gets the first name of the user.
     *
     * @return the first name of the user.
     */
    public String getFirstName() {
        return firstName;
    }

    /**
     * Gets the last name of the user.
     *
     * @return the last name of the user.
     */
    public String getLastName() {
        return lastName;
    }

    /**
     * Gets the username of the user.
     *
     * @return the username of the user.
     */
    public String getUsername() {
        return username;
    }

    /**
     * Gets the password of the user.
     *
     * @return the password of the user.
     */
    public String getPassword() { return password; }

    /**
     * Gets if the user is admin.
     *
     * @return if the user is admin.
     */
    public Boolean getIsAdmin() {
        return isAdmin;
    }
}