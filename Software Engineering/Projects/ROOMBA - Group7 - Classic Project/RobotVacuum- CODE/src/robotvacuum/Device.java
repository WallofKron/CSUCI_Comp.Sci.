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


public class Device {


    private int batteryPower;

    public Device() {

        this.batteryPower = 100;
    }

    public void turnOn() {
        System.out.println("Robot vacuum is on.\n");
    }

    public void turnOff() {
        System.out.println("Robot vacuum is off.\n");
    }

    public int getPower()
    {
        return this.batteryPower;
    }

    public void useBattery()
    {
        this.batteryPower--;
    }
}
