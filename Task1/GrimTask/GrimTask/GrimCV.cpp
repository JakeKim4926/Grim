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

    int nX;
    int nY;
    int nRadius;

    // get circle
    do {
        nRadius = rand() % (std::min(nImageWidth, nImageHeight) / 2);
        nX = rand() % nImageWidth;
        nY = rand() % nImageHeight;
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

BOOL C_GrimCV::Action()
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
