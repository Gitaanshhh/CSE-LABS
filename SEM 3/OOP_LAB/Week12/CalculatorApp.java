import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.canvas.*;
import javafx.scene.image.Image;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class CalculatorApp extends Application {

    @Override
    public void start(Stage primaryStage) {
        // Create text fields for input
        TextField numField1 = new TextField();
        numField1.setPromptText("Enter first number");

        TextField numField2 = new TextField();
        numField2.setPromptText("Enter second number");

        // Create button to compute results
        Button computeButton = new Button("Compute");

        Canvas canvas = new Canvas(400, 300);
        GraphicsContext gc = canvas.getGraphicsContext2D();

        Image calculatorImage = new Image("Calculator.png"); 

        computeButton.setOnAction(e -> {
            try {
                double num1 = Double.parseDouble(numField1.getText());
                double num2 = Double.parseDouble(numField2.getText());
                
                double sum = num1 + num2;
                double product = num1 * num2;
                double difference = num1 - num2;
                double quotient = num2 != 0 ? num1 / num2 : Double.NaN;

                // Clear the canvas and display results
                gc.clearRect(0, 0, canvas.getWidth(), canvas.getHeight());
                gc.drawImage(calculatorImage, 10, 10, 80, 80); // Drawing an image on canvas

                gc.fillText("Sum: " + sum, 100, 50);
                gc.fillText("Product: " + product, 100, 80);
                gc.fillText("Difference: " + difference, 100, 110);
                gc.fillText("Quotient: " + (num2 != 0 ? quotient : "Undefined"), 100, 140);

            } catch (NumberFormatException ex) {
                gc.clearRect(0, 0, canvas.getWidth(), canvas.getHeight());
                gc.fillText("Please enter valid numbers.", 100, 50);
            }
        });

        VBox layout = new VBox(10, new Label("Calculator"), numField1, numField2, computeButton, canvas);
        layout.setAlignment(Pos.CENTER);

        Scene scene = new Scene(layout, 400, 400);
        primaryStage.setScene(scene);
        primaryStage.setTitle("JavaFX Calculator");
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
