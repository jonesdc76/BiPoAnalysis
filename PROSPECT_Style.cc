/// \file PROSPECT_Style.cc

//Adapted from Daya Bay style file (NSB 5 Sept. 2014), which came with the following atributions:
//
// KAJ 08-DEC-2006
// Based on a style from ATLAS,
// which was based on a style file from BaBar
// and then lightly seasoned with input from Liu Jianglai
//

#include "PROSPECT_Style.hh"
#include <TColor.h>
#include <cassert>
#include <TGaxis.h>
#include <TH1.h>

void setup_PROSPECT_style(TStyle* prospectStyle) {

    if(!prospectStyle) prospectStyle = gStyle;
    assert(prospectStyle);
    TH1::SetDefaultSumw2();

    // use plain black on white colors
    Int_t icol = 0;
    prospectStyle->SetFrameBorderMode(icol);
    prospectStyle->SetCanvasBorderMode(icol);
    prospectStyle->SetPadBorderMode(icol);
    prospectStyle->SetPadColor(icol);
    prospectStyle->SetCanvasColor(icol);
    prospectStyle->SetStatColor(icol);
    //prospectStyle->SetFillColor(icol);

    // hack: assure colors get initialized!
    gROOT->GetColor(10);

    // Color palette - added by NSB 9/14, adapted from that used by NIFFTE collaboration
    // Based on http://ultrahigh.org/2007/08/20/making-pretty-root-color-palettes/
    const Int_t NRGBs = 5;
    const Int_t NCont = 99;
    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    prospectStyle->SetNumberContours(NCont);

    prospectStyle->SetPalette(kViridis); // set a good color palette

    //prospectStyle->SetFillColor(0); // explicitly don't fill
    //Int_t colors[]={4,4,7,7,6,6,6,2,2,2,1};
    //   float levels[]={1,10,14,22,45,60,200,300,400,500,600,700};

    // set the paper & margin sizes
    prospectStyle->SetPaperSize(TStyle::kUSLetter);

    // original margin settings:
    // prospectStyle->SetPadTopMargin(.10);
    // prospectStyle->SetPadLeftMargin(.151);
    // prospectStyle->SetPadRightMargin(.071);
    // prospectStyle->SetPadBottomMargin(.111);

    // Margins, assuming no top label or z scale
    prospectStyle->SetPadTopMargin(.06); // just enough to clear exponent on y axis
    prospectStyle->SetPadLeftMargin(.151);
    prospectStyle->SetPadRightMargin(.04);
    prospectStyle->SetPadBottomMargin(.12);

    // set master font
    //Int_t font=132;      //times new roman, regular (13), high precision (2)
    Int_t font=42;     //tnr, bold (4), high precision (2)

    //set master font size
    Double_t tsize=0.05; //should be set between 0.03-0.05, is in units of "% of pad"
    //Double_t tsize=0.065; //should be set between 0.03-0.05, is in units of "% of pad"

    // Text, Labels, Titles
    // All set the same here
    prospectStyle->SetTextFont(font);
    prospectStyle->SetTextSize(tsize);

    prospectStyle->SetLabelFont(font,"xyz");
    prospectStyle->SetLabelSize(tsize,"xyz");
    prospectStyle->SetLabelOffset(0.003,"xyz");

    prospectStyle->SetTitleFont(font,"xyz");
    prospectStyle->SetTitleSize(tsize,"xyz");
    prospectStyle->SetTitleOffset(1.25,"z");
    prospectStyle->SetTitleOffset(1.2,"y");
    prospectStyle->SetTitleOffset(1.1,"x");
    prospectStyle->SetTitleBorderSize(0);

    prospectStyle->SetLegendBorderSize(0);

    //use bold lines and markers
    //prospectStyle->SetMarkerStyle(20);
    //prospectStyle->SetMarkerSize(1.2);
    prospectStyle->SetHistLineWidth(2.);
    prospectStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

    //get rid of X error bars and y error bar caps
    //prospectStyle->SetErrorX(0.001);

    //do not display any of the standard histogram decorations
    prospectStyle->SetOptTitle(0);      //no title box
    prospectStyle->SetOptStat("");      //no stat info
    //prospectStyle->SetOptFit(11);     //standard fit info
    prospectStyle->SetOptFit(0);        //no fit info

    //legend and stat pad
    prospectStyle->SetStatBorderSize(1);
    prospectStyle->SetStatFont(132);
    prospectStyle->SetStatX(0.95);
    prospectStyle->SetStatY(0.95);
    prospectStyle->SetLegendBorderSize(1);

    // put tick marks on top and RHS of plots
    //prospectStyle->SetPadTickX(1);
    //prospectStyle->SetPadTickY(1);
    // tick marks only on left and bottom
    prospectStyle->SetPadTickX(0);
    prospectStyle->SetPadTickY(0);
    // fewer axis divisions to avoid label collisions
    prospectStyle->SetNdivisions(506,"XYZ");

    // additional series styles (Thanks, Jianglai)
    //   1 = solid
    //   2 = long dash (30 10)
    //   3 = dotted (4 8)
    //   4 = dash-dot (15 12 4 12)
    //   5 = short dash ( 15 15 )
    //   6 = dash-dot-dot   gStyle->SetLineStyleString(1,"[]");
    prospectStyle->SetLineStyleString(2,"[30 10]");
    prospectStyle->SetLineStyleString(3,"[4 8]");
    prospectStyle->SetLineStyleString(4,"[15 12 4 12]");
    prospectStyle->SetLineStyleString(5,"[15 15]");
    prospectStyle->SetLineStyleString(6,"[15 12 4 12 4 12]");
    prospectStyle->SetOptDate(0);
    prospectStyle->SetDateY(.98);
    prospectStyle->SetStripDecimals(kFALSE);

    TGaxis::SetMaxDigits(3);

    //  prospectStyle->SetEndErrorSize(5.0); //make the end of error bar longer

}
