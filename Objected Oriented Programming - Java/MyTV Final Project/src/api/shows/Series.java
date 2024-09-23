package api.shows;

import java.util.ArrayList;
import java.util.UUID;

/**
 * Represents a Series.
 * Extends the Show class and includes a list of seasons.
 * Provides methods to set and retrieve information about the series.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class Series extends Show {

    /** The list of seasons in the series. */
    private ArrayList<Season> seasons;

    /**
     * Constructs a new Series with the specified details.
     *
     * @param title          The title of the series.
     * @param description    A brief description of the series.
     * @param isRestricted   A boolean indicating if the series is restricted.
     * @param category       The category of the series.
     * @param stars          The list of stars in the series.
     * @param similarShows   The list of similar shows to the series.
     * @param seasons        The list of seasons in the series.
     */
    public Series(String title, String description, Boolean isRestricted, Category category, ArrayList<String> stars, ArrayList<Show> similarShows, ArrayList<Rating> ratings, ArrayList<Season> seasons) {
        super(title, description, isRestricted, category, stars, similarShows, ratings);
        setSeasons(seasons);
    }

    /**
     * Sets the list of seasons for the series.
     *
     * @param seasons The list of seasons in the series.
     */
    public void setSeasons(ArrayList<Season> seasons) {
        this.seasons = seasons;
    }

    /**
     * Retrieves the list of seasons for the series.
     *
     * @return The list of seasons in the series.
     */
    public ArrayList<Season> getSeasons() {
        return seasons;
    }

    /**
     * Retrieves a string representation of the seasons in the series.
     *
     * @return A formatted string containing information about each season.
     */
    public String getSeasonsAsString() {
        StringBuilder s = new StringBuilder();
        for (Season season : seasons) {
            s.append("Season: ").append(season.getNumber()).append(", Year: ").append(season.getYear()).append(", Episodes: ").append(season.getEpisodesAsString()).append("<br>");
            s.append('\n');
        }
        return s.toString();
    }
}
