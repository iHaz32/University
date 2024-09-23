import gui.MainGUI;

import javax.swing.*;

public class Main {

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new MainGUI(); // Create an instance of MainGUI when the Swing thread is ready
            }
        });
    }
}
