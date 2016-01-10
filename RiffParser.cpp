#include <iostream>
#include <fstream>
#include <stdio.h>

#define _FOURCHAR(a, b, c, d) ((((((a << 8) + b) << 8) + c) << 8) + d)

using namespace std;

// Big-endian!!
unsigned int GetNextFourToInt(char * in)
{
   unsigned int returnValue;

   returnValue = (unsigned int) ((*in) << 24);
   returnValue |= (*(in+1)) << 16;
   returnValue |= (*(in+2)) << 8;
   returnValue |= (*(in+3));

   return returnValue;
}

int main(int argc, char * argv[])
{
   FILE * inputFile;
   char * inputFileLocation = (char *) "../iffdigest/trunk/wav/something.wav";

   ifstream inFileStream;
   
   /* Open input filestream */
   inFileStream.open(inputFileLocation, ios::in);
   if (inFileStream.good()) {
      printf("[status] Input file stream successfully opened.\n");
   } else {
      printf("[error ] Input file stream was not successfully opened.\n");
      return EXIT_FAILURE;
   }

   /* Get the file size. */
   filebuf * rdBuf   = inFileStream.rdbuf();
   size_t   size     = (*rdBuf).pubseekoff(0, inFileStream.end, inFileStream.in);
   cout << "File is " << size << " bytes.\n";

   /* Begin to Parse. */

   // NTP : need to 'seek' the beginning position of an istream
   inFileStream.seekg(0, inFileStream.beg);
      /* Get a char pointer to the buffered file data */
   char * charBuf; // ntp: ned to allocate this before fsteram.read()
   charBuf = new char[size];
   inFileStream.read(charBuf, size);

      /* Check the status of the stream, after the read() */
   if (inFileStream) {
      cout << "[status] ifstream.read(): All characters read successfully.\n";
   } else {
      cout << "[error ] Error: only " << inFileStream.gcount() << " could be read.\n";
      inFileStream.close();
      return EXIT_FAILURE;
   }

      /* With the char pointer, locate the 'LIST' or 'RIFF' */
#ifdef EX1
   cout << "size_t size, not casted: " << size << "\n";
   cout << "(unsigned int) size    : " << ((unsigned int) size) << "\n";
   cout << "(int) size             : " << ((int) size) << "\n";
#endif

   unsigned int nextFourRead;
   unsigned int listValue = _FOURCHAR('L', 'I', 'S', 'T');

   for (int filepos = 0; filepos < size; filepos++) {

      nextFourRead = GetNextFourToInt((&charBuf[filepos]));

      if (nextFourRead == listValue) {
         cout << "Found a 'LIST'!\n";
         return EXIT_SUCCESS;
      }
   }

   cout << "'LIST' was not found...\n";


   /* Close the file stream and return successfully. */
   inFileStream.close();
   return EXIT_SUCCESS;
}
