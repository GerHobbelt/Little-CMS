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


// This is a sample on how to build a profile for decoding ITU T.42/Fax JPEG
// streams. The profile has an additional ability in the input direction of
// gamut compress values between 85 < a < -85 and -75 < b < 125. This conforms
// the default range for ITU/T.42 -- See RFC 2301, section 6.2.3 for details


//  L* = [0, 100]
//  a* = [-85, 85]
//  b* = [-75, 125]


// These functions does convert the encoding of ITUFAX to floating point

static
void ITU2Lab(cmsUInt16Number In[3], cmsCIELab *Lab)
{
   Lab -> L = (double) In[0] / 655.35;
   Lab -> a = (double) 170.* (In[1] - 32768.) / 65535.;
   Lab -> b = (double) 200.* (In[2] - 24576.) / 65535.;
}


static
void Lab2ITU(cmsCIELab *Lab, cmsUInt16Number Out[3])
{
	Out[0] = (cmsUInt16Number) floor((double) (Lab -> L / 100.)* 65535. + 0.5);
    Out[1] = (cmsUInt16Number) floor((double) (Lab -> a / 170.)* 65535. + 32768. + 0.5);
    Out[2] = (cmsUInt16Number) floor((double) (Lab -> b / 200.)* 65535. + 24576. + 0.5);
}


// These are the samplers-- They are passed as callbacks to cmsSample3DGrid()
// then, cmsSample3DGrid() will sweel whole Lab gamut calling these functions
// once for each node. In[] will contain the Lab PCS value to convert to ITUFAX
// on InputDirection, or the ITUFAX value to convert to Lab in OutputDirection
// You can change the number of sample points if desired, the algorithm will
// remain same. 33 points gives good accuracy, but you can reduce to 22 or less
// is space is critical

#define GRID_POINTS 33

static
int InputDirection(cmsContext ContextID, cmsUInt16Number In[], cmsUInt16Number Out[], void * Cargo)
{	   
    cmsCIELab Lab;

    cmsLabEncoded2Float(ContextID, &Lab, In);    
    cmsClampLab(ContextID, &Lab, 85, -85, 125, -75);    // This function does the necessary gamut remapping  
    Lab2ITU(&Lab, Out);

	return TRUE;
}


static
int OutputDirection(cmsContext ContextID, cmsUInt16Number In[], cmsUInt16Number Out[], void * Cargo)
{	

	cmsCIELab Lab;

    ITU2Lab(In, &Lab);
    cmsFloat2LabEncoded(ContextID, Out, &Lab);    

	return TRUE;
}


#if defined(BUILD_MONOLITHIC)
#define main(cnt, arr)      lcms2_itufax_example_main(cnt, arr)
#endif

// The main entry point. Just create a profile an populate it with required tags.
// note that cmsOpenProfileFromFile("itufax.icm", "w") will NOT delete the file
// if already exists. This is for obvious safety reasons.
int main(int argc, const char *argv[])
{
	LUT *AToB0;
	LUT *BToA0;
	cmsHPROFILE hProfile;
	cmsContext ContextID = cmsCreateContext(NULL, NULL);

	fprintf(stderr, "Creating itufax.icm...");

	unlink("itufax.icm");
	hProfile = cmsOpenProfileFromFile(ContextID, "itufax.icm", "w");
	
    AToB0 = cmsAllocLUT(ContextID);
	BToA0 = cmsAllocLUT(ContextID); 

	cmsAlloc3DGrid(ContextID, AToB0, GRID_POINTS, 3, 3);
	cmsAlloc3DGrid(ContextID, BToA0, GRID_POINTS, 3, 3);
    
	cmsSample3DGrid(ContextID, AToB0, InputDirection, NULL, 0);
	cmsSample3DGrid(ContextID, BToA0, OutputDirection, NULL, 0);
		
    cmsAddTag(ContextID, hProfile, cmsSigAToB0Tag, AToB0);
	cmsAddTag(ContextID, hProfile, cmsSigBToA0Tag, BToA0);

                                
	cmsSetColorSpace(ContextID, hProfile, cmsSigLabData);
    cmsSetPCS(ContextID, hProfile, cmsSigLabData);
    cmsSetDeviceClass(ContextID, hProfile, cmsSigColorSpaceClass);

	cmsAddTag(ContextID, hProfile, cmsSigProfileDescriptionTag, "ITU T.42/Fax JPEG CIEL*a*b*");
    cmsAddTag(ContextID, hProfile, cmsSigCopyrightTag,          "No Copyright, use freely.");
    cmsAddTag(ContextID, hProfile, cmsSigDeviceMfgDescTag,      "Little cms");    
    cmsAddTag(ContextID, hProfile, cmsSigDeviceModelDescTag,    "ITU T.42/Fax JPEG CIEL*a*b*");
	
	cmsCloseProfile(ContextID, hProfile);
    
	cmsFreeLUT(ContextID, AToB0);
	cmsFreeLUT(ContextID, BToA0);

	fprintf(stderr, "Done.\n");

	return 0;
}
