#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

template<class T> class Button
{
public:
	Button();
	~Button();
	void setTexture(std::string file_path_of_pic);
	void setAction(T(*your_func)());
	void setVariable(T r_variable);
	void setAction(void(*your_func)());
	void events(sf::Event *your_event);
	T onPress();
	sf::RectangleShape buttonRect;
private:
	sf::Texture buttonTexture;
	T(*t_func)();
	bool b_action, b_variable, b_press, b_action_v;
	T var;
	sf::Event ev;
	void(*t_funcv)();
};


template <class T> Button<T>::Button() {
	b_press = b_action = b_variable = b_action_v = false;

}



template <class T> Button<T>::~Button() {

}



template<class T>  void Button<T>::setAction(T(*your_func)()) {
	t_func = your_func;
	b_action = true;
	b_variable = false;
}



template<class T>  void Button<T>::setAction(void(*your_func)()) {
	t_funcv = your_func;
	b_action = true;
	b_action_v = true;
	b_variable = false;
}



template<class T>  void Button<T>::setVariable(T r_variable) {
	var = r_variable;
	b_action = false;
	b_action_v = false;
	b_variable = true;
}



template<class T>  void Button<T>::setTexture(std::string file_path_of_pic) {
	if (!buttonTexture.loadFromFile(file_path_of_pic)) {
		std::cout << "picture cant load" << std::endl;
	}
	else {
		buttonTexture.loadFromFile(file_path_of_pic);
		buttonRect.setTexture(buttonTexture);
	}
}



template <class T> void Button<T>::events(sf::Event *your_event) {
	if (your_event->type == your_event->MouseButtonReleased && your_event->mouseButton.button == sf::Mouse::Left) {
		if (buttonRect.getGlobalBounds().contains(static_cast<float>(your_event->mouseButton.x), static_cast<float>(your_event->mouseButton.x))) {
			b_press = true;
		}
	}
}



template <class T> T Button<T>::onPress() {
	if (b_action == true && b_action_v == false) {
		if (b_action) {
			return t_func();
		}
		else if (b_variable) {
			return var;
		}
		else if (b_action_v) {
			t_funcv();
		}
		b_press = false;
	}
	return static_cast<T>(NULL);
}


