package gui;

import api.Data;
import api.shows.Movie;
import api.shows.Series;
import api.shows.Show;
import api.users.User;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class SimilarShowsGUI {

    public static void editSimilarShows(Show show, JDialog parentDialog, Data data) {
        // Create a new dialog for editing similar shows
        JDialog dialog = new JDialog(parentDialog, "Edit Similar Shows", true);
        dialog.setLayout(new BorderLayout());

        // Create a DefaultListModel to hold the similar shows in the JList
        DefaultListModel<String> similarShowsListModel = new DefaultListModel<>();

        // Populate the list model with existing similar shows
        for (Show similarShow : show.getSimilarShows()) {
            similarShowsListModel.addElement(similarShow.getTitle());
        }

        JList<String> similarShowsList = new JList<>(similarShowsListModel);
        JScrollPane scrollPane = createScrollPane(similarShowsList, 300, 200);

        JButton addButton = new JButton("Add");
        JButton removeButton = new JButton("Remove");
        JButton closeButton = new JButton("Close");

        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                addSimilarShow(show, parentDialog, data);
                dialog.dispose();
            }
        });

        removeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Handle remove similar show action
                int selectedIndex = similarShowsList.getSelectedIndex();
                if (selectedIndex != -1) {
                    deleteSimilarShow(show, show.getSimilarShows().get(selectedIndex), data);
                    dialog.dispose();
                } else {
                    displayInformation("Remove Similar Show", "Please select a similar show to remove.");
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
        buttonPanel.add(removeButton);
        buttonPanel.add(closeButton);

        dialog.add(scrollPane, BorderLayout.CENTER);
        dialog.add(buttonPanel, BorderLayout.SOUTH);

        // Set the size and make the dialog visible
        dialog.setSize(400, 300);
        dialog.setLocationRelativeTo(parentDialog);
        dialog.setVisible(true);
    }

    private static void addSimilarShow(Show show, JDialog parentDialog, Data data) {
        // Create a new dialog for adding a similar show
        JDialog dialog = new JDialog(parentDialog, "Add Similar Show", true);
        dialog.setLayout(new BorderLayout());

        // Get the list of available shows (excluding those already in similar shows list)
        ArrayList<Show> availableShows = getAvailableShows(show, data);

        // Create a combo box for the user to choose from
        JComboBox<Show> showComboBox = new JComboBox<>(availableShows.toArray(new Show[0]));
        JTextField titleField = new JTextField();
        JButton addButton = new JButton("Add");

        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Retrieve the selected show from the combo box
                Show selectedShow = (Show) showComboBox.getSelectedItem();

                if (selectedShow != null) {
                    // Add the new similar show to the list
                    show.getSimilarShows().add(selectedShow);

                    // Update the data and close the dialog
                    data.save();
                    dialog.dispose();
                } else {
                    displayInformation("Add Similar Show", "Please select a valid show.");
                }
            }
        });

        // Create a panel for the components
        JPanel panel = new JPanel(new GridLayout(3, 2));
        panel.add(new JLabel("Available Shows:"));
        panel.add(showComboBox);
        panel.add(new JLabel()); // Empty label for spacing
        panel.add(addButton);

        dialog.add(panel, BorderLayout.CENTER);

        // Set the size and make the dialog visible
        dialog.setSize(300, 150);
        dialog.setLocationRelativeTo(parentDialog);
        dialog.setVisible(true);
    }

    private static ArrayList<Show> getAvailableShows(Show show, Data data) {
        ArrayList<Show> availableShows = new ArrayList<>();

        if (show instanceof Movie) {
            for (Show availableShow : data.getMovies()) {
                if (!show.getSimilarShows().contains(availableShow)) {
                    availableShows.add(availableShow);
                }
            }
        } else if (show instanceof Series) {
            for (Show availableShow : data.getSeries()) {
                if (!show.getSimilarShows().contains(availableShow)) {
                    availableShows.add(availableShow);
                }
            }
        }
        availableShows.remove(show);

        return availableShows;
    }

    private static void deleteSimilarShow(Show show, Show similarShow, Data data) {
        show.getSimilarShows().remove(similarShow);
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
}