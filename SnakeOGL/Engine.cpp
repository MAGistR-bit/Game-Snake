#include "stdafx.h"

#include "Engine.h"

// Память на последнуюю активированную текстуру
GLuint lasttex=-1 ;

void loadTexture(GLuint * tex, const char * filename) {
	// Загрузка картинки
	AUX_RGBImageRec *data = auxDIBImageLoadA(filename);

	// Создание текстуры
	glGenTextures(1, tex);
	glBindTexture(GL_TEXTURE_2D, *tex);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			
	glTexImage2D(GL_TEXTURE_2D, 0, 3, data->sizeX, data->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, data->data);
}

void renderSprite(const Sprite & spr, int x, int y) {
	// Переключаем текстуру только при необходимости
	if ((lasttex==-1)||(lasttex!=spr.texcode)) {
		glBindTexture(GL_TEXTURE_2D, spr.texcode);      
		lasttex = spr.texcode ;
	}
  
	glBegin(GL_QUADS);
	
	glTexCoord2f(0.0, 1.0); glVertex2f(x, y);
	glTexCoord2f(1.0, 1.0); glVertex2f(x+spr.width, y);
	glTexCoord2f(1.0, 0.0); glVertex2f(x+spr.width, y+spr.height);
	glTexCoord2f(0.0, 0.0); glVertex2f(x, y+spr.height);
		
	glEnd() ;  
  	
}

void renderSpriteRotated(const Sprite & spr, int x, int y, SpriteDir dir) {
	if ((lasttex==-1)||(lasttex!=spr.texcode)) {
		glBindTexture(GL_TEXTURE_2D, spr.texcode);      
		lasttex = spr.texcode ;
	}
  
	glBegin(GL_QUADS);
	if (dir==dLeft) {	
	glTexCoord2f(0.0, 1.0); glVertex2f(x, y);
	glTexCoord2f(1.0, 1.0); glVertex2f(x+spr.width, y);
	glTexCoord2f(1.0, 0.0); glVertex2f(x+spr.width, y+spr.height);
	glTexCoord2f(0.0, 0.0); glVertex2f(x, y+spr.height);
	}
	if (dir==dRight) {	
	glTexCoord2f(1.0, 0.0); glVertex2f(x, y);
	glTexCoord2f(0.0, 0.0); glVertex2f(x+spr.width, y);
	glTexCoord2f(0.0, 1.0); glVertex2f(x+spr.width, y+spr.height);
	glTexCoord2f(1.0, 1.0); glVertex2f(x, y+spr.height);
	}
	if (dir==dDown) {	
	glTexCoord2f(1.0, 1.0); glVertex2f(x, y);
	glTexCoord2f(1.0, 0.0); glVertex2f(x+spr.width, y);
	glTexCoord2f(0.0, 0.0); glVertex2f(x+spr.width, y+spr.height);
	glTexCoord2f(0.0, 1.0); glVertex2f(x, y+spr.height);
	}
	if (dir==dUp) {	
	glTexCoord2f(0.0, 0.0); glVertex2f(x, y);
	glTexCoord2f(0.0, 1.0); glVertex2f(x+spr.width, y);
	glTexCoord2f(1.0, 1.0); glVertex2f(x+spr.width, y+spr.height);
	glTexCoord2f(1.0, 0.0); glVertex2f(x, y+spr.height);
	}
	glEnd() ;  
}

void renderDigits(int num, Sprite * digits, int x, int y) {
	char str[32] ;
	sprintf(str,"%d",num) ;
	// Просто рендерим спрайты цифр со сдвигом
	for (int i=0; i<strlen(str); i++) {
		renderSprite(digits[str[i]-'0'],x,y) ;
		x+=digits[0].width ;
	}
}

void renderTimeStr(char * timestr, Sprite * digits, const Sprite & dsep, int x, int y) {
	for (int i=0; i<strlen(timestr); i++) {
		if ((timestr[i]>='0')&&(timestr[i]<='9')) renderSprite(digits[timestr[i]-'0'],x,y) ;
		if (timestr[i]==':') renderSprite(dsep,x,y) ;
		x+=digits[0].width ;
	}
}
