package api.shows;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.UUID;

/**
 * The Show class represents a multimedia show, such as a TV show or movie.
 * It includes information about the show.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class Show implements Serializable {

    /**
     * The unique identifier for the show.
     */
    private UUID id;

    /**
     * The title of the show.
     */
    private String title;

    /**
     * The description of the show.
     */
    private String description;

    /**
     * Indicates whether the show is restricted for viewers above 18 years old.
     */
    private Boolean isRestricted;

    /**
     * The category to which the show belongs.
     */
    private Category category;

    /**
     * The list of stars (actors/actresses) in the show.
     */
    private ArrayList<String> stars;

    /**
     * The list of similar shows related to this show.
     */
    private ArrayList<Show> similarShows;

    /**
     * The ratings of the show.
     */
    private ArrayList<Rating> ratings;

    /**
     * Constructs a new Show with the specified parameters.
     *
     * @param title         The title of the show.
     * @param description   The description of the show.
     * @param isRestricted  Indicates whether the show is restricted.
     * @param category      The category to which the show belongs.
     * @param stars         The list of stars in the show, separated by commas.
     * @param similarShows  The list of similar shows.
     */

    public Show(String title, String description, Boolean isRestricted, Category category, ArrayList<String> stars, ArrayList<Show> similarShows, ArrayList<Rating> ratings) {
        setId();
        setTitle(title);
        setDescription(description);
        setIsRestricted(isRestricted);
        setCategory(category);
        setStars(stars);
        setSimilarShows(similarShows);
        setRatings(ratings);
    }

    /**
     * Generates a unique identifier for the show.
     */
    public void setId() {
        id = UUID.randomUUID();
    }

    /**
     * Sets the title of the show.
     *
     * @param title The title of the show.
     * @throws IllegalArgumentException If the provided title is blank.
     */
    public void setTitle(String title) {
        if (title.isBlank()) throw new IllegalArgumentException("Title cannot be blank");
        this.title = title;
    }

    /**
     * Sets the description of the show.
     *
     * @param description The description of the show.
     * @throws IllegalArgumentException If the provided description is blank.
     */
    public void setDescription(String description) {
        if (description.isBlank()) throw new IllegalArgumentException("Description cannot be blank");
        this.description = description;
    }

    /**
     * Sets whether the show is restricted.
     *
     * @param isRestricted Indicates whether the show is restricted.
     */
    public void setIsRestricted(boolean isRestricted) {
        this.isRestricted = isRestricted;
    }

    /**
     * Sets the category of the show.
     * Will be chosen from a list of already existing categories from the Category Enumeration to prevent any mistakes.
     *
     * @param category The category to which the show belongs.
     */
    public void setCategory(Category category) {
        this.category = category;
    }

    /**
     * Sets the list of stars in the show.
     *
     * @param stars The list of stars.
     * @throws IllegalArgumentException If the provided stars string is empty.
     */
    public void setStars(ArrayList<String> stars) {
        if (stars.isEmpty() || (stars.size()==1 && stars.get((0)).isBlank())) throw new IllegalArgumentException("Stars cannot be empty");
        this.stars = new ArrayList<>(stars);
    }

    /**
     * Sets the list of similar shows.
     *
     * @param similarShows The list of similar shows.
     * @throws IllegalArgumentException If the provided similarShows string is empty.
     */
    public void setSimilarShows(ArrayList<Show> similarShows) {
        this.similarShows = new ArrayList<>(similarShows);
    }

    public void setRatings(ArrayList<Rating> ratings) { this.ratings = new ArrayList<>(ratings); }


    /**
     * Gets the unique identifier of the show.
     *
     * @return The unique identifier.
     */
    public UUID getId() {
        return id;
    }

    /**
     * Gets the title of the show.
     *
     * @return The title of the show.
     */
    public String getTitle() {
        return title;
    }

    /**
     * Gets the description of the show.
     *
     * @return The description of the show.
     */
    public String getDescription() {
        return description;
    }

    /**
     * Gets whether the show is restricted.
     *
     * @return true if the show is restricted, false otherwise.
     */
    public Boolean getIsRestricted() {
        return isRestricted;
    }

    /**
     * Gets the string representation of whether the show is restricted.
     *
     * @return "Yes (>18)" if the show is restricted, "No" otherwise.
     */
    public String getIsRestrictedAsString() {
        return isRestricted ? "Yes (>18)" : "No";
    }

    /**
     * Gets the category of the show.
     *
     * @return The category of the show.
     */
    public Category getCategory() {
        return category;
    }

    /**
     * Gets the list of stars in the show.
     *
     * @return The list of stars.
     */
    public ArrayList<String> getStars() {
        return stars;
    }

    /**
     * Gets the string representation of the list of stars.
     *
     * @return The string representation of the stars, separated by commas.
     */
    public String getStarsAsString() {
        return String.join("<br>", stars);
    }

    /**
     * Gets the list of similar shows.
     *
     * @return The list of similar shows.
     */
    public ArrayList<Show> getSimilarShows() {
        return similarShows;
    }

    /**
     * Gets the string representation of the list of similar shows.
     *
     * @return The string representation of the similar shows, separated by commas.
     */
    public String getSimilarShowsAsString() {
        if (similarShows.isEmpty()) return "";

        ArrayList<String> similarShowsTitles = new ArrayList<>();
        for (Show similarShow : similarShows) {
            similarShowsTitles.add(similarShow.getTitle());
        }
        return String.join("<br>", similarShowsTitles);
    }

    /**
     * Gets a list of the ratings of the show.
     *
     * @return The ratings of the show.
     */
    public ArrayList<Rating> getRatings() { return ratings; }

    /**
     * Gets the type of the show.
     *
     * @return A string indicating whether the show is a Movie, Series, or null if unknown.
     */
    public String getType() {
        if (this instanceof Movie) return "Movie";
        else if (this instanceof Series) return "Series";
        return null;
    }

    /**
     * Calculates and retrieves the average rating for the show.
     *
     * @return The average rating of the show, or 0 if there are no ratings.
     */
    public double getRatingsAverage() {
        int sum = 0;
        for (Rating rating : ratings) {
            sum += rating.getRating();
        }
        return ratings.isEmpty() ? 0 : ((double) sum / ratings.size());
    }

    /**
     * Formats a short description of the show, truncating it if necessary.
     *
     * @return A formatted short description of the show.
     */
    public String getShortDescriptionFormatted() {
        StringBuilder formattedText = new StringBuilder();
        int count = ("Description: ").length();

        for (char c : description.toCharArray()) {
            formattedText.append(c);
            count++;

            if (count > 30 && Character.isWhitespace(c)) {
                formattedText.append("...");
                break;
            }
        }

        return formattedText.toString();
    }

    /**
     * Formats the full description of the show, breaking lines if necessary.
     *
     * @return A formatted full description of the show.
     */
    public String getFullDescriptionFormatted() {
        StringBuilder formattedText = new StringBuilder();
        int count = ("Description: ").length();

        for (char c : description.toCharArray()) {
            formattedText.append(c);
            count++;

            if (count > 40 && Character.isWhitespace(c)) {
                formattedText.append("<br>");
                count = 0;
            }
        }

        return formattedText.toString();
    }

    /**
     * Adds a rating to the show's list of ratings.
     *
     * @param rating The rating to be added.
     */
    public void addRating(Rating rating) {
        ratings.add(rating);
    }

    /**
     * Adds a similar show to the list of similar shows.
     *
     * @param show The similar show to be added.
     */
    public void addSimilarShow(Show show) {
        similarShows.add(show);
    }

    /**
     * Returns a string representation of the show, which is its title.
     *
     * @return The title of the show.
     */
    @Override
    public String toString() {
        return getTitle();
    }

}