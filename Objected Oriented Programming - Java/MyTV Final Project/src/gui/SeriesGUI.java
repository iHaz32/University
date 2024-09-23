package gui;

import api.Data;
import api.shows.Category;
import api.shows.Movie;
import api.shows.Season;
import api.shows.Series;
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

public class SeriesGUI {

    public static void showSeriesList(JFrame frame, Data data, User user) {
        DefaultListModel<String> seriesListModel = new DefaultListModel<>();

        for (Series series : data.getSeries()) {
            seriesListModel.addElement("<html>Title: " + series.getTitle() +
                    "<br>Description: " + series.getShortDescriptionFormatted() +
                    "<br>Genre: " + series.getCategory() +
                    "<br>Seasons:<br>" + series.getSeasonsAsString() +
                    "Rating: " + ((series.getRatingsAverage() == 0)? "-" : series.getRatingsAverage() + " (" + series.getRatings().size() + ")") + "<br><br></html>");
        }

        JList<String> seriesList = new JList<>(seriesListModel);
        JScrollPane scrollPane = createScrollPane(seriesList, 300, 200);

        JPanel customPanel = new JPanel(new BorderLayout());
        customPanel.add(scrollPane, BorderLayout.CENTER);

        JButton viewButton = new JButton("View");
        viewButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int selectedIndex = seriesList.getSelectedIndex();
                if (selectedIndex != -1) {
                    showSeriesDetails(data.getSeries().get(selectedIndex), user, data, (JDialog) SwingUtilities.getWindowAncestor(customPanel));
                } else {
                    displayInformation("View Series", "Please select a series to view.");
                }
            }
        });
        JPanel viewButtonPanel = new JPanel();
        viewButtonPanel.add(viewButton);

        if (user.getIsAdmin()) {
            JButton addButton = new JButton("Add");
            addButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    addSeriesDetails(data, (JDialog) SwingUtilities.getWindowAncestor(viewButtonPanel));
                }
            });


            viewButtonPanel.add(addButton);
        }
        customPanel.add(viewButtonPanel, BorderLayout.SOUTH);

        displayInformation("Series List", customPanel);
    }

    public static void showSeriesDetails(Series series, User user, Data data, JDialog dialog) {
        String details = "<html>" + "Title: " + series.getTitle() + "<br><br>" +
                "Description: " + series.getFullDescriptionFormatted() + "<br><br>" +
                "Is restricted: " + series.getIsRestrictedAsString() + "<br><br>" +
                "Genre: " + series.getCategory() + "<br><br>" +
                "Rating: " + ((series.getRatingsAverage() == 0) ? "-" : series.getRatingsAverage() + " (" + series.getRatings().size() + ")") + "<br><br>" +
                "Stars: " + series.getStarsAsString() + "<br><br>" +
                "Seasons:<br>" + series.getSeasonsAsString() + "<br><br>" +
                "Similar Series: " + series.getSimilarShowsAsString() + "<br><br>" +
                "</html>";

        JTextPane textPane = new JTextPane();
        textPane.setContentType("text/html");
        textPane.setText(details);
        textPane.setEditable(false);

        JScrollPane scrollPane = new JScrollPane(textPane);
        scrollPane.setPreferredSize(new Dimension(400, 300));

        // Add the "Ratings" button
        JButton ratingsButton = new JButton("Ratings");
        ratingsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                RatingsGUI.showRatingsDialog(series, user, data);
            }
        });

        JPanel buttonPanel = new JPanel();
        buttonPanel.add(ratingsButton);

        // Check if the user is an admin before adding "Edit" and "Delete" buttons
        if (user.getIsAdmin()) {
            // Add the "Edit" button
            JButton editButton = new JButton("Edit");
            editButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    editSeriesDetails(series, dialog, data);
                    data.refreshFavoriteShows();

                    JDialog currentDialog = (JDialog) SwingUtilities.getWindowAncestor(buttonPanel);
                    currentDialog.dispose();
                }
            });
            buttonPanel.add(editButton);

            // Add the "Delete" button
            JButton deleteButton = new JButton("Delete");
            deleteButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    deleteSeries(series, dialog, data);
                    data.refreshFavoriteShows();

                    JDialog currentDialog = (JDialog) SwingUtilities.getWindowAncestor(buttonPanel);
                    currentDialog.dispose();
                }
            });
            buttonPanel.add(deleteButton);
        } else {
            Subscriber subscriber = (Subscriber) user;
            if (!FavoritesGUI.isFavorite(subscriber, series)) {
                JButton addFavButton = new JButton("Add to favorites");
                addFavButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {
                        subscriber.addFavoriteShow(series);
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
                        subscriber.removeFavoriteShow(series);
                        data.save();

                        JDialog currentDialog = (JDialog) SwingUtilities.getWindowAncestor(buttonPanel);
                        currentDialog.dispose();
                    }
                });

                buttonPanel.add(removeFavButton);
            }
        }

        // Create a panel to hold both the scroll pane and the button
        JPanel mainPanel = new JPanel(new BorderLayout());
        mainPanel.add(scrollPane, BorderLayout.CENTER);
        mainPanel.add(buttonPanel, BorderLayout.SOUTH);

        displayInformation("Series Details", mainPanel);
    }



    private static void editSeriesDetails(Series series, JDialog dialog, Data data) {
        JTextField titleField = new JTextField(series.getTitle());
        JTextArea descriptionArea = new JTextArea(series.getDescription());
        JCheckBox restrictedCheckBox = new JCheckBox("Restricted", series.getIsRestricted());
        JComboBox<Category> categoryComboBox = new JComboBox<>(Category.values());
        categoryComboBox.setSelectedItem(series.getCategory());

        // Button to open the dialog for editing actors
        JButton editActorsButton = new JButton("Edit Actors");

        // Text field for displaying and editing stars
        JEditorPane starsField = new JEditorPane("text/html", series.getStarsAsString());
        starsField.setEditable(false);

        JPanel detailsPanel = new JPanel(new GridLayout(0, 2));
        detailsPanel.add(new JLabel("Title:"));
        detailsPanel.add(titleField);
        detailsPanel.add(new JLabel("Description:"));
        detailsPanel.add(new JScrollPane(descriptionArea));
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
                editActors(series, dialog, data);
                starsField.setText(series.getStarsAsString()); // Update the stars field after editing
                if (dialog != null) dialog.dispose();
            }
        });

        JButton editSeasonsButton = new JButton("Edit Seasons");
        editSeasonsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                editSeasons(series, dialog, data);
            }
        });

        JPanel buttonPanel = new JPanel();
        buttonPanel.add(editSeasonsButton);

        JButton editSimilarShowsButton = new JButton("Edit Similar Shows");
        editSimilarShowsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                editSimilarShows(series, (JDialog) SwingUtilities.getWindowAncestor(buttonPanel), data);
            }
        });

        buttonPanel.add(editSimilarShowsButton);

        detailsPanel.add(buttonPanel);

        int result = JOptionPane.showConfirmDialog(null, detailsPanel,
                "Series Details", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);

        if (result == JOptionPane.OK_OPTION) {
            try {
                // Update the series information based on the edited fields
                series.setTitle(titleField.getText());
                series.setDescription(descriptionArea.getText());
                series.setIsRestricted(restrictedCheckBox.isSelected());
                series.setCategory((Category) categoryComboBox.getSelectedItem());

                data.save();
            } catch (IllegalArgumentException e) {
                showErrorDialog(e.getMessage());
            }
            if (dialog != null) dialog.dispose();
        }
    }

    private static void editActors(Series series, JDialog parentDialog, Data data) {
        // A JTextArea for editing actors
        JTextArea actorsTextArea = new JTextArea(series.getStarsAsString());
        actorsTextArea.setLineWrap(true);
        actorsTextArea.setWrapStyleWord(true);

        // A JScrollPane to provide scrolling for the JTextArea
        JScrollPane scrollPane = new JScrollPane(actorsTextArea);

        // A panel to hold the JTextArea and JScrollPane
        JPanel panel = new JPanel(new BorderLayout());
        panel.add(scrollPane, BorderLayout.CENTER);

        // A OptionPane with the panel for editing actors
        int result = JOptionPane.showConfirmDialog(parentDialog, panel, "Edit Actors (Add <br> between them)", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);

        // Process the result when the user clicks OK
        if (result == JOptionPane.OK_OPTION) {
            try {
                // Update the movie's stars based on the edited values
                String actorsText = actorsTextArea.getText();
                List<String> actorsList = Arrays.asList(actorsText.split("<br>"));
                series.setStars(new ArrayList<>(actorsList));

                data.save();
            } catch (IllegalArgumentException e) {
                showErrorDialog(e.getMessage());
            }
        }
    }

    private static void addSeriesDetails(Data data, JDialog dialog) {
        Series newSeries = new Series("SeriesName", "SeriesDescription", false, Category.HORROR, new ArrayList<>(List.of("Acotr1", "ActorN")), new ArrayList<>(), new ArrayList<>(), new ArrayList<>(List.of(
                new Season(1, 2000, new ArrayList<>(List.of(1, 1, 1, 31, 40))))));
        data.seriesAdd(newSeries);
        data.save();

        editSeriesDetails(newSeries, dialog, data);
    }

    private static void deleteSeries(Series series, JDialog dialog, Data data) {
        data.seriesDelete(series);
        data.save();

        if (dialog != null) dialog.dispose();
    }

    private static void editSeasons(Series series, JDialog parentDialog, Data data) {
        // Create a new dialog for editing seasons
        JDialog dialog = new JDialog(parentDialog, "Edit Seasons", true);
        dialog.setLayout(new BorderLayout());

        // Create a DefaultListModel to hold the seasons in the JList
        DefaultListModel<String> seasonListModel = new DefaultListModel<>();

        // Populate the list model with existing seasons
        for (Season season : series.getSeasons()) {
            seasonListModel.addElement("Season " + season.getNumber() + " (" + season.getYear() + ")");
        }

        JList<String> seasonList = new JList<>(seasonListModel);
        JScrollPane scrollPane = createScrollPane(seasonList, 300, 200);

        JButton addButton = new JButton("Add");
        JButton editButton = new JButton("Edit");
        JButton removeButton = new JButton("Remove");
        JButton closeButton = new JButton("Close");

        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                addSeason(series, parentDialog, data);
                dialog.dispose();
            }
        });

        editButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Handle edit season action
                int selectedIndex = seasonList.getSelectedIndex();
                if (selectedIndex != -1) {
                    editSeason(series.getSeasons().get(selectedIndex), parentDialog, data);
                    dialog.dispose();
                } else {
                    displayInformation("Edit Season", "Please select a season to edit.");
                }
            }
        });

        removeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Handle remove season action
                int selectedIndex = seasonList.getSelectedIndex();
                if (selectedIndex != -1) {
                    deleteSeason(series, series.getSeasons().get(selectedIndex), data);
                    dialog.dispose();
                } else {
                    displayInformation("Remove Season", "Please select a season to remove.");
                }
            }
        });

        closeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Close the dialog
                dialog.dispose();
            }
        });

        JPanel buttonPanel = new JPanel();
        buttonPanel.add(addButton);
        buttonPanel.add(editButton);
        buttonPanel.add(removeButton);
        buttonPanel.add(closeButton);

        dialog.add(scrollPane, BorderLayout.CENTER);
        dialog.add(buttonPanel, BorderLayout.SOUTH);

        // Set the size and make the dialog visible
        dialog.setSize(400, 300);
        dialog.setLocationRelativeTo(parentDialog);
        dialog.setVisible(true);
    }

    private static void addSeason(Series series, JDialog parentDialog, Data data) {
        // Create a new dialog for adding a season
        JDialog dialog = new JDialog(parentDialog, "Add Season", true);
        dialog.setLayout(new GridLayout(4, 2));

        JTextField numberField = new JTextField();
        JTextField yearField = new JTextField();
        JTextField episodesField = new JTextField();

        JButton addButton = new JButton("Add");

        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    // Get the values from text fields
                    int number = Integer.parseInt(numberField.getText());
                    int year = Integer.parseInt(yearField.getText());
                    String episodesText = episodesField.getText();
                    String[] episodesArray = episodesText.split(",");
                    ArrayList<Integer> episodesList = new ArrayList<>();

                    // Parse episode durations
                    for (String episode : episodesArray) {
                        episodesList.add(Integer.parseInt(episode.trim()));
                    }

                    // Create a new season
                    Season newSeason = new Season(number, year, episodesList);

                    // Add the new season to the series
                    series.getSeasons().add(newSeason);

                    // Update the data and close the dialog
                    data.save();
                    dialog.dispose();
                } catch (IllegalArgumentException ex) {
                    // Handle invalid input
                    showErrorDialog("Invalid input. Please enter valid numbers for Number, Year, and Episodes.");
                }
            }
        });

        dialog.add(new JLabel("Number:"));
        dialog.add(numberField);
        dialog.add(new JLabel("Year:"));
        dialog.add(yearField);
        dialog.add(new JLabel("Episodes (comma-separated):"));
        dialog.add(episodesField);
        dialog.add(new JLabel()); // Empty label for spacing
        dialog.add(addButton);

        // Set the size and make the dialog visible
        dialog.setSize(300, 200);
        dialog.setLocationRelativeTo(parentDialog);
        dialog.setVisible(true);
    }


    private static void editSeason(Season season, JDialog parentDialog, Data data) {
        // Create a new dialog for editing a season
        JDialog dialog = new JDialog(parentDialog, "Edit Season", true);
        dialog.setLayout(new GridLayout(4, 2));

        JTextField numberField = new JTextField(String.valueOf(season.getNumber()));
        JTextField yearField = new JTextField(String.valueOf(season.getYear()));
        JTextField episodesField = new JTextField(season.getEpisodesAsString());

        JButton saveButton = new JButton("Save");

        saveButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    // Get the values from text fields
                    int number = Integer.parseInt(numberField.getText());
                    int year = Integer.parseInt(yearField.getText());
                    String episodesText = episodesField.getText();
                    String[] episodesArray = episodesText.split(",");
                    ArrayList<Integer> episodesList = new ArrayList<>();

                    // Parse episode durations
                    for (String episode : episodesArray) {
                        episodesList.add(Integer.parseInt(episode.trim()));
                    }

                    // Update the season with the edited values
                    season.setNumber(number);
                    season.setYear(year);
                    season.setEpisodes(episodesList);

                    // Update the data and close the dialog
                    data.save();
                    dialog.dispose();
                } catch (IllegalArgumentException ex) {
                    // Handle invalid input
                    showErrorDialog("Invalid input. Please enter valid numbers for Number, Year, and Episodes.");
                }
            }
        });

        dialog.add(new JLabel("Number:"));
        dialog.add(numberField);
        dialog.add(new JLabel("Year:"));
        dialog.add(yearField);
        dialog.add(new JLabel("Episodes (comma-separated):"));
        dialog.add(episodesField);
        dialog.add(new JLabel()); // Empty label for spacing
        dialog.add(saveButton);

        // Set the size and make the dialog visible
        dialog.setSize(300, 200);
        dialog.setLocationRelativeTo(parentDialog);
        dialog.setVisible(true);
    }


    private static void deleteSeason(Series series, Season season, Data data) {
        series.getSeasons().remove(season);
        data.save();
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