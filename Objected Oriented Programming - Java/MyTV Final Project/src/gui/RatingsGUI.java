package gui;

import api.Data;
import api.shows.Rating;
import api.shows.Show;
import api.users.User;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class RatingsGUI {

    public static void showRatingsDialog(Show show, User user, Data data) {
        DefaultListModel<String> ratingsListModel = new DefaultListModel<>();

        ArrayList<Rating> ratings = new ArrayList<>(show.getRatings());
        for (Rating rating : ratings) {
            String ratingText = "<html>User: " + rating.getAuthor().getUsername() +
                    "<br>Rating: " + rating.getRating() +
                    "<br>Comment: " + rating.getTextFormatted() + "<br><br></html>";

            ratingsListModel.addElement(ratingText);
        }

        JList<String> ratingsList = new JList<>(ratingsListModel);
        JScrollPane scrollPane = createScrollPane(ratingsList, 300, 200);

        JPanel customPanel = new JPanel(new BorderLayout());
        customPanel.add(scrollPane, BorderLayout.CENTER);

        if (user.getIsAdmin()) {
            JButton deleteButton = new JButton("Delete Rating");
            deleteButton.addActionListener(e -> {
                handleDeleteRating(ratingsList.getSelectedIndex(), show, data, (JDialog) SwingUtilities.getWindowAncestor(customPanel));
                JOptionPane.getRootFrame().dispose(); // Close the dialog after deletion
            });
            customPanel.add(deleteButton, BorderLayout.SOUTH);
        } else {
            JButton manageButton = new JButton("Manage Rating");
            manageButton.addActionListener(e -> {
                handleManageRating(user, ratingsList.getSelectedIndex(), show, data, customPanel);
                JOptionPane.getRootFrame().dispose(); // Close the dialog after deletion
            });
            customPanel.add(manageButton, BorderLayout.SOUTH);
        }

        displayInformation("Ratings for " + show.getTitle(), customPanel);
    }

    private static void handleManageRating(User user, int selectedIndex, Show show, Data data, Component parentComponent) {
        Rating possibleRating = null;
        int possibleIndex = -1;
        for (int i = 0; i < show.getRatings().size(); i++) {
            Rating rating = show.getRatings().get(i);
            if (rating.getAuthor().getUsername().equals(user.getUsername())) {
                possibleRating = rating;
                possibleIndex = i;
                break;
            }
        }

        if ((selectedIndex == possibleIndex && selectedIndex != -1) || (selectedIndex == -1 && possibleIndex != -1)) {
            // EDIT
            handleEditRating(possibleRating, show, data, parentComponent);
        } else if (selectedIndex == -1) {
            // CREATE
            handleCreateRating(show, data, parentComponent, user);
        } else {
            // NO PERMISSION
            showErrorDialog("Permission Denied");
        }
    }

    private static void handleEditRating(Rating rating, Show show, Data data, Component parentComponent) {
        // Open a dialog for editing with previous values
        JComboBox<Integer> ratingComboBox = new JComboBox<>(new Integer[]{1, 2, 3, 4, 5});
        JTextArea commentArea = new JTextArea(rating.getText());

        JPanel editPanel = new JPanel(new GridLayout(0, 1));
        editPanel.add(new JLabel("Rating:"));
        editPanel.add(ratingComboBox);
        editPanel.add(new JLabel("Comment:"));
        editPanel.add(new JScrollPane(commentArea));

        // Set the selected rating in the combo box
        ratingComboBox.setSelectedItem((int) rating.getRating());

        // Add the "Delete" button
        JButton deleteButton = new JButton("Delete");
        deleteButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Perform the delete operation
                show.getRatings().remove(rating);
                data.save();
                JOptionPane.getRootFrame().dispose(); // Close the dialog after deletion
            }
        });
        editPanel.add(deleteButton);

        int result = JOptionPane.showConfirmDialog(parentComponent, editPanel, "Edit Rating", JOptionPane.OK_CANCEL_OPTION);

        if (result == JOptionPane.OK_OPTION) {
            // Update the rating with the new values
            int newRating = (int) ratingComboBox.getSelectedItem();
            String newComment = commentArea.getText();
            try {
                rating.setRating(newRating);
                rating.setText(newComment);
                data.save();
            } catch (IllegalArgumentException ex) {
                showErrorDialog(ex.getMessage());
            }
        }
    }


    private static void handleCreateRating(Show show, Data data, Component parentComponent, User user) {
        // Open a dialog for creating with empty values
        JComboBox<Integer> ratingComboBox = new JComboBox<>(new Integer[]{1, 2, 3, 4, 5});
        JTextArea commentArea = new JTextArea();

        JPanel createPanel = new JPanel(new GridLayout(0, 1));
        createPanel.add(new JLabel("Rating:"));
        createPanel.add(ratingComboBox);
        createPanel.add(new JLabel("Comment:"));
        createPanel.add(new JScrollPane(commentArea));

        int result = JOptionPane.showConfirmDialog(parentComponent, createPanel, "Create Rating", JOptionPane.OK_CANCEL_OPTION);
        if (result == JOptionPane.OK_OPTION) {
            // Create a new rating with the entered values
            int newRating = (int) ratingComboBox.getSelectedItem();
            String newComment = commentArea.getText();
            try {
                Rating newRatingObj = new Rating(user, newComment, newRating);
                show.addRating(newRatingObj);
                data.save();
            } catch (IllegalArgumentException e) {
                showErrorDialog(e.getMessage());
            }
        }
    }


    private static void handleDeleteRating(int selectedIndex, Show show, Data data, JDialog dialog) {
        if (selectedIndex != -1) {
            show.getRatings().remove(selectedIndex);
            data.save();

            dialog.dispose();
        } else {
            displayInformation("Delete Rating", "Please select a rating to delete.");
        }
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