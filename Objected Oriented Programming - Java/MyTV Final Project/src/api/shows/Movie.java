package api.shows;

import java.util.ArrayList;
import java.util.UUID;

/**
 * Represents a Movie.
 * Extends the Show class and includes additional properties like year and duration.
 * Provides methods to set and retrieve information about the movie.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class Movie extends Show {

    /** The release year of the movie. */
    private int year;

    /** The duration of the movie in minutes. */
    private int duration;

    /**
     * Constructs a new Movie with the specified details.
     *
     * @param title          The title of the movie.
     * @param description    A brief description of the movie.
     * @param isRestricted   A boolean indicating if the movie is restricted.
     * @param category       The category of the movie.
     * @param stars          The list of stars in the movie.
     * @param similarShows   The list of similar shows to the movie.
     */
    public Movie(String title, String description, Boolean isRestricted, Category category, ArrayList<String> stars, ArrayList<Show> similarShows, ArrayList<Rating> ratings, int year, int duration) {
        super(title, description, isRestricted, category, stars, similarShows, ratings);
        setYear(year);
        setDuration(duration);
    }

    /**
     * Sets the release year of the movie.
     *
     * @param year The release year of the movie.
     * @throws IllegalArgumentException If the provided year is not valid (less than or equal to 0).
     */
    public void setYear(int year) {
        if (year <= 0) throw new IllegalArgumentException("Year is invalid");
        this.year = year;
    }

    /**
     * Sets the duration of the movie.
     *
     * @param duration The duration of the movie in minutes.
     * @throws IllegalArgumentException If the provided duration is not valid (less than or equal to 0).
     */
    public void setDuration(int duration) {
        if (duration <= 0) throw new IllegalArgumentException("Duration is invalid");
        this.duration = duration;
    }

    /**
     * Retrieves the release year of the movie.
     *
     * @return The release year of the movie.
     */
    public int getYear() {
        return year;
    }

    /**
     * Retrieves the duration of the movie.
     *
     * @return The duration of the movie in minutes.
     */
    public int getDuration() {
        return duration;
    }

    /**
     * Retrieves the duration of the movie as a formatted string.
     *
     * @return The duration of the movie followed by the word "minutes".
     */
    public String getDurationAsString() {
        return duration + " minutes";
    }
}
