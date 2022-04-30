/**
 * @file Laboratory.cpp
 * @author Charles Owen
 *
 * You are not allowed to change this class in any way!
 *
 * This is a simple adapter class that routes all of the
 * operations to the class LaboratoryStandin, which is a standin
 * for an actual laboratory in the system.
 */

#include "pch.h"
#include "Laboratory.h"
#include "LaboratoryStandin.h"

using namespace std;

Laboratory::Laboratory()
{
    mStandin = make_shared<LaboratoryStandin>();
}

void Laboratory::SetLocation(wxPoint location)
{
    mStandin->SetLocation(location);
}

wxPoint Laboratory::GetLocation()
{
    return mStandin->GetLocation();
}


void Laboratory::DrawLaboratory(std::shared_ptr<wxGraphicsContext> graphics)
{
    mStandin->DrawLaboratory(graphics);
}


void Laboratory::SetLaboratoryFrame(int frame)
{
    mStandin->SetLaboratoryFrame(frame);
}


void Laboratory::SetFrameRate(double rate)
{

}

void Laboratory::SetLaboratoryNumber(int number)
{
    mStandin->SetLaboratory(number);
}

int Laboratory::GetLaboratoryNumber()
{
    return mStandin->GetLaboratory();
}

double Laboratory::GetLaboratoryTime()
{
    return 0;
}

