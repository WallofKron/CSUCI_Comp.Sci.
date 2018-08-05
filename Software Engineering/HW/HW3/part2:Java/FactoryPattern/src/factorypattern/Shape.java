package factorypattern;
/**
 * Robert Florence CS111
 */
public abstract class Shape {

    private int x, y;
    protected final static int X_MAX_SIZE = 800;
    protected final static int Y_MAX_SIZE = 800;

    public Shape() {
        x = 0;
        y = 0;
    }
    
    public Shape(int x, int y) {

        if (x >= 0 && x <= X_MAX_SIZE) {
            this.x = x;
        } else {
            System.out.println("error");
            this.x = 0;
        }

        if (y >= 0 && y <= Y_MAX_SIZE) {
            this.y = y;
        } else {
            System.out.println("error");
            this.y = 0;
        }
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {

        if (x >= 0 && x <= X_MAX_SIZE) {
            this.x = x;
        } else {
            System.out.println("error");
            this.x = 0;
        }
    }
    public int getY() {
        return y;
    }

    public void setY(int y) {
        if (y >= 0 && y <= Y_MAX_SIZE) {
            this.y = y;
        } else {
            System.out.println("error");
            this.y = 0;
        }
    }
    
    public abstract void display();

    public abstract double area();
}