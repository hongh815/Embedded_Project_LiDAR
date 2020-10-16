#include <iostream>

using namespace std;


class Circle { 				// 헤더파일로 거의 넘기는 부분
	public : 					// 접근제한자 public, private, protected
		int radius; 			// 멤버 변수


		Circle(); 				// 기본 생성자 :: 적지 않아도 상관없다. (필수 x)
		Circle(int r);			// 생성자 함수 선언	
		~Circle();				// 소멸자 선언
	   double getArea(); 	// 멤버 함수 선언
};

Circle::Circle():Circle(20) {
	cout << "Circle() 실행" << endl;
} 			// 기본생성자 함수 정의

Circle::Circle(int r) { 	// 생성자 함수 정의
	cout << "Circle(int r) 실행 : ";
    cout << r << endl;
	radius = r;
}		// 출력에서 보면 알겠지만 소멸자는 메인함수의 두 써클들을 소멸시킬때 가장 나중에 실행된 것부터 소멸시킨다 즉,  여기서는 30이 먼저 소멸된다.

Circle::~Circle() { // 소멸자 함수 정의
	cout << radius << " - Circle 소멸" << endl;
}

double Circle::getArea() { //멤버 함수 정의 Circle안에 있다고 표시하는 부분과 그안의 함수 정의
			return 3.14 * radius * radius;
}


int main(void) {

	Circle donut;
//	donut.radius = 1;
	double area = donut.getArea();
	cout << area << endl;

	Circle pizza(30);
	double pizzaarea = pizza.getArea();
	cout << pizzaarea << endl;
}


