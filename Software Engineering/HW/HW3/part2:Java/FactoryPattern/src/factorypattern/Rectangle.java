package factorypattern;
/**
 * Robert Florence CS111
 */
public class Rectangle extends Shape {

    private int height, width;

    public Rectangle() {
        super();
        height = 0;
        width = 0;

    }

    public Rectangle(int x, int y, int height, int width) {
        super(x, y);
        this.height = height;
        this.width = width;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public void display() {
        System.out.println("Rectangle: \nX = " + getX() + "  Y = " + getY() + "  width = "
                + width + "  height = " + height + "\nTotal Rectangle Area: " + area() + " units\n");
    }

    public double area() {
        double area = (double) (width * height);

        return area;
    }
}