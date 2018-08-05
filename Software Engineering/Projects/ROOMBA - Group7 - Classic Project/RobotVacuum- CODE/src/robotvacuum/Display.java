package robotvacuum;
/*
 * C.S. 350
 * Prof. Wasniowski
 * Classical Project
 *
 * Nicole Dubin
 * Joseph Fernandez
 * Alexandra Colette
 * Robert Florence
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Display extends JFrame implements ActionListener {

    private Font regfont = new Font("TimesRoman", Font.BOLD, 15);
    private JPanel nleft, nright, northPanel;
    private MyPanel displayPanel;
    private static JFrame frame = null;

    private JTextArea outputarea;

    private int winXsize = 600;
    private int winYsize = 600;         //just using a square window 600X600 pixels

    private int winXpos = (int) ((GetScreenWorkingWidth() - winXsize) / 2);
    private int winYpos = (int) ((GetScreenWorkingHeight() - winYsize) / 2);       //center the window in the screen using window size

    private JButton Exit;
    int x;
    int y;
    char localMap[][];
    int dirty;

    public Display(Map room) {
        frame = this;
        frame.setLayout(new BorderLayout());
        frame.setSize(winXsize, winYsize);
        frame.setLocation(winXpos, winYpos);
        frame.setResizable(false);

        //Window broken into 4 Panels. North and Display panel make up majority
        //North has 2 panels. nLeft and nRight splitting it in half
        //Display panel is just a single panel that displays the cleaning grid
        northPanel = new JPanel();
        northPanel.setBorder(BorderFactory.createLineBorder(Color.black));

        nleft = new JPanel();
        nright = new JPanel();

        northPanel.setLayout(new GridLayout());
        northPanel.add(nleft);
        northPanel.add(nright);
        
        dirty = room.getDirtCount();
        outputarea = new JTextArea("Dirt Left: " + dirty, 1, 13);
        outputarea.setFont(regfont);
        outputarea.setOpaque(false);
        outputarea.setEditable(false);

        nleft.add(outputarea);

        Exit = new JButton("Exit");
        nright.add(Exit);
        Exit.addActionListener(this);

        displayPanel = new MyPanel();
        displayPanel.setBorder(BorderFactory.createLineBorder(Color.red));
        displayPanel.setLayout(new GridLayout(room.getRows(), room.getCol()));

        getContentPane().add("North", northPanel);
        getContentPane().add("Center", displayPanel);

        x = room.getRows();
        y = room.getCol();
        localMap = new char[x][y];          //global versions of MAP variables
        
        updateMap(room);          //creates localMap to use for display

        frame.setVisible(true);                             //displays window

        repaint();

        addWindowListener(new WindowAdapter() {         //window listener
            @Override
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });

    }
    public void updateMap(Map room){
    int x = room.getRows();
    int y = room.getCol();
    dirty = room.getDirtCount();
    String output = "Dirt Left: " + dirty;
    if(dirty == 9){
        outputarea.replaceRange(output,0,output.length()+1);
    } else {
        outputarea.replaceRange(output,0,output.length());
    }
    
    for (int z = 0; z < x; z++) {
            for (int w = 0; w < y; w++) {
                localMap[z][w] = room.map[z][w];
            }
        }  
    }

    public static int GetScreenWorkingWidth() {
        return java.awt.GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds().width;
    }

    public static int GetScreenWorkingHeight() {
        return java.awt.GraphicsEnvironment.getLocalGraphicsEnvironment().getMaximumWindowBounds().height;
    }

    @Override
    public void actionPerformed(ActionEvent e) {        //Listener to handle Exit button being pressed.

        if (e.getSource() == Exit) {
            dispose();
            System.exit(0);
        }
    }

    class MyPanel extends JPanel {

        @Override
        public void paintComponent(Graphics g) {
            
            int startX = 0;
            int startY = 0;
            int PanelXsize = 600;
            int PanelYsize = 550;        //Panel size defined by window size minus header bar

            int width = (int) Math.floor(PanelXsize / y);
            int height = (int) Math.floor(PanelYsize / x);

            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {

                    startX = j * width;
                    startY = i * height;
                    g.setColor(Color.black);
                    g.drawRect(startX, startY, width, height);

                    if (localMap[i][j] == 'x') {
                        g.setColor(Color.gray);             //dirt square = gray
                    }
                    if (localMap[i][j] == 'o') {
                        g.setColor(Color.blue);             //obstacles are blue
                    }
                    if (localMap[i][j] == 'c') {
                        g.setColor(Color.green);            //clean square = green
                    }
                    if (localMap[i][j] == 'R') {
                        g.setColor(Color.red);              //roomba is red
                    }

                    g.fillRect(startX, startY, width, height);

                }
            }
        }
    }
}