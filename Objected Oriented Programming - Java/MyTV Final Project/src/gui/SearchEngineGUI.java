package gui;

import api.Data;
import api.SearchEngine;
import api.shows.Category;
import api.shows.Movie;
import api.shows.Series;
import api.shows.Show;
import api.users.User;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

public class SearchEngineGUI {

    public static void showSearchResults(JFrame parentFrame, Data data, SearchEngine searchEngine, User user) {
        JDialog searchResultsDialog = new JDialog(parentFrame, "Search Results", true);
        searchResultsDialog.setSize(400, 200);
        searchResultsDialog.setLocationRelativeTo(parentFrame);

        // Create components for the search results dialog
        JTextField titleField = new JTextField();
        JComboBox<String> typeComboBox = new JComboBox<>(new String[]{"All", "Movie", "Series"});
        JTextField actorField = new JTextField();
        JCheckBox restrictedCheckBox = new JCheckBox("Restricted");

        Category[] categoryValues = Category.values();
        Category[] allCategories = new Category[categoryValues.length + 1];
        allCategories[0] = null; // Add null for "All"
        System.arraycopy(categoryValues, 0, allCategories, 1, categoryValues.length);
        JComboBox<Category> categoryComboBox = new JComboBox<>(allCategories);

        String[] minRatingOptions = {"1", "2", "3", "4", "5"};
        JComboBox<String> minRatingComboBox = new JComboBox<>(minRatingOptions);

        // Create a button to perform the search
        JButton searchButton = new JButton("Search");
        searchButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String selectedMinRating = (String) minRatingComboBox.getSelectedItem();

                performSearch(searchEngine,
                        titleField.getText(),
                        (String) typeComboBox.getSelectedItem(),
                        actorField.getText(),
                        restrictedCheckBox.isSelected(),
                        (Category) categoryComboBox.getSelectedItem(),
                        Double.parseDouble(selectedMinRating), user, data);
                searchResultsDialog.dispose();
            }
        });

        // Create layout for search results dialog
        JPanel searchPanel = new JPanel(new GridLayout(7, 2));
        searchPanel.add(new JLabel("Title:"));
        searchPanel.add(titleField);
        searchPanel.add(new JLabel("Type:"));
        searchPanel.add(typeComboBox);
        searchPanel.add(new JLabel("Actor:"));
        searchPanel.add(actorField);
        searchPanel.add(new JLabel("Restricted:"));
        searchPanel.add(restrictedCheckBox);
        searchPanel.add(new JLabel("Category:"));
        searchPanel.add(categoryComboBox);
        searchPanel.add(new JLabel("Minimum Rating:"));
        searchPanel.add(minRatingComboBox);
        searchPanel.add(new JLabel()); // Empty label for spacing
        searchPanel.add(searchButton);

        // Add search panel to the search results dialog
        searchResultsDialog.add(searchPanel);
        searchResultsDialog.setVisible(true);
    }

    private static void performSearch(SearchEngine searchEngine, String title, String type, String actor, boolean isRestricted, Category category, double minRating, User user, Data data) {
        ArrayList<Show> searchResults = searchEngine.search(title, type, actor, isRestricted, category, minRating, data);

        // Display search results
        if (!searchResults.isEmpty()) {
            JPanel resultPanel = new JPanel(new GridLayout(searchResults.size(), 1));

            for (Show result : searchResults) {
                JLabel resultLabel = new JLabel(result.getTitle() + " (" + result.getType() + ")");
                resultLabel.addMouseListener(new MouseAdapter() {
                    @Override
                    public void mouseClicked(MouseEvent e) {
                        if (result.getType().equals("Movie")) {
                            //Movie
                            MovieGUI.showMovieDetails((Movie) result, user, data, null);
                            JDialog currentDialog = (JDialog) SwingUtilities.getWindowAncestor(resultPanel);
                            currentDialog.dispose();
                        } else if (result.getType().equals("Series")) {
                            //Series
                            SeriesGUI.showSeriesDetails((Series) result, user, data, null);
                            JDialog currentDialog = (JDialog) SwingUtilities.getWindowAncestor(resultPanel);
                            currentDialog.dispose();
                        }
                    }
                });
                resultPanel.add(resultLabel);
            }

            JScrollPane resultScrollPane = new JScrollPane(resultPanel);
            JOptionPane.showMessageDialog(null, resultScrollPane, "Search Results", JOptionPane.INFORMATION_MESSAGE);
        } else {
            JOptionPane.showMessageDialog(null, "No results found.", "Search Results", JOptionPane.INFORMATION_MESSAGE);
        }
    }

}