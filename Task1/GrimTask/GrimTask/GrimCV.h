#include "pch.h"

class C_GrimCV {
private:

public:
	C_GrimCV();
	~C_GrimCV();

	BOOL DrawCircle(unsigned char* pucImg, int nPitch, int nImageWidth, int nImageHeight);
	BOOL Action();
	BOOL OpenImage();
	BOOL DetectCircle();

};