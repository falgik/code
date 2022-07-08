#include "Program.h"


Program prog;

int main()
{

    RenderWindow window(VideoMode(1380, 880), L"Методи сортування", sf::Style::Close);
    window.setFramerateLimit(60);
    Event event;
    Font font;
    font.loadFromFile("consolab.ttf");

    prog.init(font);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            }
        }
        window.clear();

        prog.update(Vector2f( Mouse::getPosition(window)), Mouse::isButtonPressed(Mouse::Left));
        prog.draw(window);

        window.display();

    }
    return 0;
}

