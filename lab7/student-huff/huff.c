#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "huff.h"

// create a new huffcoder structure
struct huffcoder *huffcoder_new()
{
  struct huffcoder *theCoder = malloc(sizeof(struct huffcoder));
  return theCoder;
}

// count the frequency of characters in a file; set chars with zero
// frequency to one
void huffcoder_count(struct huffcoder *this, char *filename)
{
  unsigned char c; // we need the character to be
                   // unsigned to use it as an index
  FILE *file;

  file = fopen(filename, "r");
  assert(file != NULL);
  c = fgetc(file); // attempt to read a byte
  while (!feof(file))
  {                   //While there are bytes to read
    this->freqs[c]++; //increment the counter of the character found
    c = fgetc(file);  //get the next character
  }
  fclose(file);
}

//create a new huffchar (allocate memory)
struct huffchar *huffchar_new()
{
  struct huffchar *theChar = malloc(sizeof(struct huffchar));
  return theChar;
}

//swap the items in an array
void swapChars(struct huffchar *charArr[], int locA, int locB)
{
  struct huffchar *tmpA = huffchar_new();
  tmpA = charArr[locA];
  charArr[locA] = charArr[locB];
  charArr[locB] = tmpA;
}

//get the smalles number in the array and move it to the start
void sortOne(struct huffchar *charArr[], int start, int max)
{
  for (int i = start + 1; i < max; i++)
  {
    if ((charArr[start]->freq > charArr[i]->freq) ||
        (charArr[start]->freq == charArr[i]->freq && charArr[start]->seqno > charArr[i]->seqno))
    {
      swapChars(charArr, i, start); //if the current character is smaller than the current smallest -> swap
    }
  }
}

//move the two smallest characters to the front
void sortList(struct huffchar *charArr[], int max)
{
  sortOne(charArr, 0, max); //get the first character
  sortOne(charArr, 1, max); //get the second character
}

//combine two huffman characters to one
struct huffchar *combine_huffs(struct huffchar *huffL, struct huffchar *huffR, int seqNum)
{
  struct huffchar *theChar = huffchar_new();
  theChar->freq = (huffL->freq + huffR->freq);
  theChar->seqno = seqNum;
  theChar->is_compound = 1;
  theChar->u.compound.left = huffL;
  theChar->u.compound.right = huffR;
  return theChar;
}

// using the character frequencies build the tree of compound
// and simple characters that are used to compute the Huffman codes
void huffcoder_build_tree(struct huffcoder *this)
{
  struct huffchar *charArr[NUM_CHARS];
  //convert number array to huffchar array
  for (int i = 0; i < NUM_CHARS; i++)
  {
    struct huffchar *theChar = huffchar_new();
    theChar->u.c = i;
    theChar->freq = this->freqs[i];
    if (theChar->freq == 0)
      theChar->freq = 1;
    theChar->is_compound = 0;
    theChar->seqno = i;
    charArr[i] = theChar;
  }
  //Combine the two smallest huffchars until one is left
  for (int i = 0; i < NUM_CHARS; i++)
  {
    sortList(charArr, NUM_CHARS - i);
    charArr[0] = combine_huffs(charArr[0], charArr[1], NUM_CHARS + i);
    if (i < NUM_CHARS - 1)
      swapChars(charArr, 1, (NUM_CHARS - 1) - i);
  }
  this->tree = charArr[0];
}

// recursive function to convert the Huffman tree into a table of
// Huffman codes
void tree2table_recursive(struct huffcoder *this, struct huffchar *node,
                          int path, int depth)
{
  //recursively call this function until we get to a leaf
  if (node->is_compound == 1)
  {
    path <<= 1;
    tree2table_recursive(this, node->u.compound.left, path, depth + 1);
    path |= 1;
    tree2table_recursive(this, node->u.compound.right, path, depth + 1);
  }
  else
  {
    this->codes[node->u.c] = (long)path;
    this->code_lengths[node->u.c] = depth;
  }
}

// using the Huffman tree, build a table of the Huffman codes
// with the huffcoder object
void huffcoder_tree2table(struct huffcoder *this)
{
  tree2table_recursive(this, this->tree, 0, 0);
}
// print the Huffman codes for each character in order;
// you should not modify this function
void huffcoder_print_codes(struct huffcoder *this)
{
  int i, j;
  char buffer[NUM_CHARS];

  for (i = 0; i < NUM_CHARS; i++)
  {
    // put the code into a string
    assert(this->code_lengths[i] < NUM_CHARS);
    for (j = this->code_lengths[i] - 1; j >= 0; j--)
    {
      buffer[j] = ((this->codes[i] >> j) & 1) + '0';
    }
    // don't forget to add a zero to end of string
    buffer[this->code_lengths[i]] = '\0';

    // print the code
    printf("char: %d, freq: %d, code: %s\n", i, this->freqs[i], buffer);
    ;
  }
}

// encode the input file and write the encoding to the output file
void huffcoder_encode(struct huffcoder *this, char *input_filename,
                      char *output_filename)
{
  FILE * inputFile = fopen(input_filename,"r");
  FILE * outputFile = fopen(output_filename, "w");

  char theChar;
  while((theChar = getc(inputFile)) != EOF){

  }

}

// decode the input file and write the decoding to the output file
void huffcoder_decode(struct huffcoder *this, char *input_filename,
                      char *output_filename)
{
}
