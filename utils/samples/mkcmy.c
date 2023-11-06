//
//  Little cms
//  Copyright (C) 1998-2003 Marti Maria
//
// Permission is hereby granted, free of charge, to any person obtaining 
// a copy of this software and associated documentation files (the "Software"), 
// to deal in the Software without restriction, including without limitation 
// the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and/or sell copies of the Software, and to permit persons to whom the Software 
// is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in 
// all copies or substantial portions of the Software.
//
// THIS SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
// EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
// WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
//
// IN NO EVENT SHALL MARTI MARIA BE LIABLE FOR ANY SPECIAL, INCIDENTAL,
// INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
// OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
// WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
// LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
// OF THIS SOFTWARE.
//
// Version 1.12


#include "lcms2mt.h"

#include "monolithic_examples.h"



typedef struct {
				cmsHPROFILE   hLab;
				cmsHPROFILE   hRGB;
				cmsHTRANSFORM Lab2RGB;
				cmsHTRANSFORM RGB2Lab;

				} CARGO, * LPCARGO;


	 
 

// Our space will be CIE primaries plus a gamma of 4.5

static
int Forward(cmsContext ContextID, cmsUInt16Number In[], cmsUInt16Number Out[], void *Cargo)
{	
	LPCARGO C = (LPCARGO) Cargo;	
	cmsUInt16Number RGB[3];
    cmsCIELab Lab;

    cmsLabEncoded2Float(ContextID, &Lab, In);

	printf("%g %g %g\n", Lab.L, Lab.a, Lab.b);

	cmsDoTransform(ContextID, C ->Lab2RGB, In, &RGB, 1);


	Out[0] = 0xFFFF - RGB[0]; // Our CMY is negative of RGB
	Out[1] = 0xFFFF - RGB[1]; 
	Out[2] = 0xFFFF - RGB[2]; 
	
	
	return TRUE;

}


static
int Reverse(cmsContext ContextID, cmsUInt16Number In[], cmsUInt16Number Out[], void *Cargo)
{	

	LPCARGO C = (LPCARGO) Cargo;	
	cmsUInt16Number RGB[3];
  
	RGB[0] = 0xFFFF - In[0];
	RGB[1] = 0xFFFF - In[1];
	RGB[2] = 0xFFFF - In[2];

	cmsDoTransform(ContextID, C ->RGB2Lab, &RGB, Out, 1);
	
	return TRUE;

}



static
void InitCargo(cmsContext ContextID, LPCARGO Cargo)
{
	Cargo -> hLab = cmsCreateLab4Profile(ContextID, NULL);
	Cargo -> hRGB = cmsCreate_sRGBProfile(ContextID);  
	
	Cargo->Lab2RGB = cmsCreateTransform(ContextID, Cargo->hLab, TYPE_Lab_16, 
									    Cargo ->hRGB, TYPE_RGB_16,
										INTENT_RELATIVE_COLORIMETRIC, 
										0);

	Cargo->RGB2Lab = cmsCreateTransform(ContextID, Cargo ->hRGB, TYPE_RGB_16, 
										Cargo ->hLab, TYPE_Lab_16, 
										INTENT_RELATIVE_COLORIMETRIC, 
										0);
}




static
void FreeCargo(cmsContext ContextID, LPCARGO Cargo)
{
	cmsDeleteTransform(ContextID, Cargo ->Lab2RGB);
	cmsDeleteTransform(ContextID, Cargo ->RGB2Lab);
	cmsCloseProfile(ContextID, Cargo ->hLab);
	cmsCloseProfile(ContextID, Cargo ->hRGB);
}



#if defined(BUILD_MONOLITHIC)
#define main      lcms2_mkcmy_example_main
#endif

int main(void)
{
	LUT *AToB0;
	LUT *BToA0;	
	CARGO Cargo;
	cmsHPROFILE hProfile;
	cmsContext ContextID = cmsCreateContext(NULL, NULL);

	fprintf(stderr, "Creating lcmscmy.icm...");	
	
	InitCargo(ContextID, &Cargo);

	hProfile = cmsCreateLab4Profile(ContextID, NULL);
	

    AToB0 = cmsAllocLUT(ContextID);
	BToA0 = cmsAllocLUT(ContextID);

	cmsAlloc3DGrid(ContextID, AToB0, 25, 3, 3);
	cmsAlloc3DGrid(ContextID, BToA0, 25, 3, 3);
	
	
	cmsSample3DGrid(ContextID, AToB0, Reverse, &Cargo, 0);
	cmsSample3DGrid(ContextID, BToA0, Forward, &Cargo, 0);
	
	
    cmsAddTag(ContextID, hProfile, cmsSigAToB0Tag, AToB0);
	cmsAddTag(ContextID, hProfile, cmsSigBToA0Tag, BToA0);

	cmsSetColorSpace(ContextID, hProfile, cmsSigCmyData);
	cmsSetDeviceClass(ContextID, hProfile, cmsSigOutputClass);

	cmsAddTag(ContextID, hProfile, cmsSigProfileDescriptionTag, "CMY ");
    cmsAddTag(ContextID, hProfile, cmsSigCopyrightTag,          "Copyright (c) HP, 2007. All rights reserved.");
    cmsAddTag(ContextID, hProfile, cmsSigDeviceMfgDescTag,      "Little cms");    
    cmsAddTag(ContextID, hProfile, cmsSigDeviceModelDescTag,    "CMY space");

	cmsSaveProfileToFile(ContextID, hProfile, "lcmscmy.icm");
	
	
	cmsFreeLUT(ContextID, AToB0);
	cmsFreeLUT(ContextID, BToA0);
	cmsCloseProfile(ContextID, hProfile);	
	FreeCargo(ContextID, &Cargo);

	fprintf(stderr, "Done.\n");



	return 0;
}
