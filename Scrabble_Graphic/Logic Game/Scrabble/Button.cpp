//
//  Button.cpp

#include "Button.h"
#include "../Scrabble_Defs.h"

Button::Button(IMAGE_NAME state_normal,
               IMAGE_NAME state_pressed,
               int posX, int posY,
               int width, int height)
{
    m_eCurrentState = NORMAL;
    m_iPosX = posX;
    m_iPosY = posY;
    m_iWidth = width;
    m_iHeight = height;
    m_eStateNormal = state_normal;
    m_eStatePressed = state_pressed;
}

bool Button::update (int mousePosX, int mousePosY, bool mouseIsPressed) {

	//TODO 4.1: Implementar la programaci� del update..
	bool action = false;
	if(((mousePosX >= m_iPosX) && (mousePosY >= m_iPosY)) &&
			((mousePosX <= m_iPosX + m_iWidth) && (mousePosY <= m_iPosY + m_iHeight)))
	{
			if(mouseIsPressed && m_eCurrentState == NORMAL){
				m_eCurrentState = PRESSED;
			}
			else if(!mouseIsPressed && m_eCurrentState == PRESSED){
				m_eCurrentState = NORMAL;
				action =  true;
			}
	}else{
		m_eCurrentState = NORMAL;
	}

    return action; //Aix� s'ha de modificar, ho deixem posat per tal que compili sense errors.
}

void Button::render () {
    //TODO 4.2: Implementar la programaci� del render...
	switch (m_eCurrentState) {
		case NORMAL:
			GraphicManager::getInstance()->drawSprite(m_eStateNormal, m_iPosX,m_iPosY);
			break;
		case PRESSED:
			GraphicManager::getInstance()->drawSprite(m_eStatePressed, m_iPosX,m_iPosY);
			break;
		case NONE:
//No hacer nada
		default:
			break;
	}
}

