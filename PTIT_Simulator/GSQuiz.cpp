
#include "GSQuiz.h"
#include "MapConnector.h"
#include  <random>
#include  <iterator>

using namespace sf;
#define lmao const_cast <wchar_t*>

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(g));
	return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	return select_randomly(start, end, gen);
}


GSQuiz::GSQuiz(int type) {
	cout << "create quiz state\n";
	this->type = type;
}

GSQuiz::~GSQuiz() {
	
}

void GSQuiz::exit() {
}

void GSQuiz::pause() {
}

void GSQuiz::resume() {
}

void GSQuiz::init() {
	cout << "init\n";
	m_background.setTexture(*RMInstance->getTexture("quiz"));
	if (!m_soundBuffer["correct"].loadFromFile("../Resource/Sound/correct.wav")) {
		std::cout << "Loi am thanh\n";
		return;
	}

	if (!m_soundBuffer["wrong"].loadFromFile("../Resource/Sound/wrong.wav")) {
		std::cout << "Loi am thanh\n";
		return;
	}

	m_sounds["correct"].setBuffer(m_soundBuffer["correct"]);
	m_sounds["wrong"].setBuffer(m_soundBuffer["wrong"]);
	

	fontText.loadFromFile("../Resource/Font/pixelvh.ttf");
	question.setFont(fontText);


	ans1.setFont(fontText);
	ans2.setFont(fontText);
	ans3.setFont(fontText);
	ans4.setFont(fontText);


	question.setString("Question");
	question.setFillColor(Color::Yellow);
	question.setCharacterSize(15);
	question.setPosition(1024 / 6, 720 / 3);

	ans1.setString("A");
	ans1.setFillColor(Color::White);
	ans1.setCharacterSize(15);
	ans1.setPosition(1024 / 6, 720 / 3 + 100);

	ans2.setString("B");
	ans2.setFillColor(Color::White);
	ans2.setCharacterSize(15);
	ans2.setPosition(1024 / 6, 720 / 3 + 200);

	ans3.setString("C");
	ans3.setFillColor(Color::White);
	ans3.setCharacterSize(15);
	ans3.setPosition(1024 / 6, 720 / 3 + 300);

	ans4.setString("D");
	ans4.setFillColor(Color::White);
	ans4.setCharacterSize(15);
	ans4.setPosition(1024 / 6, 720 / 3 + 400);

	std::vector<Quiz> list_daicuong;
	std::vector<Quiz> list_code;


	//Quiz(wchar_t question[], wchar_t ans1[], wchar_t ans2[], wchar_t ans3[], wchar_t ans4[], int cong_tutin, int cong_code, int cong_daicuong, int correctAns);

	list_code.push_back(Quiz(
		lmao(L"Kết thúc một dòng lệnh trong chương trình C++, ta sử dụng ký hiệu gì?"),
		lmao(L"A. Dấu ;"),
		lmao(L"B. Dấu ."),
		lmao(L"C. Dấu ,"),
		lmao(L"D. Dấu ."),
		0, 3, 0, 1)
	);

	list_code.push_back(Quiz(
		lmao(L"Thuật toán nào sau đây không phải là thuật toán Greedy ?"),
		lmao(L"A. Dijkstra Algorithm"),
		lmao(L"B. Huffman Coding"),
		lmao(L"C. Prim Algorithm"),
		lmao(L"D. Bellmen Ford"),
		0, 3, 0, 4)
	);

	list_code.push_back(Quiz(
		lmao(L"Greedy Approach là một kĩ thuật lập trình !!!"),
		lmao(L"A. Đúng"),
		lmao(L"B. Sai"),
		lmao(L"C. Tuỳ trường hợp"),
		lmao(L"D. Đáp án khác"),
		0, 3, 0, 2)
	);

	list_code.push_back(Quiz(
		lmao(L"Độ phức tạp của thuật toán Dijkstra ?"),
		lmao(L"A. O(E * E Log V)"),
		lmao(L"B. O(V Log E)"),
		lmao(L"C. O(V Log V)"),
		lmao(L"D. Đáp án khác"),
		0, 3, 0, 4)
	);

	list_code.push_back(Quiz(
		lmao(L"Tên gọi khác của giải thuật Dijkstra ?"),
		lmao(L"A. Đường đi ngắn nhất đa nguồn"),
		lmao(L"B. Đường đi ngắn nhất đơn nguồn"),
		lmao(L"C. Đường đi ngắn nhất đa diểm đến"),
		lmao(L"D. Đường đi ngắn nhất đơn điểm đến"),
		0, 3, 0, 2)
	);

	list_code.push_back(Quiz(
		lmao(L"Which of the following operators is overloadable?"),
		lmao(L"A. ?:"),
		lmao(L"B. new"),
		lmao(L"C. ::"),
		lmao(L"D. ."),
		0, 3, 0, 2)
	);

	list_code.push_back(Quiz(
		lmao(L"What is true about the variable named ptr? void *ptr;"),
		lmao(L"A. It is a pointer initialized at NULL."),
		lmao(L"B. It is a pointer to a void function."),
		lmao(L"C. That declaration causes a compiler error, as pointers must specify a type."),
		lmao(L"D. It is a pointer to a value with no specific type, so it may be cast to point to any type."),
		0, 3, 0, 4)
	);

	list_code.push_back(Quiz(
		lmao(L"What is the statement below equivalent to? sprite->x"),
		lmao(L"A. sprite.x"),
		lmao(L"B. sprite.*x"),
		lmao(L"C. (*sprite).x"),
		lmao(L"D. *sprite.x"),
		0, 3, 0, 3)
	);

	list_code.push_back(Quiz(
		lmao(L"What is this expression equivalent to? A->B->C->D"),
		lmao(L"A. A.B.C.D"),
		lmao(L"B. *A.*B.*C.*D"),
		lmao(L"C. &A.&B.&C.&D"),
		lmao(L"D. *(*((*A).B).C).D"),
		0, 3, 0, 4)
	);
	list_code.push_back(Quiz(
		lmao(L"Which choice best describes the type long?"),
		lmao(L"A. an integer number of at least 32 bits"),
		lmao(L"B. a string with more than 255 characters"),
		lmao(L"C. a pointer"),
		lmao(L"D. a 64-bit floating point number"),
		0, 3, 0, 1)
	);

	list_code.push_back(Quiz(
		lmao(L"Which of the following types has the closest functionality to a class?"),
		lmao(L"A. struct"),
		lmao(L"B. union"),
		lmao(L"C. enum"),
		lmao(L"D. namespace"),
		0, 3, 0, 1)
	);

	list_code.push_back(Quiz(
		lmao(L"What is true about the variable named ptr? void* ptr; "),
		lmao(L"A. That declaration causes a compiler error, as pointers must specify a type."),
		lmao(L"B. It is a pointer to a value with no specific type, so it may be cast to point to any type."),
		lmao(L"C. It is a pointer to a void function"),
		lmao(L"D. It is a pointer initialized at NULL."),
		0, 3, 0, 2)
	);

	list_code.push_back(Quiz(
		lmao(L" What is the meaning of base class in C++ ?"),
		lmao(L"A. It inherit other class"),
		lmao(L"B. It has a pointer variable"),
		lmao(L"C. It is the first class declared"),
		lmao(L"D. Another class got inherit from this class"),
		0, 3, 0, 4)
	);

	list_code.push_back(Quiz(
		lmao(L" What is a default constructor?"),
		lmao(L"A. a constructor that can be used with no arguments"),
		lmao(L"B. a contructor that does not have a return value"),
		lmao(L"C. a constructor that is used by multiple classes"),
		lmao(L"D. a constructor that initializes all members of a class"),
		0, 3, 0, 1)
	);

	list_code.push_back(Quiz(
		lmao(L" What if else could be replace to ?"),
		lmao(L"A. certain structure"),
		lmao(L"B. choosing structure"),
		lmao(L"C. selective structure"),
		lmao(L"D. None of the Above"),
		0, 3, 0, 3)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Xác định tập lũy thừa của tập A={toán, văn}"),
		lmao(L"A. {{toán}, {văn}}"),
		lmao(L"B. {{toán}, {văn}}, {{toán}, {văn}, Ф}"),
		lmao(L"C. {{toán}, {văn}, {toán, văn}, Ф}"),
		lmao(L"D. {{toán}, {văn}, {toán, văn}}"),
		0, 0, 3, 3)
	);
	list_daicuong.push_back(Quiz(
		lmao(L"Số các xâu nhị phân có độ dài là 10 là:"),
		lmao(L"A. 1024"),
		lmao(L"B. 1000"),
		lmao(L"C. 20"),
		lmao(L"D. 10"),
		0, 0, 3, 1)
	);
	list_daicuong.push_back(Quiz(
		lmao(L"Có bao nhiêu xâu nhị phân độ dài bằng 8 bắt đầu bởi 00 và kết thúc bởi 11"),
		lmao(L"A. 64"),
		lmao(L"B. 16"),
		lmao(L"C. 32"),
		lmao(L"D. 128"),
		0, 0, 3, 2)
	);
	list_daicuong.push_back(Quiz(
		lmao(L"Có 8 đội bóng thi đấu vòng tròn. Hỏi phải tổ chức bao nhiêu trận đấu?"),
		lmao(L"A. 64"),
		lmao(L"B. 56"),
		lmao(L"C. 28"),
		lmao(L"D. 32"),
		0, 0, 3, 3)
	);
	list_daicuong.push_back(Quiz(
		lmao(L"Cây là đồ thị vô hướng liên thông…?"),
		lmao(L"A. Không có chu trình Hamilton"),
		lmao(L"B. Không có đỉnh treo"),
		lmao(L"C. Không có chu trình"),
		lmao(L"D. Không có chu trình Euler"),
		0, 0, 3, 3)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Hiệu ứng compton là do sự tán xạ của:"),
		lmao(L"A. Photon bởi electron trong nguyên tử"),
		lmao(L"B. Photon bời tinh thể"),
		lmao(L"C. Sóng De Broglie bởi tinh thể"),
		lmao(L"D. Sóng De Broglie bởi electron trong nguyên tử"),
		0, 0, 3, 1)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Spin của electron là gì?"),
		lmao(L"A. Là momen động lượng quỹđạo ứng với lượng tửl=1/2"),
		lmao(L"B. Là một phần của momen động lượng quỹ đạo (orbital)"),
		lmao(L"C. Là momen động lượng riêng của electron"),
		lmao(L"D. Là năng lượng phụdo sựtựquay quanh mình của electron"),
		0, 0, 3, 3)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Trong chân không, mọi photon có cùng:"),
		lmao(L"A. Vận tốc"),
		lmao(L"B. Tần số"),
		lmao(L"C. Năng lượng"),
		lmao(L"D. Bước sóng"),
		0, 0, 3, 1)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Theo quang học sóng, cách phát biểu nào dưới đây không đúng?"),
		lmao(L"A. Tần sốcủa ánh sáng đơn sắc thay đổi theo môi trường"),
		lmao(L"B. Ánh sáng đơn sắc có một tần sốriêng"),
		lmao(L"C. Bước sóng của ánh sáng đơn sắc thay đổi theo môi trường"),
		lmao(L"D. Chiết suất của môi trường phụthuộc vào chu kỳcủa ánh sáng"),
		0, 0, 3, 1)
	);


	list_daicuong.push_back(Quiz(
		lmao(L"Who is your mother's sister's daughter?"),
		lmao(L"A. She is my mother's nephew."),
		lmao(L"B. She my cousin."),
		lmao(L"C. Is my mother's niece."),
		lmao(L"D. My mother's sister's daughter is my cousin."),
		0, 0, 3, 4)
	);
	list_daicuong.push_back(Quiz(
		lmao(L"I was driving ______ the road when my car started making a funny sound."),
		lmao(L"A. in"),
		lmao(L"B. at"),
		lmao(L"C. away"),
		lmao(L"D. down"),
		0, 0, 3, 4)
	);
	list_daicuong.push_back(Quiz(
		lmao(L"Where ______ the Battle of the Bulge?"),
		lmao(L"A. was"),
		lmao(L"B. are"),
		lmao(L"C. is"),
		lmao(L"D. were"),
		0, 0, 3, 1)
	);
	list_daicuong.push_back(Quiz(
		lmao(L"Had they ______ arrived when you got there?"),
		lmao(L"A. after"),
		lmao(L"B. before"),
		lmao(L"C. still"),
		lmao(L"D. already"),
		0, 0, 3, 4)
	);
	list_daicuong.push_back(Quiz(
		lmao(L"______?. Adolph Hitler did."),
		lmao(L"A. Who start World War Two?"),
		lmao(L"B. Started who The Second World War?"),
		lmao(L"C. Who started The Second World War?"),
		lmao(L"D. Who caused world war two?"),
		0, 0, 3, 3)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Có bao nhiêu hàm số khác nhau từ tập có 4 phần tử đến tập có 3 phần tử:"),
		lmao(L"A. 81"),
		lmao(L"B. 64"),
		lmao(L"C. 4"),
		lmao(L"D. 12"),
		0, 0, 3, 2)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Số xâu nhị phân độ dài 4 có bít cuối cùng bằng 1 là:"),
		lmao(L"A. 8"),
		lmao(L"B. 12"),
		lmao(L"C. 16"),
		lmao(L"D. đáp án khác"),
		0, 0, 3, 1)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Có bao nhiêu số lẻ có 3 chữ số được tạo từ tập các chữ số {0,1,2,3,4,5}:"),
		lmao(L"A. 48"),
		lmao(L"B. 60"),
		lmao(L"C. 90"),
		lmao(L"D. đáp án khác"),
		0, 0, 3, 3)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Có bao nhiêu số tự nhiên có 3 chữ số được tạo từ tập các chữ số {1,3,5,7,9}"),
		lmao(L"A. 125"),
		lmao(L"B. 60"),
		lmao(L"C. 124"),
		lmao(L"D. 65"),
		0, 0, 3, 1)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Xác định tích đề các của 2 tập A = {9,x,y} và B = {9,a}:"),
		lmao(L"A. {(9,a), (x,9),(y,9),(x,a),(y,a),(9,9)}"),
		lmao(L"B. {(9,x), (9,y), (9,9), (a,9),(a,x),(a,y)}"),
		lmao(L"C. {(9,x), (9,a), (x,a), (y,a), (x,9),(y,9)} "),
		lmao(L"D. {(x,9), (a,9),(y,9),(x,a),(y,a),(9,9)}"),
		0, 0, 3, 1)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Cho tập S = a, b, c khi đó số phần tử của tập lũy thừa của tập S là:"),
		lmao(L"A. 3"),
		lmao(L"B. 6"),
		lmao(L"C. 8 "),
		lmao(L"D. 9}"),
		0, 0, 3, 3)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Peru and Chile ______ in Europe. They’re in _____."),
		lmao(L"A. is – South America"),
		lmao(L"B. is not - South America"),
		lmao(L"C. are not - South America "),
		lmao(L"D. are - Asia}"),
		0, 0, 3, 3)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Peru and Chile ______ in Europe. They’re in _____."),
		lmao(L"A. is – South America"),
		lmao(L"B. is not - South America"),
		lmao(L"C. are not - South America "),
		lmao(L"D. are - Asia}"),
		0, 0, 3, 3)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Có bao nhiêu xâu nhị phân độ dài 7 bít hoặc được bắt đầu bằng bít 10 hoặc được kết thúc bằng bít 00?."),
		lmao(L"A. 56"),
		lmao(L"B. 64"),
		lmao(L"C. 43"),
		lmao(L"D. 32"),
		0, 0, 3, 1)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Sai số nào có thể loại trừ trước khi đo?"),
		lmao(L"A. Sai số hệ thống."),
		lmao(L"B. Sai số dụng cụ."),
		lmao(L"C. Sai số ngẫu nhiên."),
		lmao(L"D. Đáp án khác"),
		0, 0, 3, 1)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Vịnh Hạ Long nằm ở tỉnh nào của Việt Nam ?"),
		lmao(L"A. Quảng Ninh."),
		lmao(L"B. Nghệ An."),
		lmao(L"C. Sơn La."),
		lmao(L"D. Bắc Ninh"),
		0, 0, 3, 1)
	);


	list_daicuong.push_back(Quiz(
		lmao(L"Vịnh Hạ Long nằm ở tỉnh nào của Việt Nam ?"),
		lmao(L"A. Quảng Ninh."),
		lmao(L"B. Nghệ An."),
		lmao(L"C. Sơn La."),
		lmao(L"D. Bắc Ninh"),
		0, 0, 3, 1)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Biểu hiện của không dân chủ là?"),
		lmao(L"A. Phát biểu tại hội nghị."),
		lmao(L"B. Góp ý vào Luật Giáo dục."),
		lmao(L"C. Đóng góp ý kiến tại buổi sinh hoạt lớp"),
		lmao(L"D. Tham gia biểu tình trái pháp luật"),
		0, 0, 3, 4)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Bảo vệ hoà bình bằng cách dùng??"),
		lmao(L"A. Uy lực để giải quyết mâu thuẫn."),
		lmao(L"B. Sức mạnh để giải quyết mâu thuẫn."),
		lmao(L"C. Quân sự để giải quyết mâu thuẫn"),
		lmao(L"D. Thương lượng để giải quyết mâu thuẫn"),
		0, 0, 3, 4)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Nền dân chủ xã hội chủ nghĩa đầu tiên ra đời gắn với sự kiện lịch sự nào?"),
		lmao(L"A. Công xã Pari năm 1871."),
		lmao(L"B. Cách mạng Tháng Mười Nga năm 1917."),
		lmao(L"C. Cách mạng tư sản Pháp 1789"),
		lmao(L"D. Cách mạng Tháng Tám Việt Nam năm 1945"),
		0, 0, 3, 2)
	);

	list_daicuong.push_back(Quiz(
		lmao(L"Cơ sở kinh tế của nền dân chủ xã hội chủ nghĩa?"),
		lmao(L"A. Chế độ tư hữu về tư liệu sản xuất chủ yếu"),
		lmao(L"B. Chế độ công hữu về tư liệu sản xuất chủ yếu"),
		lmao(L"C. Chế độ sở hữu tập thể về tư liệu sản xuất chủ yếu"),
		lmao(L"D. Chế độ chiếm hữu tư nhân về ruộng đất"),
		0, 0, 3, 2)
	);



	if (type == 1) {
		currentQuiz = &list_daicuong[select_randomly(list_daicuong.begin(), list_daicuong.end()) - list_daicuong.begin()];
	}
	else {
		currentQuiz = &list_code[select_randomly(list_code.begin(), list_code.end()) - list_code.begin()];
	}

	
	//std::cout << currentQuiz->correctAns << " " << currentQuiz->cong_code << " " << currentQuiz->cong_daicuong << " " << currentQuiz->cong_tutin << "\n";



	correctAns = currentQuiz->correctAns;
	cong_code = currentQuiz->cong_code;
	cong_daicuong = currentQuiz->cong_daicuong;
	cong_tutin = currentQuiz->cong_tutin;
	question.setString(currentQuiz->question);
	ans1.setString(currentQuiz->ans1);
	ans2.setString(currentQuiz->ans2);
	ans3.setString(currentQuiz->ans3);
	ans4.setString(currentQuiz->ans4);
	doneload = true;
	






}

void GSQuiz::update(float deltaTime) {
	if (doneload) {
		this->dt = deltaTime;
		while (WConnect->getWindow()->pollEvent(this->sfEvent))
		{
			Event e = this->sfEvent;
			if (this->sfEvent.type == sf::Event::Closed)
				WConnect->getWindow()->close();
			else if (e.type == sf::Event::KeyPressed)
			{
				if (e.key.code == sf::Keyboard::Up)
					count--;
				else if (e.key.code == sf::Keyboard::Down)
					count++;
				else if (e.key.code == sf::Keyboard::Enter) {
					std::cout << count << " " << correctAns << " " << cong_code << " " << cong_daicuong << " " << cong_tutin << "\n";
					if (count >= 1 && count <= 4) {
						if (count == correctAns) {

							MConnect->code += cong_code;
							MConnect->daicuong += cong_daicuong;
							MConnect->tutin += cong_tutin;

							m_sounds["correct"].play();
						}
						else {
							MConnect->code -= cong_code;
							MConnect->daicuong -= cong_daicuong;
							MConnect->tutin -= cong_tutin;
							MConnect->tutin -= 1;

							m_sounds["wrong"].play();
						}
						MConnect->switchBack();

					}
				}

			}
		}
		if (count > 4) count = 1;
		else if (count < 0) count = 4;

		ans1.setFillColor(Color::White);
		ans2.setFillColor(Color::White);
		ans3.setFillColor(Color::White);
		ans4.setFillColor(Color::White);

		if (count == 1) {
			ans1.setFillColor(Color::Green);
		}
		else if (count == 2) {
			ans2.setFillColor(Color::Green);
		}
		else if (count == 3) {
			ans3.setFillColor(Color::Green);
		}
		else {
			ans4.setFillColor(Color::Green);
		}
	}

	
}

void GSQuiz::render() {
	if (doneload) {
		WConnect->getWindow()->draw(m_background);
		WConnect->getWindow()->draw(question);
		WConnect->getWindow()->draw(ans1);
		WConnect->getWindow()->draw(ans2);
		WConnect->getWindow()->draw(ans3);
		WConnect->getWindow()->draw(ans4);
	}

}