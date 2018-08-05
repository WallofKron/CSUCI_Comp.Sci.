package factorypattern;
/**
 * Robert Florence CS111
 */
public class Triangle extends Shape {

    private int base, height;

    public Triangle() {
        super();
        base = 0;
        height = 0;
    }

    public Triangle(int x, int y, int height, int base) {

        super(x, y);
        this.height = height;
        this.base = base;
    }

    public int getBase() {
        return base;
    }

    public void setBase(int base) {
        this.base = base;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public void display() {
        System.out.println("Triangle: \nX = " + getX() + "  Y = " + getY() + "  height = "
                + height + "  base = " + base + "\nTotal Triangle Area: " + area() + " units\n");
    }

    public double area() {
        double area = (double) ((base * height) / 2);

        return area;
    }
}