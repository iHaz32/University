package api;

import api.shows.Category;
import api.shows.Show;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 * A simple search engine for finding shows based on various criteria.
 *
 * This SearchEngine class provides methods for searching shows based on criteria such as title, type, actor, restriction,
 * category, and minimum rating. It allows users to filter and retrieve a list of shows that match the specified criteria.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class SearchEngine {

    /**
     * Searches for shows based on the specified criteria.
     *
     * @param title      The title to search for. If null or empty, it is not considered.
     * @param type       The type of the show (Movie/Series/All). If "All", all types are considered.
     * @param actor      The name of the actor. If null or empty, it is not considered.
     * @param isRestricted Whether to filter restricted shows. If true, only restricted shows are considered.
     * @param category   The category of the show. If null, all categories are considered.
     * @param minRating  The minimum rating a show must have to be included in the results.
     * @param data       The data source containing shows.
     * @return An ArrayList of shows that match the specified criteria.
     */
    public ArrayList<Show> search(String title, String type, String actor, boolean isRestricted, Category category, double minRating, Data data) {
        List<Show> shows = new ArrayList<>();
        shows.addAll(data.getMovies());
        shows.addAll(data.getSeries());

        ArrayList<Show> results = new ArrayList<>();

        for (Show show : shows) {
            if (matchesCriteria(show, title, type, actor, isRestricted, category, minRating)) {
                results.add(show);
            }
        }

        return results;
    }

    /**
     * Checks if a show matches the specified search criteria.
     *
     * @param show        The show to check.
     * @param title       The title to match. If null or empty, it is considered a match.
     * @param type        The type of the show to match. If "All", it is considered a match.
     * @param actor       The actor's name to match. If null or empty, it is considered a match.
     * @param isRestricted Whether the show should be restricted. If true, it is considered a match.
     * @param category    The category of the show to match. If null, it is considered a match.
     * @param minRating   The minimum rating the show should have to be considered a match.
     * @return True if the show matches the criteria, false otherwise.
     */
    boolean matchesCriteria(Show show, String title, String type, String actor, boolean isRestricted, Category category, double minRating) {
        if (title != null && !title.isEmpty() && !show.getTitle().toLowerCase().contains(title.toLowerCase())) {
            return false;
        }

        if (!Objects.equals(type, "All") && !Objects.equals(show.getType(), type)) {
            return false;
        }

        if (actor != null && !actor.isEmpty() && !show.getStars().contains(actor)) {
            return false;
        }

        if (isRestricted && !show.getIsRestricted()) {
            return false;
        }

        if (category != null && !show.getCategory().equals(category)) {
            return false;
        }

        return show.getRatingsAverage() >= minRating;
    }
}