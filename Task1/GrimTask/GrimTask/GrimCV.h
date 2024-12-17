#include "pch.h"


struct S_Coordinate {
	int m_nX1;
	int m_nY1;
	int m_nX2;
	int m_nY2;

	S_Coordinate(){ 
		m_nX1 = 0;
		m_nY1 = 0;
		m_nX2 = 0;
		m_nY2 = 0;
	}
	S_Coordinate(int nX1, int nY1, int nX2, int nY2) {
		m_nX1 = nX1;
		m_nY1 = nY1;
		m_nX2 = nX2;
		m_nY2 = nY2;
	}

	void setCoordinate1(int nX1, int nY1) {
		m_nX1 = nX1;
		m_nY1 = nY1;
	}

	void setCoordinate(int nX1, int nY1, int nX2, int nY2) {
		m_nX1 = nX1;
		m_nY1 = nY1;
		m_nX2 = nX2;
		m_nY2 = nY2;
	}
};

class C_GrimCV {
private:
	S_Coordinate m_sCoordinate;
	int m_nRadius;

public:
	C_GrimCV();
	~C_GrimCV();

	BOOL DrawCircle(unsigned char* pucImg, int nPitch, int nImageWidth, int nImageHeight);
	BOOL Action(unsigned char* pucImg, int nPitch, int nImageWidth, int nImageHeight);

	BOOL ShiftImageUp();
	BOOL ShiftImageDown(int nHeight);
	BOOL ShiftImageLeft();
	BOOL ShiftImageRight(int width);

	void setCoordinate(int nX1, int nY1, int nX2, int nY2);
	S_Coordinate getCoordinate();

	int getRadius();

};