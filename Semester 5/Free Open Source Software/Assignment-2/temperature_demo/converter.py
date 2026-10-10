"""Convert temperatures between common scales."""


def celsius_to_fahrenheit(celsius):
    """Return the Fahrenheit equivalent of a Celsius temperature."""
    return celsius * 9 / 5 + 32


def fahrenheit_to_celsius(fahrenheit):
    """Return the Celsius equivalent of a Fahrenheit temperature."""
    return (fahrenheit - 32) * 5 / 9
