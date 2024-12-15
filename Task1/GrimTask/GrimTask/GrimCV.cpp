#include "pch.h"
#include "GrimCV.h"


C_GrimCV::C_GrimCV()
{
}

C_GrimCV::~C_GrimCV()
{
}


BOOL C_GrimCV::DrawCircle(unsigned char* pucImg, int nPitch, int nImageWidth, int nImageHeight)
{
	srand((unsigned int)time(NULL));

    int nX = m_sCoordinate.m_nX1;
    int nY = m_sCoordinate.m_nY1;
    int nRadius;

    // get circle
    do {
        nRadius = rand() % (std::min(nImageWidth, nImageHeight) / 2);
    } while (nX - nRadius < 0 || nX + nRadius >= nImageWidth ||
                nY - nRadius < 0 || nY + nRadius >= nImageHeight);

    // draw circle
    for (int y = 0; y < nImageHeight; y++) {
        for (int x = 0; x < nImageWidth; x++) {
            if ((x - nX) * (x - nX) + (y - nY) * (y - nY) <= nRadius * nRadius) {
                pucImg[y * nPitch + x] = COLOR_WHITE;
            }
        }
    }

    return TRUE;
}

BOOL C_GrimCV::Action(unsigned char* pucImg, int nPitch, int nImageWidth, int nImageHeigh)
{
    return 0;
}

BOOL C_GrimCV::OpenImage()
{
	return 0;
}

BOOL C_GrimCV::DetectCircle()
{
	return 0;
}

void C_GrimCV::setCoordinate(int nX1, int nY1, int nX2, int nY2)
{
    m_sCoordinate.setCoordinate(nX1, nY1, nX2, nY2);
}

S_Coordinate C_GrimCV::getCoordinate()
{
    return S_Coordinate();
}
