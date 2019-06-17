#ifndef _XM8calls_
#define _XM8calls_
// ============================================================================	//
//				X M 8 c a l l s . h				//
// ----------------------------------------------------------------------------	//
// ============================================================================	//


#ifdef XM8DLL_API			    // This is "not using the DLL"
#else
 #ifdef XM8DLL_EXPORTS
  #define XM8DLL_API __declspec(dllexport)  // This is "building the DLL"
 #else
  #define XM8DLL_API __declspec(dllimport)  // This is "using the DLL"
 #endif
#endif
// ============================================================================	//
// Function prototypes								//
// ============================================================================	//
extern "C" XM8DLL_API char* _stdcall XM8_getVersion	(void);
extern "C" XM8DLL_API char* _stdcall XM8_getDate	(void);

// ====================================================================	//
// Load a 'disguised' version of the specified .xml file into a		//
// dynamically allocated array.						//
// 'disguised' means comment & quoted value chars have the top bit set.	//
// ====================================================================	//
extern "C" XM8DLL_API bool  _stdcall XM8_readFile	(char*fileName,char*aRname);

// ====================================================================	//
// Get first Gname group bounds within bounds of lesser depth.		//
// Can handle groups-within-groups-within-groups... to a depth of 30.	//
// ====================================================================	//
extern "C" XM8DLL_API bool  _stdcall XM8_getFrstGroup	(char*aGname, long depth);

// ====================================================================	//
// Get next/last Gname group bounds within bounds of lesser depth.	//
// ====================================================================	//
extern "C" XM8DLL_API bool  _stdcall XM8_getNextGroup	(char*aGname, long depth);
extern "C" XM8DLL_API bool  _stdcall XM8_getLastGroup	(char*aGname, long depth);

// ====================================================================	//
// Within bounds of the current group find specified attribute value	//
// ====================================================================	//
extern "C" XM8DLL_API bool  _stdcall XM8_getAttribute	(char*aAname,char*aAvalu);

// ====================================================================	//
// Free the dynamic memory & zeroise the depth array.			//
// XM8_readFile or XM8_newFile now necessary.				//
// ====================================================================	//
extern "C" XM8DLL_API bool  _stdcall XM8_reset		(void);

// ====================================================================	//
// Return the last recorded error text					//
// ====================================================================	//
extern "C" XM8DLL_API char* _stdcall XM8_getLastError	(void);

// ====================================================================	//
// Create an empty .xml file in a dynamically allocated array		//
// The empty file name is Empty.xml in the running directory		//
// ====================================================================	//
extern "C" XM8DLL_API bool  _stdcall XM8_newFile	(char*aRname);

// ====================================================================	//
// Within the bounds of the current group & lastly,			//
// create the specified group.						//
// ====================================================================	//
extern "C" XM8DLL_API bool  _stdcall XM8_newGroup	(char*aGname);

// ====================================================================	//
// Within the bounds of the current group modify specified group value	//
// ====================================================================	//
extern "C" XM8DLL_API bool  _stdcall XM8_putGroup	 (char*aGname,char*aGvalu);
extern "C" XM8DLL_API bool  _stdcall XM8_newGrpPutVal	 (char*aGname,char*aGvalu);
extern "C" XM8DLL_API bool  _stdcall XM8_pokeNewGrpPutVal(char*aGname,char*aGvalu);

// ====================================================================	//
// Within the bounds of the current group				//
// create the specified attribute, if it does not exist.		//
// ====================================================================	//
extern "C" XM8DLL_API bool  _stdcall XM8_newAttribute	(char*aAname);

// ====================================================================	//
// Within the bounds of the current group				//
// modify the specified attribute value.				//
// ====================================================================	//
extern "C" XM8DLL_API bool  _stdcall XM8_putAttribute	(char*aAname,char*aAvalu);
extern "C" XM8DLL_API bool  _stdcall XM8_newAttPutVal	(char*aAname,char*aAValu);

// ====================================================================	//
// Write the buffer to the specified .xml file.				//
// ====================================================================	//
extern "C" XM8DLL_API bool  _stdcall XM8_writeFile	(char*fileName);

// ====================================================================	//
// Write a comment, properly indented, ahead of the current group	//
// ====================================================================	//
extern "C" XM8DLL_API bool _stdcall XM8_newComment	(char*aCtext);


// ====================================================================	//
// Delete the current group (& all its deeper groups)			//
// ====================================================================	//
extern "C" XM8DLL_API bool  _stdcall XM8_delGroup	(char*aGname);

// ====================================================================	//
// Delete the current attribute (& its value)				//
// ====================================================================	//
extern "C" XM8DLL_API bool  _stdcall XM8_delAttribute	(char*aAname);

// ====================================================================	//
// Delete the comments above of current group				//
// ====================================================================	//
extern "C" XM8DLL_API bool  _stdcall XM8_delComment	(char*aGname);


extern "C" XM8DLL_API bool  _stdcall XM8_newStream	(char*stream, long streamLen);
extern "C" XM8DLL_API char* _stdcall XM8_getStream	(void);


extern "C" XM8DLL_API bool _stdcall XM8_UCStoUTF	(long*lBf,char*aBf);
extern "C" XM8DLL_API bool _stdcall XM8_UTFtoUCS	(char*aBf,long*lBf);
extern "C" XM8DLL_API bool _stdcall XM8_UTF8toUTF16	(char*aBf,unsigned short*sBf);
extern "C" XM8DLL_API bool _stdcall XM8_UTF16toUTF8	(unsigned short*sBf,char*aBf);
extern "C" XM8DLL_API long _stdcall XM8_deProfundis	(void);
extern "C" XM8DLL_API void _stdcall XM8_fullCODE	(void);




extern "C" XM8DLL_API void  _stdcall XMLteaCryptKey	(char*);
extern "C" XM8DLL_API char* _stdcall XMLteaEncrypt	(char*);
extern "C" XM8DLL_API char* _stdcall XMLteaEncryptVal	(char*);
extern "C" XM8DLL_API char* _stdcall XMLteaDecrypt	(char*);


#endif//_XM8calls_
