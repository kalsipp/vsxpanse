#if !defined(AFX_ZIPARCHIVE_H__20010602_3EE9_91B0_80F5_0080AD509054__INCLUDED_)
#define AFX_ZIPARCHIVE_H__20010602_3EE9_91B0_80F5_0080AD509054__INCLUDED_

#pragma once


/*
For reference:

BOOL Open(LPCTSTR pstrFileName)
Opens a ZIP archive.

BOOL Close()
Close	Closes the archive.

BOOL GetFile(LPCTSTR pstrName, CZipFile* pFile) const
GetFile	Extracts a file entry.

BOOL SetPassword(LPCSTR pstrPassword)
SetPassword	Set password to use on encrypted files.

HANDLE FindFirstFile(LPCTSTR pstrFileName, LPZIP_FIND_DATA lpFindFileData) const
FindFirstFile	Enumerates files in ZIP.

BOOL FindNextFile(HANDLE hFindFile, LPZIP_FIND_DATA lpFindFileData) const
FinNextFile	Gets the next file in FindFirstFile enumeration.

BOOL FindClose(HANDLE hFindFile) const
FindClose	Closes the find enumeration.
*/

/////////////////////////////////////////////////////////////////////////////
// UnzipArchive - Wrapper classes for ZIP file access
//
// Written by Bjarke Viksoe (bjarke@viksoe.dk)
// ZLIB by Jean-loup Gailly and Mark Adler.
//
// Only reading from ZIP files is supported.
// Supports decrypting files as well.
//
// This code may be used in compiled form in any way you desire. This
// source file may be redistributed by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to you or your
// computer whatsoever. It's free, so don't hassle me about it.
//
// Beware of bugs.
//
#include <tchar.h>

#ifndef __cplusplus
  #error UnzipArchive requires C++ compilation (use a .cpp suffix)
#endif
#ifdef _WIN32_IE
#undef _WIN32_IE 
#endif
#define _WIN32_IE 0x0400
#if (_WIN32_IE < 0x0400)
  // See note below
  #error UnzipArchive.h requires _WIN32_IE >= 0x0400
#endif

// We use this IE4 dependant library for the PathMatchSpec() method
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

// Include ZLIB stuff. ZLIB is maintained by Jean-loup Gailly and Mark Adler.
// It is a general GZIP and PKZIP compatible compression library.
// Define ZLIB_DLL to link with the DLL version of ZLIB.
#include <zlib.h>
#if !defined(CUSTOM_ZLIB_STATIC_LINK)
   #ifdef ZLIB_DLL
      #pragma comment(lib, "zlibdll.lib")
   #else
      #pragma comment(lib, "zlibstat.lib")
   #endif
#else
   // Define CUSTOM_ZLIB_STATIC_LINK when:
   // I have special multi-thread compiled versions of the static libs
   // on my environment, otherwise you need to link with the "Single-Threaded"
   // C/C++ Runtime libraries options in MSVC because this is what
   // the default zlibstat.lib uses.
   #if !defined(_MT)
      #pragma comment(lib, "zlibstat.lib")
   #else
      #if defined(DEBUG)
         #pragma comment(lib, "zlibstat_mtd.lib")
      #else
         #pragma comment(lib, "zlibstat_mtr.lib")
      #endif
   #endif
#endif

#ifndef ATLTRY
   #define ATLTRY(x) x
#endif


///////////////////////////////////////////////////////////////
// Structures and defines

typedef struct
{
   TCHAR    szFileName[MAX_PATH];
   TCHAR    szComment[64];
   DWORD    nFileSizeCompressed;
   DWORD    nFileSizeUncompressed;
   FILETIME ftCreationDate;
   DWORD    dwFlags;
   int      nDirIndex;
} ZIP_FIND_DATA, *LPZIP_FIND_DATA;

class CZipArchive;


///////////////////////////////////////////////////////////////
// Classic ZIP file

class CZipFile
{
friend CZipArchive;
protected:
   // Stream data members
   LPBYTE m_pData;
   DWORD  m_dwPos;
   DWORD  m_dwSize;
   // Decryption
   const DWORD* m_pCrcTable;
   DWORD  m_dwKey[3];

public:
   CZipFile() : m_pData(NULL), m_dwSize(0UL), m_dwPos(0UL), m_pCrcTable(NULL)
   {
   }

   ~CZipFile()
   {
      Close();
   }

   BOOL Read(LPVOID pVoid, DWORD dwSize, LPDWORD pdwRead=NULL)
   {
      _ASSERTE(m_pData);
      if( pdwRead != NULL ) *pdwRead = 0;
      if( m_pData == NULL ) return FALSE;
      if( dwSize == 0 || m_dwPos >= m_dwSize ) return FALSE;
      if( m_dwPos+dwSize > m_dwSize ) dwSize = m_dwSize - m_dwPos; // Thanks to Shaun Wilde for fixing this!
      ::CopyMemory(pVoid, m_pData + m_dwPos, dwSize);
      m_dwPos += dwSize;
      if( pdwRead != NULL ) *pdwRead = dwSize;
      return TRUE;
   }

   BOOL Close()
   {
      if( m_pData == NULL ) return TRUE;
      ATLTRY( delete [] m_pData );
      m_pData = NULL;
      m_dwSize = 0;
      m_dwPos = 0;
      return TRUE;
   }

   BOOL IsOpen() const
   {
      return m_pData != NULL;
   }

   DWORD GetSize() const
   {
      _ASSERTE(IsOpen());
      return m_dwSize;
   }

   DWORD GetPosition() const
   {
      _ASSERTE(IsOpen());
      return m_dwPos;
   }

   DWORD Seek(DWORD dwOffset, UINT nFrom)
   {
      _ASSERTE(IsOpen());
      DWORD dwPos = m_dwPos;
      switch( nFrom ) {
      case FILE_BEGIN:
         m_dwPos = dwOffset;
         break;
      case FILE_END:
         m_dwPos = m_dwSize + dwOffset;
         break;
      case FILE_CURRENT:
         m_dwPos += dwOffset;
         break;
      }
      if( m_dwPos < 0 ) m_dwPos = 0;
      if( m_dwPos >= m_dwSize ) m_dwPos = m_dwSize;
      return dwPos;
   }

protected:
   void _Initialize(LPBYTE pData, DWORD dwSize)
   {
      _ASSERTE(pData);
      _ASSERTE(!::IsBadReadPtr(pData,dwSize));
      Close();
      m_pData = pData;
      m_dwSize = dwSize;
   }

   BOOL _DecryptFile(LPCSTR pstrPassword, LPBYTE& pData, DWORD& dwSize, DWORD crc32)
   {
      _ASSERTE(pData);
      _ASSERTE(!::IsBadStringPtrA(pstrPassword,-1));

      if( !_InitKeys(pstrPassword) ) return FALSE;
      if( !_DecryptHeader(pData, dwSize, crc32) ) return FALSE;
      if( !_DecryptData(pData, dwSize) ) return FALSE;
      return TRUE;
   }

   inline DWORD _crc32(DWORD c, BYTE b)
   {
      _ASSERTE(m_pCrcTable);
      return m_pCrcTable[ ((DWORD) (c) ^ (b)) & 0xFF ] ^ ((c) >> 8);
   }

   BOOL _InitKeys(LPCSTR pstrPassword)
   {
      m_pCrcTable = get_crc_table();
      m_dwKey[0] = 305419896;
      m_dwKey[1] = 591751049;
      m_dwKey[2] = 878082192;
      int nLen = ::lstrlenA(pstrPassword);
      if( nLen == 0 ) return FALSE;
      for( int i = 0; i < nLen; i++ ) _UpdateKeys(pstrPassword[i]);
      return TRUE;
   }

   void _UpdateKeys(BYTE c)
   {      
      m_dwKey[0] = _crc32(m_dwKey[0], c);
      m_dwKey[1] = m_dwKey[1] + (m_dwKey[0] & 0x000000FF);
      m_dwKey[1] = m_dwKey[1] * 134775813 + 1;
      BYTE b = (BYTE) (m_dwKey[1] >> 24);
      m_dwKey[2] = _crc32(m_dwKey[2], b);
   }

   BOOL _DecryptHeader(LPBYTE pData, DWORD dwSize, DWORD crc32)
   {
      if( dwSize < 12 ) return FALSE;
      BYTE header[12];
      ::CopyMemory(&header, pData, 12);
      for( int i = 0; i < 12; i++ ) {
         BYTE c = (BYTE)( header[i] ^ _DecryptByte() );
         _UpdateKeys(c);
         header[i] = c;
      }
      // Password check
      if( header[11] != (BYTE)(crc32 >> 24) ) return FALSE;
      return TRUE;
   }

   inline BYTE _DecryptByte() const
   {
      DWORD temp = (WORD) (m_dwKey[2] | 2);
      return (BYTE)((temp * (temp ^ 1)) >> 8);
   }

   BOOL _DecryptData(LPBYTE& pData, DWORD& dwSize)
   {
      LPBYTE pRawData = NULL;
      ATLTRY( pRawData = new BYTE[ dwSize - 12 ] );
      _ASSERTE(pRawData);
      if( pRawData == NULL ) return FALSE;
      LPBYTE p = pRawData;
      for( DWORD i = 12; i < dwSize; i++ ) {
         BYTE c = (BYTE) (pData[i] ^ _DecryptByte());
         _UpdateKeys(c);
         *p++ = c;
      }
      ATLTRY( delete [] pData );
      pData = pRawData;
      dwSize -= 12;
      return TRUE;
   }
};



///////////////////////////////////////////////////////////////
// ZIP Archive class

class CZipArchive
{
protected:

#pragma pack(2)

   enum
   {
     DIR_SIGNATURE = 0x06054b50,
   };

   struct ZipDirHeader
   {
     DWORD   sig;
     WORD    nDisk;
     WORD    nStartDisk;
     WORD    nDirEntries;
     WORD    totalDirEntries;
     DWORD   dirSize;
     DWORD   dirOffset;
     WORD    cmntLen;
   };

   enum
   {
      FILE_SIGNATURE = 0x02014b50,
      FILE_COMP_STORE   = 0,
      FILE_COMP_DEFLAT  = 8,
   };

   struct ZipDirFileHeader
   {
      DWORD   sig;
      WORD    verMade;
      WORD    verNeeded;
      WORD    flag;
      WORD    compression;      // COMP_xxxx
      WORD    modTime;
      WORD    modDate;
      DWORD   crc32;
      DWORD   cSize;            // Compressed size
      DWORD   ucSize;           // Uncompressed size
      WORD    fnameLen;         // Filename string follows header.
      WORD    xtraLen;          // Extra field follows filename.
      WORD    cmntLen;          // Comment field follows extra field.
      WORD    diskStart;
      WORD    intAttr;
      DWORD   extAttr;
      DWORD   hdrOffset;

      LPSTR GetName() const { return (LPSTR)(this + 1); }
      LPSTR GetExtra() const { return GetName() + fnameLen; }
      LPSTR GetComment() const { return GetExtra() + xtraLen; }
   };

   enum
   {
      LOCAL_SIGNATURE = 0x04034b50,
      LOCAL_COMP_STORE  = 0,
      LOCAL_COMP_DEFLAT = 8,
   };

   struct ZipLocalHeader
   {
      DWORD   sig;
      WORD    version;
      WORD    flag;
      WORD    compression;      // COMP_xxxx
      WORD    modTime;
      WORD    modDate;
      DWORD   crc32;
      DWORD   cSize;
      DWORD   ucSize;
      WORD    fnameLen;         // Filename string follows header.
      WORD    xtraLen;          // Extra field follows filename.
   };

#pragma pack()

   struct FindFileHandle
   {
      TCHAR szSearch[MAX_PATH];
      int nPos;
   };

   HANDLE             m_hFile;
   ZipDirHeader       m_Header;
   ZipDirFileHeader** m_Files;
   LPBYTE             m_DirData;
   CHAR               m_szPassword[64];

public:

   CZipArchive() : m_hFile(INVALID_HANDLE_VALUE), m_Files(NULL), m_DirData(NULL)
   {
   }

   ~CZipArchive()
   {
      Close();
   }

   BOOL Open(LPCTSTR pstrFileName)
   {
      _ASSERTE(!::IsBadStringPtr(pstrFileName,MAX_PATH));
      Close();
      m_hFile = ::CreateFile(pstrFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      if( m_hFile == INVALID_HANDLE_VALUE ) return FALSE;

      ::SetFilePointer(m_hFile, -(LONG)sizeof(m_Header), NULL, FILE_END);
      DWORD dwRead;
      ::ReadFile(m_hFile, &m_Header, sizeof(m_Header), &dwRead, NULL);
      _ASSERTE(dwRead==sizeof(m_Header));
      if( dwRead != sizeof(m_Header) ) { Close(); return FALSE; };
      if( m_Header.sig != DIR_SIGNATURE ) { Close(); return FALSE; }

      _ASSERTE(m_Header.nDirEntries<1000); // Sanity check
      ATLTRY( m_DirData = (LPBYTE) malloc(m_Header.dirSize) );
      _ASSERTE(m_DirData);
      ATLTRY( m_Files = new ZipDirFileHeader*[m_Header.nDirEntries] );
      _ASSERTE(m_Files);
      if( m_Files == NULL ) { Close(); return FALSE; };
      if( m_DirData == NULL ) { Close(); return FALSE; }
      
      ::SetFilePointer(m_hFile, -(LONG)(sizeof(m_Header) + m_Header.dirSize), NULL, FILE_END);
      ::ReadFile(m_hFile, m_DirData, m_Header.dirSize, &dwRead, NULL);
      _ASSERTE(dwRead==m_Header.dirSize);
      if( dwRead != m_Header.dirSize ) { Close(); return FALSE; }

      LPBYTE pData = m_DirData;
      for( int i = 0; i < m_Header.nDirEntries; i++ ) {
         // Set the header pointer in the m_Files array
         ZipDirFileHeader* fh = (ZipDirFileHeader*) pData;
         m_Files[i] = fh;
         if( fh->sig != FILE_SIGNATURE ) { Close(); return FALSE; }
         // Convert UNIX slash to Windows backslash in ANSI string
         LPSTR pstrName = fh->GetName();
         for( int i = 0; i < fh->fnameLen; i++, pstrName++ ) if( *pstrName == '/' ) *pstrName = '\\';
         // Get next header
         pData += sizeof(ZipDirFileHeader) + fh->fnameLen + fh->xtraLen + fh->cmntLen;
      }

      m_szPassword[0] = '\0';
      return TRUE;
   }

   void Close()
   {
      if( m_hFile != INVALID_HANDLE_VALUE ) {
         ::CloseHandle(m_hFile);
         m_hFile = INVALID_HANDLE_VALUE;
      }
      if( m_Files != NULL ) {
         ATLTRY( delete [] m_Files );
         m_Files = NULL;
      }
      if( m_DirData != NULL ) {
         free(m_DirData);
         m_DirData = NULL;
      }
   }

   BOOL IsOpen() const
   {
      return m_hFile != INVALID_HANDLE_VALUE;
   }

   BOOL SetPassword(LPCSTR pstrPassword)
   {
      _ASSERTE(IsOpen());
      _ASSERTE(!::IsBadStringPtrA(pstrPassword,-1));
      _ASSERTE(::lstrlenA(pstrPassword)<sizeof(m_szPassword)-1);
      if( ::lstrlenA(pstrPassword) >= sizeof(m_szPassword) - 1 ) return FALSE;
      ::lstrcpyA(m_szPassword, pstrPassword);
      return TRUE;
   }

   // ZIP File API

   BOOL GetFile(LPCTSTR pstrName, CZipFile* pFile) const
   {
      _ASSERTE(IsOpen());
      _ASSERTE(!::IsBadStringPtr(pstrName,MAX_PATH));
      ZIP_FIND_DATA fd;
      HANDLE hFindFile = FindFirstFile(pstrName, &fd);
      if( hFindFile == INVALID_HANDLE_VALUE ) return FALSE;
      BOOL bRes = GetFile(fd.nDirIndex, pFile);
      FindClose(hFindFile);
      return bRes;
   }

   BOOL GetFile(int iIndex, CZipFile* pFile) const
   {
      _ASSERTE(IsOpen());
      _ASSERTE(pFile);
      _ASSERTE(iIndex>=0 && iIndex<m_Header.nDirEntries);
      if( m_hFile == INVALID_HANDLE_VALUE ) return FALSE;
      if( iIndex < 0 || iIndex >= m_Header.nDirEntries ) return FALSE;
      
      ZipLocalHeader hdr;
      ::SetFilePointer(m_hFile, m_Files[iIndex]->hdrOffset, NULL, FILE_BEGIN);
      DWORD dwRead;
      ::ReadFile(m_hFile, &hdr, sizeof(hdr), &dwRead, NULL);
      if( dwRead != sizeof(hdr) ) return FALSE;
      if( hdr.sig != LOCAL_SIGNATURE ) return FALSE;
      ::SetFilePointer(m_hFile, hdr.fnameLen+hdr.xtraLen, NULL, FILE_CURRENT);

      // Prepare decompression file of file
      LPBYTE pData = NULL;
      ATLTRY( pData = new BYTE[hdr.cSize] );
      _ASSERTE(pData);
      if( pData == NULL ) return FALSE;

      ::ReadFile(m_hFile, pData, hdr.cSize, &dwRead, NULL);
      if( dwRead != hdr.cSize ) {
         ATLTRY( delete [] pData );
         return FALSE;
      }

      // Decrypt option
      DWORD dwSize = hdr.cSize;
      if( (hdr.flag & 1) != 0 ) {
         if( ::lstrlenA(m_szPassword) == 0 ) return FALSE;
         if( !pFile->_DecryptFile(m_szPassword, pData, dwSize, hdr.crc32) ) return FALSE;
      }

      // Decompress file
      switch( hdr.compression ) {
      case LOCAL_COMP_STORE:
         _ASSERTE(hdr.cSize==hdr.ucSize);
         break;
      case LOCAL_COMP_DEFLAT: 
         {
            LPBYTE pTarget = NULL;
            ATLTRY( pTarget = new BYTE[hdr.ucSize] );
            _ASSERTE(pTarget);
            if( pTarget == NULL ) return FALSE;

            z_stream stream = { 0 };
            stream.next_in = (Bytef*) pData;
            stream.avail_in = (uInt) dwSize;
            stream.next_out = (Bytef*) pTarget;
            stream.avail_out = hdr.ucSize;
            stream.zalloc = (alloc_func) NULL;
            stream.zfree = (free_func) NULL;
            // Perform inflation; wbits < 0 indicates no zlib header inside the data.
            int err = inflateInit2(&stream, -MAX_WBITS);
            if( err == Z_OK ) {
               err = inflate(&stream, Z_NO_FLUSH);
               if( err == Z_STREAM_END) err = Z_OK;
               inflateEnd(&stream);
            }
            ATLTRY( delete [] pData );
            if( err != Z_OK ) {
               ATLTRY( delete [] pTarget );
               return FALSE;
            }
            pData = pTarget;
         }
         break;
      default:
         _ASSERTE(false); // unsupported compression scheme
         return FALSE;
      }

      // The memory we allocated is passed to the file, which
      // takes ownership of it.
      pFile->_Initialize(pData, hdr.ucSize);
      return TRUE;
   }

   // FindFile API

   HANDLE FindFirstFile(LPCTSTR pstrFileName, LPZIP_FIND_DATA lpFindFileData) const
   {
      _ASSERTE(IsOpen());
      _ASSERTE(!::IsBadStringPtr(pstrFileName,MAX_PATH));
      _ASSERTE(!::IsBadWritePtr(lpFindFileData, sizeof(ZIP_FIND_DATA)));

      ::ZeroMemory(lpFindFileData, sizeof(ZIP_FIND_DATA));

      FindFileHandle* pFF = NULL;
      ATLTRY( pFF = new FindFileHandle );
      if( pFF == NULL ) return INVALID_HANDLE_VALUE;
      ::lstrcpy(pFF->szSearch, pstrFileName);
      pFF->nPos = 0;

      BOOL bSuccess = FindNextFile( (HANDLE) pFF, lpFindFileData );
      if( !bSuccess ) {
         ATLTRY( delete pFF );
         return INVALID_HANDLE_VALUE;
      }
      else {
         return (HANDLE)pFF;
      }
   }

   BOOL FindNextFile(HANDLE hFindFile, LPZIP_FIND_DATA lpFindFileData) const
   {
      _ASSERTE(IsOpen());
      if( m_hFile == INVALID_HANDLE_VALUE ) return FALSE;
      if( hFindFile == INVALID_HANDLE_VALUE || hFindFile == NULL ) return FALSE;
      
      FindFileHandle* pFF = reinterpret_cast<FindFileHandle*>(hFindFile);
      while( true ) {
         if( pFF->nPos >= m_Header.nDirEntries ) return FALSE;
         // Extract filename and match with pattern
         const ZipDirFileHeader* fh = m_Files[pFF->nPos];
         TCHAR szFile[MAX_PATH] = { 0 };
         ::OemToCharBuff(fh->GetName(), szFile, fh->fnameLen);
         if( ::PathMatchSpec(szFile, pFF->szSearch) != NULL ) {
            // Copy data to the ZIP_FIND_DATA structure
            lpFindFileData->nDirIndex = pFF->nPos;
            ::lstrcpy( lpFindFileData->szFileName, szFile );
            lpFindFileData->szComment[0] = _T('\0'); // unsupported right now
            lpFindFileData->nFileSizeCompressed = fh->cSize;
            lpFindFileData->nFileSizeUncompressed = fh->ucSize;
            ::DosDateTimeToFileTime(fh->modDate, fh->modTime, &lpFindFileData->ftCreationDate);
            // Figure out the file attributes
            DWORD& dwFlags = lpFindFileData->dwFlags = 0;
            if( (fh->flag & 1) != 0 ) dwFlags |= FILE_ATTRIBUTE_ENCRYPTED;
            if( (fh->flag & (2|4)) != 0 ) dwFlags |= FILE_ATTRIBUTE_COMPRESSED;
            if( (fh->flag & (16|32|64)) != 0 ) dwFlags |= FILE_ATTRIBUTE_OFFLINE; // unsupported compression used
            if( dwFlags == 0 ) dwFlags = FILE_ATTRIBUTE_NORMAL;
            // Ready for next entry...
            pFF->nPos++;
            return TRUE;
         }
         pFF->nPos++;
      }
      return FALSE;
   }

   BOOL FindClose(HANDLE hFindFile) const
   {
      if( hFindFile == INVALID_HANDLE_VALUE || hFindFile == NULL ) return FALSE;
      FindFileHandle* pFF = reinterpret_cast<FindFileHandle*>(hFindFile);
      ATLTRY( delete pFF );
      return TRUE;
   }
};


#endif // !defined(AFX_ZIPARCHIVE_H__20010602_3EE9_91B0_80F5_0080AD509054__INCLUDED_)
