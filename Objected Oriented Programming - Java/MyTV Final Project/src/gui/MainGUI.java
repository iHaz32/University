package gui;

import api.Auth;
import api.Data;
import api.SearchEngine;
import api.shows.Category;
import api.shows.Show;
import api.users.Subscriber;
import api.users.User;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;

import static gui.MovieGUI.showMovieList;
import static gui.SeriesGUI.showSeriesList;

public class MainGUI {

    private JFrame frame;
    private Data data;
    private Auth auth;
    private SearchEngine searchEngine;
    private JTextField loginUsernameField;
    private JPasswordField loginPasswordField;
    private JTextField registerFirstNameField;
    private JTextField registerLastNameField;
    private JTextField registerUsernameField;
    private JPasswordField registerPasswordField;

    private User user;

    public MainGUI() {
        frame = new JFrame("MyTV");
        frame.setSize(400, 300);
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        buildUI();
        data = new Data();
        auth = new Auth();
        searchEngine = new SearchEngine();
        data.load();
        frame.setVisible(true);
    }

    private void buildUI() {

        // Login Panel
        JPanel loginPanel = new JPanel(new GridLayout(3, 2));
        loginUsernameField = new JTextField();
        loginPasswordField = new JPasswordField();
        JButton loginButton = new JButton("Login");

        loginPanel.add(new JLabel("Username:"));
        loginPanel.add(loginUsernameField);
        loginPanel.add(new JLabel("Password:"));
        loginPanel.add(loginPasswordField);
        loginPanel.add(new JLabel()); // Empty label for spacing
        loginPanel.add(loginButton);

        // Register Panel
        JPanel registerPanel = new JPanel(new GridLayout(5, 2));
        registerFirstNameField = new JTextField();
        registerLastNameField = new JTextField();
        registerUsernameField = new JTextField();
        registerPasswordField = new JPasswordField();
        JButton registerButton = new JButton("Register");

        registerPanel.add(new JLabel("First Name:"));
        registerPanel.add(registerFirstNameField);
        registerPanel.add(new JLabel("Last Name:"));
        registerPanel.add(registerLastNameField);
        registerPanel.add(new JLabel("Username:"));
        registerPanel.add(registerUsernameField);
        registerPanel.add(new JLabel("Password:"));
        registerPanel.add(registerPasswordField);
        registerPanel.add(new JLabel()); // Empty label for spacing
        registerPanel.add(registerButton);

        // Tabbed Pane for Login and Register
        JTabbedPane tabbedPane = new JTabbedPane();
        tabbedPane.addTab("Login", loginPanel);
        tabbedPane.addTab("Register", registerPanel);

        // Add tabbedPane to the main frame
        frame.add(tabbedPane);

        // Add action listeners for login and register buttons
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                handleLogin(loginUsernameField.getText(), new String(loginPasswordField.getPassword()));
            }
        });

        registerButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                handleRegister(
                        registerFirstNameField.getText(),
                        registerLastNameField.getText(),
                        registerUsernameField.getText(),
                        new String(registerPasswordField.getPassword())
                );
            }
        });

        // Save data on window close
        frame.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                data.save();
            }
        });
    }

    private void handleLogin(String username, String password) {
        try {
            user = auth.login(data.getUsers(), username, password);
            if (user == null) showErrorDialog("Unknown Error");
            else {
                if (user.getIsAdmin()) openAdminPanel();
                else openSubscriberPanel();
            }
        } catch (IllegalArgumentException e) {
            showErrorDialog(e.getMessage());
        }
    }

    private void handleRegister(String firstName, String lastName, String username, String password) {
        try {
            auth.register(data.getUsers(), firstName, lastName, username, password);
        } catch (IllegalArgumentException e) {
            showErrorDialog(e.getMessage());
        }
    }

    private void openAdminPanel() {
        JPanel adminPanelContent = new JPanel();
        adminPanelContent.setLayout(new BoxLayout(adminPanelContent, BoxLayout.Y_AXIS));

        JLabel welcomeLabel = new JLabel("Welcome " + user.getUsername());
        welcomeLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        JButton moviesButton = new JButton("Movies");
        JButton seriesButton = new JButton("Series");
        JButton searchButton = new JButton("Search");
        JButton logOutButton = new JButton("Log Out");

        moviesButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        seriesButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        searchButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        logOutButton.setAlignmentX(Component.CENTER_ALIGNMENT);

        adminPanelContent.add(welcomeLabel);
        adminPanelContent.add(Box.createVerticalStrut(30));
        adminPanelContent.add(moviesButton);
        adminPanelContent.add(Box.createVerticalStrut(20));
        adminPanelContent.add(seriesButton);
        adminPanelContent.add(Box.createVerticalStrut(20));
        adminPanelContent.add(searchButton);
        adminPanelContent.add(Box.createVerticalStrut(20));
        adminPanelContent.add(logOutButton);

        moviesButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                showMovieList(data, user);
            }
        });

        seriesButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                showSeriesList(frame, data, user);
            }
        });

        searchButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                SearchEngineGUI.showSearchResults(frame, data, searchEngine, user);
            }
        });

        logOutButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                logOut();
            }
        });

        frame.setContentPane(adminPanelContent);
        frame.revalidate();
        frame.repaint();

        showSuccessDialog("Welcome " + user.getFirstName() + " " + user.getLastName() + "!");
    }

    private void openSubscriberPanel() {
        JPanel subscriberPanelContent = new JPanel();
        subscriberPanelContent.setLayout(new BoxLayout(subscriberPanelContent, BoxLayout.Y_AXIS));

        JLabel welcomeLabel = new JLabel("Welcome " + user.getUsername());
        welcomeLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        JButton moviesButton = new JButton("Movies");
        JButton seriesButton = new JButton("Series");
        JButton favoritesButton = new JButton("Favorites");
        JButton searchButton = new JButton("Search");
        JButton logOutButton = new JButton("Log Out");

        moviesButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        seriesButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        favoritesButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        searchButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        logOutButton.setAlignmentX(Component.CENTER_ALIGNMENT);

        subscriberPanelContent.add(welcomeLabel);
        subscriberPanelContent.add(Box.createVerticalStrut(30));
        subscriberPanelContent.add(moviesButton);
        subscriberPanelContent.add(Box.createVerticalStrut(20));
        subscriberPanelContent.add(seriesButton);
        subscriberPanelContent.add(Box.createVerticalStrut(20));
        subscriberPanelContent.add(favoritesButton);
        subscriberPanelContent.add(Box.createVerticalStrut(20));
        subscriberPanelContent.add(searchButton);
        subscriberPanelContent.add(Box.createVerticalStrut(20));
        subscriberPanelContent.add(logOutButton);

        moviesButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                showMovieList(data, user);
            }
        });

        seriesButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                showSeriesList(frame, data, user);
            }
        });

        favoritesButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                FavoritesGUI.showFavoritesDialog(frame, data, (Subscriber) user);
            }
        });

        searchButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                SearchEngineGUI.showSearchResults(frame, data, searchEngine, user);
            }
        });

        logOutButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                logOut();
            }
        });

        frame.setContentPane(subscriberPanelContent);
        frame.revalidate();
        frame.repaint();

        showSuccessDialog("Welcome " + user.getFirstName() + " " + user.getLastName() + "!");
    }

    private void showErrorDialog(String message) {
        JOptionPane.showMessageDialog(frame, message, "Error", JOptionPane.ERROR_MESSAGE);
    }

    private void showSuccessDialog(String message) {
        JOptionPane.showMessageDialog(frame, message, "Success", JOptionPane.PLAIN_MESSAGE);
    }

    private static void displayInformation(String title, String message) {
        JOptionPane.showMessageDialog(null, message, title, JOptionPane.INFORMATION_MESSAGE);
    }

    private void logOut() {
        // Clear user reference
        user = null;

        // Reset the frame content to the login and register tabs
        frame.getContentPane().removeAll();
        buildUI();
        frame.revalidate();
        frame.repaint();

        // Show a success message
        showSuccessDialog("Logged out successfully!");
    }
}