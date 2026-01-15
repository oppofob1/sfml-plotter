#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <math.h>
#include <optional>
#include <iostream>


//draws points as connected line segments
sf::VertexArray buildGraph(
    const std::vector<float>& x_vals,
    const std::vector<float>& y_vals)
{
    sf::VertexArray graph(sf::PrimitiveType::LineStrip);

    //new technique, scaleable graph
    constexpr float SCALE = 100.f;
    constexpr float ORIGIN_X = 960.f;
    constexpr float ORIGIN_Y = 540.f;

    for (size_t i = 0; i < x_vals.size(); ++i)
    {   
        //graph based on the scale
        float pointX = ORIGIN_X + x_vals[i] * SCALE;
        float pointY = ORIGIN_Y - y_vals[i] * SCALE;

        graph.append({{pointX, pointY}, sf::Color::White});
    }

    return graph;
}




//draws the axis as lines
sf::VertexArray buildAxes()
{   
    sf::VertexArray axes(sf::PrimitiveType::Lines);

    //y
    axes.append({ {960, 0}, sf::Color::Red });
    axes.append({ {960, 1080}, sf::Color::Red });

    //x
    axes.append({ {0, 540}, sf::Color::Red });
    axes.append({ {1920, 540}, sf::Color::Red });

    return axes;
}


int main()
{   
    //creates the windows
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    //arays to hold the x and y values
    std::vector<float> x_vals  = {};
    std::vector<float> y_vals  = {};

    // a range to draw in, values bigger than this or 
    // smaller than the negative of this will not be calculated
    int drawRange = 300;

    //changeable function inside of y_vals.push_back
    for (float i = -drawRange; i < drawRange; i += 0.1f)
    {
        x_vals.push_back(i);
        y_vals.push_back(cos(i));
    }


    //windows event polling
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        //rendering
        window.clear();
        //draws the axis and the graph points
        window.draw(buildAxes());
        window.draw(buildGraph(x_vals, y_vals));
        window.display();
    }
}
