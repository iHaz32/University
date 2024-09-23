package api.shows;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.UUID;

/**
 * Represents a Season of episodes in the class Series.
 * Each Season has an id, number, a release year, and a list of episodes duration.
 * Provides methods to set and retrieve information about the season.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class Season implements Serializable {

    /**
     * The unique identifier for the season.
     */
    private UUID id;

    /**
     * The number of the season.
     */
    private int number;

    /**
     * The release year of the season.
     */
    private int year;

    /**
     * The list of episodes duration in the season.
     */
    private ArrayList<Integer> episodes;

    /**
     * Constructs a new Season with the specified details.
     *
     * @param number   The number of the season.
     * @param year     The release year of the season.
     * @param episodes A string representing episodes duration, separated by commas and spaces.
     * @throws IllegalArgumentException If the provided number, year, or episodes are invalid.
     */
    public Season(int number, int year, ArrayList<Integer> episodes) {
        setId();
        setNumber(number);
        setYear(year);
        setEpisodes(episodes);
    }

    /**
     * Generates a unique identifier for the season.
     */
    public void setId() { id = UUID.randomUUID(); }

    /**
     * Sets the number of the season.
     *
     * @param number The number of the season.
     * @throws IllegalArgumentException If the provided number is not valid (less than or equal to 0).
     */
    public void setNumber(int number) {
        if (number <= 0) throw new IllegalArgumentException("Number of season is invalid");
        this.number = number;
    }

    /**
     * Sets the release year of the season.
     *
     * @param year The release year of the season.
     * @throws IllegalArgumentException If the provided year is not valid (less than or equal to 0).
     */
    public void setYear(int year) {
        if (year <= 0) throw new IllegalArgumentException("Year is invalid");
        this.year = year;
    }

    /**
     * Sets the list of episodes duration for the season.
     *
     * @param episodes A string representing episodes duration.
     * @throws IllegalArgumentException If the provided episodes string is blank or invalid.
     */
    public void setEpisodes(ArrayList<Integer> episodes) {
        if (episodes.isEmpty()) throw new IllegalArgumentException("Duration of episodes is invalid");
        this.episodes = new ArrayList<>(episodes);
    }

    /**
     * Gets the unique identifier of the season.
     *
     * @return The unique identifier.
     */
    public UUID getId() { return id; }

    /**
     * Retrieves the number of the season.
     *
     * @return The number of the season.
     */
    public int getNumber() { return number; }

    /**
     * Retrieves the release year of the season.
     *
     * @return The release year of the season.
     */
    public int getYear() { return year; }

    /**
     * Retrieves the list of episodes duration for the season.
     *
     * @return The list of episodes duration.
     */
    public ArrayList<Integer> getEpisodes() { return episodes; }

    /**
     * Retrieves a string representation of the episodes in the show.
     *
     * @return A string containing the names of the episodes, separated by commas.
     */
    public String getEpisodesAsString() {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < episodes.size() - 1; i++) {
            result.append(episodes.get(i)).append(", ");
        }
        result.append(episodes.get(episodes.size() - 1));
        return result.toString();
    }
}
