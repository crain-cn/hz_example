/* 
	===== PE structures and types definition =====
*/



#ifndef PE_H
#define PE_H

typedef struct
{
  unsigned short cpuType;
  unsigned short numSections;
  unsigned long dateStamp;
  unsigned long symbolTable;
  unsigned long numSymbols;
  unsigned short optionalHeaderSize;
  unsigned short flags;
} PEHeader;


typedef struct 
{
  unsigned short magic;
  unsigned char linkerMajor;
  unsigned char linkerMinor;
  unsigned long codeSize;
  unsigned long initDataSize;
  unsigned long uninitDataSize;
  unsigned long entryPoint;
  unsigned long codeBase;
  unsigned long dataBase;
} StdOptionalHeader;


typedef struct 
{
  unsigned short magic;
  unsigned char linkerMajor;
  unsigned char linkerMinor;
  unsigned long codeSize;
  unsigned long initDataSize;
  unsigned long uninitDataSize;
  unsigned long entryPoint;
  unsigned long codeBase;
  unsigned long dataBase;

  // extra NT stuff
  unsigned long imageBase;
  unsigned long sectionAlign;
  unsigned long fileAlign;
  unsigned short osMajor;
  unsigned short osMinor;
  unsigned short imageMajor;
  unsigned short imageMinor;
  unsigned short subsystemMajor;
  unsigned short subsystemMinor;
  unsigned long reserved;
  unsigned long imageSize;
  unsigned long headersSize;
  unsigned long checksum;
  unsigned short subsystem;
  unsigned short dllFlags;
  unsigned long stackReserveSize;
  unsigned long stackCommitSize;
  unsigned long heapReserveSize;
  unsigned long heapCommitSize;
  unsigned long loaderFlags;
  unsigned long numDataDirectories;
} NTOptionalHeader;

typedef struct 
{
  unsigned short magic;
  unsigned char linkerMajor;
  unsigned char linkerMinor;
  unsigned long codeSize;
  unsigned long initDataSize;
  unsigned long uninitDataSize;
  unsigned long entryPoint;
  unsigned long codeBase;
  unsigned long dataBase;
  unsigned long bssBase;
  unsigned long gprMask;
  unsigned long cprMask[4];
  unsigned long gpValue;
} ROMOptionalHeader;

#define NTOptionalHeaderMagic 0x10b
#define ROMOptionalHeaderMagic 0x107

typedef struct
{
  unsigned long RVA;
  unsigned long size;
} DataDirectory;

typedef struct
{
  unsigned char name[8];
  union
  {
    unsigned long virtualSize;
    unsigned long physicalAddress;
  } misc;
  unsigned long RVA;
  unsigned long dataAlignSize;
  unsigned long dataOffset;
  unsigned long relocationsOffset; //}not actually used in PE
  unsigned long lineNumbersOffset; //}
  unsigned short numRelocations;   //}
  unsigned short numLineNumbers;   //}
  unsigned long flags;
} Section;


#define ExportDataDirectory 0
#define ImportDataDirectory 1
#define ResourceDataDirectory 2
#define ExceptionDataDirectory 3
#define SecurityDataDirectory 4
#define BaseRelocDataDirectory 5
#define DebugDataDirectory 6
#define CopyrightDataDirectory 7
#define GlobalPtrdataDirectory 8
#define TlsDataDirectory 9
#define LoadConfigDataDirectory 10

static char *dataDirNames[] = {"Export",
			       "Import",
			       "Resource",
			       "Exception",
			       "Security",
			       "BaseReloc",
			       "Debug",
			       "Copyright",
			       "GlobalPtr",
			       "TlsData",
			       "LoadConfig",
			       "BoundImport",
			       "IAT"};

#endif
