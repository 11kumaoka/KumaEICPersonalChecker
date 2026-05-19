#include <TCanvas.h>
#include <TMarker.h>
#include <TColor.h>
#include <TROOT.h>
#include <iostream>

void testColor()
{
   auto* c = new TCanvas("c","c",800,400);

   Color_t myGreen = TColor::GetFreeColorIndex();
   new TColor(myGreen, 0.0, 204./255.0, 150./255.0);

   std::cout << "myGreen id = " << myGreen
             << ", ptr = " << gROOT->GetColor(myGreen) << std::endl;

   auto* m1 = new TMarker(1.0, 1.0, kFullCircle);
   m1->SetMarkerSize(3.0);
   m1->SetMarkerColor(myGreen);
   m1->Draw();

   auto* m2 = new TMarker(2.0, 1.0, kFullCircle);
   m2->SetMarkerSize(3.0);
   m2->SetMarkerColor(myGreen);
   m2->Draw("same");

   c->SaveAs("color_sanity.pdf");
}