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

import java.util.concurrent.TimeUnit;
public class Move {

    private Map room = new Map();
    private Device rc = new Device();
    private Display window;
    private int[][] visitCount;
    private static int MAX = 2;

    public Move(Map room, Device rc) {
        this.room = room;
        this.rc = rc;
        this.visitCount = new int[this.room.getRows()][this.room.getCol()];
        this.window = new Display(room);

        for(int i = 0; i < this.room.getRows(); i++){
            for(int j = 0; j < this.room.getCol(); j++){
                visitCount[i][j] = 0;
            }
        }
    }

    public boolean vacuuming(int x, int y) throws InterruptedException {
        if (this.room.getDirtCount() > 0 && this.rc.getPower() > 0) {

            if (this.room.insideMap(x, y - 1)) {
                if (this.room.checkMap(x, y - 1) == 'x') {
                    vacuumFunction(x, y, x, y - 1);
                    this.room.removeDirt();
                    return vacuuming(x, y - 1);
                }
            }

            if (this.room.insideMap(x + 1, y)) {
                if (this.room.checkMap(x + 1, y) == 'x') {
                    vacuumFunction(x, y, x + 1, y);
                    this.room.removeDirt();
                    return vacuuming(x + 1, y);
                }
            }

            if (this.room.insideMap(x, y + 1)) {
                if (this.room.checkMap(x, y + 1) == 'x') {
                    vacuumFunction(x, y, x, y + 1);
                    this.room.removeDirt();
                    return vacuuming(x, y + 1);
                }
            }

            if (this.room.insideMap(x - 1, y)) {
                if (this.room.checkMap(x - 1, y) == 'x') {
                    vacuumFunction(x, y, x - 1, y);
                    this.room.removeDirt();
                    return vacuuming(x - 1, y);
                }
            }


            ///when surround by clean bits

            if (this.room.insideMap(x, y - 1)) {
                if (this.room.checkMap(x, y - 1) == 'c' && visitCount[x][y-1] <= MAX) {
                    vacuumFunction(x, y, x, y - 1);
                    this.visitCount[x][y]++;
                    return vacuuming(x, y - 1);
                }
            }
            if (this.room.insideMap(x + 1, y)) {
                if (this.room.checkMap(x + 1, y) == 'c' && visitCount[x+1][y] <= MAX) {
                    vacuumFunction(x, y, x + 1, y);
                    this.visitCount[x][y]++;
                    return vacuuming(x + 1, y);
                }
            }

            if (this.room.insideMap(x, y + 1)) {
                if (this.room.checkMap(x, y + 1) == 'c' && visitCount[x][y+1] <= MAX) {
                    vacuumFunction(x, y, x, y + 1);
                    this.visitCount[x][y]++;
                    return vacuuming(x, y + 1);
                }
            }
            if (this.room.insideMap(x - 1, y)) {
                if (this.room.checkMap(x - 1, y) == 'c' && visitCount[x-1][y] <= MAX) {
                    vacuumFunction(x, y, x - 1, y);
                    this.visitCount[x][y]++;
                    return vacuuming(x - 1, y);
                }
            }


        }
        return false;
    }

    void vacuumFunction(int x, int y, int newR, int newC) throws InterruptedException {
        this.room.updateMap(x, y, 'c');
        this.room.updateMap(newR, newC, 'R');
        this.room.displayMap();                     //terminal display map
        this.window.updateMap(room);        //updates local map for Swing
        this.window.repaint();                  //repaint window
        this.rc.useBattery();

        
        TimeUnit.SECONDS.sleep(1);              // 1 second delay
        
        System.out.println("Dirt count is: " + this.room.getDirtCount());
        System.out.println("Battery Power: " + rc.getPower());
    }
}