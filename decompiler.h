#ifndef INC_S2DC_DECOMPILER_H
#define INC_S2DC_DECOMPILER_H

/* General Decompiler Notes:

   *Values are in little endian order and are integer values, unless stated otherwise.
   *Size and offset values are measured in bytes, unless stated otherwise.
   *All offsets are from the current stream position, not from the start of the file.
   *Blocks are padded to the next 16 bytes, including additional compiled data. This is not included in the block size.
   --------------------------------------------------------------------------------------------------------------------------------
   Header(16 bytes)
   4 bytes:  Size of file
   4 bytes : Unknown(constant 0x0000000c)
   4 bytes : Offset to block information
   4 bytes : Number of blocks

   Block information(12 bytes)
   4 bytes : Block name(i.e.RERL, REDI, NTRO, DATA)
   4 bytes : Offset to block start
   4 bytes : Size of block
*/

#include <stdint.h>
#include <string>
#include <fstream>
#include <vector>
#include "rerl.h"
#include "ntro.h"

class S2Decompiler
{
	public:
		S2Decompiler();
		S2Decompiler(const std::vector<std::string>& szFileList);

		void StartDecompile(const std::string& szBaseDirectory, const std::string& szOutputDirectory);
	private:
		void ProcessDirectory(const std::string& szDirectory);
		void Decompile(const std::string& szPathname);

		void DecompileVMAT(const std::string& szFilename, const std::string& szOutputDirectory);
		void DecompileVPCF(const std::string& szFilename, const std::string& szOutputDirectory);
		void DecompileVTEX(const std::string& szFilename, const std::string& szOutputDirectory, bool bGenerateVTEX = true, bool bGenerateMipmaps = true);

		uint32_t _uSuccessCount, _uFailedCount;
		std::string _szBaseDirectory;
		std::string _szOutputDirectory;
		std::vector<std::string> _szFileList;
};

#endif