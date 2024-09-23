package api.users;

/**
 * The Admin class represents an administrative user in the system,
 * inheriting from the User class.
 *
 * An admin user has the ability to perform administrative tasks and holds
 * additional privileges compared to regular users.
 *
 * This class provides a constructor to create a new admin user with the specified
 * parameters such as first name, last name, username, and password.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class Admin extends User {
    /**
     * Constructs a new Admin with the specified parameters.
     *
     * @param firstName the first name of the admin.
     * @param lastName  the last name of the admin.
     * @param username  the username of the admin.
     * @param password  the password of the admin.
     * @throws IllegalArgumentException if any of the parameters violate validation rules.
     */
    public Admin(String firstName, String lastName, String username, String password) {
        super(firstName, lastName, username, password, true);
    }
}
