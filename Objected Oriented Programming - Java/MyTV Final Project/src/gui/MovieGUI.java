package gui;

import api.Data;
import api.shows.Category;
import api.shows.Movie;
import api.users.Subscriber;
import api.users.User;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static gui.SimilarShowsGUI.editSimilarShows;

public class MovieGUI {

    public static void showMovieList(Data data, User user) {
        DefaultListModel<String> movieListModel = new DefaultListModel<>();

        for (Movie movie : data.getMovies()) {
            movieListModel.addElement("<html>Title: " + movie.getTitle() +
                    "<br>Description: " + movie.getShortDescriptionFormatted() +
                    "<br>Genre: " + movie.getCategory() +
                    "<br>Year: " + movie.getYear() +
                    "<br>Duration: " + movie.getDurationAsString() +
                    "<br>Rating: " + ((movie.getRatingsAverage() == 0)? "-" : movie.getRatingsAverage() + " (" + movie.getRatings().size() + ")") + "<br><br></html>");;
        }

        JList<String> movieList = new JList<>(movieListModel);
        JScrollPane scrollPane = createScrollPane(movieList, 300, 200);

        JPanel customPanel = new JPanel(new BorderLayout());
        customPanel.add(scrollPane, BorderLayout.CENTER);

        JButton viewButton = new JButton("View");

        JPanel viewButtonPanel = new JPanel();
        viewButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Handle view action
                int selectedIndex = movieList.getSelectedIndex();
                if (selectedIndex != -1) {
                    showMovieDetails(data.getMovies().get(selectedIndex), user, data, (JDialog) SwingUtilities.getWindowAncestor(customPanel));
                } else {
                    displayInformation("View Movie", "Please select a movie to view.");
                }
            }
        });

        viewButtonPanel.add(viewButton);

        if (user.getIsAdmin()) {
            JButton addButton = new JButton("Add");
            addButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    addMovieDetails(data, (JDialog) SwingUtilities.getWindowAncestor(customPanel));
                }
            });

            viewButtonPanel.add(addButton);
        }
        customPanel.add(viewButtonPanel, BorderLayout.SOUTH);

        displayInformation("Movies List", customPanel);
    }

    private static void addMovieDetails(Data data, JDialog dialog) {
        Movie newMovie = new Movie("MovieName", "MovieDescription", false, Category.SCIFI, new ArrayList<>(List.of("Actor 1", "Actor N")), new ArrayList<>(), new ArrayList<>(),2000, 60);
        data.movieAdd(newMovie);
        data.save();

        editMovieDetails(newMovie, dialog, data);
    }

    public static void showMovieDetails(Movie movie, User user, Data data, JDialog dialog) {
        String details = "<html>" + "Title: " + movie.getTitle() + "<br><br>" +
                "Description: " + movie.getFullDescriptionFormatted() + "<br><br>" +
                "Year: " + movie.getYear() + "<br><br>" +
                "Duration: " + movie.getDurationAsString() + "<br><br>" +
                "Is restricted: " + movie.getIsRestrictedAsString() + "<br><br>" +
                "Genre: " + movie.getCategory() + "<br><br>" +
                "Rating: " + ((movie.getRatingsAverage() == 0)? "-" : movie.getRatingsAverage() + " (" + movie.getRatings().size() + ")") + "<br><br>" +
                "Stars: " + movie.getStarsAsString() + "<br><br>" +
                "Similar Movies: " + movie.getSimilarShowsAsString() + "<br><br>" +
                "</html>";

        JTextPane textPane = new JTextPane();
        textPane.setContentType("text/html");
        textPane.setText(details);
        textPane.setEditable(false);

        JScrollPane scrollPane = new JScrollPane(textPane);
        scrollPane.setPreferredSize(new Dimension(400, 300));

        // Adding the "Ratings" button
        JButton ratingsButton = new JButton("Ratings");
        ratingsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                RatingsGUI.showRatingsDialog(movie, user, data);
            }
        });

        JPanel buttonPanel = new JPanel();
        buttonPanel.add(ratingsButton);

        // Check if the user is an admin before adding "Edit" and "Delete" buttons
        if (user.getIsAdmin()) {
            // Adding the "Edit" button
            JButton editButton = new JButton("Edit");
            editButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    editMovieDetails(movie, dialog, data);
                    data.refreshFavoriteShows();

                    JDialog currentDialog = (JDialog) SwingUtilities.getWindowAncestor(buttonPanel);
                    currentDialog.dispose();
                }
            });
            buttonPanel.add(editButton);

            // Adding the "Delete" button
            JButton deleteButton = new JButton("Delete");
            deleteButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    deleteMovie(movie, dialog, data);
                    data.refreshFavoriteShows();

                    JDialog currentDialog = (JDialog) SwingUtilities.getWindowAncestor(buttonPanel);
                    currentDialog.dispose();
                }
            });
            buttonPanel.add(deleteButton);
        } else {
            Subscriber subscriber = (Subscriber) user;
            if (!FavoritesGUI.isFavorite(subscriber, movie)) {
                JButton addFavButton = new JButton("Add to favorites");
                addFavButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        subscriber.addFavoriteShow(movie);
                        data.save();

                        JDialog currentDialog = (JDialog) SwingUtilities.getWindowAncestor(buttonPanel);
                        currentDialog.dispose();
                    }
                });

                buttonPanel.add(addFavButton);
            } else {
                JButton removeFavButton = new JButton("Remove from favorites");
                removeFavButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        subscriber.removeFavoriteShow(movie);
                        data.save();

                        JDialog currentDialog = (JDialog) SwingUtilities.getWindowAncestor(buttonPanel);
                        currentDialog.dispose();
                    }
                });

                buttonPanel.add(removeFavButton);
            }
        }

        // A panel to hold both the scroll pane and the buttons
        JPanel mainPanel = new JPanel(new BorderLayout());
        mainPanel.add(scrollPane, BorderLayout.CENTER);
        mainPanel.add(buttonPanel, BorderLayout.SOUTH);

        displayInformation("Movie Details", mainPanel);
    }

    private static void editMovieDetails(Movie movie, JDialog dialog, Data data) {
        JTextField titleField = new JTextField(movie.getTitle());
        JTextArea descriptionArea = new JTextArea(movie.getDescription());
        JTextField yearField = new JTextField(String.valueOf(movie.getYear()));
        JTextField durationField = new JTextField(String.valueOf(movie.getDuration()));
        JCheckBox restrictedCheckBox = new JCheckBox("Restricted", movie.getIsRestricted());
        JComboBox<Category> categoryComboBox = new JComboBox<>(Category.values());
        categoryComboBox.setSelectedItem(movie.getCategory());

        // Button to open the dialog for editing actors
        JButton editActorsButton = new JButton("Edit Actors");

        // Text field for displaying and editing stars
        JEditorPane starsField = new JEditorPane("text/html", movie.getStarsAsString());
        starsField.setEditable(false);

        JPanel detailsPanel = new JPanel(new GridLayout(0, 2));
        detailsPanel.add(new JLabel("Title:"));
        detailsPanel.add(titleField);
        detailsPanel.add(new JLabel("Description:"));
        detailsPanel.add(new JScrollPane(descriptionArea));
        detailsPanel.add(new JLabel("Year:"));
        detailsPanel.add(yearField);
        detailsPanel.add(new JLabel("Duration:"));
        detailsPanel.add(durationField);
        detailsPanel.add(new JLabel("Restricted:"));
        detailsPanel.add(restrictedCheckBox);
        detailsPanel.add(new JLabel("Genre:"));
        detailsPanel.add(categoryComboBox);
        detailsPanel.add(new JLabel("Stars:"));
        detailsPanel.add(starsField);
        detailsPanel.add(new JLabel()); // Empty label for spacing
        detailsPanel.add(editActorsButton);

        // Action listener for the "Edit Actors" button
        editActorsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Open a new dialog for editing actors
                editActors(movie, dialog, data);
                starsField.setText(movie.getStarsAsString()); // Update the stars field after editing
                if (dialog != null) dialog.dispose();
            }
        });

        JButton editSimilarShowsButton = new JButton("Edit Similar Shows");
        editSimilarShowsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                editSimilarShows(movie, (JDialog) SwingUtilities.getWindowAncestor(detailsPanel), data);
            }
        });

        detailsPanel.add(editSimilarShowsButton);

        int result = JOptionPane.showConfirmDialog(null, detailsPanel,
                "Movie Details", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);

        if (result == JOptionPane.OK_OPTION) {
            try {
                // Update the movie information based on the edited fields
                movie.setTitle(titleField.getText());
                movie.setDescription(descriptionArea.getText());
                movie.setYear(Integer.parseInt(yearField.getText()));
                movie.setDuration(Integer.parseInt(durationField.getText()));
                movie.setIsRestricted(restrictedCheckBox.isSelected());
                movie.setCategory((Category) categoryComboBox.getSelectedItem());

                data.save();
            } catch (IllegalArgumentException e) {
                showErrorDialog(e.getMessage());
            }
            if (dialog != null) dialog.dispose();
        }
    }

    private static void editActors(Movie movie, JDialog parentDialog, Data data) {
        // A JTextArea for editing actors
        JTextArea actorsTextArea = new JTextArea(movie.getStarsAsString());
        actorsTextArea.setLineWrap(true);
        actorsTextArea.setWrapStyleWord(true);

        // A JScrollPane to provide scrolling for the JTextArea
        JScrollPane scrollPane = new JScrollPane(actorsTextArea);

        // A panel to hold the JTextArea and JScrollPane
        JPanel panel = new JPanel(new BorderLayout());
        panel.add(scrollPane, BorderLayout.CENTER);

        // A JOptionPane with the panel for editing actors
        int result = JOptionPane.showConfirmDialog(parentDialog, panel, "Edit Actors (Add <br> between them)", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);

        // Process the result when the user clicks OK
        if (result == JOptionPane.OK_OPTION) {
            try {
                // Update the movie's stars based on the edited values
                String actorsText = actorsTextArea.getText();
                List<String> actorsList = Arrays.asList(actorsText.split("<br>"));
                movie.setStars(new ArrayList<>(actorsList));

                data.save();
            } catch (IllegalArgumentException e) {
                showErrorDialog(e.getMessage());
            }
        }
    }

    private static void deleteMovie(Movie movie, JDialog dialog, Data data) {
        data.movieDelete(movie);
        data.save();

        if (dialog != null) dialog.dispose();
    }

    private static JScrollPane createScrollPane(JComponent component, int width, int height) {
        JScrollPane scrollPane = new JScrollPane(component);
        setPreferredSize(scrollPane, width, height);
        return scrollPane;
    }

    private static void setPreferredSize(JComponent component, int width, int height) {
        Dimension dimension = new Dimension(width, height);
        component.setPreferredSize(dimension);
        component.setMaximumSize(dimension);
        component.setMinimumSize(dimension);
    }

    private static void displayInformation(String title, Component component) {
        JOptionPane.showMessageDialog(null, component, title, JOptionPane.INFORMATION_MESSAGE);
    }

    private static void displayInformation(String title, String message) {
        JOptionPane.showMessageDialog(null, message, title, JOptionPane.INFORMATION_MESSAGE);
    }

    private static void showErrorDialog(String message) {
        JOptionPane.showMessageDialog(null, message, "Error", JOptionPane.ERROR_MESSAGE);
    }
}
