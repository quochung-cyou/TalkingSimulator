#include "GSPlay.h"
#include "DialogSystem.h"
#include "Map.h"
#include "Tile.h"
#include "MapConnector.h"
#define mapSizeX 64
#define mapSizeY 45
using namespace sf;



GSPlay::GSPlay() {
}

GSPlay::~GSPlay() {
}

void GSPlay::exit() {
	this->bgmsound.stop();
}

void GSPlay::pause() {
}

void GSPlay::resume() {
}

void GSPlay::init() {
	

	//init walk sound
	if (!this->bgmsound.openFromFile("../Resource/Sound/bgmmenu.wav")) {
		std::cout << "Loi am thanh\n";
		return;
	}

	//Sound play
	this->bgmsound.play();
	this->bgmsound.setVolume(50);
	this->bgmsound.setLoop(true);


	if (!m_soundBuffer["opendoor"].loadFromFile("../Resource/Sound/dooropen.wav")) {
		std::cout << "Loi am thanh\n";
		return;
	}
	if (!m_soundBuffer["alarm"].loadFromFile("../Resource/Sound/alarm.wav")) {
		std::cout << "Loi am thanh\n";
		return;
	}
		
	m_sounds["opendoor"].setBuffer(m_soundBuffer["opendoor"]);
	m_sounds["alarm"].setBuffer(m_soundBuffer["alarm"]);


	//energy
	energy1.setTexture(*RMInstance->getTexture("gui/energy"));
	energy2.setTexture(*RMInstance->getTexture("gui/energy"));
	energy1.setScale(0.5, 0.5);
	energy2.setScale(0.5, 0.5);
	energy1.setPosition(750, 600);
	energy2.setPosition(750, 560);



	//init player and npc
	this->textures["playersprite"].loadFromFile("../Resource/Player/full.png");
	this->textures["NPC1"].loadFromFile("../Resource/Entity/entity1.png");



	//init loading screen
	for (int i = 0; i <= 47; i++) {
		this->textures["animationloading" + to_string(i)].loadFromFile("../Data/Texture/animationloading/anim-" + to_string(i) + ".png");
		this->sprites["animationloading" + to_string(i)].setTexture(this->textures["animationloading" + to_string(i)]);
	}

	//startLoadingScreen();


	//init text display
	dialogFont.loadFromFile("../Resource/Font/pixelvh.ttf");


	displayDay.setFont(dialogFont);
	displayTuTin.setFont(dialogFont);
	displayCode.setFont(dialogFont);
	displayDaiCuong.setFont(dialogFont);

	displayDay.setFillColor(Color::White);
	displayDay.setPosition(800, 560);
	displayDay.setCharacterSize(15);

	displayTuTin.setFillColor(Color::White);
	displayTuTin.setPosition(800, 600);
	displayTuTin.setCharacterSize(15);

	displayCode.setFillColor(Color::White);
	displayCode.setPosition(800, 640);
	displayCode.setCharacterSize(15);

	displayDaiCuong.setFillColor(Color::White);
	displayDaiCuong.setPosition(800, 680);
	displayDaiCuong.setCharacterSize(15);







	
	this->textures["ppmneutral"].loadFromFile("../Data/Texture/charface/ppmneutral.png");
	this->textures["ppmnhaymat"].loadFromFile("../Data/Texture/charface/ppmnhaymat.png");
	this->textures["ppmcuoikhinh"].loadFromFile("../Data/Texture/charface/ppmcuoikhinh.png");
	this->textures["ppmcuoi"].loadFromFile("../Data/Texture/charface/ppmcuoi.png");

	this->textures["selfneutral"].loadFromFile("../Data/Texture/charface/selfneutral.png");
	this->textures["selfsuynghi"].loadFromFile("../Data/Texture/charface/selfsuynghi.png");
	this->textures["selfvui"].loadFromFile("../Data/Texture/charface/selfvui.png");


	this->sprites["selfneutral"].setTexture(this->textures["selfneutral"]);
	this->sprites["selfsuynghi"].setTexture(this->textures["selfsuynghi"]);
	this->sprites["selfvui"].setTexture(this->textures["selfvui"]);


	this->sprites["ppmneutral"].setTexture(this->textures["ppmneutral"]);
	this->sprites["ppmnhaymat"].setTexture(this->textures["ppmnhaymat"]);
	this->sprites["ppmcuoikhinh"].setTexture(this->textures["ppmcuoikhinh"]);
	this->sprites["ppmcuoi"].setTexture(this->textures["ppmcuoi"]);






	this->player = new Player(200, 250, this->textures["playersprite"], "Cyou");
	this->npcList.push_back(new Player(712, 250, this->textures["NPC1"], "PPM"));


	this->objectList.push_back(new Player(232, 120, this->textures["null"], "SchoolDoor"));
	this->objectList.push_back(new Player(320, 349, this->textures["null"], "DaiCuong"));
	this->objectList.push_back(new Player(360, 224, this->textures["null"], "Bed"));
	this->objectList.push_back(new Player(590, 260, this->textures["null"], "Code"));
	this->objectList.push_back(new Player(440, 142, this->textures["null"], "HomeDoor"));
	this->objectList.push_back(new Player(424, 586, this->textures["null"], "Piano"));
	this->objectList.push_back(new Player(144, 455, this->textures["null"], "DisplayPC"));
	this->objectList.push_back(new Player(144, 324, this->textures["null"], "DaiCuongSchool"));
	this->objectList.push_back(new Player(900, 152, this->textures["null"], "TuDo"));


	this->player->setFace(this->sprites["selfneutral"]);
	this->npcList[0]->setFace(this->sprites["ppmneutral"]);


	this->curMap = MConnect->m_currentMap;
	MConnect->currentMap = MConnect->lastMap;
	this->player->setPosition(MConnect->lastX, MConnect->lastY);
}



void GSPlay::update(float dt) {
	



	this->dt = dt;
	while (WConnect->getWindow()->pollEvent(this->sfEvent))
	{
		Event e = this->sfEvent;
		if (this->sfEvent.type == sf::Event::Closed)
			WConnect->getWindow()->close();
		else if (e.type == sf::Event::KeyPressed)
		{
			if (isLoadingScreen) {
				return;
			}
			AnimationHandler* animation = this->player->getAnimation();
			Movement* movement = this->player->getMovement();
			if (e.key.code == sf::Keyboard::Left)
				this->player->move(-1.f, 0.f, dt);
			else if (e.key.code == sf::Keyboard::Right)
				this->player->move(1.f, 0.f, dt);
			else if (e.key.code == sf::Keyboard::Up)
				this->player->move(0.f, -1.f, dt);
			else if (e.key.code == sf::Keyboard::Down)
				this->player->move(0.f, 1.f, dt);
			
		}
		else if (e.type == sf::Event::KeyReleased)
		{
			if (isLoadingScreen) {
				return;
			}
			if (e.key.code == sf::Keyboard::F) {
				//Noi chuyen

				if (this->player->getChattingWith() != nullptr) {
					Sprite f_PPM = this->player->getChattingWith()->getFace();
					Sprite f_Player = this->player->getFace();
					String n_PPM = this->player->getChattingWith()->getName();
					String n_P = this->player->getName();

					//sprite face, cast, name, emote, player
					if (MConnect->energyPlayer > 0) {

						if (!MConnect->dayTalked[MConnect->dayCount]) {

							switch (MConnect->dayCount % 6) {
							case 0:
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Chào bạn.....Umm....trời hôm nay đẹp nhỉ ?"), n_P, "fun", this->player);
								addQueueDialog(this->sprites["ppmneutral"], const_cast <wchar_t*>(L"Hả là sao ?"), n_PPM, "wtf", this->player->getChattingWith());
								addQueueDialog(this->sprites["selfsuynghi"], const_cast <wchar_t*>(L"À không có gì đâu....."), n_P, "wtf", this->player);
								break;
							case 1:
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Này...này...cậu giúp mình câu này được không"), n_P, "fun", this->player);
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Có bao nhiêu xâu nhị phân độ dài 7 bít hoặc được bắt đầ-..."), n_P, "fun", this->player);
								addQueueDialog(this->sprites["ppmneutral"], const_cast <wchar_t*>(L"Không"), n_PPM, "wtf", this->player->getChattingWith());
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"À oke..."), n_P, "wtf", this->player);
								break;
							case 2:
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Nè, cậu có muốn xem code trái tim của thủ khoa Lý khôngggg?"), n_P, "fun", this->player);
								addQueueDialog(this->sprites["ppmneutral"], const_cast <wchar_t*>(L"Không"), n_PPM, "wtf", this->player->getChattingWith());
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Vào thời điểm này...bạn nhận ra vấn đề không phải ở code"), n_P, "think", this->player);
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Mà vấn đề ở thủ khoa Lý"), n_P, "think", this->player);
								break;
							case 3:
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Nè, cậu có muốn xem code trái tim của thủ khoa Lý khôngggg?"), n_P, "fun", this->player);
								addQueueDialog(this->sprites["ppmneutral"], const_cast <wchar_t*>(L"Không"), n_PPM, "wtf", this->player->getChattingWith());
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Vào thời điểm này...bạn nhận ra vấn đề không phải ở code"), n_P, "think", this->player);
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Mà vấn đề ở thủ khoa Lý"), n_P, "think", this->player);
								break;
							case 4:
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Nay cậu vẫn đi làm ở quán cafe gần trường àđó à, công việc ổn không?"), n_P, "fun", this->player);
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Công việc ổn không?"), n_P, "fun", this->player);
								addQueueDialog(this->sprites["ppmneutral"], const_cast <wchar_t*>(L"Cũng không tệ lắm"), n_PPM, "wtf", this->player->getChattingWith());
								break;
							case 5:
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Hellooo"), n_P, "fun", this->player);
								addQueueDialog(this->sprites["ppmneutral"], const_cast <wchar_t*>(L"Có việc gì vậy ?"), n_PPM, "think", this->player->getChattingWith());
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Cậu có phải thiên thần không ? O_O"), n_P, "fun", this->player);
								addQueueDialog(this->sprites["ppmneutral"], const_cast <wchar_t*>(L"Há là sao ?"), n_PPM, "think", this->player->getChattingWith());
								addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Không có gì....hỏi cho vui thôi xD"), n_P, "fun", this->player);
								break;
							}
							MConnect->tutin++;
							MConnect->dayTalked[MConnect->dayCount] = 1;
						}
					}
					else {
						addQueueDialog(this->sprites["selfsuynghi"], const_cast <wchar_t*>(L"Mình không còn sức cho việc này"), this->player->getName(), "tired", this->player);
					}
				}




				//check interact school door
				else if (MConnect->currentMap == "school") {
					int kq = 0, piano = 0, displaypc = 0, daicuongschool = 0, tudo = 0;
					for (int i = 0; i < this->objectList.size(); i++) {
						if (this->objectList[i]->getName() == "SchoolDoor") {
							int curdis = this->objectList[i]->getDistance(*this->player);
							if (curdis < 60) kq = 1;
						}
						else if (this->objectList[i]->getName() == "Piano") {
							int curdis = this->objectList[i]->getDistance(*this->player);
							if (curdis < 60) piano = 1;
						}
						else if (this->objectList[i]->getName() == "DisplayPC") {
							int curdis = this->objectList[i]->getDistance(*this->player);
							if (curdis < 60) displaypc = 1;
						}
						else if (this->objectList[i]->getName() == "DaiCuongSchool") {
							int curdis = this->objectList[i]->getDistance(*this->player);
							if (curdis < 60) daicuongschool = 1;
						}
						else if (this->objectList[i]->getName() == "TuDo") {
							int curdis = this->objectList[i]->getDistance(*this->player);
							if (curdis < 60) tudo = 1;
						}
					}
					if (kq) {
						startLoadingScreen();
						m_sounds["opendoor"].play();
						this->curMap = MConnect->m_home;
						MConnect->currentMap = "home";
						this->player->setPosition(386, 252);
						
					}
					else if (piano) {
						addQueueDialog(this->sprites["selfsuynghi"], const_cast <wchar_t*>(L"Một cái đàn piano...Nhưng mà mình không biết chơi đàn"), this->player->getName(), "scare", this->player);
						addQueueDialog(this->sprites["selfsuynghi"], const_cast <wchar_t*>(L"Giá như ngày xưa mình học chơi đàn..."), this->player->getName(), "scare", this->player);
					}
					else if (displaypc) {
						addQueueDialog(this->sprites["selfsuynghi"], const_cast <wchar_t*>(L"Một cái màn hình...nhưng mà không có cây máy??"), this->player->getName(), "think", this->player);
						addQueueDialog(this->sprites["selfsuynghi"], const_cast <wchar_t*>(L"Đúng là trường P..."), this->player->getName(), "think", this->player);
					}
					else if (daicuongschool) {
						addQueueDialog(this->sprites["selfsuynghi"], const_cast <wchar_t*>(L"Ngồi học đại cương ở đây có vẻ không phải ý hay ..."), this->player->getName(), "think", this->player);
					}
					else if (tudo) {
						addQueueDialog(this->sprites["selfsuynghi"], const_cast <wchar_t*>(L"Thẻ xe ..., ai đó lại sắp mất 50 nghìn...."), this->player->getName(), "think", this->player);
					}


					





				}
				else if (MConnect->currentMap == "home") {
					int kq = 0, bed = 0, daicuong = 0, code = 1;
					for (int i = 0; i < this->objectList.size(); i++) {
						if (this->objectList[i]->getName() == "HomeDoor") {
							int curdis = this->objectList[i]->getDistance(*this->player);
							if (curdis < 60) kq = 1;
						}
						else if (this->objectList[i]->getName() == "Bed") {
							int curdis = this->objectList[i]->getDistance(*this->player);
							if (curdis < 60) bed = 1;
						}
						else if (this->objectList[i]->getName() == "DaiCuong") {
							int curdis = this->objectList[i]->getDistance(*this->player);
							if (curdis < 60) daicuong = 1;
						}
						else if (this->objectList[i]->getName() == "Code") {
							int curdis = this->objectList[i]->getDistance(*this->player);
							if (curdis < 60) code = 1;
						}
					}
					if (kq) {
						startLoadingScreen();
						m_sounds["opendoor"].play();
						this->curMap = MConnect->m_school;
						MConnect->currentMap = "school";
						this->player->setPosition(200, 250);
					}
					else if (bed) {
						m_sounds["alarm"].play();
						startLoadingScreen();
						MConnect->dayCount++;
						this->player->setPosition(574, 448);
						MConnect->energyPlayer = 2;
						addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Chào ngày mới !"), this->player->getName(), "fun", this->player);
						addQueueDialog(this->sprites["selfvui"], const_cast <wchar_t*>(L"Năng lượng của bạn đã được hồi lại"), this->player->getName(), "fun", this->player);
					}
					else if (daicuong) {
						if (MConnect->energyPlayer > 0) {
							MConnect->lastMap = MConnect->currentMap;
							MConnect->lastX = this->player->getPosition().x;
							MConnect->lastY = this->player->getPosition().y;
							MConnect->energyPlayer--;
							GSM->changeState(StateTypes::QUIZDAICUONG);
						}
						else {
							addQueueDialog(this->sprites["selfsuynghi"], const_cast <wchar_t*>(L"Mình không còn sức nữa..."), this->player->getName(), "tired", this->player);
						}
					}
					else if (code) {
						if (MConnect->energyPlayer > 0) {
							MConnect->lastMap = MConnect->currentMap;
							MConnect->lastX = this->player->getPosition().x;
							MConnect->lastY = this->player->getPosition().y;
							MConnect->energyPlayer--;
							GSM->changeState(StateTypes::QUIZCODE);
						}
						else {
							addQueueDialog(this->sprites["selfsuynghi"], const_cast <wchar_t*>(L"Mình không còn sức nữa..."), this->player->getName(), "tired", this->player);
						}
					}

				}
			}

			//debug get location
			if (e.key.code == sf::Keyboard::L) {
				std::cout << this->player->getPosition().x << " " << this->player->getPosition().y << "\n";
			}
		}

	}

	this->curMap->Update(dt, this->player);
}

void GSPlay::addQueueDialog(sf::Sprite face, wchar_t text[], std::string npcName, std::string emotes, Player * player) {
	DialogSystem* dialog = new DialogSystem();
	//std::cout << wcslen(text) << "\n";
	dialog->setText(face, text, npcName, 250, 600, 20, emotes, player);
	this->queueDialog.push(dialog);
}



void GSPlay::startLoadingScreen() {
	isLoadingScreen = true;
	isLoadingScreen_time = 0.f;
}

void GSPlay::render() {


	ppmWalk += this->dt;




	this->bgmsound.setVolume(25);

	if (MConnect->tutin <= 0 || MConnect->code <= 0 || MConnect->daicuong <= 0) {
		GSM->changeState(StateTypes::END);
	}
	if (MConnect->dayCount > 30) {
		GSM->changeState(StateTypes::END);
	}




	//WConnect->getWindow()->draw(m_background);

	//load tilemap
	this->curMap->Render(WConnect->getWindow());

	//render player
	this->player->render(*WConnect->getWindow(), true, this->dt);




	


	//check npc chat + render npc
	this->player->setChattingWith(nullptr);
	Player* npcChat = nullptr;
	int distance = 1e6;
	for (int i = 0; i < this->npcList.size(); i++) {
		//render npc
		if (MConnect->currentMap == "school") {
			this->npcList[i]->render(*WConnect->getWindow(), true, this->dt);
			int curdis = this->npcList[i]->getDistance(*this->player);
			if (curdis < 60) {
				if (curdis < distance) {
					npcChat = this->npcList[i];
				}
			}
		}

	}

	//show chat bubble
	if (npcChat != nullptr) {
		npcChat->showSpeechBubble(*WConnect->getWindow());
		this->player->setChattingWith(npcChat);
	}


	//render object (door interact etc)
	for (int i = 0; i < this->objectList.size(); i++) {
		
		if (MConnect->currentMap == "school") {
			if (this->objectList[i]->getName() == "SchoolDoor") {
				int curdis = this->objectList[i]->getDistance(*this->player);
				if (curdis < 60) {
					this->objectList[i]->emote("exit", this->dt, this->dt);
				}
				this->objectList[i]->render(*WConnect->getWindow(), false, 1.f);
			}
			if (this->objectList[i]->getName() == "Piano") {
				int curdis = this->objectList[i]->getDistance(*this->player);
				if (curdis < 60) {
					this->objectList[i]->emote("action", this->dt, this->dt);
				}
				this->objectList[i]->render(*WConnect->getWindow(), false, 1.f);
			}
			if (this->objectList[i]->getName() == "DisplayPC") {
				int curdis = this->objectList[i]->getDistance(*this->player);
				if (curdis < 60) {
					this->objectList[i]->emote("action", this->dt, this->dt);
				}
				this->objectList[i]->render(*WConnect->getWindow(), false, 1.f);
			}
			if (this->objectList[i]->getName() == "DaiCuongSchool") {
				int curdis = this->objectList[i]->getDistance(*this->player);
				if (curdis < 60) {
					this->objectList[i]->emote("action", this->dt, this->dt);
				}
				this->objectList[i]->render(*WConnect->getWindow(), false, 1.f);
			}
			if (this->objectList[i]->getName() == "TuDo") {
				int curdis = this->objectList[i]->getDistance(*this->player);
				if (curdis < 60) {
					this->objectList[i]->emote("action", this->dt, this->dt);
				}
				this->objectList[i]->render(*WConnect->getWindow(), false, 1.f);
			}
			
		}
		else if (MConnect->currentMap == "home") {
			if (this->objectList[i]->getName() == "DaiCuong") {
				int curdis = this->objectList[i]->getDistance(*this->player);
				if (curdis < 60) {
					this->objectList[i]->emote("learn", this->dt, 1.f);
				}
				this->objectList[i]->render(*WConnect->getWindow(), false, this->dt);
			}
			if (this->objectList[i]->getName() == "Code") {
				int curdis = this->objectList[i]->getDistance(*this->player);
				if (curdis < 60) {
					this->objectList[i]->emote("learn", this->dt, 1.f);
				}
				this->objectList[i]->render(*WConnect->getWindow(), false, this->dt);
			}
			if (this->objectList[i]->getName() == "HomeDoor") {
				int curdis = this->objectList[i]->getDistance(*this->player);
				if (curdis < 60) {
					this->objectList[i]->emote("exit", this->dt, 1.f);
				}
				this->objectList[i]->render(*WConnect->getWindow(), false, this->dt);
			}
			if (this->objectList[i]->getName() == "Bed") {
				int curdis = this->objectList[i]->getDistance(*this->player);
				if (curdis < 60) {
					this->objectList[i]->emote("clock", this->dt, 1.f);
				}
				this->objectList[i]->render(*WConnect->getWindow(), false, this->dt);
			}
		}
	}

	


	//load dialog
	if (this->queueDialog.size()) {
		if (!isLoadingScreen) {
			DialogSystem* queueFront = this->queueDialog.front();
			//std::cout << this->queueDialog.size() << " " << queueFront->isDone << "\n";
			if (queueFront->isDone == false) {
				queueFront->drawDialogSystem(*WConnect->getWindow(), this->dt);
				if (queueFront->startEmote == false) {
					if (queueFront->emotes != "none") queueFront->player->emote(queueFront->emotes, this->dt, 2.f);
					queueFront->startEmote = true;
				}
			}
			else {
				queueDialog.pop();
			}
		}
	}

	if (isLoadingScreen) {
		int tocdo = 25;
		isLoadingScreen_time += this->dt*tocdo;
		int timeint = isLoadingScreen_time;
		if (timeint >= 0 && timeint <= 47) {
			WConnect->getWindow()->draw(this->sprites["animationloading" + to_string(timeint)]);
		}
		else {
			isLoadingScreen = false;
		}

	}

	if (!isLoadingScreen) {
		displayDay.setString(L"Ngày thứ: " + to_string(MConnect->dayCount));
		displayTuTin.setString(L"Tự tin: " + to_string(MConnect->tutin));
		displayCode.setString(L"Code: " + to_string(MConnect->code));
		displayDaiCuong.setString(L"Đại cương: " + to_string(MConnect->daicuong));
		WConnect->getWindow()->draw(displayDay);
		WConnect->getWindow()->draw(displayTuTin);
		WConnect->getWindow()->draw(displayCode);
		WConnect->getWindow()->draw(displayDaiCuong);
		if (MConnect->energyPlayer > 0) {
			WConnect->getWindow()->draw(energy1);
		}
		if (MConnect->energyPlayer > 1) {
			WConnect->getWindow()->draw(energy2);
		}
		
	}

	


	
	


	
}