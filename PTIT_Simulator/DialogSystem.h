#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
using namespace sf;

class DialogSystem {

public:
    bool isDone = false;
    bool startEmote = false;
    Player* player;
    std::string emotes;
    int lenText;
    DialogSystem()
    {
        t_DialogSystem.loadFromFile("../Resource/Chat/dialog.png");
        s_DialogSystem.setTexture(t_DialogSystem);


        isDone = false;

        Pixel.loadFromFile("../Resource/Font/pixelvh.ttf");
        DialogSystem_text.setFont(Pixel);
        DialogSystem_npcName.setFont(Pixel);

        sf::SoundBuffer soundBuffer;
        this->soundBuffer = new sf::SoundBuffer;
        this->sound = new sf::Sound;
        if (!this->soundBuffer->loadFromFile("../Resource/Sound/penchat.wav"))
        {
            return;
        }
        this->sound->setBuffer(*this->soundBuffer);



        

    }

    void setText(sf::Sprite sprite, wchar_t text[], std::string npcName, int x, int y, int size, std::string emotes, Player* player)
    {
        this->visible = true;
        this->s_FaceChat = sprite;
        this->emotes = emotes;
        this->player = player;

        curTime = 0;
        count = 1;
        DialogSystem_text.setFillColor(Color::Black);
        DialogSystem_text.setPosition(x, y-50);
        DialogSystem_text.setCharacterSize(size);

        DialogSystem_npcName.setString(npcName);
        DialogSystem_npcName.setFillColor(Color::Black);
        DialogSystem_npcName.setPosition(x - 25, y-150);
        DialogSystem_npcName.setCharacterSize(size);

        this->s_FaceChat.setPosition(x - 300, y - 250);
       
        this->s_FaceChat.setScale(0.7f, 0.7f);
        int len = wcslen(text);
        for (int i = 0; i < len; i++) {
            display[i] = text[i];
            stringList.push_back('?');
        }
        lenText = len;
        
        //std::cout << "size " << (std::string) DialogSystem_npcName.getString() << "\n";
    }

    void setVisibile(bool type) {
        this->visible = type;
    }

    void drawDialogSystem(RenderWindow& window, float dt)
    {
        wchar_t curText[1000] = {};
        float tocdo = 0.04f; //cang lon cang chay lau
        if (curTime > (int)(stringList.size() + 3)* tocdo) {
            std::cout << "Done chat\n";
            isDone = true;
            this->setVisibile(false);
        }
        if (visible == true)
        {
            s_DialogSystem.setPosition(0, 400);
            
            curTime += dt;
            if (count < stringList.size() && curTime >= count * tocdo) {
                if ((int)count % 3 == 0) this->sound->play();
                count++;
               
                for (int i = 0; i < count; i++) curText[i] = display[i];

                DialogSystem_text.setString(curText);
            }
            window.draw(s_DialogSystem);
            window.draw(DialogSystem_npcName);
            window.draw(DialogSystem_text);
            window.draw(s_FaceChat);
        }
    }


private:
    Texture t_DialogSystem;
    Sprite  s_DialogSystem;

    Texture t_FaceChat;
    Sprite  s_FaceChat;


    Font Pixel;
    Text DialogSystem_text;
    Text DialogSystem_npcName;

    bool visible = false;
    

    int currentText = 0;
    float curTime = 0;
    std::vector<char> stringList;
    wchar_t display[1000];
    
    float count = 1;

    sf::Sound* sound;
    sf::SoundBuffer* soundBuffer;


};