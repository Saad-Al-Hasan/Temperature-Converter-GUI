//Temperature Converter with GUI
//Project of Group-02_Section-04
//2024-1-60-233 [Saad]


import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

// Temperature Converter GUI Application
public class TemperatureConverterApp {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(TemperatureConverterFrame::new);
    }
}

// Core GUI Frame for the Temperature Converter
class TemperatureConverterFrame extends JFrame {
    private JTextField inputField;
    private JComboBox<String> fromComboBox;
    private JComboBox<String> toComboBox;
    private JLabel resultLabel;

    public TemperatureConverterFrame() {
        setTitle("Temperature Converter");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(6, 1, 10, 10));

        // Initialize the ArrayList with temperature units
        ArrayList<String> temperatureUnits = new ArrayList<>();
        temperatureUnits.add("Celsius");
        temperatureUnits.add("Fahrenheit");
        temperatureUnits.add("Kelvin");

        // Input Field
        JLabel inputLabel = new JLabel("Enter temperature value:");
        inputField = new JTextField();
        add(inputLabel);
        add(inputField);

        // From ComboBox
        JLabel fromLabel = new JLabel("Convert from:");
        fromComboBox = new JComboBox<>(temperatureUnits.toArray(new String[0]));
        add(fromLabel);
        add(fromComboBox);

        // To ComboBox
        JLabel toLabel = new JLabel("Convert to:");
        toComboBox = new JComboBox<>(temperatureUnits.toArray(new String[0]));
        add(toLabel);
        add(toComboBox);

        // Convert Button
        JButton convertButton = new JButton("Convert");
        convertButton.addActionListener(new ConvertButtonListener());
        add(convertButton);

        // Result Label
        resultLabel = new JLabel("Converted Temperature: ", JLabel.CENTER);
        add(resultLabel);

        setLocationRelativeTo(null); // Center the frame
        setVisible(true);
    }

    // Getter and Setter for inputField
    public String getInputFieldText() {
        return inputField.getText();
    }

    public void setInputFieldText(String text) {
        inputField.setText(text);
    }

    // Getter and Setter for fromComboBox
    public String getFromComboBoxSelection() {
        return (String) fromComboBox.getSelectedItem();
    }

    public void setFromComboBoxSelection(String selection) {
        fromComboBox.setSelectedItem(selection);
    }

    // Getter and Setter for toComboBox
    public String getToComboBoxSelection() {
        return (String) toComboBox.getSelectedItem();
    }

    public void setToComboBoxSelection(String selection) {
        toComboBox.setSelectedItem(selection);
    }

    // Getter and Setter for resultLabel
    public String getResultLabelText() {
        return resultLabel.getText();
    }

    public void setResultLabelText(String text) {
        resultLabel.setText(text);
    }

    // Action Listener for the Convert Button
    private class ConvertButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            try {
                double inputTemp = Double.parseDouble(inputField.getText());
                String fromUnit = (String) fromComboBox.getSelectedItem();
                String toUnit = (String) toComboBox.getSelectedItem();

                // Polymorphic usage of TemperatureConverter
                TemperatureConverter converter;
                switch (fromUnit) {
                    case "Celsius":
                        converter = new CelsiusConverter();
                        break;
                    case "Fahrenheit":
                        converter = new FahrenheitConverter();
                        break;
                    case "Kelvin":
                        converter = new KelvinConverter();
                        break;
                    default:
                        throw new IllegalArgumentException("Unknown temperature unit: " + fromUnit);
                }

                double convertedTemp = converter.convertTemperature(inputTemp, toUnit);
                resultLabel.setText("Converted Temperature: " + convertedTemp + " " + toUnit);
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(TemperatureConverterFrame.this, "Please enter a valid number for temperature.", "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }
}

// Base class for temperature conversion
abstract class TemperatureConverter {
    public abstract double convertTemperature(double value, String to);
}

// Celsius Converter
class CelsiusConverter extends TemperatureConverter {
    @Override
    public double convertTemperature(double value, String to) {
        switch (to) {
            case "Fahrenheit":
                return value * 9 / 5 + 32;
            case "Kelvin":
                return value + 273.15;
            default:
                return value; // Celsius to Celsius
        }
    }
}

// Fahrenheit Converter
class FahrenheitConverter extends TemperatureConverter {
    @Override
    public double convertTemperature(double value, String to) {
        switch (to) {
            case "Celsius":
                return (value - 32) * 5 / 9;
            case "Kelvin":
                return (value - 32) * 5 / 9 + 273.15;
            default:
                return value; // Fahrenheit to Fahrenheit
        }
    }
}

// Kelvin Converter
class KelvinConverter extends TemperatureConverter {
    @Override
    public double convertTemperature(double value, String to) {
        switch (to) {
            case "Celsius":
                return value - 273.15;
            case "Fahrenheit":
                return (value - 273.15) * 9 / 5 + 32;
            default:
                return value; // Kelvin to Kelvin
        }
    }
}
