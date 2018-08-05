package robotvacuum;
/**
 * C.S. 350 
 * Prof. Wasniowski 
 * Classical Project
 *
 * Nicole Dubin 
 * Joseph Fernandez 
 * Alexandra Colette 
 * Robert Florence
 */

import java.util.Random;

public class Map {

    public char[][] map;
    private int rows;
    private int col;
    private int dirtCount;
    private int obstacleNum;
    private int min = 4;
    private int max = 8;

    public Map() {
        Random rand = new Random();
        this.rows = rand.nextInt((this.max - this.min) + 1) + min;
        this.col = rand.nextInt((this.max - this.min) + 1) + min;
        this.dirtCount = (int) Math.floor(((this.rows * this.col) * 4) / 5);
        this.obstacleNum = ((this.rows * this.col) - this.dirtCount);
        this.map = new char[this.rows][this.col];
    }

    public void populateMap() {

        Random rand = new Random();         //will generate a random number for rows and cols

        int randRow, randCol = 0;
        //System.out.println("r: " + this.rows + "\nc: " + this.col + "\nD: " + this.dirtCount + "\no: " + obstacleNum);
        for(int q = 0; q < this.rows; q++){
            for(int w = 0; w < this.col; w++){
                map[q][w] = 'x';
            }
        }                                           //init everything to dirt

        for (int k = 0; k < obstacleNum; k++) {

            randRow = rand.nextInt(this.rows);
            randCol = rand.nextInt(this.col);

            if (map[randRow][randCol] != 'o') {
                map[randRow][randCol] = 'o';
            } else {
                k--;
            }                                       //randomly change spots to obstacles if they aren't already
        }

    }

    public void displayMap() {
        System.out.println("------------------");
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < this.col; j++) {
                System.out.print(this.map[i][j] + "  ");
            }
            System.out.println("\n");
        }
        System.out.println("------------------");
    }

    public void updateMap(int x, int y, char mark) {
        this.map[x][y] = mark;
    }

    public char checkMap(int x, int y) {
        return this.map[x][y];
    }

    public boolean insideMap(int x, int y) {

        return (x < this.rows && x >= 0 && y < this.col && y >= 0);
    }

    public int getRows() {
        return this.rows;
    }


    public int getCol() {
        return this.col;
    }

    public int getDirtCount() {
        return dirtCount;
    }

    public void removeDirt() {
        dirtCount--;
    }


}
