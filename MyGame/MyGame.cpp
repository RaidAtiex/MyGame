#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <algorithm>

using namespace sf;
using namespace std;
class Map {

public:
    sf::RenderWindow& w;
    sf::Texture& tex;
    int density;

    int X;
    int Y;

    std::vector<Sprite> sprites;

    std::vector<sf::FloatRect> spriteBounds;
    bool iscreated = false;


    Map(sf::RenderWindow& window, sf::Texture& texture, int size, int Xo, int Yo) : w(window), tex(texture), density(size), X(Xo), Y(Yo) {}
    void createmap()
    {

        int width = tex.getSize().x; //получение размера спрайта по оси x
        int height = tex.getSize().y; //получение размера спрайта по оси y
        //размер плоскости X на Y
        int rows = X;
        int columns = Y;

        sf::Sprite sprite;//спрайт из которого будет состоять вся плоскость

        int centerX = 350; // Позиция центра поля по оси X
        int centerY = 150; // Позиция центра поля по оси Y

        sprite.setTexture(tex);

        //цикл для создания изометрической плоскости
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < columns; col++)
            {
                int x = (row - col) * density / 2;
                int y = (row + col) * density / 4;

                sprite.setPosition(centerX + x, centerY + y);



                if (iscreated == false) {

                    sprites.push_back(sprite);
                    spriteBounds.push_back(sprite.getGlobalBounds());
                    //std::cout << "X " << sprite.getPosition().x << " Y " << sprite.getPosition().y << " row " << row << " col " << col << endl;
                }


                w.draw(sprite);
                //sf::Vector2f position(centerX + x, centerY + y);



            }
        }


        iscreated = true;



    }

};

class LevelGenerator {
public:

    sf::RenderWindow& w;
    string ph;
    sf::Event event;

    class spawner {
    public:
        Texture tx1;
        Sprite sp;
        spawner() {
            tx1.loadFromFile("textures\\spawner.png");
            sp.setTexture(tx1);

        }
        void toPos(int x, int y) {
            sp.setPosition(x, y);
        }



    };


    class signpost {
    public:
        Texture tx1;
        Sprite sp;


        signpost() {

            tx1.loadFromFile("textures\\indicator.png");


            sp.setTexture(tx1);
        }
        void toPos(int x, int y) {
            sp.setPosition(x, y);
        }


    };
    class theText {
    public:
        
        sf::Font font;
        Text txt;
       

        theText() {
            
           
            sf::Text text("", font, 0);
            font.loadFromFile("fonts\\arial.ttf");
            text.setFillColor(sf::Color::White);
            
            txt = text;
            

        }
        void setText(string thestr) {
            txt.setString(thestr);
        }
        void toPos(int x, int y) {
            txt.setPosition(x, y);
        }
        void setSize(int s) {
            txt.setCharacterSize(s);
        }

       
    };



    class flag {
    public:
        Texture tx1;
        Sprite sp;
        string type;

        void settexture() {
            if (type == "Red") {
                tx1.loadFromFile("textures\\redflag.png");
            }
            else if (type == "Green") {
                tx1.loadFromFile("textures\\greenflag.png");
            }

            sp.setTexture(tx1);
        }
        void toPos(int x, int y) {
            sp.setPosition(x, y );
        }

    };





    bool flag1draw = false;
    bool flag2draw = false;
    bool sgnpost = false;
    bool spawnerdrive = false;


    spawner spwn;
    signpost sgn;
    flag fl1;
    flag fl2;
    theText tx;
    std::vector<Text> texts;
    

    void drawobj(Sprite spr) {
        w.draw(spr);
    }

    LevelGenerator(string path, RenderWindow& window) : w(window) {
        fl1.type = "Red";
        fl2.type = "Green";
        fl1.settexture();
        fl2.settexture();


        ph = path;

        std::ifstream inFile(path); // открытие файла для чтения
        std::string line;


        while (std::getline(inFile, line)) {
            if (line.substr(0, 7) == "Spawner") {
                //spwn.toPos(10, 10);
                spwn.toPos(a(line)[0], a(line)[1]);
                //std::cout << a(line)[0] << " " << a(line)[1];
                spawnerdrive = true;
                //drawobj(spwn.sp);

                //drawobj(spwn.sp);

            }
            else if (line.substr(0, 7) == "RedFlag") {
                //spwn.toPos(10, 10);
                fl1.toPos(a(line)[0], a(line)[1]);
                //std::cout << a(line)[0] << " " << a(line)[1];
                flag1draw = true;
                //drawobj(spwn.sp);

                //drawobj(spwn.sp);

            }
            else if (line.substr(0, 9) == "GreenFlag") {
                //spwn.toPos(10, 10);
                fl2.toPos(a(line)[0], a(line)[1]);
                //std::cout << a(line)[0] << " " << a(line)[1];
                flag2draw = true;
                //drawobj(spwn.sp);

                //drawobj(spwn.sp);

            }
            //signpost
            else if (line.substr(0, 8) == "Signpost") {
                //spwn.toPos(10, 10);
                sgn.toPos(a(line)[0], a(line)[1]);
                //std::cout << a(line)[0] << " " << a(line)[1];
                sgnpost = true;

                //drawobj(spwn.sp);

                //drawobj(spwn.sp);

            }
            else if (line.substr(0, 4) == "Text") {
                
                tx.toPos(a(line)[0], a(line)[1]);
                tx.setSize(a(line)[2]);
                tx.setText(gettext(line));

                texts.push_back(tx.txt);

            }



        }
        inFile.close(); // закрытие файла
    }

    std::vector<int> a(const std::string& str) {
        std::vector<int> nums;
        std::string numStr;
        for (char c : str) {
            if (std::isdigit(c)) {
                numStr += c;
            }
            else if (!numStr.empty()) {
                nums.push_back(std::stoi(numStr));
                numStr.clear();
            }
        }
        if (!numStr.empty()) {
            nums.push_back(std::stoi(numStr));
        }
        return nums;
    }

    std::string gettext(std::string a) {
        std::string b;
        bool start = false;
        bool end = false;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] == '@' && start == false && end == false) {
                start = true;
                i += 1; // Пропустить кавычку
            }
            if (a[i] == '@' && start == true && end == false) {
                end = true;
                start = false;
            }
            else if (start == true && end == false) {
                b += a[i];
            }
        }
        return b;
    }






};

class trolley {
public:
    string type;
    Texture tx1;
    Texture tx2;
    Sprite sp;
    bool draw = false;
    bool end = false;

    trolley(string tp) {
        type = tp;
        tx1.loadFromFile("textures\\red_trolley.png");
        tx2.loadFromFile("textures\\green_trolley.png");
        if (type == "Red") {

            sp.setTexture(tx1);
        }

        else {
            sp.setTexture(tx2);
        }


    }
    void drive(std::vector<Vector2f> pos, std::vector<bool>& states, Vector2f ps, Vector2f sc) {


        //std::cout << sp.getPosition().x << " " << sp.getPosition().y << endl;

        if (type == "Red" && sf::Vector2f(sp.getPosition().x + 16, sp.getPosition().y - 8) == sc) {
            states[0] = 0;
            states[1] = 1;
            states[2] = 0;
            states[3] = 0;
           // std::cout << 3;
            sp.setPosition(sp.getPosition().x - 16, sp.getPosition().y - 8);

            sf::sleep(sf::seconds(1.f));
        }
        else if (type == "Green" && sf::Vector2f(sp.getPosition().x - 16, sp.getPosition().y + 8) == sc) {
            states[0] = 1;
            states[1] = 0;
            states[2] = 0;
            states[3] = 0;
            //std::cout << 3;
            sp.setPosition(sp.getPosition().x + 16, sp.getPosition().y + 8);

            sf::sleep(sf::seconds(1.f));
        }

        else if (std::find(pos.begin(), pos.end(), sf::Vector2f(sp.getPosition().x + 16, sp.getPosition().y + 8)) != pos.end() && states[1] == 0) {
            states[0] = 1;
            states[1] = 0;
            states[2] = 0;
            states[3] = 0;
            //std::cout << 1;
            sp.setPosition(sp.getPosition().x + 16, sp.getPosition().y + 8);


            sf::sleep(sf::seconds(1.f));
        }
        else if (std::find(pos.begin(), pos.end(), sf::Vector2f(sp.getPosition().x - 16, sp.getPosition().y - 8)) != pos.end() && states[0] == 0) {
            states[0] = 0;
            states[1] = 1;
            states[2] = 0;
            states[3] = 0;
           // std::cout << 2;
            sp.setPosition(sp.getPosition().x - 16, sp.getPosition().y - 8);


            sf::sleep(sf::seconds(1.f));
        }

        else if (std::find(pos.begin(), pos.end(), sf::Vector2f(sp.getPosition().x + 16, sp.getPosition().y - 8)) != pos.end() && states[3] == 0) {
            states[0] = 0;
            states[1] = 0;
            states[2] = 1;
            states[3] = 0;
            //std::cout << 3;
            sp.setPosition(sp.getPosition().x + 16, sp.getPosition().y - 8);

            sf::sleep(sf::seconds(1.f));
        }

        else if (std::find(pos.begin(), pos.end(), sf::Vector2f(sp.getPosition().x - 16, sp.getPosition().y + 8)) != pos.end() && states[2] == 0) {
            states[0] = 0;
            states[1] = 0;
            states[2] = 0;
            states[3] = 1;
            //std::cout << 4;
            sp.setPosition(sp.getPosition().x - 16, sp.getPosition().y + 8);

            sf::sleep(sf::seconds(1.f));
        }
        else if (sf::Vector2f(sp.getPosition().x + 32, sp.getPosition().y) == ps || Vector2f(sp.getPosition().x, sp.getPosition().y + 16) == ps || Vector2f(sp.getPosition().x, sp.getPosition().y) == ps || Vector2f(sp.getPosition().x + 32, sp.getPosition().y + 16) == ps)
        {
            end = true;
            

        }


    }


    void toPos(int x, int y) {
        sp.setPosition(x, y);
    }



};





int main()
{
    
    

    bool isrestart = false;
   
    int click = 0;
    bool bg = false;

    std::vector<Sprite> spr;
    std::vector<Vector2f> RilsesPos;

    trolley tr("Red");
    trolley tr1("Green");


    std::vector<bool> states{ 0, 0, 0, 0 };
    std::vector<bool> states1{ 0, 0, 0, 0 };

    int size = 32; // Размер ячейки на поле
    int width = 800; // Ширина окна
    int height = 600; // Высота окна

    sf::RenderWindow window(sf::VideoMode(width, height), "Isometric Field", sf::Style::Titlebar | sf::Style::Close);


    Texture texture, texture1, texture2, texture3, texture4;

    texture.loadFromFile("textures\\bulaga.png");
    texture1.loadFromFile("textures\\robot.png");
    texture2.loadFromFile("textures\\stone3.png");
    texture3.loadFromFile("textures\\rails.png");
    texture4.loadFromFile("textures\\rail4.png");



    Map map(window, texture, size, 15, 15);
    LevelGenerator lg("LevelGenerator\\generator.txt", window);

    Sprite sp2, sp3;
    sp2.setTexture(texture3);
    sp3.setTexture(texture2);


    bool spawnCharacter = false; // Флаг для отслеживания нужности спавна персонажа
    // Хранение позиции клика мыши
    int clickX = 0;
    int clickY = 0;

    // Главный цикл приложения
    while (window.isOpen())
    {
        

        if (tr.end == true && tr1.end == true) {
          
            std::cout << "WIN" << endl;

             
        }
        Vector2i vect = Mouse::getPosition(window);
        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

        if (tr.draw == true) {
            tr.drive(RilsesPos, states, lg.fl1.sp.getPosition(), lg.sgn.sp.getPosition());
        }
        if (tr1.draw == true) {

            tr1.drive(RilsesPos, states1, lg.fl2.sp.getPosition(), lg.sgn.sp.getPosition());
        }
        for (int i = 0; i < map.spriteBounds.size(); i++) {
            if (map.spriteBounds[i].contains(mousePosition)) {

                sp3.setPosition(map.sprites[i].getPosition().x, map.sprites[i].getPosition().y - 16);





            }
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {

                window.close();
            }
            if (isrestart == true) {
                window.close();
                main();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::S)
                {


                    //std::cout << "1" << std::endl;
                    //std::cout << lg.spwn.sp.getPosition().x << " " << lg.spwn.sp.getPosition().y << endl;
                    if (click == 0) {
                        tr.toPos(lg.spwn.sp.getPosition().x + 16, lg.spwn.sp.getPosition().y + 8);
                        tr.draw = true;

                    }
                    if (click >= 1) {
                        tr1.toPos(lg.spwn.sp.getPosition().x + 16, lg.spwn.sp.getPosition().y + 8);
                        tr1.draw = true;
                    }






                }
                if (event.key.code == sf::Keyboard::R)
                {
                    
                    isrestart = true;
                    

                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                // Проверяем, была ли нажата кнопка мыши
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    sp2.setPosition(sp3.getPosition());
                    RilsesPos.push_back(sp2.getPosition());
                    for (int i = 0; i < RilsesPos.size(); i++) {
                        if (sp2.getPosition().x - RilsesPos[i].x == -16 && sp2.getPosition().y - RilsesPos[i].y == -8) {
                            //std::cout << 1;
                            sp2.setTexture(texture4);
                            map.sprites[map.sprites.size() - 1].setTexture(texture4);
                        }
                        else if (sp2.getPosition().x - RilsesPos[i].x == 16 && sp2.getPosition().y - RilsesPos[i].y == 8) {
                            //std::cout << 1;
                            sp2.setTexture(texture4);
                            map.sprites[map.sprites.size() - 1].setTexture(texture4);
                        }

                        if (sp2.getPosition().x - RilsesPos[i].x == -16 && sp2.getPosition().y - RilsesPos[i].y == 8) {
                            //std::cout << 1;
                            sp2.setTexture(texture3);
                            map.sprites[map.sprites.size() - 1].setTexture(texture3);
                        }
                        else if (sp2.getPosition().x - RilsesPos[i].x == 16 && sp2.getPosition().y - RilsesPos[i].y == -8) {
                            //std::cout << 1;
                            sp2.setTexture(texture3);
                            map.sprites[map.sprites.size() - 1].setTexture(texture3);
                        }







                    }

                    map.sprites.push_back(sp2);
                    std::cout << "X " << sp3.getPosition().x << " Y  " << sp3.getPosition().y << endl;

                }
                else  if (event.mouseButton.button == sf::Mouse::Right)
                {

                    
                   
                    for (int i = 0; i < (map.sprites.size()); i++) {

                        if (Vector2f(map.sprites[i].getPosition().x, map.sprites[i].getPosition().y) == sp3.getPosition() && i > (map.X - 1) * (map.Y - 1)) {
                           // std::cout << 1;
                            
                            map.sprites[i].setPosition(-100, -100);

                            for (int j = 0; j < RilsesPos.size(); j++) {
                                if (RilsesPos[j] == sp3.getPosition()) {
                                    auto it = std::find(RilsesPos.begin(), RilsesPos.end(), RilsesPos[j]);
                                    RilsesPos.erase(std::remove(RilsesPos.begin(), RilsesPos.end(), RilsesPos[j]));
                                    //std::cout << 1;
                                }
                            }
                        }


                       


                    }





                    }
            }

        }

        // Вызов функции отрисовки поля
        window.clear();


        map.createmap();


        for (auto i : map.sprites) {
            window.draw(i);
        }

        if (lg.spawnerdrive == true) {
            lg.drawobj(lg.spwn.sp);
        }
        if (lg.flag1draw == true) {
            lg.drawobj(lg.fl1.sp);
        }
        if (lg.flag1draw == true) {
            lg.drawobj(lg.fl2.sp);
        }

        if (tr.draw == true) {
            window.draw(tr.sp);
            click += 1;



        }
        if (tr1.draw == true) {

            window.draw(tr1.sp);

        }

        if (lg.sgnpost == true) {
            lg.drawobj(lg.sgn.sp);

        }

        for (auto i :lg.texts) {
            window.draw(i);
        }
       
        


        window.draw(sp3);
      


        //window.draw(sp3);

        window.display();

        // Спавн персонажа при клике на изометрический объект

    }

    return 0;
}
