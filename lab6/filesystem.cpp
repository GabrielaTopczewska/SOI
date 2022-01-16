#include <unistd.h>
#include <cstring>
#include "filesystem.h"
#include "math.h"
int run = 1;

void *virtualDisc;
superBlock *super;
// iNode *inodes;
// dataBlock *dataBlocks;

using namespace std;

void interface(){
    string name;
    int result, size;
    cout << "File system started. Choose action." << endl;
    deleteVDisc();

    while(run){
        cout << "--------------------------------------------" << endl;
        cout << "$ 1 - create virtual disc" << endl;
        cout << "$ 2 - delete virtual disc" << endl;
        cout << "$ 3 - ls" << endl;
        cout << "$ 4 - upload file" << endl;
        cout << "$ 5 - download file" << endl;
        cout << "$ 6 - delete file" << endl;
        cout << "$ 7 - listAll" << endl;
        cout << "$ q - exit file system" << endl;
        cout << "$ ";
        switch(getchar())
        {
            case '1':
                while(getchar() != '\n');
                cout << "Enter the disc size (number of blocks): ";
                scanf("%d", &size);
                result = createVDisc(size);
                if(result == 0) cout << "Disc created." << endl;
                else cout << "Error occured." << endl;

                break;

            case '2':
                while(getchar() != '\n');
                result = deleteVDisc();
                if(result == 0) cout << "Disc deleted." << endl;
                else cout << "Error occured." << endl;
                break;

            case '3':
                while(getchar() != '\n');
                ls();
                break;
            case '4':
                while(getchar() != '\n');
                cout << "File name to upload: ";
                getline(cin, name);
                result = uploadFile(name);
                if(result == 0) cout << "File " << name << " uploaded." << endl;
                else cout << "Error occured." << endl;
                break;
            case '5':
                while(getchar() != '\n');
                cout << "File name to download: ";
                getline(cin, name);
                downloadFile(name);
                cout << "File " << name << " downloaded." << endl;
                break;
            case '6':
                while(getchar() != '\n');
                if(super->numFiles <= 0) cout << "No files found." << endl;
                else{
                    cout << "Choose file:" << endl;
                    for (int i=0; i < super->numFiles; i++){
                        // printf("File %d: %s\n", i + 1, inodes[i].name);
                    }
                    getline(cin, name);
                    while(getchar() != '\n');
                    deleteFile(name);
                }
                break;
            case '7':
                while(getchar() != '\n');
                listAll();
                break;
            case 'q':
                while(getchar() != '\n');
                run = 0;
                break;

            default:
                while(getchar() != '\n');
                cout << "Invalid choice." << endl;
                break;
        }
    }
}

int createVDisc(unsigned int discSize){

    // int discSize = sizeof(superBlock) + sizeof(iNode)*size + sizeof(dataBlock)*size;
    virtualDisc = malloc(discSize);

    // inodes = (iNode*) malloc(sizeof(iNode)*size);
    // dataBlocks = (dataBlock*) malloc(sizeof(dataBlock)*size);


    // for(int i = 0; i<size; i++)
    //     bitmap[i] = false;

    super = (superBlock*) virtualDisc;
    super->magicNumber = 5;
    super->size = discSize;
    super->numFiles = 0;
    super->numFreeBlocks = (discSize - sizeof(superBlock) - sizeof(iNode))/sizeof(dataBlock) ;
    // super->numBlocks = discSize;
    super->offsetINode = sizeof(superBlock);
    super->offsetFile = sizeof(superBlock);
    // super->offsetALast = sizeof(superBlock);

    // printf("%d = %d + %d + %d \n", super->size, size*BLOCK_SIZE, (int)sizeof(iNode)*size, (int) sizeof(superBlock));
    FILE *disc = fopen("disc", "wb+");
    if (fwrite(super, sizeof(superBlock), 1, disc) != 1){
        fclose(disc);
        return 1;
    }
    else{
        fclose(disc);
        return 0;
    }
}

int deleteVDisc(){

    if(remove("disc") != 0) return 1;

    // free(inodes);
    free(virtualDisc);
    // free(dataBlocks);
    return 0;
}

int downloadFile(string name){
    return 0;
}

int uploadFile(string name){
    unsigned int fSize;
    char data;

    FILE *file = fopen(name.c_str(), "r+b");
    FILE *disc = fopen("disc", "w+b");

    if(file == NULL){
        cout << "No such file." << endl;
        return 1;
    }
    if(disc == NULL){
        cout << "No such disc." << endl;
        return 1;
    }

    fseek(file, 0L, SEEK_END);
    fSize = ftell(file);
    if(fSize > super->numFreeBlocks*BLOCK_SIZE){
        cout << "There isn't enough space for the file.";
        return 1;
    }

    int blocks = (fSize/BLOCK_SIZE) + 1;

    iNode *inode = (iNode*) virtualDisc + sizeof(superBlock) + sizeof(iNode)*super->numFiles;
    strcpy(inode->name, name.c_str());
    inode->size = fSize;
    inode->fileAddress = sizeof(iNode)*super->numFiles + sizeof(dataBlock)*super->numBlocks;

    memmove(virtualDisc + super->offsetFile + sizeof(iNode), virtualDisc + super->offsetFile, super->numBlocks*sizeof(dataBlock));
    fseek(disc, super->offsetFile, SEEK_SET);
    fwrite(inode, sizeof(iNode), 1, disc);
    // super->offsetFile += sizeof(iNode);

    fseek(file, 0L, SEEK_SET);
    fseek(disc, 0L, SEEK_END);
    while(data != EOF){
        data = fgetc(file);
        fputc(data, disc);
    }


    super->numFiles++;
    super->numFreeBlocks -= blocks;
    super->numBlocks += blocks;
    super->offsetFile += sizeof(iNode);

    fclose(disc);
    fclose(file);

    return 0;
}

int deleteFile(string name){

    return 0;
}

void ls(){
    char *ptr;
    int *ptr2;
    FILE *disc = fopen("disc", "r+b");
    fseek(disc, super->offsetINode, SEEK_SET);

    for(int i=0; i<super->numFiles; i++)
    {
        fread(ptr, 256, 1, disc);
        cout << i+1 << ". " << ptr << endl;
        // fread(ptr2, 4, 1, disc);
        // cout << "File size: " << ptr2 << endl;
        // fread(ptr2, sizeof(int), 1, disc);
        // cout << "File begins at: " << ptr2 << endl;
    }
    fclose (disc);
}

void listAll(){
    int taken = sizeof(superBlock) + sizeof(iNode)*super->numFiles + sizeof(dataBlock)*super->numBlocks;

    cout << "--------------------------------------------" << endl;
    cout << "Total disc space: " << super->size << endl;
    cout << "Number of files stored: " << super->numFiles << endl;
    cout << "Total disc space taken: " << taken << endl;
    cout << "Total disc space remaining: " << super->size - taken << endl;
    cout << "INodes starting with offset: " << super->offsetINode << endl;
    cout << "DataBlocks starting with offset: " << super->offsetFile << endl;
}