/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
extern const char* Background_png;
const int Background_pngSize = 23066;

extern const char* KNB02bi43_png;
const int KNB02bi43_pngSize = 20241;

extern const char* KNB02uni43_png;
const int KNB02uni43_pngSize = 19161;

// Number of elements in the namedResourceList and originalFileNames arrays.
const int namedResourceListSize = 3;

// Points to the start of a list of resource names.
extern const char* namedResourceList[];

// Points to the start of a list of resource filenames.
extern const char* originalFilenames[];

// If you provide the name of one of the binary resource variables above, this
// function will return the corresponding data and its size (or a null pointer
// if the name isn't found).
const char* getNamedResource(const char* resourceNameUTF8,
                             int& dataSizeInBytes);

// If you provide the name of one of the binary resource variables above, this
// function will return the corresponding original, non-mangled filename (or a
// null pointer if the name isn't found).
const char* getNamedResourceOriginalFilename(const char* resourceNameUTF8);
} // namespace BinaryData
