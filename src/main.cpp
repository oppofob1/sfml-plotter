#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <math.h>
#include <optional>
#include <iostream>

// function to map value from x to axis range
float mapValue(float value, float inMin, float inMax, float outMin, float outMax)
{   //mapping formula
    return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
}

float sqrt_estimator(float a, int iterations)
{
    float x = a / 2; // the number to take the square root of

    for (int i = 0; i < iterations; ++i)
    {
        x = 0.5f * (x + (a / x));

    }

    return x;
}

//draws points as connected line segments
sf::VertexArray buildGraph(
    const std::vector<float>& x_vals,
    const std::vector<float>& y_vals)
{
    float xmin = *std::min_element(x_vals.begin(), x_vals.end());
    float xmax = *std::max_element(x_vals.begin(), x_vals.end());
    float ymin = *std::min_element(y_vals.begin(), y_vals.end());
    float ymax = *std::max_element(y_vals.begin(), y_vals.end());

    sf::VertexArray graph(sf::PrimitiveType::LineStrip);

    for (size_t i = 0; i < x_vals.size(); ++i)
    {
        float sx = mapValue(x_vals[i], xmin, xmax, 200.f, 1720.f);
        float sy = mapValue(y_vals[i], 0, ymax, 880.f, 200.f);

        graph.append({ {sx, sy}, sf::Color::White });
    }

    return graph;
}

//draws the axis as lines
sf::VertexArray buildAxes()
{
    sf::VertexArray axes(sf::PrimitiveType::Lines);

    axes.append({ {200, 200}, sf::Color::Red });
    axes.append({ {200, 880}, sf::Color::Red });

    axes.append({ {200, 880}, sf::Color::Red });
    axes.append({ {1720, 880}, sf::Color::Red });

    return axes;
}


int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    std::vector<float> x_vals;
    std::vector<float> y_vals;

    //x and y values for the graph
    x_vals = {};
    y_vals = {};

    for (int i = 1; i < 1000000; i += 1)
    {
        x_vals.push_back(i);
        y_vals.push_back(sqrt_estimator(-i, i));
    }



    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }


        window.clear();
        //draws the axis and the graph points
        window.draw(buildAxes());
        window.draw(buildGraph(x_vals, y_vals));
        window.display();
    }
}
