package api.shows;

import api.users.User;

import java.io.Serializable;
import java.util.UUID;

/**
 * Represents a rating given by a user for a show.
 * Ratings include an identifier, the author of the rating, the text of the rating, and the numerical rating itself.
 *
 *  The text of the rating can be formatted for display, inserting HTML line breaks ("<br>") at appropriate intervals.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */

public class Rating implements Serializable {

    /**
     * The unique identifier for the rating.
     */
    private UUID id;

    /**
     * The user who authored the rating.
     */
    private User author;

    /**
     * The text content of the rating.
     */
    private String text;

    /**
     * The numerical rating given by the user.
     */
    private int rating;

    /**
     * Constructs a new Rating object with the specified author, text, and numerical rating.
     *
     * @param author The user who authored the rating.
     * @param text   The text content of the rating.
     * @param rating The numerical rating given by the user (must be between 1 and 5).
     */
    public Rating(User author, String text, int rating) {
        setId();
        setAuthor(author);
        setText(text);
        setRating(rating);
    }

    /**
     * Sets a new unique identifier for the rating.
     */
    public void setId() {
        id = UUID.randomUUID();
    }

    /**
     * Sets the author of the rating. Throws a SecurityException if the author is an admin.
     *
     * @param author The user who authored the rating.
     * @throws SecurityException If the author is an admin.
     */
    public void setAuthor(User author) {
        if (author.getIsAdmin()) throw new SecurityException("Permission Denied");
        this.author = author;
    }

    /**
     * Sets the text content of the rating. Throws an IllegalArgumentException for empty or excessively long text.
     *
     * @param text The text content of the rating.
     * @throws IllegalArgumentException If the text is empty or exceeds 500 characters.
     */
    public void setText(String text) {
        if (text.trim().isEmpty()) throw new IllegalArgumentException("Text cannot be empty");
        if (text.length() > 500) throw new IllegalArgumentException("Text length cannot be over 500 characters");
        this.text = text;
    }

    /**
     * Sets the numerical rating given by the user. Throws an IllegalArgumentException if the rating is not between 1 and 5.
     *
     * @param rating The numerical rating given by the user.
     * @throws IllegalArgumentException If the rating is not between 1 and 5.
     */
    public void setRating(int rating) {
        if (rating < 1 || rating > 5) throw new IllegalArgumentException("Rating must be between 1 and 5");
        this.rating = rating;
    }

    /**
     * Gets the unique identifier for the rating.
     *
     * @return The unique identifier.
     */
    public UUID getId() {
        return id;
    }

    /**
     * Gets the author of the rating.
     *
     * @return The user who authored the rating.
     */
    public User getAuthor() {
        return author;
    }

    /**
     * Gets the text content of the rating.
     *
     * @return The text content.
     */
    public String getText() {
        return text;
    }

    /**
     * Gets the formatted text content of the rating, inserting HTML line breaks at appropriate intervals.
     *
     * @return The formatted text content.
     */
    public String getTextFormatted() {
        StringBuilder formattedText = new StringBuilder();
        int count = ("Comment: ").length();

        for (char c : text.toCharArray()) {
            formattedText.append(c);
            count++;

            if (count > 35 && Character.isWhitespace(c)) {
                formattedText.append("<br>");
                count = 0;
            }
        }

        return formattedText.toString();
    }

    /**
     * Gets the numerical rating given by the user.
     *
     * @return The numerical rating.
     */
    public int getRating() {
        return rating;
    }
}