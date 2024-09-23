package api;

import api.shows.*;
import api.users.Admin;
import api.users.Subscriber;
import api.users.User;

import java.io.*;
import java.util.ArrayList;
import java.io.Serializable;
import java.util.List;

/**
 * The `Data` class represents the central data storage for users, movies, and series in the streaming service.
 * It provides methods for adding, deleting, and retrieving users, movies, and series. Additionally, it supports
 * serialization for data persistence and includes initialization methods for default data.
 *
 * @author Nikolaos Askitopoulos
 * @author Charalampos Deligiannakis
 */
public class Data implements Serializable {
    private ArrayList<User> users;
    private ArrayList<Movie> movies;
    private ArrayList<Series> series;

    /**
     * Constructs a new `Data` object with empty lists for users, movies, and series, and initializes default data.
     */
    public Data() {
        users = new ArrayList<>();
        movies = new ArrayList<>();
        series = new ArrayList<>();
        initialize();
    }

    /**
     * Adds a user to the list of users.
     *
     * @param user The user to be added.
     */
    public void userAdd(User user) {
        users.add(user);
    }

    /**
     * Adds a movie to the list of movies.
     *
     * @param newMovie The movie to be added.
     */
    public void movieAdd(Movie newMovie) {
        movies.add(newMovie);
    }

    /**
     * Deletes a movie from the list of movies.
     *
     * @param deletedMovie The movie to be deleted.
     */
    public void movieDelete(Movie deletedMovie) {
        movies.removeIf(movieFromDB -> movieFromDB.getId().compareTo(deletedMovie.getId()) == 0);
    }

    /**
     * Adds a series to the list of series.
     *
     * @param newSeries The series to be added.
     */
    public void seriesAdd(Series newSeries) {
        series.add(newSeries);
    }

    /**
     * Deletes a series from the list of series.
     *
     * @param deletedSeries The series to be deleted.
     */
    public void seriesDelete(Series deletedSeries) {
        series.removeIf(seriesFromDB -> seriesFromDB.getId().compareTo(deletedSeries.getId()) == 0);
    }

    /**
     * Retrieves the list of users.
     *
     * @return The list of users.
     */
    public ArrayList<User> getUsers() {
        return users;
    }

    /**
     * Retrieves the list of movies.
     *
     * @return The list of movies.
     */
    public ArrayList<Movie> getMovies() {
        return movies;
    }

    /**
     * Retrieves the list of series.
     *
     * @return The list of series.
     */
    public ArrayList<Series> getSeries() {
        return series;
    }

    /**
     * Saves the current state of users, movies, and series to respective data files.
     */
    public void save() {
        saveUsers();
        saveMovies();
        saveSeries();
    }

    /**
     * Loads the saved state of users, movies, and series from respective data files.
     */
    public void load() {
        loadUsers();
        loadMovies();
        loadSeries();
    }

    /**
     * Saves the list of users to a file named "users.dat".
     * Uses object serialization to persist the data.
     * In case of an IOException, a RuntimeException is thrown.
     */
    private void saveUsers() {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("users.dat"))) {
            oos.writeObject(users);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Loads the list of users from the file named "users.dat".
     * Uses object deserialization to retrieve the data.
     * In case of a FileNotFoundException, no action is taken.
     * In case of an IOException or ClassNotFoundException, a RuntimeException is thrown.
     */
    private void loadUsers() {
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream("users.dat"))) {
            users = (ArrayList<User>) ois.readObject();
        } catch (FileNotFoundException e) {
            // do nothing
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Saves the list of movies to a file named "movies.dat".
     * Uses object serialization to persist the data.
     * In case of an IOException, a RuntimeException is thrown.
     */
    private void saveMovies() {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("movies.dat"))) {
            oos.writeObject(movies);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Loads the list of movies from the file named "movies.dat".
     * Uses object deserialization to retrieve the data.
     * In case of a FileNotFoundException, no action is taken.
     * In case of an IOException or ClassNotFoundException, a RuntimeException is thrown.
     */
    private void loadMovies() {
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream("movies.dat"))) {
            movies = (ArrayList<Movie>) ois.readObject();
        } catch (FileNotFoundException e) {
            // do nothing
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Saves the list of series to a file named "series.dat".
     * Uses object serialization to persist the data.
     * In case of an IOException, a RuntimeException is thrown.
     */
    private void saveSeries() {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream("series.dat"))) {
            oos.writeObject(series);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Loads the list of series from the file named "series.dat".
     * Uses object deserialization to retrieve the data.
     * In case of a FileNotFoundException, no action is taken.
     * In case of an IOException or ClassNotFoundException, a RuntimeException is thrown.
     */
    private void loadSeries() {
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream("series.dat"))) {
            series = (ArrayList<Series>) ois.readObject();
        } catch (FileNotFoundException e) {
            // do nothing
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Initializes the data by loading users, movies, and series from files,
     * and setting up default data including users, movies, series, ratings, and favorite shows.
     */
    public void initialize() {
        load();
        initializeUsers();
        initializeMovies();
        initializeSeries();
        initializeFavoriteShows();
    }

    /**
     * Initializes the list of movies with default data if not already initialized.
     * Default movies include "Inception," "The Shawshank Redemption," "The Dark Knight," "Pulp Fiction," and "Forrest Gump."
     * Each movie is added with relevant details, similar shows, and ratings.
     */
    public void initializeMovies() {
        boolean alreadyInitialized = false;
        for (Movie movie : movies) {
            if (movie.getTitle().equals("Inception")) {
                alreadyInitialized = true;
                break;
            }
        }

        if (!alreadyInitialized) {
            Movie movie1 = new Movie("Inception", "A mind-bending thriller", false, Category.SCIFI, new ArrayList<>(List.of("Leonardo DiCaprio", "Joseph Gordon-Levitt")), new ArrayList<>(), new ArrayList<>(), 2010, 148);
            Movie movie2 = new Movie("The Shawshank Redemption", "A tale of hope and redemption", false, Category.DRAMA, new ArrayList<>(List.of("Tim Robbins", "Morgan Freeman")), new ArrayList<>(), new ArrayList<>(), 1994, 142);
            Movie movie3 = new Movie("The Dark Knight", "A superhero masterpiece", false, Category.ACTION, new ArrayList<>(List.of("Christian Bale", "Heath Ledger")), new ArrayList<>(), new ArrayList<>(), 2008, 152);
            Movie movie4 = new Movie("Pulp Fiction", "A nonlinear crime film", true, Category.ACTION, new ArrayList<>(List.of("John Travolta", "Samuel L. Jackson")), new ArrayList<>(), new ArrayList<>(), 1994, 154);
            Movie movie5 = new Movie("Forrest Gump", "A heartwarming journey", false, Category.COMEDY, new ArrayList<>(List.of("Tom Hanks", "Robin Wright")), new ArrayList<>(), new ArrayList<>(), 1994, 142);

            movie1.addSimilarShow(movie2);
            movie2.addSimilarShow(movie1);
            movie3.addSimilarShow(movie4);
            movie4.addSimilarShow(movie3);

            initializeRatings(new ArrayList<>(List.of(movie1, movie2, movie3, movie4, movie5)));

            movies.add(movie1);
            movies.add(movie2);
            movies.add(movie3);
            movies.add(movie4);
            movies.add(movie5);
        }
    }

    /**
     * Initializes the list of series with default data if not already initialized.
     * Default series include "Stranger Things," "Breaking Bad," "Game of Thrones," "The Mandalorian," and "The Witcher."
     * Each series is added with relevant details, similar shows, and ratings.
     */
    public void initializeSeries() {
        boolean alreadyInitialized = false;
        for (Series series : series) {
            if (series.getTitle().equals("Stranger Things")) {
                alreadyInitialized = true;
                break;
            }
        }

        if (!alreadyInitialized) {
            Series series1 = new Series("Stranger Things", "Mystery series", false, Category.HORROR, new ArrayList<>(List.of("Millie Bobby Brown", "Finn Wolfhard")), new ArrayList<>(), new ArrayList<>(), new ArrayList<>(List.of(
                    new Season(1, 2016, new ArrayList<>(List.of(40, 34, 69, 31, 40))),
                    new Season(2, 2017, new ArrayList<>(List.of(32, 58, 49, 28, 59))),
                    new Season(3, 2019, new ArrayList<>(List.of(48, 39, 58, 38, 29)))
            )));
            Series series2 = new Series("Breaking Bad", "Crime drama series", true, Category.DRAMA, new ArrayList<>(List.of("Bryan Cranston", "Aaron Paul")), new ArrayList<>(), new ArrayList<>(), new ArrayList<>(List.of(
                    new Season(1, 2008, new ArrayList<>(List.of(57, 58, 47, 48, 33))),
                    new Season(2, 2009, new ArrayList<>(List.of(43, 51, 63, 43, 63))),
                    new Season(3, 2010, new ArrayList<>(List.of(43, 45, 43, 61, 83)))
            )));
            Series series3 = new Series("Game of Thrones", "Epic fantasy series", false, Category.ACTION, new ArrayList<>(List.of("Emilia Clarke", "Kit Harington")), new ArrayList<>(), new ArrayList<>(), new ArrayList<>(List.of(
                    new Season(1, 2011, new ArrayList<>(List.of(40, 34, 69, 31, 40))),
                    new Season(2, 2012, new ArrayList<>(List.of(43, 45, 43, 61, 83))),
                    new Season(3, 2013, new ArrayList<>(List.of(40, 34, 69, 31, 40)))
            )));
            Series series4 = new Series("The Mandalorian", "Space Western series", false, Category.SCIFI, new ArrayList<>(List.of("Pedro Pascal", "Gina Carano")), new ArrayList<>(), new ArrayList<>(), new ArrayList<>(List.of(
                    new Season(1, 2019, new ArrayList<>(List.of(43, 45, 43, 61, 83))),
                    new Season(2, 2020, new ArrayList<>(List.of(40, 34, 69, 31, 40)))
            )));
            Series series5 = new Series("The Witcher", "Dark fantasy series", false, Category.ACTION, new ArrayList<>(List.of("Henry Cavill", "Anya Chalotra")), new ArrayList<>(), new ArrayList<>(), new ArrayList<>(List.of(
                    new Season(1, 2019, new ArrayList<>(List.of(57, 58, 47, 48, 33))),
                    new Season(2, 2021, new ArrayList<>(List.of(32, 58, 49, 28, 59)))
            )));

            series1.addSimilarShow(series2);
            series2.addSimilarShow(series1);
            series3.addSimilarShow(series4);
            series4.addSimilarShow(series3);

            initializeRatings(new ArrayList<>(List.of(series1, series2, series3, series4, series5)));

            series.add(series1);
            series.add(series2);
            series.add(series3);
            series.add(series4);
            series.add(series5);
        }
    }

    /**
     * Initializes the list of users with default data if not already initialized.
     * Default users include two Admin users and two Subscriber users.
     */
    public void initializeUsers() {
        boolean alreadyInitialized = false;
        for (User user : users) {
            if (user.getUsername().equals("admin1")) {
                alreadyInitialized = true;
                break;
            }
        }

        if (!alreadyInitialized) {
            users.add(new Admin("Admin", "First", "admin1", "password1"));
            users.add(new Admin("Admin", "Second", "admin2", "password2"));
            users.add(new Subscriber("User", "First", "user1", "password1", new ArrayList<Show>()));
            users.add(new Subscriber("User", "Second", "user2", "password2", new ArrayList<Show>()));
        }
    }

    /**
     * Initializes the ratings for a list of shows with default data.
     * Default ratings include ratings from two users for each show in the list.
     * Ratings include comments and numerical scores.
     * @param show The list of shows for which ratings are initialized.
     */
    public void initializeRatings(ArrayList<Show> show) {
        User user1 = getUsers().get(2);
        User user2 = getUsers().get(3);

        Rating rating1A = new Rating(user1, "Good show Good show Good show Good show Good show Good show Good show", 5);
        Rating rating1B = new Rating(user2, "Bad show", 1);
        Rating rating2A = new Rating(user1, "Good show", 3);
        Rating rating2B = new Rating(user2, "Bad show", 2);
        Rating rating3A = new Rating(user1, "Good show", 4);
        Rating rating3B = new Rating(user2, "Bad show", 3);
        Rating rating4A = new Rating(user1, "Good show", 3);
        Rating rating4B = new Rating(user2, "Bad show", 2);
        Rating rating5A = new Rating(user1, "Good show", 5);
        Rating rating5B = new Rating(user2, "Bad show", 3);

        show.get(0).addRating(rating1A);
        show.get(0).addRating(rating1B);
        show.get(1).addRating(rating2A);
        show.get(1).addRating(rating2B);
        show.get(2).addRating(rating3A);
        show.get(2).addRating(rating3B);
        show.get(3).addRating(rating4A);
        show.get(3).addRating(rating4B);
        show.get(4).addRating(rating5A);
        show.get(4).addRating(rating5B);
    }

    /**
     * Initializes favorite shows for two Subscriber users.
     * User1's favorite show is the first movie, and User2's favorite show is the first series.
     */
    public void initializeFavoriteShows() {
        Subscriber user1 = (Subscriber) getUsers().get(2);
        Subscriber user2 = (Subscriber) getUsers().get(3);

        Show show1 = getMovies().get(0);
        Show show2 = getSeries().get(0);

        user1.addFavoriteShow(show1);
        user2.addFavoriteShow(show2);
    }

    /**
     * Refreshes the favorite shows for all Subscriber users.
     * Compares the current favorite shows with the available shows and updates the list.
     */
    public void refreshFavoriteShows() {
        ArrayList<Show> shows = new ArrayList<>();
        shows.addAll(getMovies());
        shows.addAll(getSeries());

        for (User user : getUsers()) {
            if (user instanceof Subscriber) {
                Subscriber subscriber = (Subscriber) user;

                List<Show> showsToAdd = new ArrayList<>();
                List<Show> showsToRemove = new ArrayList<>();

                for (Show favoriteShow : subscriber.getFavoriteShows()) {
                    boolean showFound = false;

                    for (Show show : shows) {
                        if (show.getId().equals(favoriteShow.getId())) {
                            showsToAdd.add(show);
                            showsToRemove.add(favoriteShow);
                            showFound = true;
                            break;
                        }
                    }

                    if (!showFound) {
                        showsToRemove.add(favoriteShow);
                    }
                }

                subscriber.getFavoriteShows().removeAll(showsToRemove);
                subscriber.getFavoriteShows().addAll(showsToAdd);
            }
        }
    }
}