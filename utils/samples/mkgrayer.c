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
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE 
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#include "lcms2mt.h"

#include "monolithic_examples.h"


static
int Forward(cmsContext ContextID, cmsUInt16Number In[], cmsUInt16Number Out[], void * Cargo)
{	
    cmsCIELab Lab;


    cmsLabEncoded2Float(ContextID, &Lab, In);

	if (fabs(Lab.a) < 3 && fabs(Lab.b) < 3) {
		
		double L_01 = Lab.L / 100.0;
		cmsUInt16Number K;

		if (L_01 > 1) L_01 = 1;
		K = (cmsUInt16Number) floor(L_01* 65535.0 + 0.5);

		Out[0] = Out[1] = Out[2] = K; 
	}
	else {
		Out[0] = 0xFFFF; Out[1] = 0; Out[2] = 0; 
	}

	return TRUE;
}




#if defined(BUILD_MONOLITHIC)
#define main(cnt, arr)      lcms2_mkgrayer_example_main(cnt, arr)
#endif

int main(int argc, const char *argv[])
{
	LUT *BToA0;
	cmsHPROFILE hProfile;
	cmsContext ContextID = cmsCreateContext(NULL, NULL);

	fprintf(stderr, "Creating interpol2.icc...");

	unlink("interpol2.icc");
	hProfile = cmsOpenProfileFromFile(ContextID, "interpol2.icc", "w8");


    BToA0 = cmsAllocLUT(ContextID);

	cmsAlloc3DGrid(ContextID, BToA0, 17, 3, 3);
	    
	cmsSample3DGrid(ContextID, BToA0, Forward, NULL, 0);
			
    cmsAddTag(ContextID, hProfile, cmsSigBToA0Tag, BToA0);
	                                
	cmsSetColorSpace(ContextID, hProfile, cmsSigRgbData);
    cmsSetPCS(ContextID, hProfile, cmsSigLabData);
    cmsSetDeviceClass(ContextID, hProfile, cmsSigOutputClass);

	cmsAddTag(ContextID, hProfile, cmsSigProfileDescriptionTag, "Interpolation test");
    cmsAddTag(ContextID, hProfile, cmsSigCopyrightTag,          "Copyright (c) HP 2007. All rights reserved.");
    cmsAddTag(ContextID, hProfile, cmsSigDeviceMfgDescTag,      "Little cms");    
    cmsAddTag(ContextID, hProfile, cmsSigDeviceModelDescTag,    "Interpolation test profile");

	
	cmsCloseProfile(ContextID, hProfile);
    
	cmsFreeLUT(ContextID, BToA0);
	
	fprintf(stderr, "Done.\n");

	return 0;
}
