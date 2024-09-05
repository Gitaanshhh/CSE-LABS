// Online Java Compiler
// Use this editor to write, compile and run your Java code online
import java.util.Scanner

class Person {
    private String name, DOB;
    Person(){
    }
    Person(String name, String DOB){
        this.name = name;
        this.DOB = DOB;
    }
    public void displayName(){
        System.out.println("Name "+name);
        System.out.println("Date of Birth "+DOB);
    }
}

class CollegeGraduate extends Person{
    private float GPA;
    private int yearOfGrad;
    CollegeGraduate(){
    }
    CollegeGraduate(float GPA, int yearOfGrad){
        this.GPA = GPA;
        this.yearOfGrad = yearOfGrad;
    }
    public void displayDeets(){
        super.displayName();
        System.out.println("GPA "+gpa);
        System.out.println("Graduation Year "+yearOfGrade);
    }
}

public class Q3 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        System.out.println("Input Person's details:\n");
        String name, DOB;
        System.out.println("Name : ");
        name = s.nextLine();
        System.out.println("Date of birth (dd/mm/yy) : ");
        DOB = s.nextLine();
        Person p1 = new Person(name, DOB);
        p1.displayName();
        System.out.println("\nAccessing College Graduates details:\n");
        CollegeGraduate cg = new CollegeGraduate();
        cg.accessDetails();
    }
}
