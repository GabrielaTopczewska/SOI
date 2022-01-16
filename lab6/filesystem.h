#ifndef FS_H
#define FS_H

#include <iostream>
#include <string>
#include <stdio.h>
#define BLOCK_SIZE 2048
#define NAME_SIZE 256
extern int run;

struct superBlock{
    int magicNumber;
    unsigned int size;      // disc size
    int numFiles;           // num inodes(files)
    int numFreeBlocks;      // free data blocks
    int numBlocks;          // taken datablocks
    int offsetINode;        // offset to first inode
    int offsetFile;         // offset to first datablock
};

struct iNode{
    char name[NAME_SIZE];
    unsigned int size;
    int fileAddress;
};

struct dataBlock{
    char data[BLOCK_SIZE];
};

void interface();

int createVDisc(unsigned int size);
int deleteVDisc();

int downloadFile(std::string name);
int uploadFile(std::string dName);
int deleteFile(std::string name);

int open(std::string name);
int close(std::string name);
void ls();
void listAll();

extern bool *bitmap;
extern void *virtualDisc;
extern superBlock *super;
extern iNode *inodes;
extern dataBlock *datablocks;
#endif
