package factorypattern;
/**
 *  * Robert Florence CS111
 */
public class Circle extends Shape {

    private int radius;

    public Circle() {
        super();
        radius = 0;
    }

    public Circle(int x, int y, int radius) {
        super(x, y);
        this.radius = radius;
    }

    public int getRadius() {
        return radius;
    }

    public void setRadius(int radius) {
        if(radius>0){
            this.radius = radius;
        }
    }
    public void display() {
        System.out.println("Circle: \nX = " + getX() + "  Y = " + getY() + "  radius = "
                + getRadius()+"\nTotal Circle Area: " + area() + " units\n");
    }

    public double area() {
        double rsquared = radius * radius;
        double area = Math.PI * rsquared;

        return area;
    }
}