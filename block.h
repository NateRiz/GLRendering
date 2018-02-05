#ifndef BLOCK_H
#define BLOCK_H

enum BlockType{
    BlockType_Default = 0,
    BlockType_Grass,
    BlockType_Dirt,
    BlockType_Stone
};


class Block
{
public:
    Block(){};

    static const int BLOCK_SIZE = 1;
private:
    BlockType mBlockType;


};

#endif // BLOCK_H
