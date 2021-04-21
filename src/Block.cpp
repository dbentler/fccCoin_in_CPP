#include "Block.h"

Block::Block(const int& index, const int& proofNum, const std::string& prevHash, const std::vector<std::string>& data, const double& timeStamp){
    blockIndex = index;
    blockProofNum = proofNum;
    blockPrevHash = prevHash;
    blockData = data;
    blockTimeStamp = timeStamp;
}

Block::~Block(){};

std::string Block::calculateHash(){
    //TO DO, Find a way to hash all of this information eventually.
    std::string blockAsString;
    blockAsString = std::to_string(blockIndex) + std::to_string(blockProofNum) + blockPrevHash;
    return blockAsString;
}

void Block::viewBlock(){
    printf("{\n Block Index: %d \n Block Proof: %d \n Previous Hash: %s \n Block Time Stamp: %f \n}", blockIndex, blockProofNum,
    blockPrevHash.c_str(), blockTimeStamp);
}