package factorypattern;
/**
 * Robert Florence CS111
 */
public class factorypattern {

    private Shape[] thearray = new Shape[100];                              // 100 Shapes, circle's, tri's and rects

    public static void main(String[] args) {
        factorypattern tpo = new factorypattern();

        tpo.run();
    }

    public void run() {
        int count = 0;
        
// ------------------------   Fill the array section here ----------------------
        
        
        thearray[count++] = new Circle(20, 20, 40);
        thearray[count++] = new Triangle(70, 70, 20, 30);
        thearray[count++] = new Rectangle(150, 150, 20, 30);
        
        thearray[count++] = new Circle(20, 20, 50);
        thearray[count++] = new Triangle(90, 90, 10, 20);
        thearray[count++] = new Rectangle(10, 100, 60, 20);
        
        thearray[count++] = new Circle(20, 20, 20);
        thearray[count++] = new Triangle(40, 60, 25, 35);
        thearray[count++] = new Rectangle(100, 15, 40, 40);
        
        //testing values for creating new inherited objects

// ------------------------------  end of array fill area  ------------------------
        
        
        
        for (int i = 0; i < count; i++) {                      // loop through all objects in the array
            thearray[i].display();                             // don’t care what kind of object, display it
        }                                                     // end for loop

        int offset = 0;
        double totalarea = 0.0;

        while (thearray[offset] != null) {                                    // loop through all objects in the array
            totalarea = totalarea + thearray[offset].area();                  // get area for this object
            offset++;
        }                                                                       // end while loop

        System.out.println("The total area for " + offset + " Shape objects is " + totalarea +" units");
    }
}