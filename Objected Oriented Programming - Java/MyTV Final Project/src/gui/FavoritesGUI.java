package gui;

import api.Data;
import api.shows.Show;
import api.users.Subscriber;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class FavoritesGUI {

    public static void showFavoritesDialog(JFrame parentFrame, Data data, Subscriber subscriber) {
        JDialog dialog = new JDialog(parentFrame, "Favorites", true);
        dialog.setLayout(new BorderLayout());

        DefaultListModel<String> favoritesListModel = new DefaultListModel<>();
        JList<String> favoritesList = new JList<>(favoritesListModel);
        JScrollPane scrollPane = createScrollPane(favoritesList, 300, 200);

        JButton addButton = new JButton("Add Favorite");
        JButton removeButton = new JButton("Remove Favorite");
        JButton closeButton = new JButton("Close");

        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                addFavorite(subscriber, dialog, data);
                refreshFavoritesList(subscriber, favoritesListModel);
            }
        });

        removeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int selectedIndex = favoritesList.getSelectedIndex();
                if (selectedIndex != -1) {
                    removeFavorite(subscriber, selectedIndex, data);
                    refreshFavoritesList(subscriber, favoritesListModel);
                } else {
                    displayInformation("Delete favorite show", "Please select a show to delete from favorites list.");
                }
            }
        });

        closeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dialog.dispose();
            }
        });

        JPanel buttonPanel = new JPanel();
        buttonPanel.add(addButton);
        buttonPanel.add(removeButton);
        buttonPanel.add(closeButton);

        dialog.add(scrollPane, BorderLayout.CENTER);
        dialog.add(buttonPanel, BorderLayout.SOUTH);

        refreshFavoritesList(subscriber, favoritesListModel);

        dialog.setSize(400, 300);
        dialog.setLocationRelativeTo(parentFrame);
        dialog.setVisible(true);
    }

    public static void addFavorite(Subscriber subscriber, JDialog parentDialog, Data data) {
        JDialog dialog = new JDialog(parentDialog, "Add Favorite", true);
        dialog.setLayout(new BorderLayout());

        ArrayList<Show> availableShows = getAvailableShows(subscriber, data);

        JComboBox<Show> showComboBox = new JComboBox<>(availableShows.toArray(new Show[0]));
        JButton addButton = new JButton("Add");

        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Show selectedShow = (Show) showComboBox.getSelectedItem();

                if (selectedShow != null) {
                    subscriber.addFavoriteShow(selectedShow);
                    data.save();
                    dialog.dispose();
                } else {
                    displayInformation("Add Favorite", "Please select a valid show.");
                }
            }
        });

        JPanel panel = new JPanel(new GridLayout(3, 2));
        panel.add(new JLabel("Available Shows:"));
        panel.add(showComboBox);
        panel.add(new JLabel()); // Empty label for spacing
        panel.add(addButton);

        dialog.add(panel, BorderLayout.CENTER);

        dialog.setSize(300, 150);
        dialog.setLocationRelativeTo(parentDialog);
        dialog.setVisible(true);
    }

    private static ArrayList<Show> getAvailableShows(Subscriber subscriber, Data data) {
        ArrayList<Show> availableShows = new ArrayList<>();

        for (Show availableShow : data.getMovies()) {
            if (!subscriber.getFavoriteShows().contains(availableShow)) {
                availableShows.add(availableShow);
            }
        }

        for (Show availableShow : data.getSeries()) {
            if (!subscriber.getFavoriteShows().contains(availableShow)) {
                availableShows.add(availableShow);
            }
        }

        return availableShows;
    }

    public static void removeFavorite(Subscriber subscriber, int index, Data data) {
        subscriber.getFavoriteShows().remove(index);
        data.save();
    }

    private static void refreshFavoritesList(Subscriber subscriber, DefaultListModel<String> favoritesListModel) {
        favoritesListModel.clear();
        for (Show favorite : subscriber.getFavoriteShows()) {
            favoritesListModel.addElement(favorite.getTitle());
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

    private static void displayInformation(String title, String message) {
        JOptionPane.showMessageDialog(null, message, title, JOptionPane.INFORMATION_MESSAGE);
    }

    public static boolean isFavorite(Subscriber subscriber, Show show) {
        return subscriber.getFavoriteShows().contains(show);
    }
}