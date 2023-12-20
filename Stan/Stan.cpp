// Stan.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

// Контекст, який визначає інтерфейс для клієнтів та утримує екземпляр конкретного стану
class Context;

// Абстрактний клас для стану
class State {
public:
    virtual void handle(Context& context) = 0;
    virtual ~State() = default;
};

// Конкретний стан A
class ConcreteStateA : public State {
public:
    void handle(Context& context) override;
};

// Конкретний стан B
class ConcreteStateB : public State {
public:
    void handle(Context& context) override;
};

// Контекст, що утримує стан
class Context {
public:
    Context(State* initialState) : state(initialState) {}

    void setState(State* newState) {
        delete state;  // Звільнення попереднього стану
        state = newState;
    }

    void request() {
        state->handle(*this);
    }

    ~Context() {
        delete state;  // Звільнення поточного стану при знищенні об'єкта
    }

private:
    State* state;
};

// Реалізація методів для конкретних станів

void ConcreteStateA::handle(Context& context) {
    std::cout << "Handling request in State A. Transitioning to State B." << std::endl;
    context.setState(new ConcreteStateB);
}

void ConcreteStateB::handle(Context& context) {
    std::cout << "Handling request in State B. Transitioning to State A." << std::endl;
    context.setState(new ConcreteStateA);
}

int main() {
    // Створення контексту з початковим станом StateA
    Context context(new ConcreteStateA);

    // Послідовне викликання запитів
    context.request();
    context.request();
    context.request();

    return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
