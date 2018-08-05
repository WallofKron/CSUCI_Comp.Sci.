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

public class RobotVacuum {

    public static void main(String[] args) throws InterruptedException {

        boolean startValid = false;
        int start_x = -1;
        int start_y = -1;
        Random rand = new Random();

        Map room = new Map();
        room.populateMap();
        room.displayMap();

        while (startValid != true)
        {

            while (start_x < 0 || start_x > room.getCol()) {
                start_x = rand.nextInt((room.getRows()));
//                System.out.print("\n");
//                if (start_x < 0 || start_x > room.getCol()) {
//                    System.out.print("\nIncorrect bounds\n");
//                }
            }

            while (start_y < 0 || start_y > room.getRows()) {
                start_y = rand.nextInt((room.getCol()));
//                System.out.print("\n");
//                if (start_y < 0 || start_y > room.getCol()) {
//                    System.out.print("\nIncorrect bounds\n");
//                }
            }

            if (room.insideMap(start_x,start_y) && room.checkMap(start_x, start_y) == 'x') {
                startValid = true;

            } else {

//              System.out.println("Desired start on top of obstacle.\n");
                startValid = false;
                start_x = -1;
                start_y = -1;
            }
            
        }

        Device rc = new Device();

        room.updateMap(start_x, start_y, 'R');
        room.removeDirt();
        room.displayMap();
        rc.turnOn();
                  //Put in a delay here (maybe a second or second and a half?)
        System.out.println("Battery: " + rc.getPower());
        Move running = new Move(room, rc);

        running.vacuuming(start_x, start_y);

        //room.displayMap();
        
            //if (!running.vacuuming(start_x, start_y)) {
                //rc.turnOff();
                //Display window = new Display(room);
    }
}